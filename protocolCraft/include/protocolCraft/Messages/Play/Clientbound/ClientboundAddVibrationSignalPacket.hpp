#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/VibrationPath.hpp"

namespace ProtocolCraft
{
    class ClientboundAddVibrationSignalPacket : public BaseMessage<ClientboundAddVibrationSignalPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 // 1.17
            return 0x05;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Add Vibration Signal";
        }

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
            vibration_path.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            vibration_path.Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["vibration_path"] = vibration_path.Serialize();

            return value;
    }

    private:
        VibrationPath vibration_path;

    };
} //ProtocolCraft
#endif