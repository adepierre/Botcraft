#pragma once

#include <string>

#include "botcraft/Game/Enums.hpp"

namespace Botcraft
{
    struct ItemProperties
    {
        int id;
#if PROTOCOL_VERSION < 347
        unsigned char damage_id;
#endif
        std::string name;
        unsigned char stack_size;
    };

    class Item
    {
    public:
        Item(const ItemProperties& props);

        const int GetId() const;
#if PROTOCOL_VERSION < 347
        const unsigned char GetDamageId() const;
#endif
        const std::string& GetName() const;
        const unsigned char GetStackSize() const;
        const ToolType GetToolType() const;
        const ToolMaterial GetToolMaterial() const;

    private:
        void LoadTypeAndMaterialFromName();

    private:
        int id;
        std::string name;
        unsigned char stack_size;
#if PROTOCOL_VERSION < 347
        unsigned char damage_id;
#endif
        ToolType tool_type;
        ToolMaterial tool_material;
    };
} // Botcraft
