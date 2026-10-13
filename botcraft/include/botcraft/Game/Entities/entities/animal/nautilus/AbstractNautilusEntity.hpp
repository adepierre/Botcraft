#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once

#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"

namespace Botcraft
{
    class AbstractNautilusEntity : public TamableAnimalEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_dash"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = TamableAnimalEntity::metadata_count + TamableAnimalEntity::hierarchy_metadata_count;

    public:
        AbstractNautilusEntity();
        virtual ~AbstractNautilusEntity();

        virtual bool IsAbstractNautilus() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetDataDash() const;

        void SetDataDash(const bool data_dash);

        // Attribute stuff
        double GetAttributeAttackDamageValue() const;

    };
}
#endif
