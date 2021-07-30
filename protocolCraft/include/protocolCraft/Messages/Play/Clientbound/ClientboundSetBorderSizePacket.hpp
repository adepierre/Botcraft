#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderSizePacket : public BaseMessage<ClientboundSetBorderSizePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x44;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Border Size";
        }

        virtual ~ClientboundSetBorderSizePacket() override
        {

        }


        void SetSize(const double size_)
        {
            size = size_;
        }


        const double GetSize() const
        {
            return size;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            size = ReadData<double>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<double>(size, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["size"] = picojson::value(size);

            return value;
        }

    private:
        double size;

    };
} //ProtocolCraft
#endif