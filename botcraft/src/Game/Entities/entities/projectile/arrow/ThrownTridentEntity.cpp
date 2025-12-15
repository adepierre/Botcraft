#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/projectile/arrow/ThrownTridentEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, ThrownTridentEntity::metadata_count> ThrownTridentEntity::metadata_names{ {
        "id_loyalty",
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        "id_foil",
#endif
    } };

    ThrownTridentEntity::ThrownTridentEntity()
    {
        // Initialize all metadata with default values
        SetIdLoyalty(0);
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        SetIdFoil(false);
#endif
    }

    ThrownTridentEntity::~ThrownTridentEntity()
    {

    }


    std::string ThrownTridentEntity::GetName() const
    {
        return "trident";
    }

    EntityType ThrownTridentEntity::GetType() const
    {
        return EntityType::ThrownTrident;
    }


    std::string ThrownTridentEntity::GetClassName()
    {
        return "trident";
    }

    EntityType ThrownTridentEntity::GetClassType()
    {
        return EntityType::ThrownTrident;
    }


    ProtocolCraft::Json::Value ThrownTridentEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractArrowEntity::Serialize();

        output["metadata"]["id_loyalty"] = GetIdLoyalty();
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
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
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char ThrownTridentEntity::GetIdLoyalty() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("id_loyalty"));
    }

#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    bool ThrownTridentEntity::GetIdFoil() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("id_foil"));
    }
#endif


    void ThrownTridentEntity::SetIdLoyalty(const char id_loyalty)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["id_loyalty"] = id_loyalty;
    }

#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    void ThrownTridentEntity::SetIdFoil(const bool id_foil)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["id_foil"] = id_foil;
    }
#endif


    double ThrownTridentEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double ThrownTridentEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
#endif
