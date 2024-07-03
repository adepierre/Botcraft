#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundRecipeBookUpdatePacket : public BaseMessage<ServerboundRecipeBookUpdatePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Recipe Book Update";

        DECLARE_CONDITION(Purpose0, GetPurpose() == 0);
        DECLARE_CONDITION(Purpose1, GetPurpose() == 1);

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (Internal::Conditioned<VarInt, &THIS::Purpose0>, Internal::Conditioned<Identifier, &THIS::Purpose0>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>),
            (Purpose,                                        Recipe,                                             GuiOpen,                                      FilteringCraftable)
        );
#elif PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS(
            (Internal::Conditioned<VarInt, &THIS::Purpose0>, Internal::Conditioned<Identifier, &THIS::Purpose0>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>),
            (Purpose,                                        Recipe,                                             GuiOpen,                                      FilteringCraftable,                           FurnaceGuiOpen,                               FurnaceFilteringCraftable)
        );
#else
        DECLARE_FIELDS(
            (Internal::Conditioned<VarInt, &THIS::Purpose0>, Internal::Conditioned<Identifier, &THIS::Purpose0>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>, Internal::Conditioned<bool, &THIS::Purpose1>),
            (Purpose,                                        Recipe,                                             GuiOpen,                                      FilteringCraftable,                           FurnaceGuiOpen,                               FurnaceFilteringCraftable,                    BlastFurnaceGuiOpen,                          BlastFurnaceFilteringCraftable,               SmokerGuiOpen,                                SmokerFilteringCraftable)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Purpose);
        GETTER_SETTER(Recipe);
        GETTER_SETTER(GuiOpen);
        GETTER_SETTER(FilteringCraftable);
#if PROTOCOL_VERSION > 358 /* > 1.12.2 */
        GETTER_SETTER(FurnaceGuiOpen);
        GETTER_SETTER(FurnaceFilteringCraftable);
#endif
#if PROTOCOL_VERSION > 450 /* > 1.13.2 */
        GETTER_SETTER(BlastFurnaceGuiOpen);
        GETTER_SETTER(BlastFurnaceFilteringCraftable);
        GETTER_SETTER(SmokerGuiOpen);
        GETTER_SETTER(SmokerFilteringCraftable);
#endif
    };
} //ProtocolCraft
#endif
