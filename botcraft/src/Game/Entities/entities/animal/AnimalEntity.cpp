#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include <mutex>
#endif

namespace Botcraft
{
    AnimalEntity::AnimalEntity()
    {
        // Initialize all attributes with default values
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        attributes.insert({ EntityAttribute::Type::TemptRange, EntityAttribute(EntityAttribute::Type::TemptRange, 10.0) });
#endif

    }

    AnimalEntity::~AnimalEntity()
    {

    }

    bool AnimalEntity::IsAnimal() const
    {
        return true;
    }

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    ProtocolCraft::Json::Value AnimalEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AgeableMobEntity::Serialize();

        output["attributes"]["tempt_range"] = GetAttributeTemptRangeValue();

        return output;
    }
#endif


#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    double AnimalEntity::GetAttributeTemptRangeValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::TemptRange).GetValue();
    }
#endif

}
