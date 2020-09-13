#pragma once

#if PROTOCOL_VERSION > 471
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class UpdateJigsawBlock : public BaseMessage<UpdateJigsawBlock>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x27;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x27;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x28;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2 or 1.16.3
            return 0x29;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Jigsaw Block";
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
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
        void SetJointType(const std::string& joint_type_)
        {
            joint_type = joint_type_;
        }
#endif

        const NetworkPosition& GetLocation() const
        {
            return location;
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
        const std::string& GetJointType() const
        {
            return joint_type;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            location.Read(iter, length);
#if PROTOCOL_VERSION > 708
            name_ = ReadString(iter, length);
            target = ReadString(iter, length);
            pool = ReadString(iter, length);
#else
            attachment_type = ReadString(iter, length);
            target_pool = ReadString(iter, length);
#endif
            final_state = ReadString(iter, length);
#if PROTOCOL_VERSION > 708
            joint_type = ReadString(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            location.Write(container);
#if PROTOCOL_VERSION > 708
            WriteString(name_, container);
            WriteString(target, container);
            WriteString(pool, container);
#else
            WriteString(attachment_type, container);
            WriteString(target_pool, container);
#endif
            WriteString(final_state, container);
#if PROTOCOL_VERSION > 708
            WriteString(joint_type, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["location"] = location.Serialize();
#if PROTOCOL_VERSION > 708
            object["name"] = picojson::value(name_);
            object["target"] = picojson::value(target);
            object["pool"] = picojson::value(pool);
#else
            object["attachment_type"] = picojson::value(attachment_type);
            object["target_pool"] = picojson::value(target_pool);
#endif
            object["final_state"] = picojson::value(final_state);
#if PROTOCOL_VERSION > 708
            object["joint_type"] = picojson::value(joint_type);
#endif

            return value;
        }

    private:
        NetworkPosition location;
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
        std::string joint_type;
#endif

    };
} //ProtocolCraft
#endif
