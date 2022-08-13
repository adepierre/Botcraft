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
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x44;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x43;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x46;
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["size"] = size;

            return output;
        }

    private:
        double size;

    };
} //ProtocolCraft
#endif