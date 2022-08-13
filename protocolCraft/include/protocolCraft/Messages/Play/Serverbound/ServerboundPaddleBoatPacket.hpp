#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPaddleBoatPacket : public BaseMessage<ServerboundPaddleBoatPacket>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x17;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x17;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x16;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x16;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x18;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x19;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Paddle Boat";
        }

        virtual ~ServerboundPaddleBoatPacket() override
        {

        }

        void SetLeft(const bool left_)
        {
            left = left_;
        }

        void SetRight(const bool right_)
        {
            right = right_;
        }


        const bool GetLeft() const
        {
            return left;
        }

        const bool GetRight() const
        {
            return right;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            left = ReadData<bool>(iter, length);
            right = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(left, container);
            WriteData<bool>(right, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["left"] = left;
            output["right"] = right;

            return output;
        }

    private:
        bool left;
        bool right;

    };
} //ProtocolCraft