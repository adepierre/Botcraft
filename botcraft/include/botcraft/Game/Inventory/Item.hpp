#pragma once

#include <string>
#if PROTOCOL_VERSION < 347
#include <utility>
#endif

#include "botcraft/Game/Enums.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION < 347
    using ItemId = std::pair<int, unsigned char>;
#else
    using ItemId = int;
#endif

    struct ItemProperties
    {
        ItemId id;
        std::string name;
        unsigned char stack_size;
    };

    class Item
    {
    public:
        Item(const ItemProperties& props);

        ItemId GetId() const;
        const std::string& GetName() const;
        const unsigned char GetStackSize() const;
        const ToolType GetToolType() const;
        const ToolMaterial GetToolMaterial() const;

    private:
        void LoadTypeAndMaterialFromName();

    private:
        ItemId id;
        std::string name;
        unsigned char stack_size;
        ToolType tool_type;
        ToolMaterial tool_material;
    };
} // Botcraft

#if PROTOCOL_VERSION < 347
namespace std
{
    template<>
    struct hash<std::pair<int, unsigned char>>
    {
        size_t operator()(const std::pair<int, unsigned char>& p) const
        {
            const size_t hash1 = std::hash<int>{}(p.first);
            const size_t hash2 = std::hash<unsigned char>{}(p.second);

            return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
        }
    };
}
#endif
