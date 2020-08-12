#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SteerBoat : public BaseMessage<SteerBoat>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x11;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x14;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x16;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x16;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x17;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x17;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Steer Boat";
        }

        void SetRightPaddleTurning(const bool right_paddle_turning_)
        {
            right_paddle_turning = right_paddle_turning_;
        }

        void SetLeftPaddleTurning(const bool left_paddle_turning_)
        {
            left_paddle_turning = left_paddle_turning_;
        }


        const bool GetRightPaddleTurning() const
        {
            return right_paddle_turning;
        }

        const bool GetLeftPaddleTurning() const
        {
            return left_paddle_turning;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            right_paddle_turning = ReadData<bool>(iter, length);
            left_paddle_turning = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(right_paddle_turning, container);
            WriteData<bool>(left_paddle_turning, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["right_paddle_turning"] = picojson::value(right_paddle_turning);
            object["left_paddle_turning"] = picojson::value(left_paddle_turning);

            return value;
        }

    private:
        bool right_paddle_turning;
        bool left_paddle_turning;

    };
} //ProtocolCraft