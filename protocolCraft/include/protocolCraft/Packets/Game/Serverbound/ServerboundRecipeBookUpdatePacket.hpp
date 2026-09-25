#if PROTOCOL_VERSION > 316 /* > 1.11.2 */ && PROTOCOL_VERSION < 737 /* < 1.16.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundRecipeBookUpdatePacket : public BasePacket<ServerboundRecipeBookUpdatePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Recipe Book Update";

        DEFINE_CONDITION(Purpose0, GetPurpose() == 0);
        DEFINE_CONDITION(Purpose1, GetPurpose() == 1);

        SERIALIZED_FIELD(Purpose, VarInt);
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        SERIALIZED_FIELD(Recipe, Internal::Conditioned<Identifier, &THIS::Purpose0>);
#else
        SERIALIZED_FIELD(Recipe, Internal::Conditioned<int, &THIS::Purpose0>);
#endif
        SERIALIZED_FIELD(GuiOpen, Internal::Conditioned<bool, &THIS::Purpose1>);
        SERIALIZED_FIELD(FilteringCraftable, Internal::Conditioned<bool, &THIS::Purpose1>);
#if PROTOCOL_VERSION > 358 /* > 1.12.2 */
        SERIALIZED_FIELD(FurnaceGuiOpen, Internal::Conditioned<bool, &THIS::Purpose1>);
        SERIALIZED_FIELD(FurnaceFilteringCraftable, Internal::Conditioned<bool, &THIS::Purpose1>);
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
        SERIALIZED_FIELD(BlastFurnaceGuiOpen, Internal::Conditioned<bool, &THIS::Purpose1>);
        SERIALIZED_FIELD(BlastFurnaceFilteringCraftable, Internal::Conditioned<bool, &THIS::Purpose1>);
        SERIALIZED_FIELD(SmokerGuiOpen, Internal::Conditioned<bool, &THIS::Purpose1>);
        SERIALIZED_FIELD(SmokerFilteringCraftable, Internal::Conditioned<bool, &THIS::Purpose1>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
