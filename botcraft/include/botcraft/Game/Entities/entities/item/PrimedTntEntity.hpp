#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class PrimedTntEntity : public Entity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_fuse_id"),
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            std::string_view("data_block_state_id"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
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
