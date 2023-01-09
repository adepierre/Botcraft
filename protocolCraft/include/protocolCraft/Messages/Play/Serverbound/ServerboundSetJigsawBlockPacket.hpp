#pragma once

#if PROTOCOL_VERSION > 471
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundSetJigsawBlockPacket : public BaseMessage<ServerboundSetJigsawBlockPacket>
    {
    public:
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x2C;
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

#if PROTOCOL_VERSION > 708
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

#if PROTOCOL_VERSION > 708
        void SetJoint(const std::string& joint_)
        {
            joint = joint_;
        }
#endif

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

#if PROTOCOL_VERSION > 708
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

#if PROTOCOL_VERSION > 708
        const std::string& GetJoint() const
        {
            return joint;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            pos = ReadData<NetworkPosition>(iter, length);
#if PROTOCOL_VERSION > 708
            name_ = ReadData<Identifier>(iter, length);
            target = ReadData<Identifier>(iter, length);
            pool = ReadData<Identifier>(iter, length);
#else
            attachment_type = ReadData<Identifier>(iter, length);
            target_pool = ReadData<Identifier>(iter, length);
#endif
            final_state = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 708
            joint = ReadData<std::string>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<NetworkPosition>(pos, container);
#if PROTOCOL_VERSION > 708
            WriteData<Identifier>(name_, container);
            WriteData<Identifier>(target, container);
            WriteData<Identifier>(pool, container);
#else
            WriteData<Identifier>(attachment_type, container);
            WriteData<Identifier>(target_pool, container);
#endif
            WriteData<std::string>(final_state, container);
#if PROTOCOL_VERSION > 708
            WriteData<std::string>(joint, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos.Serialize();
#if PROTOCOL_VERSION > 708
            output["name_"] = name_.Serialize();
            output["target"] = target.Serialize();
            output["pool"] = pool.Serialize();
#else
            output["attachment_type"] = attachment_type.Serialize();
            output["target_pool"] = target_pool.Serialize();
#endif
            output["final_state"] = final_state;
#if PROTOCOL_VERSION > 708
            output["joint"] = joint;
#endif

            return output;
        }

    private:
        NetworkPosition pos;
#if PROTOCOL_VERSION > 708
        Identifier name_;
        Identifier target;
        Identifier pool;
#else
        Identifier attachment_type;
        Identifier target_pool;
#endif
        std::string final_state;
#if PROTOCOL_VERSION > 708
        std::string joint;
#endif

    };
} //ProtocolCraft
#endif
