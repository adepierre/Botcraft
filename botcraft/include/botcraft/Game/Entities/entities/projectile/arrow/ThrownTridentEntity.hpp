#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "botcraft/Game/Entities/entities/projectile/arrow/AbstractArrowEntity.hpp"

namespace Botcraft
{
    class ThrownTridentEntity : public AbstractArrowEntity
    {
    protected:
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        static constexpr int metadata_count = 2;
#else
        static constexpr int metadata_count = 1;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractArrowEntity::metadata_count + AbstractArrowEntity::hierarchy_metadata_count;

    public:
        ThrownTridentEntity();
        virtual ~ThrownTridentEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        char GetIdLoyalty() const;
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        bool GetIdFoil() const;
#endif

        void SetIdLoyalty(const char id_loyalty);
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        void SetIdFoil(const bool id_foil);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
