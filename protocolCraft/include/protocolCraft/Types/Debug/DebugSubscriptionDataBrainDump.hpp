#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"

#include "protocolCraft/Types/NetworkPosition.hpp"

#include <vector>

namespace ProtocolCraft
{
    class DebugSubscriptionDataBrainDump : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(Name, std::string);
        SERIALIZED_FIELD(Profession, std::string);
        SERIALIZED_FIELD(Xp, int);
        SERIALIZED_FIELD(Health, float);
        SERIALIZED_FIELD(MaxHealth, float);
        SERIALIZED_FIELD(Inventory, std::string);
        SERIALIZED_FIELD(WantsGolem, bool);
        SERIALIZED_FIELD(AngerLevel, int);
        SERIALIZED_FIELD(Activities, std::vector<std::string>);
        SERIALIZED_FIELD(Behaviors, std::vector<std::string>);
        SERIALIZED_FIELD(Memories, std::vector<std::string>);
        SERIALIZED_FIELD(Gossips, std::vector<std::string>);
        SERIALIZED_FIELD(Pois, std::vector<NetworkPosition>);
        SERIALIZED_FIELD(PotentialPois, std::vector<NetworkPosition>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
