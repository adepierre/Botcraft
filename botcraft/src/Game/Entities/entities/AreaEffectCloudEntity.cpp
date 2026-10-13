#include "botcraft/Game/Entities/entities/AreaEffectCloudEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Particles/ColorParticleOption.hpp"
#endif

namespace Botcraft
{
    AreaEffectCloudEntity::AreaEffectCloudEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SetDataRadius(0.5f);
#else
        SetDataRadius(3.0f);
#endif
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SetDataColor(0);
#endif
        SetDataWaiting(false);
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        ProtocolCraft::Particle particle;
        particle.SetParticleType(ProtocolCraft::ParticleType::EntityEffect);
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        std::dynamic_pointer_cast<ProtocolCraft::ColorParticleOption>(particle.GetOption())->SetColor(-1);
#endif
        SetDataParticle(particle);
#else
        SetDataParticle(std::optional<int>());
        SetDataParticleArgument1(0);
        SetDataParticleArgument2(0);
#endif
    }

    AreaEffectCloudEntity::~AreaEffectCloudEntity()
    {

    }


    std::string AreaEffectCloudEntity::GetName() const
    {
        return "area_effect_cloud";
    }

    EntityType AreaEffectCloudEntity::GetType() const
    {
        return EntityType::AreaEffectCloud;
    }


    std::string AreaEffectCloudEntity::GetClassName()
    {
        return "area_effect_cloud";
    }

    EntityType AreaEffectCloudEntity::GetClassType()
    {
        return EntityType::AreaEffectCloud;
    }


    ProtocolCraft::Json::Value AreaEffectCloudEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_radius"] = GetDataRadius();
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        output["metadata"]["data_color"] = GetDataColor();
#endif
        output["metadata"]["data_waiting"] = GetDataWaiting();
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        output["metadata"]["data_particle"] = GetDataParticle().Serialize();
#else
        output["metadata"]["data_particle"] = GetDataParticle() ? ProtocolCraft::Json::Value(GetDataParticle().value()) : ProtocolCraft::Json::Value();
        output["metadata"]["data_particle_argument1"] = GetDataParticleArgument1();
        output["metadata"]["data_particle_argument2"] = GetDataParticleArgument2();
#endif
        return output;
    }


    void AreaEffectCloudEntity::OnMetadataChangedImpl(const int index)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::OnMetadataChangedImpl(index);
        }
#if USE_GUI
        else if (index == BOTCRAFT_ENTITY_METADATA_INDEX("data_radius"))
        {
            OnSizeUpdated();
        }
#endif
    }

    float AreaEffectCloudEntity::GetDataRadius() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetDataRadiusImpl();
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    int AreaEffectCloudEntity::GetDataColor() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_color"));
    }
#endif

    bool AreaEffectCloudEntity::GetDataWaiting() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_waiting"));
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    ProtocolCraft::Particle AreaEffectCloudEntity::GetDataParticle() const
    {
        return GetMetadata<ProtocolCraft::Particle>(BOTCRAFT_ENTITY_METADATA_INDEX("data_particle"));
    }
#else
    std::optional<int> AreaEffectCloudEntity::GetDataParticle() const
    {
        return GetMetadata<std::optional<int>>(BOTCRAFT_ENTITY_METADATA_INDEX("data_particle"));
    }

    int AreaEffectCloudEntity::GetDataParticleArgument1() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_particle_argument1"));
    }

    int AreaEffectCloudEntity::GetDataParticleArgument2() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_particle_argument2"));
    }
#endif


    void AreaEffectCloudEntity::SetDataRadius(const float data_radius)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_radius"), data_radius);
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    void AreaEffectCloudEntity::SetDataColor(const int data_color)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_color"), data_color);
    }
#endif

    void AreaEffectCloudEntity::SetDataWaiting(const bool data_waiting)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_waiting"), data_waiting);
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    void AreaEffectCloudEntity::SetDataParticle(const ProtocolCraft::Particle& data_particle)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_particle"), data_particle);
    }
#else
    void AreaEffectCloudEntity::SetDataParticle(const std::optional<int>& data_particle)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_particle"), data_particle);
    }

    void AreaEffectCloudEntity::SetDataParticleArgument1(const int data_particle_argument1)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_particle_argument1"), data_particle_argument1);
    }

    void AreaEffectCloudEntity::SetDataParticleArgument2(const int data_particle_argument2)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_particle_argument2"), data_particle_argument2);
    }
#endif


    float AreaEffectCloudEntity::GetDataRadiusImpl() const
    {
        return GetMetadataImpl<float>(BOTCRAFT_ENTITY_METADATA_INDEX("data_radius"));
    }

    double AreaEffectCloudEntity::GetWidthImpl() const
    {
        return GetDataRadiusImpl() * 2.0;
    }

    double AreaEffectCloudEntity::GetHeightImpl() const
    {
        return 0.5;
    }
}
