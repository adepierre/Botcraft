#pragma once

#if PROTOCOL_VERSION < 755 || PROTOCOL_VERSION > 755
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveEntitiesPacket : public BaseMessage<ClientboundRemoveEntitiesPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x32;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 756 || PROTOCOL_VERSION == 757 ||  \
      PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x3E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Remove Entities";

        virtual ~ClientboundRemoveEntitiesPacket() override
        {

        }


        void SetEntityIds(const std::vector<int>& entity_ids_)
        {
            entity_ids = entity_ids_;
        }


        const std::vector<int>& GetEntityIds() const
        {
            return entity_ids;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_ids = ReadVector<int>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadData<VarInt>(i, l);
                }
            );
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVector<int>(entity_ids, container,
                [](const int& i, WriteContainer& c)
                {
                    WriteData<VarInt>(i, c);
                }
            );
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity_ids"] = entity_ids;

            return output;
        }

    private:
        std::vector<int> entity_ids;

    };
} //ProtocolCraft
#endif
