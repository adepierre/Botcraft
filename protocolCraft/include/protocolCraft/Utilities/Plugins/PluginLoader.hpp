#pragma once

#include <memory>

namespace ProtocolCraft
{
    class PluginObject;

    /// @brief Create an abstract PluginObject using a runtime loaded plugin (dll/so)
    /// @param identifier Identifier of the type we want to create (minecraft:register, minecraft:brand etc...)
    /// @return A shared_ptr of the plugin specified type, or nullptr if no known plugin exposes this identifier
    std::shared_ptr<PluginObject> CreateObjectFromPlugin(const char* identifier);
}
