#pragma once

#if PROTOCOL_VERSION > 471 /* > 1.13.2 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundSetJigsawBlockPacket : public BaseMessage<ServerboundSetJigsawBlockPacket>
    {
    public:
#if   PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */ || PROTOCOL_VERSION == 761 /* 1.19.3 */ ||  \
      PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x2F;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x30;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Jigsaw Block";

        virtual ~ServerboundSetJigsawBlockPacket() override
        {

        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
        void SetName_(const Identifier& name__)
        {
            name_ = name__;
        }

        void SetTarget(const Identifier& target_)
        {
            target = target_;
        }

        void SetPool(const Identifier& pool_)
        {
            pool = pool_;
        }
#else
        void SetAttachmentType(const Identifier& attachment_type_)
        {
            attachment_type = attachment_type_;
        }

        void SetTargetPool(const Identifier& target_pool_)
        {
            target_pool = target_pool_;
        }
#endif

        void SetFinalState(const std::string& final_state_)
        {
            final_state = final_state_;
        }

#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
        void SetJoint(const std::string& joint_)
        {
            joint = joint_;
        }
#endif


#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        void SetSelectionPriority(const int selection_priority_)
        {
            selection_priority = selection_priority_;
        }

        void SetPlacementPriority(const int placement_priority_)
        {
            placement_priority = placement_priority_;
        }
#endif


        const NetworkPosition& GetPos() const
        {
            return pos;
        }

#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
        const Identifier& GetName_() const
        {
            return name_;
        }

        const Identifier& GetTarget() const
        {
            return target;
        }
        
        const Identifier& GetPool() const
        {
            return pool;
        }
#else
        const Identifier& GetAttachmentType() const
        {
            return attachment_type;
        }

        const Identifier& GetTargetPool() const
        {
            return target_pool;
        }
#endif

        const std::string& GetFinalState() const
        {
            return final_state;
        }

#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
        const std::string& GetJoint() const
        {
            return joint;
        }
#endif

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        int GetSelectionPriority() const
        {
            return selection_priority;
        }

        int GetPlacementPriority() const
        {
            return placement_priority;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            pos = ReadData<NetworkPosition>(iter, length);
#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
            name_ = ReadData<Identifier>(iter, length);
            target = ReadData<Identifier>(iter, length);
            pool = ReadData<Identifier>(iter, length);
#else
            attachment_type = ReadData<Identifier>(iter, length);
            target_pool = ReadData<Identifier>(iter, length);
#endif
            final_state = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
            joint = ReadData<std::string>(iter, length);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            selection_priority = ReadData<VarInt>(iter, length);
            placement_priority = ReadData<VarInt>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<NetworkPosition>(pos, container);
#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
            WriteData<Identifier>(name_, container);
            WriteData<Identifier>(target, container);
            WriteData<Identifier>(pool, container);
#else
            WriteData<Identifier>(attachment_type, container);
            WriteData<Identifier>(target_pool, container);
#endif
            WriteData<std::string>(final_state, container);
#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
            WriteData<std::string>(joint, container);
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            WriteData<VarInt>(selection_priority, container);
            WriteData<VarInt>(placement_priority, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos;
#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
            output["name_"] = name_;
            output["target"] = target;
            output["pool"] = pool;
#else
            output["attachment_type"] = attachment_type;
            output["target_pool"] = target_pool;
#endif
            output["final_state"] = final_state;
#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
            output["joint"] = joint;
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
            output["selection_priority"] = selection_priority;
            output["placement_priority"] = placement_priority;
#endif

            return output;
        }

    private:
        NetworkPosition pos;
#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
        Identifier name_;
        Identifier target;
        Identifier pool;
#else
        Identifier attachment_type;
        Identifier target_pool;
#endif
        std::string final_state;
#if PROTOCOL_VERSION > 708 /* > 1.15.2 */
        std::string joint;
#endif
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        int selection_priority;
        int placement_priority;
#endif

    };
} //ProtocolCraft
#endif
