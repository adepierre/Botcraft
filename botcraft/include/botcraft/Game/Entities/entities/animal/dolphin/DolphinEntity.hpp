#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "botcraft/Game/Entities/entities/animal/fish/WaterAnimalEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/animal/AgeableWaterCreatureEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    class DolphinEntity : public WaterAnimalEntity
#else
    class DolphinEntity : public AgeableWaterCreatureEntity
#endif
    {
    protected:
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        static constexpr int metadata_count = 3;
#else
        static constexpr int metadata_count = 2;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        static constexpr int hierarchy_metadata_count = WaterAnimalEntity::metadata_count + WaterAnimalEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = AgeableWaterCreatureEntity::metadata_count + AgeableWaterCreatureEntity::hierarchy_metadata_count;
#endif

    public:
        DolphinEntity();
        virtual ~DolphinEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        Position GetTreasurePos() const;
#endif
        bool GetGotFish() const;
        int GetMoistnessLevel() const;

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        void SetTreasurePos(const Position& treasure_pos);
#endif
        void SetGotFish(const bool got_fish);
        void SetMoistnessLevel(const int moistness_level);

        // Attribute stuff
        double GetAttributeAttackDamageValue() const;

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
