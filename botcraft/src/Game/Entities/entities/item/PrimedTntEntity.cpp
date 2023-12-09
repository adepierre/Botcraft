#include "botcraft/Game/Entities/entities/item/PrimedTntEntity.hpp"
#include "botcraft/Game/AssetsManager.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, PrimedTntEntity::metadata_count> PrimedTntEntity::metadata_names{ {
        "data_fuse_id",
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        "data_block_state_id",
#endif
    } };

    PrimedTntEntity::PrimedTntEntity()
    {
        // Initialize all metadata with default values
        SetDataFuseId(80);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        SetDataBlockStateId(AssetsManager::getInstance().GetBlockstate("minecraft:tnt")->GetId());
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


    void PrimedTntEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int PrimedTntEntity::GetDataFuseId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_fuse_id"));
    }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    int PrimedTntEntity::GetDataBlockStateId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_block_state_id"));
    }
#endif


    void PrimedTntEntity::SetDataFuseId(const int data_fuse_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_fuse_id"] = data_fuse_id;
    }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    void PrimedTntEntity::SetDataBlockStateId(const int data_block_state_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_block_state_id"] = data_block_state_id;
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
