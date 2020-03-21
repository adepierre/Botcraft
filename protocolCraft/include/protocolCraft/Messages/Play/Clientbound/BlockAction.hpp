#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class BlockAction : public BaseMessage<BlockAction>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0A;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x0B;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Block Action";
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }

        void SetActionId1(const unsigned char action_id_1_)
        {
            action_id_1 = action_id_1_;
        }

        void SetActionId2(const unsigned char action_id_2_)
        {
            action_id_2 = action_id_2_;
        }

        void SetBlockType(const int block_type_)
        {
            block_type = block_type_;
        }


        const NetworkPosition& GetLocation() const
        {
            return location;
        }

        const unsigned char GetActionId1() const
        {
            return action_id_1;
        }

        const unsigned char GetActionId2() const
        {
            return action_id_2;
        }

        const int GetBlockType() const
        {
            return block_type;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            location.Read(iter, length);
            action_id_1 = ReadData<unsigned char>(iter, length);
            action_id_2 = ReadData<unsigned char>(iter, length);
            block_type = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            location.Write(container);
            WriteData<unsigned char>(action_id_1, container);
            WriteData<unsigned char>(action_id_2, container);
            WriteVarInt(block_type, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["location"] = location.Serialize();
            object["action_id_1"] = picojson::value((double)action_id_1);
            object["action_id_2"] = picojson::value((double)action_id_2);
            object["block_type"] = picojson::value((double)block_type);

            return value;
        }

    private:
        NetworkPosition location;
        unsigned char action_id_1;
        unsigned char action_id_2;
        int block_type;

    };
} //ProtocolCraft