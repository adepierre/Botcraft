#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "botcraft/Game/Entities/entities/monster/MonsterEntity.hpp"

namespace Botcraft
{
    class CreakingEntity : public MonsterEntity
    {
    protected:
#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
        static constexpr int metadata_count = 2;
#else
        static constexpr int metadata_count = 4;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = MonsterEntity::metadata_count + MonsterEntity::hierarchy_metadata_count;

    public:
        CreakingEntity();
        virtual ~CreakingEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        bool GetCanMove() const;
        bool GetIsActive() const;
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        bool GetIsTearingDown() const;
        const std::optional<Position>& GetHomePos() const;
#endif

        void SetCanMove(const bool can_move);
        void SetIsActive(const bool is_active);
#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        void SetIsTearingDown(const bool is_tearing_down);
        void SetHomePos(const std::optional<Position>& home_pos);
#endif

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
#endif
