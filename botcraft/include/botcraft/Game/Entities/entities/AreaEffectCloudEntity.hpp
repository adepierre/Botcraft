#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Types/Particles/Particle.hpp"
#endif

namespace Botcraft
{
    class AreaEffectCloudEntity : public Entity
    {
    protected:
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        static constexpr int metadata_count = 4;
#else
        static constexpr int metadata_count = 6;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        AreaEffectCloudEntity();
        virtual ~AreaEffectCloudEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        float GetDataRadius() const;
        int GetDataColor() const;
        bool GetDataWaiting() const;
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        //TODO: pointed object won't be thread safe
        std::shared_ptr<ProtocolCraft::Particle> GetDataParticle() const;
#else
        std::optional<int> GetDataParticle() const;
        int GetDataParticleArgument1() const;
        int GetDataParticleArgument2() const;
#endif

        void SetDataRadius(const float data_radius);
        void SetDataColor(const int data_color);
        void SetDataWaiting(const bool data_waiting);
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        void SetDataParticle(const std::shared_ptr<ProtocolCraft::Particle>& data_particle);
#else
        void SetDataParticle(const std::optional<int>& data_particle_type_id);
        void SetDataParticleArgument1(const int data_particle_argument1);
        void SetDataParticleArgument2(const int data_particle_argument2);
#endif

    };
}
