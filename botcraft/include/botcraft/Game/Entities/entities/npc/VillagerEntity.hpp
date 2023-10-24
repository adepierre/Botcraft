#pragma once

#if PROTOCOL_VERSION > 477 /* > 1.14 */
#include "botcraft/Game/Entities/entities/npc/AbstractVillagerEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/AgeableMobEntity.hpp"
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/VillagerData.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 477 /* > 1.14 */
    class VillagerEntity : public AbstractVillagerEntity
#else
    class VillagerEntity : public AgeableMobEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
#if PROTOCOL_VERSION > 477 /* > 1.14 */
        static constexpr int hierarchy_metadata_count = AbstractVillagerEntity::metadata_count + AbstractVillagerEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = AgeableMobEntity::metadata_count + AgeableMobEntity::hierarchy_metadata_count;
#endif

    public:
        VillagerEntity();
        virtual ~VillagerEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        VillagerData GetDataVillagerData() const;

        void SetDataVillagerData(const VillagerData& data_villager_data);
#else
        int GetDataVillagerProfessionId() const;

        void SetDataVillagerProfessionId(const int data_villager_profession_id);
#endif

    };
}
