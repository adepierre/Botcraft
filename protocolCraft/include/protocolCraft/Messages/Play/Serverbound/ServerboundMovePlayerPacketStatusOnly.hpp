#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketStatusOnly : public BaseMessage<ServerboundMovePlayerPacketStatusOnly>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x14;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Move Player Status Only";
        }

        virtual ~ServerboundMovePlayerPacketStatusOnly() override
        {

        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }


        const bool GetOnGround() const
        {
            return on_ground;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(on_ground, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["on_ground"] = picojson::value(on_ground);

            return value;
        }

    private:
        bool on_ground;

    };
} //ProtocolCraft
#endif