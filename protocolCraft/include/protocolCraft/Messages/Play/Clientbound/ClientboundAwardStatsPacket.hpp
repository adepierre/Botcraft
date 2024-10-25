#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "protocolCraft/Utilities/CustomType.hpp"
#endif

#include <map>

namespace ProtocolCraft
{
    class ClientboundAwardStatsPacket : public BaseMessage<ClientboundAwardStatsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Award Stats";

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    private:
        std::optional<Json::Value> SerializeStats(const std::map<std::pair<int, int>, int>& stats) const
        {
            Json::Array output;
            for (const auto& p : stats)
            {
                output.push_back({
                    {"category_id", p.first.first},
                    {"stats_id", p.first.second},
                    {"value", p.second}
                });
            }
            return output;
        }
#endif

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        SERIALIZED_FIELD(Stats, std::map<std::string, VarInt>);
#else
        SERIALIZED_FIELD(Stats, Internal::CustomType<std::map<std::pair<VarInt, VarInt>, VarInt>, nullptr, nullptr, &THIS::SerializeStats>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
