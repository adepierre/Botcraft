#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include "botcraft/Game/Entities/entities/animal/goat/GoatEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, GoatEntity::metadata_count> GoatEntity::metadata_names{ {
        "data_is_screaming_goat",
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        "data_has_left_horn",
        "data_has_right_horn",
#endif
    } };

    GoatEntity::GoatEntity()
    {
        // Initialize all metadata with default values
        SetDataIsScreamingGoat(false);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SetDataHasLeftHorn(true);
        SetDataHasRightHorn(true);
#endif
    }

    GoatEntity::~GoatEntity()
    {

    }


    std::string GoatEntity::GetName() const
    {
        return "goat";
    }

    EntityType GoatEntity::GetType() const
    {
        return EntityType::Goat;
    }


    std::string GoatEntity::GetClassName()
    {
        return "goat";
    }

    EntityType GoatEntity::GetClassType()
    {
        return EntityType::Goat;
    }


    ProtocolCraft::Json::Value GoatEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_is_screaming_goat"] = GetDataIsScreamingGoat();
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        output["metadata"]["data_has_left_horn"] = GetDataHasLeftHorn();
        output["metadata"]["data_has_right_horn"] = GetDataHasRightHorn();
#endif

        return output;
    }


    void GoatEntity::SetMetadataValue(const int index, const std::any& value)
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

    bool GoatEntity::GetDataIsScreamingGoat() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_is_screaming_goat"));
    }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    bool GoatEntity::GetDataHasLeftHorn() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_has_left_horn"));
    }

    bool GoatEntity::GetDataHasRightHorn() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_has_right_horn"));
    }
#endif


    void GoatEntity::SetDataIsScreamingGoat(const bool data_is_screaming_goat)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_is_screaming_goat"] = data_is_screaming_goat;
    }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    void GoatEntity::SetDataHasLeftHorn(const bool data_has_left_horn)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_has_left_horn"] = data_has_left_horn;
    }

    void GoatEntity::SetDataHasRightHorn(const bool data_has_right_horn)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_has_right_horn"] = data_has_right_horn;
    }
#endif


    double GoatEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double GoatEntity::GetHeightImpl() const
    {
        return 1.3;
    }

}
#endif
