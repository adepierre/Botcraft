#pragma once

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerSlotStateChangedPacket : public BaseMessage<ServerboundContainerSlotStateChangedPacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x0F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Container Slot State Changed";

        virtual ~ServerboundContainerSlotStateChangedPacket() override
        {

        }

        void SetSlotId(const int slot_id_)
        {
            slot_id = slot_id_;
        }

        void SetContainerId(const int container_id_)
        {
            container_id = container_id_;
        }

        void SetNewState(const bool new_state_)
        {
            new_state = new_state_;
        }


        int GetSlotId() const
        {
            return slot_id;
        }

        int GetContainerId() const
        {
            return container_id;
        }

        bool GetNewState() const
        {
            return new_state;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            slot_id = ReadData<VarInt>(iter, length);
            container_id = ReadData<VarInt>(iter, length);
            new_state = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(slot_id, container);
            WriteData<VarInt>(container_id, container);
            WriteData<bool>(new_state, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["slot_id"] = slot_id;
            output["container_id"] = container_id;
            output["new_state"] = new_state;

            return output;
        }

    private:
        int slot_id = 0;
        int container_id = 0;
        bool new_state = false;

    };
} //ProtocolCraft
#endif
