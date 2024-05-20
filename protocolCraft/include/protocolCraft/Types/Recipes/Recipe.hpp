#pragma once

#if PROTOCOL_VERSION > 347 /* > 1.12.2 */

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
    public:
        virtual ~Recipe() override;


        void SetRecipeId(const Identifier& recipe_id_);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetType(const Identifier& type_);
#else
        void SetType(const RecipeDataType type_);
#endif


        const Identifier& GetRecipeId() const;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const Identifier& GetType() const;
#else
        RecipeDataType GetType() const;
        std::string_view GetName() const;
#endif
        std::shared_ptr<RecipeData> GetData() const;

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        virtual void WriteImpl(WriteContainer& container) const override;
        virtual Json::Value SerializeImpl() const override;

    private:
        Identifier recipe_id;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        Identifier type;
#else
        RecipeDataType type = RecipeDataType::None;
#endif
        std::shared_ptr<RecipeData> data;
    };
}
#endif
