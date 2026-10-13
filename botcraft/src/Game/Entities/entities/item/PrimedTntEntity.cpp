#include "botcraft/Game/Entities/entities/item/PrimedTntEntity.hpp"
#include "botcraft/Game/AssetsManager.hpp"

namespace Botcraft
{
    PrimedTntEntity::PrimedTntEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataFuseId(80);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        static const BlockstateId tnt_id = AssetsManager::getInstance().GetBlockstate("minecraft:tnt")->GetId();
        SetDataBlockStateId(tnt_id);
#endif
    }

    PrimedTntEntity::~PrimedTntEntity()
    {

    }


    std::string PrimedTntEntity::GetName() const
    {
        return "tnt";
    }

    EntityType PrimedTntEntity::GetType() const
    {
        return EntityType::PrimedTnt;
    }


    std::string PrimedTntEntity::GetClassName()
    {
        return "tnt";
    }

    EntityType PrimedTntEntity::GetClassType()
    {
        return EntityType::PrimedTnt;
    }


    ProtocolCraft::Json::Value PrimedTntEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_fuse_id"] = GetDataFuseId();
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        output["metadata"]["data_block_state_id"] = GetDataBlockStateId();
#endif

        return output;
    }


    int PrimedTntEntity::GetDataFuseId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_fuse_id"));
    }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    int PrimedTntEntity::GetDataBlockStateId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_block_state_id"));
    }
#endif


    void PrimedTntEntity::SetDataFuseId(const int data_fuse_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_fuse_id"), data_fuse_id);
    }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    void PrimedTntEntity::SetDataBlockStateId(const int data_block_state_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_block_state_id"), data_block_state_id);
    }
#endif


    double PrimedTntEntity::GetWidthImpl() const
    {
        return 0.98;
    }

    double PrimedTntEntity::GetHeightImpl() const
    {
        return 0.98;
    }

}
