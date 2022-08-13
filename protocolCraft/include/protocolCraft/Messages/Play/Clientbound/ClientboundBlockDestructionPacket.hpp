#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockDestructionPacket : public BaseMessage<ClientboundBlockDestructionPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x08;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x08;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x08;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x09;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x08;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x08;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x09;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x09;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x06;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x06;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Block Break Animation";
        }

        virtual ~ClientboundBlockDestructionPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

        void SetProgress(const char progress_)
        {
            progress = progress_;
        }


        const int GetId_() const
        {
            return id_;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        const char GetProgress() const
        {
            return progress;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            pos.Read(iter, length);
            progress = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(id_, container);
            pos.Write(container);
            WriteData<char>(progress, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["id_"] = id_;
            output["pos"] = pos.Serialize();
            output["progress"] = progress;

            return output;
        }

    private:
        int id_;
        NetworkPosition pos;
        char progress;

    };
} //ProtocolCraft