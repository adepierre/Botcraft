#if PROTOCOL_VERSION > 760
#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerInfoRemovePacket : public BaseMessage<ClientboundPlayerInfoRemovePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 761 // 1.19.3
            return 0x35;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Info Remove";
        }

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
            const int profile_ids_length = ReadData<VarInt>(iter, length);
            profile_ids = std::vector<UUID>(profile_ids_length);
            for (size_t i = 0; i < profile_ids_length; ++i)
            {
                profile_ids[i] = ReadData<UUID>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(static_cast<int>(profile_ids.size()), container);
            for (size_t i = 0; i < profile_ids.size(); ++i)
            {
                WriteData<UUID>(profile_ids[i], container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["profile_ids"] = nlohmann::json::array();
            for (size_t i = 0; i < profile_ids.size(); ++i)
            {
                output["profile_ids"].push_back(profile_ids[i]);
            }

            return output;
        }

    private:
        std::vector<UUID> profile_ids;
    };
} //ProtocolCraft
#endif
