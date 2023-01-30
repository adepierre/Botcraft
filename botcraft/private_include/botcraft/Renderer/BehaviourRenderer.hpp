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
            void Render() const;
            void CleanUp();

        private:
            void RenderNode(const size_t index) const;

        private:
            ax::NodeEditor::EditorContext* context;
            std::unique_ptr<ax::NodeEditor::Config> config;
            std::vector<std::unique_ptr<ImNode>> nodes;
            mutable std::mutex mutex;
        };
    }
}
#endif
