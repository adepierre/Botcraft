#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class PrimedTntEntity : public Entity
    {
    protected:
#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        static constexpr int metadata_count = 1;
#else
        static constexpr int metadata_count = 2;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        PrimedTntEntity();
        virtual ~PrimedTntEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataFuseId() const;
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        int GetDataBlockStateId() const;
#endif

        void SetDataFuseId(const int data_fuse_id);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        void SetDataBlockStateId(const int data_block_state_id);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
