#pragma once

#if PROTOCOL_VERSION > 471
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class UpdateViewDistance : public BaseMessage<UpdateViewDistance>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x41;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x42;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x41;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update View Distance";
        }

        void SetViewDistance(const int view_distance_)
        {
            view_distance = view_distance_;
        }


        const int GetViewDistance() const
        {
            return view_distance;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            view_distance = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(view_distance, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["view_distance"] = picojson::value((double)view_distance);

            return value;
        }

    private:
        int view_distance;

    };
} //ProtocolCraft
#endif
