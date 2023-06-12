#if USE_IMGUI
#include "botcraft/Renderer/BehaviourRenderer.hpp"
#include "botcraft/AI/BaseNode.hpp"

#include "botcraft/Utilities/StdAnyUtilities.hpp"
#include "botcraft/Utilities/StringUtilities.hpp"

#include <imgui_node_editor.h>

static constexpr float TREE_SPACING_VERTICAL = 50.0f;
static constexpr float TREE_SPACING_HORIZONTAL = 150.0f;
static constexpr float MIN_NODE_WIDTH = 200.0f;
static constexpr float PIN_RADIUS = 5.0f;
static constexpr float LINK_THICKNESS = 4.0f;

static constexpr double BLACKBOARD_HIGHLIGHT_DURATION = 0.5;
static const ImVec4 BLACKBOARD_HIGHLIGHT_COLOR = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

namespace Botcraft
{
    namespace Renderer
    {
        enum class ImNodeStatus
        {
            Idle,
            Success,
            Failure,
            Running
        };

        /// @brief A class to hold data to be drawn on ImNode context
        struct ImNode
        {
            const int id;
            const BehaviourNodeType type;
            const std::string name;
            const std::string classname;
            int in_attr_id = -1;
            ImNode* parent = nullptr;
            std::vector<int> out_attr_ids;
            std::vector<ImNode*> children;

            float width = 0.0f;
            float height = 0.0f;
            float x = 0.0f;
            float y = 0.0f;

            ImNodeStatus status = ImNodeStatus::Idle;
            bool visible = true;

            ImNode(const int id_, const BehaviourNodeType t,
                const std::string& name_, const std::string& classname_) :
                id(id_), type(t), name(name_), classname(classname_) {}
        };

        /// @brief Convert a tree to a vector of ImNode with proper data
        /// @param node Root node of the tree
        /// @param index Index to give to the next node/pin
        /// @return A vector of all the nodes
        std::vector<std::unique_ptr<ImNode>> UnrollTreeStructure(const BaseNode* node, const int index = 1);

        /// @brief Apply Buchheim & al. algorithm to position all nodes in the tree
        /// (position is directly set inside the nodes)
        /// Christoph Buchheim, Michael Jünger, and Sebastian Leipert, "Improving Walker’s algorithm to run in linear time", 2002
        void PlaceNodesBuchheim(ImNode* root);

        /// @brief Helper struct used in Buchheim algorithm
        struct TreePosNode;

        // Helper functions used in Buchheim algorithm
        void FirstWalk(TreePosNode* v);
        void SecondWalk(TreePosNode* v, const float m = 0.0f);
        TreePosNode* Apportion(TreePosNode* v, TreePosNode* default_ancestor);
        TreePosNode* Ancestor(TreePosNode* vim, TreePosNode* v, TreePosNode* default_ancestor);
        void ExecuteShifts(TreePosNode* v);
        void MoveSubtree(TreePosNode* wm, TreePosNode* wp, const float shift);
        void GetMaxWidthPerDepthLevel(TreePosNode* node, std::vector<float>& max_width_depth);
        void SetRealNodePos(TreePosNode* node, std::vector<float>& max_width_depth);
        ImColor GetNodeColor(const BehaviourNodeType type);
        ImColor GetStatusColor(const ImNodeStatus s);
        void ToggleNodeVisibility(ImNode* node, const bool b);

        BehaviourRenderer::BehaviourRenderer() :
            context(nullptr), config(nullptr), active_node(nullptr),
            recompute_node_position(false), paused(false), step(false)
        {

        }

        BehaviourRenderer::~BehaviourRenderer()
        {

        }

        void BehaviourRenderer::Init()
        {
            {
                std::scoped_lock<std::mutex> lock(nodes_mutex);
                config = std::make_unique<ax::NodeEditor::Config>();
                config->SettingsFile = nullptr;
                config->DragButtonIndex = 3;
                context = ax::NodeEditor::CreateEditor(config.get());
            }

            // Reset blackboard is already thread safe
            {
                ResetBlackboard();
            }
        }

