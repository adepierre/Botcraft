#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomSoundPacket : public BaseMessage<ClientboundCustomSoundPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x19;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x19;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x19;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x18;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x19;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Custom Sound";
        }

        virtual ~ClientboundCustomSoundPacket() override
        {

        }

        void SetName_(const std::string& name__)
        {
            name_ = name__;
        }

        void SetSource(const int source_)
        {
            source = source_;
        }

        void SetX(const int x_)
        {
            x = x_;
        }

        void SetY(const int y_)
        {
            y = y_;
        }

        void SetZ(const int z_)
        {
            z = z_;
        }

        void SetVolume(const float volume_)
        {
            volume = volume_;
        }

        void SetPitch(const float pitch_)
        {
            pitch = pitch_;
        }


        const std::string& GetName_() const
        {
            return name_;
        }

        const int GetSource() const
        {
            return source;
        }

        const int GetX() const
        {
            return x;
        }

        const int GetY() const
        {
            return y;
        }

        const int GetZ() const
        {
            return z;
        }

        const float GetVolume() const
        {
            return volume;
        }

        const float GetPitch() const
        {
            return pitch;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            name_ = ReadString(iter, length);
            source = ReadVarInt(iter, length);
            x = ReadData<int>(iter, length);
            y = ReadData<int>(iter, length);
            z = ReadData<int>(iter, length);
            volume = ReadData<float>(iter, length);
            pitch = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(name_, container);
            WriteVarInt(source, container);
            WriteData<int>(x, container);
            WriteData<int>(y, container);
            WriteData<int>(z, container);
            WriteData<float>(volume, container);
            WriteData<float>(pitch, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["name_"] = picojson::value(name_);
            object["source"] = picojson::value((double)source);
            object["x"] = picojson::value((double)x);
            object["y"] = picojson::value((double)y);
            object["z"] = picojson::value((double)z);
            object["volume"] = picojson::value((double)volume);
            object["pitch"] = picojson::value((double)pitch);

            return value;
        }

    private:
        std::string name_;
        int source;
        int x;
        int y;
        int z;
        float volume;
        float pitch;

    };
} //ProtocolCraft