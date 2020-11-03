#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SetPassengers : public BaseMessage<SetPassengers>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x43;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x46;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x4A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x4B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x4B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x4B;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Passengers";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetPassengerCount(const int passenger_count_)
        {
            passenger_count = passenger_count_;
        }

        void SetPassengers_(const std::vector<int>& passengers__)
        {
            passengers_ = passengers__;
        }


        const int GetEntityId() const
        {
            return entity_id;
        }

        const int GetPassengerCount() const
        {
            return passenger_count;
        }

        const std::vector<int>& GetPassengers_() const
        {
            return passengers_;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            passenger_count = ReadVarInt(iter, length);
            passengers_ = std::vector<int>(passenger_count);
            for (int i = 0; i < passenger_count; ++i)
            {
                passengers_[i] = ReadVarInt(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteVarInt(passenger_count, container);
            for (int i = 0; i < passenger_count; ++i)
            {
                WriteVarInt(passengers_[i], container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["passenger_count"] = picojson::value((double)passenger_count);

            object["passengers"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["passengers"].get<picojson::array>();

            for (int i = 0; i < passengers_.size(); ++i)
            {
                array.push_back(picojson::value((double)passengers_[i]));
            }

            return value;
        }

    private:
        int entity_id;
        int passenger_count;
        std::vector<int> passengers_;

    };
} //ProtocolCraft