        void BehaviourRenderer::RenderNodes()
        {
            std::scoped_lock<std::mutex> lock(nodes_mutex);
            if (context == nullptr)
            {
                return;
            }

            ax::NodeEditor::SetCurrentEditor(context);

            if (paused)
            {
                if (ImGui::ArrowButton("Play button", ImGuiDir_Right))
                {
                    paused = false;
                }
            }
            else
            {
                if (ImGui::Button("##Pause button", ImVec2(ImGui::GetFrameHeight(), ImGui::GetFrameHeight())))
                {
                    paused = true;
                }
                // Draw pause icon (two rects) on button
                const ImVec2 button_min_rect = ImGui::GetItemRectMin();
                const ImVec2 button_size = ImGui::GetItemRectSize();

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                draw_list->AddRectFilled(
                    ImVec2(button_min_rect.x + 0.2f * button_size.x, button_min_rect.y + 0.1f * button_size.y),
                    ImVec2(button_min_rect.x + 0.4f * button_size.x, button_min_rect.y + 0.9f * button_size.y),
                    ImGui::GetColorU32(ImGuiCol_Text)
                );
                draw_list->AddRectFilled(
                    ImVec2(button_min_rect.x + 0.6f * button_size.x, button_min_rect.y + 0.1f * button_size.y),
                    ImVec2(button_min_rect.x + 0.8f * button_size.x, button_min_rect.y + 0.9f * button_size.y),
                    ImGui::GetColorU32(ImGuiCol_Text)
                );
            }
            const bool disabled = !paused;
            if (disabled)
            {
                ImGui::BeginDisabled();
            }
            ImGui::SameLine();
            if (ImGui::Button("##Step button", ImVec2(ImGui::GetFrameHeight(), ImGui::GetFrameHeight())))
            {
                paused = false;
                step = true;
            }
            // Draw step icon (rect + triangle) on button
            const ImVec2 button_min_rect = ImGui::GetItemRectMin();
            const ImVec2 button_size = ImGui::GetItemRectSize();
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            draw_list->AddRectFilled(
                ImVec2(button_min_rect.x + 0.15f * button_size.x, button_min_rect.y + 0.2f * button_size.y),
                ImVec2(button_min_rect.x + 0.3f * button_size.x, button_min_rect.y + 0.8f * button_size.y),
                ImGui::GetColorU32(ImGuiCol_Text)
            );

            const ImVec2 triangle_center = ImVec2(button_min_rect.x + 0.7f * button_size.x, button_min_rect.y + 0.5f * button_size.y);

            draw_list->AddTriangleFilled(
                ImVec2(triangle_center.x + 0.205f * button_size.x, triangle_center.y),
                ImVec2(triangle_center.x - 0.205f * button_size.x, triangle_center.y + 0.237f * button_size.y),
                ImVec2(triangle_center.x - 0.205f * button_size.x, triangle_center.y - 0.237f * button_size.y),
                ImGui::GetColorU32(ImGuiCol_Text)
            );
            if (disabled)
            {
                ImGui::EndDisabled();
            }

            ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_FlowDuration, 0.5f);
            ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_SelectedNodeBorderWidth, 10.0f);
            ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_Flow, GetStatusColor(ImNodeStatus::Running));
            ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_FlowMarker, GetStatusColor(ImNodeStatus::Running));
            ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_PinRect, ImColor(0, 0, 0, 0));
            ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_Bg, ImColor(60, 60, 70, 100));

            ax::NodeEditor::Begin("Behaviour");

            // Render all nodes
            for (size_t i = 0; i < nodes.size(); ++i)
            {
                RenderNode(i);

                // If thats the first time we render this node,
                // update its size (needed for placing it correctly)
                if (nodes[i]->width == 0.0f && nodes[i]->height == 0.0f)
                {
                    const ImVec2 size = ax::NodeEditor::GetNodeSize(nodes[i]->id);
                    nodes[i]->width = size.x;
                    nodes[i]->height = size.y;
                }
            }

            if (recompute_node_position)
            {
                if (nodes.size() > 1)
                {
                    PlaceNodesBuchheim(nodes.front().get());
                }
                recompute_node_position = false;
            }

            // Draw all links between nodes
            int current_link_id = 0;
            for (const std::unique_ptr<ImNode>& node : nodes)
            {
                for (size_t i = 0; i < node->out_attr_ids.size(); ++i)
                {
                    if (!node->children[i]->visible)
                    {
                        continue;
                    }
                    ax::NodeEditor::Link(current_link_id++, node->out_attr_ids[i], node->children[i]->in_attr_id, GetStatusColor(node->children[i]->status), LINK_THICKNESS);
                    if (node->children[i]->status == ImNodeStatus::Running)
                    {
                        ax::NodeEditor::Flow(current_link_id - 1);
                    }
                }
            }

            ax::NodeEditor::End();
            if (paused)
            {
                const ImVec2 node_editor_min_rect = ImGui::GetItemRectMin();
                const ImVec2 node_editor_max_rect = ImGui::GetItemRectMax();
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                draw_list->AddRect(
                    node_editor_min_rect,
                    node_editor_max_rect,
                    ImColor(5, 195, 221)
                );
            }

            ax::NodeEditor::PopStyleColor();
            ax::NodeEditor::PopStyleColor();
            ax::NodeEditor::PopStyleColor();
            ax::NodeEditor::PopStyleColor();
            ax::NodeEditor::PopStyleVar();
            ax::NodeEditor::PopStyleVar();

            if (paused && ImGui::IsKeyPressed(ImGuiKey_F5))
            {
                paused = false;
                step = false;
            }
            if (paused && ImGui::IsKeyPressed(ImGuiKey_F10))
            {
                paused = false;
                step = true;
            }

            ax::NodeEditor::SetCurrentEditor(nullptr);
        }

        ImVec4 ColorInterpolation(const ImVec4& a, const ImVec4& b, const float t)
        {
            if (t < 0.0f)
            {
                return a;
            }
            if (t >= 1.0f)
            {
                return b;
            }

            return ImVec4(
                (1 - t) * a.x + t * b.x,
                (1 - t) * a.y + t * b.y,
                (1 - t) * a.z + t * b.z,
                (1 - t) * a.w + t * b.w
            );
        }

        void RecursiveRenderBlackboardJsonNode(const std::string& name, ProtocolCraft::Json::Value& node)
        {
            ImGui::PushID(&node);
            if (node.contains("children"))
            {
                // If expanded, display children
                ImGui::PushStyleColor(ImGuiCol_Text, ColorInterpolation(ImGui::GetStyle().Colors[ImGuiCol_Text], BLACKBOARD_HIGHLIGHT_COLOR, node["timer"].get<double>() / BLACKBOARD_HIGHLIGHT_DURATION));
                const bool item_clicked = ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth);
                ImGui::PopStyleColor();
                if (item_clicked)
                {
                    ProtocolCraft::Json::Object& children = node["children"].get_object();
                    for (auto& [k, v] : children)
                    {
                        RecursiveRenderBlackboardJsonNode(k, v);
                    }
                    ImGui::TreePop();
                }
            }
            else
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ColorInterpolation(ImGui::GetStyle().Colors[ImGuiCol_Text], BLACKBOARD_HIGHLIGHT_COLOR, node["timer"].get<double>() / BLACKBOARD_HIGHLIGHT_DURATION));
                if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth))
                {
                    if (ImGui::TreeNodeEx(node["content"].get_string().c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanFullWidth))
                    {
                        // Do something when value is clicked?
                    }
                    ImGui::TreePop();
                }
                ImGui::PopStyleColor();
            }
            ImGui::PopID();
        }

        void RecursiveUpdateTimerBlackboardJsonNode(ProtocolCraft::Json::Value& node)
        {
            node["timer"] = std::max(0.0, node["timer"].get<double>() - ImGui::GetIO().DeltaTime);
            if (node.contains("children"))
            {
                ProtocolCraft::Json::Object& children = node["children"].get_object();
                for (auto& [_, v] : children)
                {
                    RecursiveUpdateTimerBlackboardJsonNode(v);
                }
            }
        }

        void BehaviourRenderer::RenderBlackboard()
        {
            std::scoped_lock<std::mutex> lock(blackboard_mutex);
            RecursiveRenderBlackboardJsonNode("Blackboard", blackboard);
            RecursiveUpdateTimerBlackboardJsonNode(blackboard);
        }

        void BehaviourRenderer::CleanUp()
        {
            {
                std::scoped_lock<std::mutex> lock(nodes_mutex);
                ax::NodeEditor::DestroyEditor(context);
                context = nullptr;
                config.reset();
                nodes.clear();
                active_node = nullptr;
                recompute_node_position = true;
                paused = false;
                step = false;
            }

            ResetBlackboard();
        }

        void BehaviourRenderer::SetCurrentBehaviourTree(const BaseNode* root)
        {
            std::scoped_lock<std::mutex> lock(nodes_mutex);
            nodes = UnrollTreeStructure(root);
            recompute_node_position = true;
        }

        void BehaviourRenderer::ResetBehaviourState()
        {
            std::scoped_lock<std::mutex> lock(nodes_mutex);
            for (const auto& node : nodes)
            {
                node->status = ImNodeStatus::Idle;
            }

            active_node = nodes[0].get();
        }

        void BehaviourRenderer::BehaviourStartTick()
        {
            std::scoped_lock<std::mutex> lock(nodes_mutex);
            if (active_node != nullptr)
            {
                active_node->status = ImNodeStatus::Running;

                if (context != nullptr && active_node->visible)
                {
                    ax::NodeEditor::SetCurrentEditor(context);
                    if (ax::NodeEditor::IsNodeSelected(active_node->id))
                    {
                        paused = true;
                        NavigateToActiveNode();
                    }
                    else if (paused || step)
                    {
                        NavigateToActiveNode();
                    }
                    ax::NodeEditor::SetCurrentEditor(nullptr);

                    if (step)
                    {
                        paused = true;
                        step = false;
                    }
                }
                // If current node is not visible, don't stop to it
                else
                {
                    step = paused || step;
                    paused = false;
                }
            }
        }

        void BehaviourRenderer::BehaviourEndTick(const bool b)
        {
            std::scoped_lock<std::mutex> lock(nodes_mutex);
            if (active_node != nullptr)
            {
                active_node->status = b ? ImNodeStatus::Success : ImNodeStatus::Failure;
                if (active_node->parent != nullptr)
                {
                    active_node = active_node->parent;
                }
            }
        }

        void BehaviourRenderer::BehaviourTickChild(const size_t i)
        {
            std::scoped_lock<std::mutex> lock(nodes_mutex);
            if (active_node != nullptr)
            {
                active_node = active_node->children[i];
            }
        }

        bool BehaviourRenderer::IsBehaviourPaused() const
        {
            std::scoped_lock<std::mutex> lock(nodes_mutex);
            return paused;
        }

        void BehaviourRenderer::RenderNode(const size_t index)
        {
            ImNode* node = nodes[index].get();

            if (!node->visible)
            {
                return;
            }

            const ImVec2 mouse_pos = ImGui::GetMousePos();
            const bool mouse_left_click = ImGui::IsMouseClicked(ImGuiMouseButton_Left);

            ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar::StyleVar_NodePadding, ImVec4(0, 4, 0, 8));
            ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar::StyleVar_NodeRounding, 4.0f);
            ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar::StyleVar_NodeBorderWidth, 0.0f);

            ax::NodeEditor::BeginNode(node->id);

            // Header
            ImGui::BeginGroup();
            ImGui::Dummy(ImVec2(1, 0));
            ImGui::SameLine();
            ImGui::TextUnformatted(node->name.c_str());
            ImGui::SameLine();
            ImGui::Dummy(ImVec2(1, 0));
            ImGui::Dummy(ImVec2(0, ax::NodeEditor::GetStyle().NodePadding.y));
            ImGui::EndGroup();
            const float title_bar_max_y = ImGui::GetItemRectMax().y;
            const float title_bar_width = ImGui::GetItemRectSize().x;

            // In Pin
            ImGui::BeginGroup();
            if (node->in_attr_id != -1)
            {
                ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PivotAlignment, ImVec2(0.0f, 0.5f));
                ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PivotSize, ImVec2(0, 0));
                ax::NodeEditor::BeginPin(node->in_attr_id, ax::NodeEditor::PinKind::Input);

                ImGui::Dummy(ImVec2(1, ImGui::GetTextLineHeight()));

                const ImVec2 size = ImGui::GetItemRectSize();
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                const ImVec2 p = ImGui::GetCursorScreenPos();
                draw_list->AddCircleFilled(ImVec2(p.x, p.y - size.y + 0.5f * PIN_RADIUS), PIN_RADIUS, GetStatusColor(node->status), 8);

                ax::NodeEditor::EndPin();
                ax::NodeEditor::PopStyleVar();
                ax::NodeEditor::PopStyleVar();
            }
            ImGui::EndGroup();
            float pins_width = ImGui::GetItemRectSize().x;

            ImGui::SameLine();
            ImGui::TextUnformatted(node->classname.c_str());
            ImGui::SameLine();
            pins_width += ImGui::GetItemRectSize().x;


            ImGui::BeginGroup();
            for (int i = 0; i < node->out_attr_ids.size(); ++i)
            {
                ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PivotAlignment, ImVec2(1.0f, 0.5f));
                ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_PivotSize, ImVec2(0, 0));
                ax::NodeEditor::BeginPin(node->out_attr_ids[i], ax::NodeEditor::PinKind::Output);

                ImGui::Dummy(ImVec2(std::max(1.0f, std::max(MIN_NODE_WIDTH - pins_width, title_bar_width - pins_width)), ImGui::GetTextLineHeight()));
                const ImVec2 size = ImGui::GetItemRectSize();

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 p = ImGui::GetCursorScreenPos();
                const ImVec2 circle_center(p.x + size.x, p.y - size.y + 0.5f * PIN_RADIUS);
                // If click in the pin, then toggle on/off the visibility of this child
                if (mouse_left_click &&
                    (
                        (mouse_pos.x - circle_center.x) * (mouse_pos.x - circle_center.x) +
                        (mouse_pos.y - circle_center.y) * (mouse_pos.y - circle_center.y)
                    ) < PIN_RADIUS * PIN_RADIUS)
                {
                    ToggleNodeVisibility(node->children[i], !node->children[i]->visible);
                    recompute_node_position = true;
                }

                if (node->children[i]->visible)
                {
                    draw_list->AddCircleFilled(circle_center, PIN_RADIUS, GetStatusColor(node->children[i]->status), 8);
                }
                else
                {
                    draw_list->AddCircle(circle_center, PIN_RADIUS, GetStatusColor(node->children[i]->status), 8);
                }

                ax::NodeEditor::EndPin();
                ax::NodeEditor::PopStyleVar();
                ax::NodeEditor::PopStyleVar();
            }
            if (node->out_attr_ids.size() == 0)
            {
                ImGui::Dummy(ImVec2(std::max(1.0f, std::max(MIN_NODE_WIDTH - pins_width, title_bar_width - pins_width)), ImGui::GetTextLineHeight()));
            }
            ImGui::EndGroup();

            ax::NodeEditor::EndNode();

            ImVec2 node_rect_min = ImGui::GetItemRectMin();
            ImVec2 node_rect_max = ImGui::GetItemRectMax();


            ImDrawList* draw_list = ax::NodeEditor::GetNodeBackgroundDrawList(node->id);
            //Draw header background
            draw_list->AddRectFilled(
                ImVec2(node_rect_min.x, node_rect_min.y),
                ImVec2(node_rect_max.x, title_bar_max_y),
                GetNodeColor(node->type),
                ax::NodeEditor::GetStyle().NodeRounding,
                ImDrawFlags_RoundCornersTop);

            // Custom node border
            draw_list->AddRect(
                node_rect_min,
                node_rect_max,
                GetStatusColor(node->status),
                ax::NodeEditor::GetStyle().NodeRounding,
                ImDrawFlags_RoundCornersAll,
                2.5f);


            ax::NodeEditor::PopStyleVar();
            ax::NodeEditor::PopStyleVar();
            ax::NodeEditor::PopStyleVar();

            ax::NodeEditor::SetNodePosition(node->id, ImVec2(node->x, node->y));
        }

        void BehaviourRenderer::NavigateToActiveNode() const
        {
            // Get all currently selected elements
            std::vector<ax::NodeEditor::NodeId> selected_nodes;
            std::vector<ax::NodeEditor::LinkId> selected_links;

            selected_nodes.resize(ax::NodeEditor::GetSelectedObjectCount());
            selected_links.resize(ax::NodeEditor::GetSelectedObjectCount());

            const int node_count = ax::NodeEditor::GetSelectedNodes(selected_nodes.data(), static_cast<int>(selected_nodes.size()));
            const int link_count = ax::NodeEditor::GetSelectedLinks(selected_links.data(), static_cast<int>(selected_links.size()));

            selected_nodes.resize(node_count);
            selected_links.resize(link_count);

            // Deselect everything
            for (const auto& nid : selected_nodes)
            {
                ax::NodeEditor::DeselectNode(nid);
            }
            for (const auto& lid : selected_links)
            {
                ax::NodeEditor::DeselectLink(lid);
            }

            // select active node
            ax::NodeEditor::SelectNode(active_node->id);
            ax::NodeEditor::NavigateToSelection();
            ax::NodeEditor::DeselectNode(active_node->id);

            // Reselect everything
            for (const auto& nid : selected_nodes)
            {
                ax::NodeEditor::SelectNode(nid, true);
            }
            for (const auto& lid : selected_links)
            {
                ax::NodeEditor::SelectLink(lid, true);
            }
        }


        std::vector<std::unique_ptr<ImNode>> UnrollTreeStructure(const BaseNode* node, const int index)
        {
            std::vector<std::unique_ptr<ImNode>> output;

            if (node == nullptr)
            {
                return output;
            }

            int current_index = index;

            output.push_back(std::make_unique<ImNode>(current_index++, node->GetNodeType(), node->GetName(), node->GetClassName()));

            // We are no longer processing the root, so add an input attr
            if (index != 1)
            {
                output.back()->in_attr_id = current_index++;
            }

            // We need to remember this node place because after the
            // first child it won't be located at output.back() anymore
            const size_t this_node_index = output.size() - 1;

            for (size_t i = 0; i < node->GetNumChildren(); ++i)
            {
                // Recursive call to get the tree representation of the child
                std::vector<std::unique_ptr<ImNode>> child_tree = UnrollTreeStructure(node->GetChild(i), current_index);

                // Update current indices
                current_index += static_cast<int>(child_tree.size());
                for (size_t j = 0; j < child_tree.size(); ++j)
                {
                    current_index += 1 + static_cast<int>(child_tree[j]->children.size());
                }

                // Create one out attribute for this child
                output[this_node_index]->out_attr_ids.push_back(current_index++);

                // Set parent/child relationship
                child_tree.front()->parent = output[this_node_index].get();
                output[this_node_index]->children.push_back(child_tree.front().get());

                // Copy the child tree node in this output
                output.insert(
                    output.end(),
                    std::make_move_iterator(child_tree.begin()),
                    std::make_move_iterator(child_tree.end())
                );
            }

            return output;
        }

        struct TreePosNode
        {
            TreePosNode(ImNode* real_node_, TreePosNode* parent_ = nullptr, int depth_ = 0, int sibling_order_number_ = 1)
            {
                prelim = 0.0f;
                depth = depth_;
                real_node = real_node_;
                ancestor = this;

                children.reserve(real_node->children.size());
                int sibling_index = 1;
                for (int i = 0; i < real_node->children.size(); ++i)
                {
                    if (real_node->children[i]->visible)
                    {
                        children.push_back(std::make_unique<TreePosNode>(real_node->children[i], this, depth + 1, sibling_index++));
                    }
                }
                parent = parent_;
                thread = nullptr;
                mod = 0.0f;
                change = 0;
                shift = 0;
                number = sibling_order_number_;
            }

            bool IsLeaf() const
            {
                return children.size() == 0;
            }

            TreePosNode* NextLeft() const
            {
                return IsLeaf() ? thread : children[0].get();
            }

            TreePosNode* NextRight() const
            {
                return IsLeaf() ? thread : children[children.size() - 1].get();
            }

            TreePosNode* LeftBrother() const
            {
                TreePosNode* output = nullptr;
                if (parent != nullptr)
                {
                    for (const auto& c : parent->children)
                    {
                        if (c.get() == this)
                        {
                            return output;
                        }
                        output = c.get();
                    }
                }
                return output;
            }

            bool IsLeftmostSibling() const
            {
                if (parent != nullptr && parent->children[0].get() == this)
                {
                    return true;
                }
                return false;
            }

            TreePosNode* GetLeftMostSibling() const
            {
                if (parent != nullptr && this != parent->children[0].get())
                {
                    return parent->children[0].get();
                }
                return nullptr;
            }

            float prelim;
            int depth;
            ImNode* real_node;
            TreePosNode* ancestor;
            std::vector<std::unique_ptr<TreePosNode>> children;
            TreePosNode* parent;
            TreePosNode* thread;
            float mod;
            float change;
            float shift;
            int number;
        };

        void PlaceNodesBuchheim(ImNode* root)
        {
            TreePosNode root_pos_node(root);

            FirstWalk(&root_pos_node);
            SecondWalk(&root_pos_node, -root_pos_node.prelim);

            std::vector<float> max_width_depth;
            GetMaxWidthPerDepthLevel(&root_pos_node, max_width_depth);

            SetRealNodePos(&root_pos_node, max_width_depth);
        }

        void FirstWalk(TreePosNode* v)
        {
            if (v->IsLeaf())
            {
                if (v->IsLeftmostSibling())
                {
                    v->prelim = 0.0f;
                }
                else
                {
                    v->prelim = v->LeftBrother()->prelim + v->LeftBrother()->real_node->height + TREE_SPACING_VERTICAL;
                }
            }
            else
            {
                TreePosNode* default_ancestor = v->children[0].get();
                for (const auto& w : v->children)
                {
                    FirstWalk(w.get());
                    default_ancestor = Apportion(w.get(), default_ancestor);
                }
                ExecuteShifts(v);

                const float midpoint = 0.5f * (
                    v->children[0].get()->prelim +
                    v->children[v->children.size() - 1].get()->prelim +
                    v->children[v->children.size() - 1].get()->real_node->height -
                    v->children[0].get()->real_node->height
                );
                if (TreePosNode* w = v->LeftBrother())
                {
                    v->prelim = w->prelim + w->real_node->height + TREE_SPACING_VERTICAL;
                    v->mod = v->prelim - midpoint;
                }
                else
                {
                    v->prelim = midpoint;
                }
            }
        }

        void SecondWalk(TreePosNode* v, const float m)
        {
            for (const auto& w : v->children)
            {
                SecondWalk(w.get(), m + v->mod);
            }
            v->prelim += m;
        }

        TreePosNode* Apportion(TreePosNode* v, TreePosNode* default_ancestor)
        {
            TreePosNode* output = default_ancestor;

            TreePosNode* w = v->LeftBrother();

            if (w == nullptr)
            {
                return output;
            }

            TreePosNode* vip = v;
            TreePosNode* vop = v;
            TreePosNode* vim = w;
            TreePosNode* vom = vip->GetLeftMostSibling();
            float sip = vip->mod;
            float sop = vop->mod;
            float sim = vim->mod;
            float som = vom->mod;

            while (vim->NextRight() != nullptr && vip->NextLeft() != nullptr)
            {
                vim = vim->NextRight();
                vip = vip->NextLeft();
                vom = vom->NextLeft();
                vop = vop->NextRight();
                vop->ancestor = v;
                const float shift = (vim->prelim + sim) - (vip->prelim + sip) + TREE_SPACING_VERTICAL + vim->real_node->height;
                if (shift > 0.0f)
                {
                    MoveSubtree(Ancestor(vim, v, default_ancestor), v, shift);
                    sip += shift;
                    sop += shift;
                }
                sim += vim->mod;
                sip += vip->mod;
                som += vom->mod;
                sop += vop->mod;
            }
            if (vim->NextRight() != nullptr && vop->NextRight() == nullptr)
            {
                vop->thread = vim->NextRight();
                vop->mod += sim - sop;
            }
            else
            {
                if (vip->NextLeft() != nullptr && vom->NextLeft() == nullptr)
                {
                    vom->thread = vip->NextLeft();
                    vom->mod += sip - som;
                }
                output = v;
            }
            return output;
        }

        TreePosNode* Ancestor(TreePosNode* vim, TreePosNode* v, TreePosNode* default_ancestor)
        {
            if (v->parent == nullptr)
            {
                return default_ancestor;
            }

            for (const auto& c : v->parent->children)
            {
                if (vim->ancestor == c.get())
                {
                    return vim->ancestor;
                }
            }
            return default_ancestor;
        }

        void ExecuteShifts(TreePosNode* v)
        {
            float shift = 0.0f;
            float change = 0.0f;
            for (int i = static_cast<int>(v->children.size()) - 1; i >= 0; --i)
            {
                TreePosNode* w = v->children[i].get();
                w->prelim += shift;
                w->mod += shift;
                change += w->change;
                shift += w->shift + change;
            }
        }

        void MoveSubtree(TreePosNode* wm, TreePosNode* wp, const float shift)
        {
            const int num_subtrees = wp->number - wm->number;
            const float shift_per_subtree = shift / num_subtrees;
            wp->change -= shift_per_subtree;
            wp->shift += shift;
            wm->change += shift_per_subtree;
            wp->prelim += shift;
            wp->mod += shift;
        }

        void GetMaxWidthPerDepthLevel(TreePosNode* node, std::vector<float>& max_width_depth)
        {
            if (max_width_depth.size() < node->depth + 1)
            {
                max_width_depth.resize(node->depth + 1, 0.0f);
            }

            max_width_depth[node->depth] = std::max(node->real_node->width, max_width_depth[node->depth]);

            for (const auto& c : node->children)
            {
                GetMaxWidthPerDepthLevel(c.get(), max_width_depth);
            }
        }

        void SetRealNodePos(TreePosNode* node, std::vector<float>& max_width_depth)
        {
            float depth_offset = 0.0f;
            for (size_t i = 0; i < node->depth; ++i)
            {
                depth_offset += max_width_depth[i] + TREE_SPACING_HORIZONTAL;
            }

            node->real_node->x = depth_offset + 0.5f * (max_width_depth[node->depth] - node->real_node->width);
            node->real_node->y = node->prelim;
            for (const auto& c : node->children)
            {
                SetRealNodePos(c.get(), max_width_depth);
            }
        }

        ImColor GetNodeColor(const BehaviourNodeType type)
        {
            switch (type)
            {
            case BehaviourNodeType::Tree:
                return ImColor(60, 40, 0);
            case BehaviourNodeType::Leaf:
                return ImColor(0, 50, 0);
            case BehaviourNodeType::Composite:
                return ImColor(40, 75, 125);
            case BehaviourNodeType::Decorator:
                return ImColor(100, 40, 125);
            }

            // Never reached
            return ImColor();
        }

        ImColor GetStatusColor(const ImNodeStatus s)
        {
            switch (s)
            {
            case ImNodeStatus::Idle:
                return ImColor(225, 225, 225);
            case ImNodeStatus::Success:
                return ImColor(25, 225, 25);
            case ImNodeStatus::Failure:
                return ImColor(225, 25, 25);
            case ImNodeStatus::Running:
                return ImColor(255, 255, 0);
            }

            // Never reached
            return ImColor();
        }

        void ToggleNodeVisibility(ImNode* node, const bool b)
        {
            node->visible = b;
            for (size_t i = 0; i < node->children.size(); ++i)
            {
                ToggleNodeVisibility(node->children[i], b);
            }
        }

        void BehaviourRenderer::ResetBlackboard()
        {
            std::scoped_lock<std::mutex> lock(blackboard_mutex);
            blackboard = { { "children", ProtocolCraft::Json::Object() }, { "timer", BLACKBOARD_HIGHLIGHT_DURATION } };
        }

        void BehaviourRenderer::UpdateBlackboardValue(const std::string& key, const std::any& value)
        {
            std::vector<std::string> splitted = SplitString(key, '.');
            // Empty key
            if (splitted.size() == 0)
            {
                return;
            }

            std::scoped_lock<std::mutex> lock(blackboard_mutex);

            bool changed = false;
            ProtocolCraft::Json::Value* current_json = &blackboard;
            for (size_t i = 0; i < splitted.size(); ++i)
            {
                // Create intermediary nodes
                if (!(*current_json)["children"].contains(splitted[i]))
                {
                    changed = true;
                    if (i < splitted.size() - 1)
                    {
                        (*current_json)["children"][splitted[i]] = { { "children", {} }, { "timer", 0.0 } };
                    }
                    else
                    {
                        (*current_json)["children"][splitted[i]] = { { "content", ""}, { "timer", 0.0 }};
                    }
                }
                current_json = &(*current_json)["children"][splitted[i]];
            }
            const std::string new_content = AnyParser::ToString(value);
            changed = changed || (*current_json)["content"].get_string() != new_content;

            if (changed)
            {
                // Go down all values to update timers
                current_json = &blackboard;
                for (size_t i = 0; i < splitted.size(); ++i)
                {
                    (*current_json)["timer"] = BLACKBOARD_HIGHLIGHT_DURATION;
                    current_json = &(*current_json)["children"][splitted[i]];
                }

                // Update leaf value
                (*current_json)["timer"] = BLACKBOARD_HIGHLIGHT_DURATION;
                (*current_json)["content"] = new_content;
            }
        }

        void BehaviourRenderer::RemoveBlackboardValue(const std::string& key)
        {
            std::vector<std::string> splitted = SplitString(key, '.');
            // Empty key
            if (splitted.size() == 0)
            {
                return;
            }

            std::scoped_lock<std::mutex> lock(blackboard_mutex);

            // From bottom to top, update the timer and remove the child
            // if no more siblings, mark parent for removal too
            bool remove = true;
            for (int depth = static_cast<int>(splitted.size()) - 1; depth > -1; --depth)
            {
                // Go down depth level
                ProtocolCraft::Json::Value* json_element = &blackboard;
                for (size_t i = 0; i < depth; ++i)
                {
                    json_element = &(*json_element)["children"][splitted[i]];
                }
                (*json_element)["timer"] = BLACKBOARD_HIGHLIGHT_DURATION;
                if (remove)
                {
                    (*json_element)["children"].get_object().erase(splitted[depth]);
                    remove = (*json_element)["children"].size() == 0;
                }
            }
        }
    }
}
#endif
