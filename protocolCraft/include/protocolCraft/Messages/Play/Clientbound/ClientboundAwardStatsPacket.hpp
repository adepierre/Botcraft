#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <map>

namespace ProtocolCraft
{
    class ClientboundAwardStatsPacket : public BaseMessage<ClientboundAwardStatsPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Award Stats";

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

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (std::map<std::string, VarInt>),
            (Stats)
        );
#else
        DECLARE_FIELDS(
            (Internal::CustomType<std::map<std::pair<VarInt, VarInt>, VarInt>, nullptr, nullptr, &THIS::SerializeStats>),
            (Stats)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Stats);
    };
} //ProtocolCraft
