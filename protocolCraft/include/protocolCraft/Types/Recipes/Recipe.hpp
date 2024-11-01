#if PROTOCOL_VERSION > 347 /* > 1.12.2 */ && PROTOCOL_VERSION < 768 /* < 1.21.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <memory>
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include <string_view>
#endif

namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    enum class RecipeDataType
    {
        None = -1,
        CraftingShaped,
        CraftingShapeless,
        CraftingSpecialArmordye,
        CraftingSpecialBookcloning,
        CraftingSpecialMapcloning,
        CraftingSpecialMapextending,
        CraftingSpecialFireworkRocket,
        CraftingSpecialFireworkStar,
        CraftingSpecialFireworkStarFade,
        CraftingSpecialTippedarrow,
        CraftingSpecialBannerduplicate,
        CraftingSpecialShielddecoration,
        CraftingSpecialShulkerboxcoloring,
        CraftingSpecialSuspiciousstew,
        CraftingSpecialRepairitem,
        Smelting,
        Blasting,
        Smoking,
        CampfireCooking,
        Stonecutting,
        SmithingTransform,
        SmithingTrim,
        CraftingDecoratedPot,
        NUM_RECIPE_DATA_TYPES
    };
#endif

    class RecipeData;

    class Recipe : public NetworkType
    {
        SERIALIZED_FIELD(RecipeId, Identifier);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Type, Identifier);
#else
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Type, RecipeDataType);
#endif
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Data, std::shared_ptr<RecipeData>);

        DECLARE_READ_WRITE_SERIALIZE;

        GETTER(Type);
        GETTER(Data);

    public:
        virtual ~Recipe() override;

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        Recipe& SetType(const Identifier& type_);
#else
        Recipe& SetType(const RecipeDataType type_);
#endif


#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        std::string_view GetName() const;
#endif
    };
}
#endif
