#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "botcraft/Game/Entities/entities/projectile/arrow/AbstractArrowEntity.hpp"

namespace Botcraft
{
    class ThrownTridentEntity : public AbstractArrowEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("id_loyalty"),
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
            std::string_view("id_foil"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
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
