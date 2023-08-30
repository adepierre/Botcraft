#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockDestructionPacket : public BaseMessage<ClientboundBlockDestructionPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 || PROTOCOL_VERSION == 393 ||  \
      PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 ||  \
      PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 759 || PROTOCOL_VERSION == 760 ||  \
      PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x07;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Block Break Animation";

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


        int GetId_() const
        {
            return id_;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        char GetProgress() const
        {
            return progress;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            pos = ReadData<NetworkPosition>(iter, length);
            progress = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteData<NetworkPosition>(pos, container);
            WriteData<char>(progress, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id_"] = id_;
            output["pos"] = pos;
            output["progress"] = progress;

            return output;
        }

    private:
        int id_ = 0;
        NetworkPosition pos;
        char progress = 0;

    };
} //ProtocolCraft
