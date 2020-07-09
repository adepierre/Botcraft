#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class Effect : public BaseMessage<Effect>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x21;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x23;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x22;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x23;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x22;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Effect";
        }

        void SetEffectId(const int effect_id_)
        {
            effect_id = effect_id_;
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }

        void SetData(const int data_)
        {
            data = data_;
        }

        void SetDisableRelativeVolume(const bool disable_relative_volume_)
        {
            disable_relative_volume = disable_relative_volume_;
        }


        const int GetEffectId() const
        {
            return effect_id;
        }

        const NetworkPosition& GetLocation() const
        {
            return location;
        }

        const int GetData() const
        {
            return data;
        }

        const bool GetDisableRelativeVolume() const
        {
            return disable_relative_volume;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            effect_id = ReadData<int>(iter, length);
            location.Read(iter, length);
            data = ReadData<int>(iter, length);
            disable_relative_volume = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(effect_id, container);
            location.Write(container);
            WriteData<int>(data, container);
            WriteData<bool>(disable_relative_volume, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["effect_id"] = picojson::value((double)effect_id);
            object["location"] = location.Serialize();
            object["data"] = picojson::value((double)data);
            object["disable_relative_volume"] = picojson::value((double)disable_relative_volume);

            return value;
        }

    private:
        int effect_id;
        NetworkPosition location;
        int data;
        bool disable_relative_volume;

    };
} //ProtocolCraft