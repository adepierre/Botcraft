#pragma once

#include "botcraft/Game/Entities/entities/animal/horse/AbstractHorseEntity.hpp"

namespace Botcraft
{
    class HorseEntity : public AbstractHorseEntity
    {
    protected:
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        static constexpr int metadata_count = 1;
#else
        static constexpr int metadata_count = 2;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractHorseEntity::metadata_count + AbstractHorseEntity::hierarchy_metadata_count;

    public:
        HorseEntity();
        virtual ~HorseEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataIdTypeVariant() const;
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        std::optional<int> GetArmorType() const;
#endif

        void SetDataIdTypeVariant(const int data_id_type_variant);
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        void SetArmorType(const std::optional<int>& armor_type);
#endif

        // Attribute stuff
        // 556e1665-8b10-40c8-8f9d-cf9b1667f295
        static constexpr std::array<unsigned char, 16> armor_modifier_uuid = { 0x55, 0x6E, 0x16, 0x65, 0x8B, 0x10, 0x40, 0xC8, 0x8F, 0x9D, 0xCF, 0x9B, 0x16, 0x67, 0xF2, 0x95 };

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
