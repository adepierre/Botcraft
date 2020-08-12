#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    enum class WorldBorderAction
    {
        SetSize = 0,
        LerpSize = 1,
        SetCenter = 2,
        Initialize = 3,
        SetWarningTime = 4,
        SetWarningBlocks = 5
    };

    class WorldBorder : public BaseMessage<WorldBorder>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x3D;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x3D;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "World Border";
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetDiameter(const double diameter_)
        {
            diameter = diameter_;
        }

        void SetOldDiameter(const double old_diameter_)
        {
            old_diameter = old_diameter_;
        }

        void SetNewDiameter(const double new_diameter_)
        {
            new_diameter = new_diameter_;
        }

        void SetSpeed(const long long int speed_)
        {
            speed = speed_;
        }

        void SetX(const double x_)
        {
            x = x_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }

        void SetPortalTeleportBoundary(const int portal_teleport_boundary_)
        {
            portal_teleport_boundary = portal_teleport_boundary_;
        }

        void SetWarningTime(const int warning_time_)
        {
            warning_time = warning_time_;
        }

        void SetWarningBlocks(const int warning_blocks_)
        {
            warning_blocks = warning_blocks_;
        }


        const int GetAction() const
        {
            return action;
        }

        const double GetDiameter() const
        {
            return diameter;
        }

        const double GetOldDiameter() const
        {
            return old_diameter;
        }

        const double GetNewDiameter() const
        {
            return new_diameter;
        }

        const long long int GetSpeed() const
        {
            return speed;
        }

        const double GetX() const
        {
            return x;
        }

        const double GetZ() const
        {
            return z;
        }

        const int GetPortalTeleportBoundary() const
        {
            return portal_teleport_boundary;
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
            action = ReadVarInt(iter, length);
            switch ((WorldBorderAction)action)
            {
            case WorldBorderAction::SetSize:
                diameter = ReadData<double>(iter, length);
                break;
            case WorldBorderAction::LerpSize:
                old_diameter = ReadData<double>(iter, length);
                new_diameter = ReadData<double>(iter, length);
                speed = ReadVarLong(iter, length);
                break;
            case WorldBorderAction::SetCenter:
                x = ReadData<double>(iter, length);
                z = ReadData<double>(iter, length);
                break;
            case WorldBorderAction::Initialize:
                x = ReadData<double>(iter, length);
                z = ReadData<double>(iter, length);
                old_diameter = ReadData<double>(iter, length);
                new_diameter = ReadData<double>(iter, length);
                speed = ReadVarLong(iter, length);
                portal_teleport_boundary = ReadVarInt(iter, length);
                warning_time = ReadVarInt(iter, length);
                warning_blocks = ReadVarInt(iter, length);
                break;
            case WorldBorderAction::SetWarningTime:
                warning_time = ReadVarInt(iter, length);
                break;
            case WorldBorderAction::SetWarningBlocks:
                warning_blocks = ReadVarInt(iter, length);
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(action, container);
            switch ((WorldBorderAction)action)
            {
            case WorldBorderAction::SetSize:
                WriteData<double>(diameter, container);
                break;
            case WorldBorderAction::LerpSize:
                WriteData<double>(old_diameter, container);
                WriteData<double>(new_diameter, container);
                WriteVarLong(speed, container);
                break;
            case WorldBorderAction::SetCenter:
                WriteData<double>(x, container);
                WriteData<double>(z, container);
                break;
            case WorldBorderAction::Initialize:
                WriteData<double>(x, container);
                WriteData<double>(z, container);
                WriteData<double>(old_diameter, container);
                WriteData<double>(new_diameter, container);
                WriteVarLong(speed, container);
                WriteVarInt(portal_teleport_boundary, container);
                WriteVarInt(warning_time, container);
                WriteVarInt(warning_blocks, container);
                break;
            case WorldBorderAction::SetWarningTime:
                WriteVarInt(warning_time, container);
                break;
            case WorldBorderAction::SetWarningBlocks:
                WriteVarInt(warning_blocks, container);
                break;
            default:
                break;
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["action"] = picojson::value((double)action);
            switch ((WorldBorderAction)action)
            {
            case WorldBorderAction::SetSize:
                object["diameter"] = picojson::value(diameter);
                break;
            case WorldBorderAction::LerpSize:
                object["old_diameter"] = picojson::value(old_diameter);
                object["new_diameter"] = picojson::value(new_diameter);
                object["speed"] = picojson::value((double)speed);
                break;
            case WorldBorderAction::SetCenter:
                object["x"] = picojson::value(x);
                object["z"] = picojson::value(z);
                break;
            case WorldBorderAction::Initialize:
                object["x"] = picojson::value(x);
                object["z"] = picojson::value(z);
                object["old_diameter"] = picojson::value(old_diameter);
                object["new_diameter"] = picojson::value(new_diameter);
                object["speed"] = picojson::value((double)speed);
                object["portal_teleport_boundary"] = picojson::value((double)portal_teleport_boundary);
                object["warning_time"] = picojson::value((double)warning_time);
                object["warning_blocks"] = picojson::value((double)warning_blocks);
                break;
            case WorldBorderAction::SetWarningTime:
                object["warning_time"] = picojson::value((double)warning_time);
                break;
            case WorldBorderAction::SetWarningBlocks:
                object["warning_blocks"] = picojson::value((double)warning_blocks);
                break;
            default:
                break;
            }

            return value;
        }

    private:
        int action;
        double diameter;
        double old_diameter;
        double new_diameter;
        long long int speed;
        double x;
        double z;
        int portal_teleport_boundary;
        int warning_time;
        int warning_blocks;

    };
} //ProtocolCraft