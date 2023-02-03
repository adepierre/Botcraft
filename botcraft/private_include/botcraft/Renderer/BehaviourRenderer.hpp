#if USE_IMGUI
#pragma once
#include <memory>
#include <vector>
#include <mutex>

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

            void SetCurrentBehaviourTree(const BaseNode* root);
            void Init();
            void Render();
            void CleanUp();

            void ResetBehaviourState();
            void BehaviourStartTick();
            void BehaviourEndTick(const bool b);
            void BehaviourTickChild(const size_t i);

        private:
            void RenderNode(const size_t index);

        private:
            ax::NodeEditor::EditorContext* context;
            std::unique_ptr<ax::NodeEditor::Config> config;
            std::vector<std::unique_ptr<ImNode>> nodes;
            mutable std::mutex mutex;

            ImNode* active_node;
            bool recompute_node_position;
        };
    }
}
#endif
