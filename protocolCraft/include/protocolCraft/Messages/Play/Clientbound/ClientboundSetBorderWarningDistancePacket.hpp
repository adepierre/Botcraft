#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderWarningDistancePacket : public BaseMessage<ClientboundSetBorderWarningDistancePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x46;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Border Warning Distance";
        }

        virtual ~ClientboundSetBorderWarningDistancePacket() override
        {

        }


        void SetWarningBlocks(const int warning_blocks_)
        {
            warning_blocks = warning_blocks_;
        }


        const int GetWarningBlocks() const
        {
            return warning_blocks;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            warning_blocks = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(warning_blocks, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["warning_blocks"] = picojson::value((double)warning_blocks);

            return value;
        }

    private:
        int warning_blocks;

    };
} //ProtocolCraft
#endif