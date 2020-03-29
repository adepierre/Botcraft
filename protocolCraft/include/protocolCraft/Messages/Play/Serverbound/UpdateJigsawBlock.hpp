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

        void SetAttachmentType(const Identifier& attachment_type_)
        {
            attachment_type = attachment_type_;
        }

        void SetTargetPool(const Identifier& target_pool_)
        {
            target_pool = target_pool_;
        }

        void SetFinalState(const std::string& final_state_)
        {
            final_state = final_state_;
        }


        const NetworkPosition& GetLocation() const
        {
            return location;
        }

        const Identifier& GetAttachmentType() const
        {
            return attachment_type;
        }

        const Identifier& GetTargetPool() const
        {
            return target_pool;
        }

        const std::string& GetFinalState() const
        {
            return final_state;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            location.Read(iter, length);
            attachment_type = ReadString(iter, length);
            target_pool = ReadString(iter, length);
            final_state = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            location.Write(container);
            WriteString(attachment_type, container);
            WriteString(target_pool, container);
            WriteString(final_state, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["location"] = location.Serialize();
            object["attachment_type"] = picojson::value(attachment_type);
            object["target_pool"] = picojson::value(target_pool);
            object["final_state"] = picojson::value(final_state);

            return value;
        }

    private:
        NetworkPosition location;
        Identifier attachment_type;
        Identifier target_pool;
        std::string final_state;

    };
} //ProtocolCraft
#endif
