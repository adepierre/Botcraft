#pragma once

#if PROTOCOL_VERSION < 755 /* < 1.17 */
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    enum class SetBorderType
    {
        SetSize = 0,
        LerpSize = 1,
        SetCenter = 2,
        Initialize = 3,
        SetWarningTime = 4,
        SetWarningBlocks = 5
    };

    class ClientboundSetBorderPacket : public BaseMessage<ClientboundSetBorderPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x3D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Border";

        virtual ~ClientboundSetBorderPacket() override
        {

        }

        void SetAction(const SetBorderType action_)
        {
            action = action_;
        }

        void SetNewAbsoluteMaxSize(const int new_absolute_max_size_)
        {
            new_absolute_max_size = new_absolute_max_size_;
        }

        void SetNewCenterX(const double new_center_x_)
        {
            new_center_x = new_center_x_;
        }

        void SetNewCenterZ(const double new_center_z_)
        {
            new_center_z = new_center_z_;
        }

        void SetNewSize(const double new_size_)
        {
            new_size = new_size_;
        }

        void SetOldSize(const double old_size_)
        {
            old_size = old_size_;
        }

        void SetLerpTime(const long long int lerp_time_)
        {
            lerp_time = lerp_time_;
        }

        void SetWarningTime(const int warning_time_)
        {
            warning_time = warning_time_;
        }

        void SetWarningBlocks(const int warning_blocks_)
        {
            warning_blocks = warning_blocks_;
        }


        SetBorderType GetAction() const
        {
            return action;
        }

        int GetNewAbsoluteMaxSize() const
        {
            return new_absolute_max_size;
        }

        double GetNewCenterX() const
        {
            return new_center_x;
        }

        double GetNewCenterZ() const
        {
            return new_center_z;
        }

        double GetNewSize() const
        {
            return new_size;
        }

        double GetOldSize() const
        {
            return old_size;
        }

        long long int GetLerpTime() const
        {
            return lerp_time;
        }

        int GetWarningTime() const
        {
            return warning_time;
        }

        int GetWarningBlocks() const
        {
            return warning_blocks;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            action = static_cast<SetBorderType>(static_cast<int>(ReadData<VarInt>(iter, length)));
            switch (action)
            {
            case SetBorderType::SetSize:
                new_size = ReadData<double>(iter, length);
                break;
            case SetBorderType::LerpSize:
                old_size = ReadData<double>(iter, length);
                new_size = ReadData<double>(iter, length);
                lerp_time = ReadData<VarLong>(iter, length);
                break;
            case SetBorderType::SetCenter:
                new_center_x = ReadData<double>(iter, length);
                new_center_z = ReadData<double>(iter, length);
                break;
            case SetBorderType::Initialize:
                new_center_x = ReadData<double>(iter, length);
                new_center_z = ReadData<double>(iter, length);
                old_size = ReadData<double>(iter, length);
                new_size = ReadData<double>(iter, length);
                lerp_time = ReadData<VarLong>(iter, length);
                new_absolute_max_size = ReadData<VarInt>(iter, length);
                warning_time = ReadData<VarInt>(iter, length);
                warning_blocks = ReadData<VarInt>(iter, length);
                break;
            case SetBorderType::SetWarningTime:
                warning_time = ReadData<VarInt>(iter, length);
                break;
            case SetBorderType::SetWarningBlocks:
                warning_blocks = ReadData<VarInt>(iter, length);
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(static_cast<int>(action), container);
            switch (static_cast<SetBorderType>(action))
            {
            case SetBorderType::SetSize:
                WriteData<double>(new_size, container);
                break;
            case SetBorderType::LerpSize:
                WriteData<double>(old_size, container);
                WriteData<double>(new_size, container);
                WriteData<VarLong>(lerp_time, container);
                break;
            case SetBorderType::SetCenter:
                WriteData<double>(new_center_x, container);
                WriteData<double>(new_center_z, container);
                break;
            case SetBorderType::Initialize:
                WriteData<double>(new_center_x, container);
                WriteData<double>(new_center_z, container);
                WriteData<double>(old_size, container);
                WriteData<double>(new_size, container);
                WriteData<VarLong>(lerp_time, container);
                WriteData<VarInt>(new_absolute_max_size, container);
                WriteData<VarInt>(warning_time, container);
                WriteData<VarInt>(warning_blocks, container);
                break;
            case SetBorderType::SetWarningTime:
                WriteData<VarInt>(warning_time, container);
                break;
            case SetBorderType::SetWarningBlocks:
                WriteData<VarInt>(warning_blocks, container);
                break;
            default:
                break;
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["action"] = action;
            switch ((SetBorderType)action)
            {
            case SetBorderType::SetSize:
                output["new_size"] = new_size;
                break;
            case SetBorderType::LerpSize:
                output["old_size"] = old_size;
                output["new_size"] = new_size;
                output["lerp_time"] = lerp_time;
                break;
            case SetBorderType::SetCenter:
                output["new_center_x"] = new_center_x;
                output["new_center_z"] = new_center_z;
                break;
            case SetBorderType::Initialize:
                output["new_center_x"] = new_center_x;
                output["new_center_z"] = new_center_z;
                output["old_size"] = old_size;
                output["new_size"] = new_size;
                output["lerp_time"] = lerp_time;
                output["new_absolute_max_size"] = new_absolute_max_size;
                output["warning_time"] = warning_time;
                output["warning_blocks"] = warning_blocks;
                break;
            case SetBorderType::SetWarningTime:
                output["warning_time"] = warning_time;
                break;
            case SetBorderType::SetWarningBlocks:
                output["warning_blocks"] = warning_blocks;
                break;
            default:
                break;
            }

            return output;
        }

    private:
        SetBorderType action;
        int new_absolute_max_size = 0;
        double new_center_x = 0.0;
        double new_center_z = 0.0;
        double new_size = 0.0;
        double old_size = 0.0;
        long long int lerp_time = 0;
        int warning_blocks = 0;
        int warning_time = 0;

    };
} //ProtocolCraft
#endif
