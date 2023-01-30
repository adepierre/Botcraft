#pragma once

#include <string>

namespace Botcraft
{
    enum class BehaviourNodeType
    {
        Tree,
        Leaf,
        Composite,
        Decorator
    };

    class BaseNode
    {
    public:
        BaseNode(const std::string& name_);
        virtual ~BaseNode();

        // Helper functions not directly related to behaviour trees
        // but useful to work with the tree structure
        virtual BehaviourNodeType GetNodeType() const = 0;
        virtual size_t GetNumChildren() const = 0;
        virtual const BaseNode* GetChild(const size_t index) const = 0;

        std::string GetFullDescriptor() const;
        const std::string& GetName() const;
        std::string GetClassName() const;
    protected:
        const std::string name;
    };
}
