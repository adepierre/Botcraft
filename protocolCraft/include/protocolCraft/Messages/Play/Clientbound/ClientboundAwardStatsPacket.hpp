#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <map>

namespace ProtocolCraft
{
    class ClientboundAwardStatsPacket : public BaseMessage<ClientboundAwardStatsPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Award Stats";

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (std::map<std::string, VarInt>),
            (Stats)
        );
#else
        DECLARE_FIELDS(
            (std::map<std::pair<VarInt, VarInt>, VarInt>),
            (Stats)
        );
#endif
        DECLARE_READ;
        DECLARE_WRITE;

        GETTER_SETTER(Stats);

    protected:
        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 346 /* < 1.13 */
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Stats)])] = GetStats();
#else
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Stats)])] = Json::Array();
            for (const auto& p : GetStats())
            {
                output.push_back({
                    {"category_id", p.first.first},
                    {"stats_id", p.first.second},
                    {"value", p.second} }
                );
            }
#endif

            return output;
        }
    };
} //ProtocolCraft
