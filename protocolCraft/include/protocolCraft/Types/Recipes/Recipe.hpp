#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
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
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS_TYPES(Identifier, Identifier, std::shared_ptr<RecipeData>);
        DECLARE_FIELDS_NAMES(RecipeId,   Type,       Data);
#else
        DECLARE_FIELDS_TYPES(Identifier, RecipeDataType, std::shared_ptr<RecipeData>);
        DECLARE_FIELDS_NAMES(RecipeId,   Type,           Data);
#endif

        GETTER_SETTER(RecipeId);

    public:
        virtual ~Recipe() override;

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetType(const Identifier& type_);
#else
        void SetType(const RecipeDataType type_);
#endif

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const Identifier& GetType() const;
#else
        RecipeDataType GetType() const;
        std::string_view GetName() const;
#endif
        const std::shared_ptr<RecipeData>& GetData() const;

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        virtual void WriteImpl(WriteContainer& container) const override;
        virtual Json::Value SerializeImpl() const override;
    };
}
#endif
