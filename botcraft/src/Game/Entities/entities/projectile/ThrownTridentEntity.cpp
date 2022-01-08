#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/projectile/ThrownTridentEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, ThrownTridentEntity::metadata_count> ThrownTridentEntity::metadata_names{ {
        "id_loyalty",
#if PROTOCOL_VERSION > 498
        "id_foil",
#endif
    } };

    ThrownTridentEntity::ThrownTridentEntity()
    {
        // Initialize all metadata with default values
        SetIdLoyalty(0);
#if PROTOCOL_VERSION > 498
        SetIdFoil(false);
#endif
    }

    ThrownTridentEntity::~ThrownTridentEntity()
    {

    }


    std::string ThrownTridentEntity::GetName() const
    {
        return "ThrownTrident";
    }

    EntityType ThrownTridentEntity::GetType() const
    {
        return EntityType::ThrownTrident;
    }

    AABB ThrownTridentEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ThrownTridentEntity::GetWidth() const
    {
        return 0.5;
    }

    double ThrownTridentEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string ThrownTridentEntity::GetClassName()
    {
        return "ThrownTrident";
    }

    EntityType ThrownTridentEntity::GetClassType()
    {
        return EntityType::ThrownTrident;
    }


    nlohmann::json ThrownTridentEntity::Serialize() const
    {
        nlohmann::json output = AbstractArrowEntity::Serialize();

        output["metadata"]["id_loyalty"] = GetIdLoyalty();
#if PROTOCOL_VERSION > 498
        output["metadata"]["id_foil"] = GetIdFoil();
#endif

        return output;
    }


    void ThrownTridentEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractArrowEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char ThrownTridentEntity::GetIdLoyalty() const
    {
        return std::any_cast<char>(metadata.at("id_loyalty"));
    }

#if PROTOCOL_VERSION > 498
    bool ThrownTridentEntity::GetIdFoil() const
    {
        return std::any_cast<bool>(metadata.at("id_foil"));
    }
#endif


    void ThrownTridentEntity::SetIdLoyalty(const char id_loyalty)
    {
        metadata["id_loyalty"] = id_loyalty;
    }

#if PROTOCOL_VERSION > 498
    void ThrownTridentEntity::SetIdFoil(const bool id_foil)
    {
        metadata["id_foil"] = id_foil;
    }
#endif

}
#endif
