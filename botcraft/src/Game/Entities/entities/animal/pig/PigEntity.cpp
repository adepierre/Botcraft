#include "botcraft/Game/Entities/entities/animal/pig/PigEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, PigEntity::metadata_count> PigEntity::metadata_names{ {
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        "data_saddle_id",
#endif
        "data_boost_time",
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        "data_variant_id",
#endif
    } };

    PigEntity::PigEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SetDataSaddleId(false);
#endif
        SetDataBoostTime(0);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        SetDataVariantId(0);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 10.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
    }

    PigEntity::~PigEntity()
    {

    }


    std::string PigEntity::GetName() const
    {
        return "pig";
    }

    EntityType PigEntity::GetType() const
    {
        return EntityType::Pig;
    }


    std::string PigEntity::GetClassName()
    {
        return "pig";
    }

    EntityType PigEntity::GetClassType()
    {
        return EntityType::Pig;
    }


    ProtocolCraft::Json::Value PigEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        output["metadata"]["data_saddle_id"] = GetDataSaddleId();
#endif
        output["metadata"]["data_boost_time"] = GetDataBoostTime();
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        output["metadata"]["data_variant_id"] = GetDataVariantId();
#endif

        return output;
    }


    void PigEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    bool PigEntity::GetDataSaddleId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_saddle_id"));
    }
#endif

    int PigEntity::GetDataBoostTime() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_boost_time"));
    }

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    int PigEntity::GetDataVariantId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_variant_id"));
    }
#endif


#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
    void PigEntity::SetDataSaddleId(const bool data_saddle_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_saddle_id"] = data_saddle_id;
    }
#endif

    void PigEntity::SetDataBoostTime(const int data_boost_time)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_boost_time"] = data_boost_time;
    }

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    void PigEntity::SetDataVariantId(const int data_variant_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_variant_id"] = data_variant_id;
    }
#endif


    double PigEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double PigEntity::GetHeightImpl() const
    {
        return 0.9;
    }

}
