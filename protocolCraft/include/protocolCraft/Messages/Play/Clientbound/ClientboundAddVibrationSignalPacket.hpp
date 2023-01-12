#if PROTOCOL_VERSION > 754 && PROTOCOL_VERSION < 759
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Vibrations/VibrationPath.hpp"

namespace ProtocolCraft
{
    class ClientboundAddVibrationSignalPacket : public BaseMessage<ClientboundAddVibrationSignalPacket>
    {
    public:
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x05;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Add Vibration Signal";

        virtual ~ClientboundAddVibrationSignalPacket() override
        {

        }


        void SetVibrationPath(const VibrationPath& vibration_path_)
        {
            vibration_path = vibration_path_;
        }

        
        const VibrationPath& GetVibrationPath() const
        {
            return vibration_path;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            vibration_path = ReadData<VibrationPath>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VibrationPath>(vibration_path, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["vibration_path"] = vibration_path;

            return output;
    }

    private:
        VibrationPath vibration_path;

    };
} //ProtocolCraft
#endif
