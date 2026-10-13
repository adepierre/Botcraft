#pragma once

#if PROTOCOL_VERSION > 477 /* > 1.14 */
#include "botcraft/Game/Entities/entities/npc/villager/AbstractVillagerEntity.hpp"
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
    private:
        static constexpr std::array metadata_names{
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
            std::string_view("data_villager_data"),
#else
            std::string_view("data_villager_profession_id"),
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
            std::string_view("data_villager_data_finalized"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
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

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        VillagerData GetDataVillagerData() const;
#else
        int GetDataVillagerProfessionId() const;
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        bool GetDataVillagerDataFinalized() const;
#endif


#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        void SetDataVillagerData(const VillagerData& data_villager_data);
#else
        void SetDataVillagerProfessionId(const int data_villager_profession_id);
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        void SetDataVillagerDataFinalized(const bool data_villager_data_finalized);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
