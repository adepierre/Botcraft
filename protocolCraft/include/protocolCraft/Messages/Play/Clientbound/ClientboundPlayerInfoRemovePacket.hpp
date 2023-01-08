#if PROTOCOL_VERSION > 760
#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerInfoRemovePacket : public BaseMessage<ClientboundPlayerInfoRemovePacket>
    {
    public:
#if PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x35;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Player Info Remove";

        virtual ~ClientboundPlayerInfoRemovePacket() override
        {

        }

        void SetProfileIds(const std::vector<UUID>& profile_ids_)
        {
            profile_ids = profile_ids_;
        }


        const std::vector<UUID>& GetProfileIds() const
        {
            return profile_ids;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            profile_ids = ReadVector<UUID>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVector<UUID>(profile_ids, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["profile_ids"] = nlohmann::json::array();
            for (const auto& p : profile_ids)
            {
                output["profile_ids"].push_back(p);
            }

            return output;
        }

    private:
        std::vector<UUID> profile_ids;
    };
} //ProtocolCraft
#endif
