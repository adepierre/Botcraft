#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#pragma once

#include "botcraft/Game/Entities/entities/AgeableMobEntity.hpp"

namespace Botcraft
{
    class AbstractCubeMobEntity : public AgeableMobEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("id_size"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = AgeableMobEntity::metadata_count + AgeableMobEntity::hierarchy_metadata_count;

    public:
        AbstractCubeMobEntity();
        virtual ~AbstractCubeMobEntity();

        virtual bool IsAbstractCubeMob() const override;

        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        int GetIdSize() const;

        void SetIdSize(const int id_size);

    protected:
        void OnMetadataChangedImpl(const int index) override;
        int GetIdSizeImpl() const;
        virtual void SizeChanged(const int new_size);

    };
}
#endif
