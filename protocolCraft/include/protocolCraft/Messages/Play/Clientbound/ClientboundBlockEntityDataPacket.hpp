#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockEntityDataPacket : public BaseMessage<ClientboundBlockEntityDataPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x09;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x09;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x09;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x0A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x09;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x09;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x0A;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Block Entity Data";
        }

        virtual ~ClientboundBlockEntityDataPacket() override
        {

        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

        void SetType(const unsigned char type_)
        {
            type = type_;
        }

        void SetTag(const NBT& tag_)
        {
            tag = tag_;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        const unsigned char GetType() const
        {
            return type;
        }

        const NBT& GetTag() const
        {
            return tag;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            pos.Read(iter, length);
            type = ReadData<unsigned char>(iter, length);
            tag.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            pos.Write(container);
            WriteData<unsigned char>(type, container);
            tag.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["pos"] = pos.Serialize();
            output["type"] = type;
            output["tag"] = tag.Serialize();

            return output;
        }

    private:
        NetworkPosition pos;
        unsigned char type;
        NBT tag;
    };
} //ProtocolCraft