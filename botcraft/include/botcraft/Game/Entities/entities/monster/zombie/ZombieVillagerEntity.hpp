#pragma once

#include "botcraft/Game/Entities/entities/monster/zombie/ZombieEntity.hpp"
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/VillagerData.hpp"
#endif

namespace Botcraft
{
    class ZombieVillagerEntity : public ZombieEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_converting_id"),
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
        static constexpr int hierarchy_metadata_count = ZombieEntity::metadata_count + ZombieEntity::hierarchy_metadata_count;

    public:
        ZombieVillagerEntity();
        virtual ~ZombieVillagerEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetDataConvertingId() const;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        VillagerData GetDataVillagerData() const;
#else
        int GetDataVillagerProfessionId() const;
#endif
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        bool GetDataVillagerDataFinalized() const;
#endif

        void SetDataConvertingId(const bool data_converting_id);
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
