#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundInitializeBorderPacket : public BaseMessage<ClientboundInitializeBorderPacket>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x1E;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Initialize Border";

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


        double GetNewCenterX() const
        {
            return new_center_x;
        }

        double GetNewCenterZ() const
        {
            return new_center_z;
        }

        double GetOldSize() const
        {
            return old_size;
        }

        double GetNewSize() const
        {
            return new_size;
        }

        long long int GetLerpTime() const
        {
            return lerp_time;
        }

        int GetNewAbsoluteMaxSize() const
        {
            return new_absolute_max_size;
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["new_center_x"] = new_center_x;
            output["new_center_z"] = new_center_z;
            output["old_size"] = old_size;
            output["new_size"] = new_size;
            output["lerp_time"] = lerp_time;
            output["new_absolute_max_size"] = new_absolute_max_size;
            output["warning_blocks"] = warning_blocks;
            output["warning_time"] = warning_time;

            return output;
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
