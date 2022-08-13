#pragma once

#if PROTOCOL_VERSION < 755 //1.17
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
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x38;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x3B;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x3D;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x3E;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x3D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x3D;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Border";
        }

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


        const SetBorderType GetAction() const
        {
            return action;
        }

        const int GetNewAbsoluteMaxSize() const
        {
            return new_absolute_max_size;
        }

        const double GetNewCenterX() const
        {
            return new_center_x;
        }

        const double GetNewCenterZ() const
        {
            return new_center_z;
        }

        const double GetNewSize() const
        {
            return new_size;
        }

        const double GetOldSize() const
        {
            return old_size;
        }

        const long long int GetLerpTime() const
        {
            return lerp_time;
        }

        const int GetWarningTime() const
        {
            return warning_time;
        }

        const int GetWarningBlocks() const
        {
            return warning_blocks;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            action = (SetBorderType)(int)ReadData<VarInt>(iter, length);
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
            WriteData<VarInt>((int)action, container);
            switch ((SetBorderType)action)
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

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
        int new_absolute_max_size;
        double new_center_x;
        double new_center_z;
        double new_size;
        double old_size;
        long long int lerp_time;
        int warning_blocks;
        int warning_time;

    };
} //ProtocolCraft
#endif