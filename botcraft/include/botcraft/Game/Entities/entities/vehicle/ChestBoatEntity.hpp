#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "botcraft/Game/Entities/entities/vehicle/BoatEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/vehicle/AbstractChestBoatEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
    class ChestBoatEntity : public BoatEntity
#else
    class ChestBoatEntity : public AbstractChestBoatEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 0;
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        static constexpr int hierarchy_metadata_count = BoatEntity::metadata_count + BoatEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = AbstractChestBoatEntity::metadata_count + AbstractChestBoatEntity::hierarchy_metadata_count;
#endif

    public:
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        ChestBoatEntity();
#else
        ChestBoatEntity(const EntityType type);
#endif
        virtual ~ChestBoatEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        static EntityType GetClassType();
#else
        virtual bool IsChestBoat() const override;
#endif


#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        virtual ProtocolCraft::Json::Value Serialize() const override;
#endif

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    protected:
        const EntityType type;
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
