#include "botcraft/AI/BaseNode.hpp"

#if __has_include(<cxxabi.h>)
#include <cxxabi.h>
#include <memory>
#define DEMANGLE_AVAILABLE
#endif

namespace Botcraft
{
    std::string Demangle(const std::string& name)
    {
#ifdef DEMANGLE_AVAILABLE
        int status = 0;
        std::unique_ptr<char, void(*)(void*)> result{
            abi::__cxa_demangle(name.c_str(), NULL, NULL, &status),
            std::free
        };

        const std::string demangled = status == 0 ? std::string(result.get()) : name;
#else
        const std::string& demangled = name;
#endif
        std::string output = demangled.substr(0, demangled.find('<'));
        size_t match_pos = output.find("::");
        if (match_pos != std::string::npos)
        {
            output = output.substr(match_pos + 2);
        }
        match_pos = output.find("class ");
        if (match_pos != std::string::npos)
        {
            output = output.substr(match_pos + 6);
        }

        return output;
    }

    BaseNode::BaseNode(const std::string& name_) : name(name_)
    {

    }

    BaseNode::~BaseNode()
    {

    }

    std::string BaseNode::GetFullDescriptor() const
    {
        return this->name.empty() ? GetClassName() : ("\"" + this->name + "\" (" + GetClassName() + ")");
    }

    const std::string& BaseNode::GetName() const
    {
        return name;
    }

    std::string BaseNode::GetClassName() const
    {
        return Demangle(typeid(*this).name());
    }
} // namespace Botcraft
