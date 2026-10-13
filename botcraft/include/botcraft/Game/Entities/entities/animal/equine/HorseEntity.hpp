#pragma once

#include "botcraft/Game/Entities/entities/animal/equine/AbstractHorseEntity.hpp"

namespace Botcraft
{
    class HorseEntity : public AbstractHorseEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_id_type_variant"),
#if PROTOCOL_VERSION < 405 /* < 1.14 */
            std::string_view("armor_type"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
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
        int GetDataIdTypeVariant() const;
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        std::optional<int> GetArmorType() const;
#endif

        void SetDataIdTypeVariant(const int data_id_type_variant);
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        void SetArmorType(const std::optional<int>& armor_type);
#endif

        // Attribute stuff
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        // 556e1665-8b10-40c8-8f9d-cf9b1667f295
        static constexpr std::array<unsigned char, 16> armor_modifier_uuid = { 0x55, 0x6E, 0x16, 0x65, 0x8B, 0x10, 0x40, 0xC8, 0x8F, 0x9D, 0xCF, 0x9B, 0x16, 0x67, 0xF2, 0x95 };
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
