#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once

#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"

namespace Botcraft
{
    class AbstractNautilusEntity : public TamableAnimalEntity
    {
    protected:
        static constexpr int metadata_count = 1;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = TamableAnimalEntity::metadata_count + TamableAnimalEntity::hierarchy_metadata_count;

    public:
        AbstractNautilusEntity();
        virtual ~AbstractNautilusEntity();

        virtual bool IsAbstractNautilus() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetDataDash() const;

        void SetDataDash(const bool data_dash);

        // Attribute stuff
        double GetAttributeAttackDamageValue() const;

    };
}
#endif
