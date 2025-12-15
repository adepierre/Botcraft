#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class AbstractHorseEntity : public AnimalEntity
    {
    protected:
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
        static constexpr int metadata_count = 2;
#else
        static constexpr int metadata_count = 1;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        AbstractHorseEntity();
        virtual ~AbstractHorseEntity();

        virtual bool IsAbstractHorse() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

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
