#pragma once

#include "botcraft/Game/Entities/entities/animal/golem/AbstractGolemEntity.hpp"

namespace Botcraft
{
    class ShulkerEntity : public AbstractGolemEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_attach_face_id"),
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            std::string_view("data_attach_pos_id"),
#endif
            std::string_view("data_peek_id"),
            std::string_view("data_color_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AbstractGolemEntity::metadata_count + AbstractGolemEntity::hierarchy_metadata_count;

    public:
        ShulkerEntity();
        virtual ~ShulkerEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        Direction GetDataAttachFaceId() const;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        std::optional<Position> GetDataAttachPosId() const;
#endif
        char GetDataPeekId() const;
        char GetDataColorId() const;

        void SetDataAttachFaceId(const Direction data_attach_face_id);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        void SetDataAttachPosId(const std::optional<Position>& data_attach_pos_id);
#endif
        void SetDataPeekId(const char data_peek_id);
        void SetDataColorId(const char data_color_id);

        // Attribute stuff
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        // 7e0292f2-9434-48d5-a29f-9583af7df27f
        static constexpr std::array<unsigned char, 16> covered_armor_modifier_key = { 0x7E, 0x2, 0x92, 0xF2, 0x94, 0x34, 0x48, 0xD5, 0xA2, 0x9F, 0x95, 0x83, 0xAF, 0x7D, 0xF2, 0x7F };
#else
        inline static const std::string covered_armor_modifier_key = "minecraft:covered";
#endif


    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
