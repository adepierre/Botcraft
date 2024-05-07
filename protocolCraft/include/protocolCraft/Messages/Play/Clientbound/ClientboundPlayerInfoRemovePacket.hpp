#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include <vector>

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerInfoRemovePacket : public BaseMessage<ClientboundPlayerInfoRemovePacket>
    {
    public:
#if   PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x3D;
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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            profile_ids = ReadVector<UUID>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVector<UUID>(profile_ids, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["profile_ids"] = profile_ids;

            return output;
        }

    private:
        std::vector<UUID> profile_ids;
    };
} //ProtocolCraft
#endif
