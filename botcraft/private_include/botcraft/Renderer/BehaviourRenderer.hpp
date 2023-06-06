#pragma once

#include <any>
#include <string>

#if USE_IMGUI
#include <memory>
#include <vector>
#include <mutex>
#include <map>

namespace ax
{
    namespace NodeEditor
    {
        struct EditorContext;
        struct Config;
    }
}

namespace Botcraft
{
    class BaseNode;

    namespace Renderer
    {
        struct ImNode;

        class BehaviourRenderer
        {
        public:
            BehaviourRenderer();
            ~BehaviourRenderer();

            void Init();
            void RenderNodes();
            void RenderBlackboard();
            void CleanUp();

            void SetCurrentBehaviourTree(const BaseNode* root);
            void ResetBehaviourState();
            void BehaviourStartTick();
            void BehaviourEndTick(const bool b);
            void BehaviourTickChild(const size_t i);
            bool IsBehaviourPaused() const;

            void ResetBlackboard();
            void UpdateBlackboardValue(const std::string& key, const std::any& value);
            void RemoveBlackboardValue(const std::string& key);

        private:
            void RenderNode(const size_t index);
            void NavigateToActiveNode() const;

        private:
            ax::NodeEditor::EditorContext* context;
            std::unique_ptr<ax::NodeEditor::Config> config;
            std::vector<std::unique_ptr<ImNode>> nodes;
            mutable std::mutex nodes_mutex;

            ImNode* active_node;
            bool recompute_node_position;
            bool paused;
            bool step;

            std::map<std::string, std::string> blackboard;
            mutable std::mutex blackboard_mutex;
        };
    }
}
#else
namespace Botcraft
{
    class BaseNode;
    namespace Renderer
    {
        class BehaviourRenderer
        {
        public:
            void SetCurrentBehaviourTree(const BaseNode* root) {}
            void ResetBehaviourState() {}
            void BehaviourStartTick() {}
            void BehaviourEndTick(const bool b) {}
            void BehaviourTickChild(const size_t i) {}
            bool IsBehaviourPaused() const { return false; }

            void ResetBlackboard() {}
            void UpdateBlackboardValue(const std::string& key, const std::any& value) {}
            void RemoveBlackboardValue(const std::string& key) {}

        };
    }
}
#endif
