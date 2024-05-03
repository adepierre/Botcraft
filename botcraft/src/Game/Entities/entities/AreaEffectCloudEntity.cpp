#include "botcraft/Game/Entities/entities/AreaEffectCloudEntity.hpp"

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Particles/ColorParticleOptions.hpp"
#endif

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, AreaEffectCloudEntity::metadata_count> AreaEffectCloudEntity::metadata_names{ {
        "data_radius",
        "data_color",
        "data_waiting",
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        "data_particle",
#endif
#if PROTOCOL_VERSION < 341 /* < 1.13 */
        "data_particle_argument1",
        "data_particle_argument2",
#endif
    } };

    AreaEffectCloudEntity::AreaEffectCloudEntity()
    {
        // Initialize all metadata with default values
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
        std::dynamic_pointer_cast<ProtocolCraft::ColorParticleOptions>(particle.GetOptions())->SetColor(-1);
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
        output["metadata"]["data_particle"] = GetDataParticle() ? ProtocolCraft::Json::Value({ {"particle_type", GetDataParticle()->GetName() }, {"particle_data", GetDataParticle()->Serialize()} }) : ProtocolCraft::Json::Value();
#else
        output["metadata"]["data_particle"] = GetDataParticle() ? ProtocolCraft::Json::Value(GetDataParticle().value()) : ProtocolCraft::Json::Value();
#endif
        return output;
    }


    void AreaEffectCloudEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            const std::string& metadata_name = metadata_names[index - hierarchy_metadata_count];
            metadata[metadata_name] = value;
#if USE_GUI
            if (metadata_name == "data_radius")
            {
                OnSizeUpdated();
            }
#endif
        }
    }

    float AreaEffectCloudEntity::GetDataRadius() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetDataRadiusImpl();
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    int AreaEffectCloudEntity::GetDataColor() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_color"));
    }
#endif

    bool AreaEffectCloudEntity::GetDataWaiting() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_waiting"));
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    std::shared_ptr<ProtocolCraft::Particle> AreaEffectCloudEntity::GetDataParticle() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::shared_ptr<ProtocolCraft::Particle>>(metadata.at("data_particle"));
    }
#else
    std::optional<int> AreaEffectCloudEntity::GetDataParticle() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::optional<int>>(metadata.at("data_particle"));
    }

    int AreaEffectCloudEntity::GetDataParticleArgument1() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_particle_argument1"));
    }

    int AreaEffectCloudEntity::GetDataParticleArgument2() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_particle_argument2"));
    }
#endif


    void AreaEffectCloudEntity::SetDataRadius(const float data_radius)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_radius"] = data_radius;
#if USE_GUI
        OnSizeUpdated();
#endif
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    void AreaEffectCloudEntity::SetDataColor(const int data_color)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_color"] = data_color;
    }
#endif

    void AreaEffectCloudEntity::SetDataWaiting(const bool data_waiting)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_waiting"] = data_waiting;
    }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    void AreaEffectCloudEntity::SetDataParticle(const ProtocolCraft::Particle& data_particle)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_particle"] = data_particle;
    }
#else
    void AreaEffectCloudEntity::SetDataParticle(const std::optional<int>& data_particle)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_particle"] = data_particle;
    }

    void AreaEffectCloudEntity::SetDataParticleArgument1(const int data_particle_argument1)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_particle_argument1"] = data_particle_argument1;
    }

    void AreaEffectCloudEntity::SetDataParticleArgument2(const int data_particle_argument2)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_particle_argument2"] = data_particle_argument2;
    }
#endif


    float AreaEffectCloudEntity::GetDataRadiusImpl() const
    {
        return std::any_cast<float>(metadata.at("data_radius"));
    }

    double AreaEffectCloudEntity::GetWidthImpl() const
    {
        return std::any_cast<float>(metadata.at("data_radius")) * 2.0;
    }

    double AreaEffectCloudEntity::GetHeightImpl() const
    {
        return 0.5;
    }
}
