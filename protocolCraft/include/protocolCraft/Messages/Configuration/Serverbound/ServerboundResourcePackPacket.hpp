#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundResourcePackConfigurationPacket : public BaseMessage<ServerboundResourcePackConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x05;

        static constexpr std::string_view packet_name = "Resource Pack (Configuration)";

        virtual ~ServerboundResourcePackConfigurationPacket() override
        {

        }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        void SetUUID(const UUID& uuid_)
        {
            uuid = uuid_;
        }
#endif

        void SetAction(const int action_)
        {
            action = action_;
        }


#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        const UUID& GetUUID() const
        {
            return uuid;
        }
#endif

        int GetAction() const
        {
            return action;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            uuid = ReadData<UUID>(iter, length);
#endif
            action = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            WriteData<UUID>(uuid, container);
#endif
            WriteData<VarInt>(action, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            output["uuid"] = uuid;
#endif
            output["action"] = action;

            return output;
        }

    private:
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        UUID uuid = {};
#endif
        int action = 0;

    };
} //ProtocolCraft
#endif
