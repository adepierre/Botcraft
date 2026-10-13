#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class AbstractHorseEntity : public AnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_id_flags"),
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
            std::string_view("data_id_owner_uuid"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        AbstractHorseEntity();
        virtual ~AbstractHorseEntity();

        virtual bool IsAbstractHorse() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        char GetDataIdFlags() const;
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        std::optional<ProtocolCraft::UUID> GetDataIdOwnerUuid() const;
#endif

        void SetDataIdFlags(const char data_id_flags);
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        void SetDataIdOwnerUuid(const std::optional<ProtocolCraft::UUID>& data_id_owner_uuid);
#endif

        // Attribute stuff
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        double GetAttributeJumpStrengthValue() const;
#endif

    };
}
