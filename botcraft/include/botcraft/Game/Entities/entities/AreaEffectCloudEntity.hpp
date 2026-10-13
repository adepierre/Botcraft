#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Types/Particles/Particle.hpp"
#endif

namespace Botcraft
{
    class AreaEffectCloudEntity : public Entity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_radius"),
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            std::string_view("data_color"),
#endif
            std::string_view("data_waiting"),
            std::string_view("data_particle"),
#if PROTOCOL_VERSION < 341 /* < 1.13 */
            std::string_view("data_particle_argument1"),
            std::string_view("data_particle_argument2"),
#endif
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        AreaEffectCloudEntity();
        virtual ~AreaEffectCloudEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        float GetDataRadius() const;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        int GetDataColor() const;
#endif
        bool GetDataWaiting() const;
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ProtocolCraft::Particle GetDataParticle() const;
#else
        std::optional<int> GetDataParticle() const;
        int GetDataParticleArgument1() const;
        int GetDataParticleArgument2() const;
#endif

        void SetDataRadius(const float data_radius);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetDataColor(const int data_color);
#endif
        void SetDataWaiting(const bool data_waiting);
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        void SetDataParticle(const ProtocolCraft::Particle& data_particle);
#else
        void SetDataParticle(const std::optional<int>& data_particle_type_id);
        void SetDataParticleArgument1(const int data_particle_argument1);
        void SetDataParticleArgument2(const int data_particle_argument2);
#endif

    protected:
        void OnMetadataChangedImpl(const int index) override;
        float GetDataRadiusImpl() const;
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;
    };
}
