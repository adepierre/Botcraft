#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPongPacket : public BaseMessage<ServerboundPongPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 // 1.17
            return 0x1D;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Pong";
        }

        virtual ~ServerboundPongPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }


        const int GetId_() const
        {
            return id_;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(id_, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["id"] = picojson::value((double)id_);

            return value;
        }

    private:
        int id_;

    };
} //ProtocolCraft
#endif