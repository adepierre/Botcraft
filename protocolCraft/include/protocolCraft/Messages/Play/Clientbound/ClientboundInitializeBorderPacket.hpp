#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundInitializeBorderPacket : public BaseMessage<ClientboundInitializeBorderPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x20;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Initialize Border";
        }

        virtual ~ClientboundInitializeBorderPacket() override
        {

        }

        void SetNewCenterX(const double new_center_x_)
        {
            new_center_x = new_center_x_;
        }

        void SetNewCenterZ(const double new_center_z_)
        {
            new_center_z = new_center_z_;
        }

        void SetOldSize(const double old_size_)
        {
            old_size = old_size_;
        }

        void SetNewSize(const double new_size_)
        {
            new_size = new_size_;
        }

        void SetLerpTime(const long long int lerp_time_)
        {
            lerp_time = lerp_time_;
        }

        void SetNewAbsoluteMaxSize(const int new_absolute_max_size_)
        {
            new_absolute_max_size = new_absolute_max_size_;
        }

        void SetWarningTime(const int warning_time_)
        {
            warning_time = warning_time_;
        }

        void SetWarningBlocks(const int warning_blocks_)
        {
            warning_blocks = warning_blocks_;
        }


        const double GetNewCenterX() const
        {
            return new_center_x;
        }

        const double GetNewCenterZ() const
        {
            return new_center_z;
        }

        const double GetOldSize() const
        {
            return old_size;
        }

        const double GetNewSize() const
        {
            return new_size;
        }

        const long long int GetLerpTime() const
        {
            return lerp_time;
        }

        const int GetNewAbsoluteMaxSize() const
        {
            return new_absolute_max_size;
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
            new_center_x = ReadData<double>(iter, length);
            new_center_z = ReadData<double>(iter, length);
            old_size = ReadData<double>(iter, length);
            new_size = ReadData<double>(iter, length);
            lerp_time = ReadData<VarLong>(iter, length);
            new_absolute_max_size = ReadData<VarInt>(iter, length);
            warning_blocks = ReadData<VarInt>(iter, length);
            warning_time = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<double>(new_center_x, container);
            WriteData<double>(new_center_z, container);
            WriteData<double>(old_size, container);
            WriteData<double>(new_size, container);
            WriteData<VarLong>(lerp_time, container);
            WriteData<VarInt>(new_absolute_max_size, container);
            WriteData<VarInt>(warning_blocks, container);
            WriteData<VarInt>(warning_time, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["new_center_x"] = picojson::value(new_center_x);
            object["new_center_z"] = picojson::value(new_center_z);
            object["old_size"] = picojson::value(old_size);
            object["new_size"] = picojson::value(new_size);
            object["lerp_time"] = picojson::value((double)lerp_time);
            object["new_absolute_max_size"] = picojson::value((double)new_absolute_max_size);
            object["warning_blocks"] = picojson::value((double)warning_blocks);
            object["warning_time"] = picojson::value((double)warning_time);

            return value;
        }

    private:
        double new_center_x;
        double new_center_z;
        double old_size;
        double new_size;
        long long int lerp_time;
        int new_absolute_max_size;
        int warning_blocks;
        int warning_time;

    };
} //ProtocolCraft
#endif