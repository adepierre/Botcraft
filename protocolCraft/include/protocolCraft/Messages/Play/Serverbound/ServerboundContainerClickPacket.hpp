#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include <map>
#endif

namespace ProtocolCraft
{
    class ServerboundContainerClickPacket : public BaseMessage<ServerboundContainerClickPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */ ||  \
      PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x0D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Container Click";

        virtual ~ServerboundContainerClickPacket() override
        {

        }

        void SetContainerId(const unsigned char container_id_)
        {
            container_id = container_id_;
        }

        void SetSlotNum(const short slot_num_)
        {
            slot_num = slot_num_;
        }

        void SetButtonNum(const char button_num_)
        {
            button_num = button_num_;
        }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        void SetUid(const short uid_)
        {
            uid = uid_;
        }
#endif

        void SetClickType(const int click_type_)
        {
            click_type = click_type_;
        }

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        void SetChangedSlots(const std::map<short, Slot>& changed_slots_)
        {
            changed_slots = changed_slots_;
        }
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        void SetItemStack(const Slot& item_stack_)
        {
            item_stack = item_stack_;
        }
#else
        void SetCarriedItem(const Slot& carried_item_)
        {
            carried_item = carried_item_;
        }
#endif

#if PROTOCOL_VERSION > 755 /* > 1.17 */
        void SetStateId(const int state_id_)
        {
            state_id = state_id_;
        }
#endif

        unsigned char GetContainerId() const
        {
            return container_id;
        }

        short GetSlotNum() const
        {
            return slot_num;
        }

        char GetButtonNum() const
        {
            return button_num;
        }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        short GetUid() const
        {
            return uid;
        }
#endif

        int GetClickType() const
        {
            return click_type;
        }

#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        const std::map<short, Slot>& GetChangeSlots() const
        {
            return changed_slots;
        }
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        const Slot& GetItemStack() const
        {
            return item_stack;
        }
#else
        const Slot& GetCarriedItem() const
        {
            return carried_item;
        }
#endif

#if PROTOCOL_VERSION > 755 /* > 1.17 */
        int GetStateId() const
        {
            return state_id;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION > 755 /* > 1.17 */
            state_id = ReadData<VarInt>(iter, length);
#endif
            slot_num = ReadData<short>(iter, length);
            button_num = ReadData<char>(iter, length);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            uid = ReadData<short>(iter, length);
#endif
            click_type = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            changed_slots = ReadMap<short, Slot>(iter, length);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            item_stack = ReadData<Slot>(iter, length);
#else
            carried_item = ReadData<Slot>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(container_id, container);
#if PROTOCOL_VERSION > 755 /* > 1.17 */
            WriteData<VarInt>(state_id, container);
#endif
            WriteData<short>(slot_num, container);
            WriteData<char>(button_num, container);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<short>(uid, container);
#endif
            WriteData<VarInt>(click_type, container);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            WriteMap<short, Slot>(changed_slots, container);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<Slot>(item_stack, container);
#else
            WriteData<Slot>(carried_item, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
#if PROTOCOL_VERSION > 755 /* > 1.17 */
            output["state_id"] = state_id;
#endif
            output["slot_num"] = slot_num;
            output["button_num"] = button_num;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            output["uid"] = uid;
#endif
            output["click_type"] = click_type;
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */

            output["changed_slots"] = Json::Object();
            for (const auto& p : changed_slots)
            {
                output["changed_slots"][std::to_string(p.first)] = p.second;
            }
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            output["item_stack"] = item_stack;
#else
            output["carried_item"] = carried_item;
#endif

            return output;
        }

    private:
        unsigned char container_id = 0;
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        int state_id = 0;
#endif
        short slot_num = 0;
        char button_num = 0;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        short uid = 0;
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        Slot item_stack;
#else
        Slot carried_item;
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        std::map<short, Slot> changed_slots;
#endif
        int click_type = 0;

    };
} //ProtocolCraft
