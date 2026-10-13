#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/projectile/arrow/ThrownTridentEntity.hpp"

namespace Botcraft
{
    ThrownTridentEntity::ThrownTridentEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    char ThrownTridentEntity::GetIdLoyalty() const
    {
        return GetMetadata<char>(BOTCRAFT_ENTITY_METADATA_INDEX("id_loyalty"));
    }

#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    bool ThrownTridentEntity::GetIdFoil() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("id_foil"));
    }
#endif


    void ThrownTridentEntity::SetIdLoyalty(const char id_loyalty)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("id_loyalty"), id_loyalty);
    }

#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    void ThrownTridentEntity::SetIdFoil(const bool id_foil)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("id_foil"), id_foil);
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
