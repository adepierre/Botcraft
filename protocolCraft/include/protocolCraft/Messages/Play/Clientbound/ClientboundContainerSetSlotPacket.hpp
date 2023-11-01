#pragma once

#include <string>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetSlotPacket : public BaseMessage<ClientboundContainerSetSlotPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 759 /* 1.19 */ || PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x15;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Container Set Slot";

        virtual ~ClientboundContainerSetSlotPacket() override
        {

        }

        void SetContainerId(const char container_id_)
        {
            container_id = container_id_;
        }

        void SetSlot_(const short slot_)
        {
            slot = slot_;
        }

        void SetItemStack(const Slot& item_stack_)
        {
            item_stack = item_stack_;
        }

#if PROTOCOL_VERSION > 755 /* > 1.17 */
        void SetStateId(const int state_id_)
        {
            state_id = state_id_;
        }
#endif

        char GetContainerId() const
        {
            return container_id;
        }

        short GetSlot() const
        {
            return slot;
        }

        const Slot& GetItemStack() const
        {
            return item_stack;
        }

#if PROTOCOL_VERSION > 755 /* > 1.17 */
        int GetStateId() const
        {
            return state_id;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<char>(iter, length);
#if PROTOCOL_VERSION > 755 /* > 1.17 */
            state_id = ReadData<VarInt>(iter, length);
#endif
            slot = ReadData<short>(iter, length);
            item_stack = ReadData<Slot>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(container_id, container);
#if PROTOCOL_VERSION > 755 /* > 1.17 */
            WriteData<VarInt>(state_id, container);
#endif
            WriteData<short>(slot, container);
            WriteData<Slot>(item_stack, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
            output["slot"] = slot;
            output["item_stack"] = item_stack;
#if PROTOCOL_VERSION > 755 /* > 1.17 */
            output["state_id"] = state_id;
#endif

            return output;
        }

    private:
        char container_id = 0;
        short slot = 0;
        Slot item_stack;
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        int state_id = 0;
#endif

    };
} //ProtocolCraft
