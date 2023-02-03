#if USE_IMGUI
#include "botcraft/Renderer/BehaviourRenderer.hpp"
#include "botcraft/AI/BaseNode.hpp"

#include <imgui_node_editor.h>

static constexpr float TREE_SPACING_VERTICAL = 50.0f;
static constexpr float TREE_SPACING_HORIZONTAL = 150.0f;
static constexpr float MIN_NODE_WIDTH = 200.0f;

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

        BehaviourRenderer::BehaviourRenderer() : context(nullptr), config(nullptr), active_node(nullptr)
        {

        }

        BehaviourRenderer::~BehaviourRenderer()
        {

        }

        void BehaviourRenderer::SetCurrentBehaviourTree(const BaseNode* root)
        {
            std::scoped_lock<std::mutex> lock(mutex);
            nodes = UnrollTreeStructure(root);
        }

        void BehaviourRenderer::Init()
        {
            std::scoped_lock<std::mutex> lock(mutex);
            config = std::make_unique<ax::NodeEditor::Config>();
            config->SettingsFile = nullptr;
            config->DragButtonIndex = 3;
            context = ax::NodeEditor::CreateEditor(config.get());
        }

        void BehaviourRenderer::Render() const
        {
            std::scoped_lock<std::mutex> lock(mutex);
            if (context == nullptr)
            {
                return;
            }

            ax::NodeEditor::SetCurrentEditor(context);

            ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_FlowDuration, 0.5f);
            ax::NodeEditor::PushStyleVar(ax::NodeEditor::StyleVar_SelectedNodeBorderWidth, 10.0f);
            ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_Flow, GetStatusColor(ImNodeStatus::Running));
            ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_FlowMarker, GetStatusColor(ImNodeStatus::Running));
            ax::NodeEditor::PushStyleColor(ax::NodeEditor::StyleColor_PinRect, ImColor(0,0,0,0));

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

            if (nodes.size() > 1 && nodes.back()->x == 0.0f && nodes.back()->y == 0.0f)
            {
                PlaceNodesBuchheim(nodes.front().get());
            }

            // Draw all links between nodes
            int current_link_id = 0;
            for (const std::unique_ptr<ImNode>& node : nodes)
            {
                for (size_t i = 0; i < node->out_attr_ids.size(); ++i)
                {
                    ax::NodeEditor::Link(current_link_id++, node->out_attr_ids[i], node->children[i]->in_attr_id, GetStatusColor(node->children[i]->status), 3.0f);
                    if (node->children[i]->status == ImNodeStatus::Running)
                    {
                        ax::NodeEditor::Flow(current_link_id - 1);
                    }
                }
            }

            ax::NodeEditor::End();

            ax::NodeEditor::PopStyleColor();
            ax::NodeEditor::PopStyleColor();
            ax::NodeEditor::PopStyleColor();
            ax::NodeEditor::PopStyleVar();
            ax::NodeEditor::PopStyleVar();

            ax::NodeEditor::SetCurrentEditor(nullptr);
        }

        void BehaviourRenderer::CleanUp()
        {
            std::scoped_lock<std::mutex> lock(mutex);
            ax::NodeEditor::DestroyEditor(context);
            context = nullptr;
            config.reset();
            nodes.clear();
        }

        void BehaviourRenderer::ResetBehaviourState()
        {
            std::scoped_lock<std::mutex> lock(mutex);
            for (const auto& node : nodes)
            {
                node->status = ImNodeStatus::Idle;
            }

            active_node = nodes[0].get();
        }

        void BehaviourRenderer::BehaviourStartTick()
        {
            std::scoped_lock<std::mutex> lock(mutex);
            if (active_node != nullptr)
            {
                active_node->status = ImNodeStatus::Running;
            }
        }

        void BehaviourRenderer::BehaviourEndTick(const bool b)
        {
            std::scoped_lock<std::mutex> lock(mutex);
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
            std::scoped_lock<std::mutex> lock(mutex);
            if (active_node != nullptr)
            {
                active_node = active_node->children[i];
            }
        }

        void BehaviourRenderer::RenderNode(const size_t index) const
        {
            ImNode* node = nodes[index].get();

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
                draw_list->AddCircleFilled(ImVec2(p.x, p.y - size.y + 2.0f), 4.0f, GetStatusColor(node->status), 8);

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

                ImVec2 size = ImGui::GetItemRectSize();
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 p = ImGui::GetCursorScreenPos();
                draw_list->AddCircleFilled(ImVec2(p.x + size.x, p.y - size.y + 2.0f), 4.0f, GetStatusColor(node->children[i]->status), 8);

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


        std::vector<std::unique_ptr<ImNode>> UnrollTreeStructure(const BaseNode* node, const int index)
        {
            std::vector<std::unique_ptr<ImNode>> output;

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
                for (int i = 0; i < real_node->children.size(); ++i)
                {
                    children.push_back(std::make_unique<TreePosNode>(real_node->children[i], this, depth + 1, i + 1));
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
    }
}
#endif
