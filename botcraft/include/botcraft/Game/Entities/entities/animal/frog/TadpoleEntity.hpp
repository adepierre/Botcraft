#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "botcraft/Game/Entities/entities/animal/fish/AbstractFishEntity.hpp"

namespace Botcraft
{
    class TadpoleEntity : public AbstractFishEntity
    {
#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
    private:
        static constexpr std::array metadata_names{
            std::string_view("age_locked"),
        };
#endif
    protected:
#if PROTOCOL_VERSION < 775 /* < 26.1 */
        static constexpr int metadata_count = 0;
#else
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
#endif
        static constexpr int hierarchy_metadata_count = AbstractFishEntity::metadata_count + AbstractFishEntity::hierarchy_metadata_count;

    public:
        TadpoleEntity();
        virtual ~TadpoleEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        bool GetAgeLocked() const;

        void SetAgeLocked(const bool age_locked);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
