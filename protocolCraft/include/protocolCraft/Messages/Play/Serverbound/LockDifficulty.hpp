#pragma once

#if PROTOCOL_VERSION > 463
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class LockDifficulty : public BaseMessage<LockDifficulty>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x10;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x10;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x11;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x11;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Lock Difficulty";
        }

        void SetLocked(const bool locked_)
        {
            locked = locked_;
        }


        const bool GetLocked() const
        {
            return locked;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            locked = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(locked, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["locked"] = picojson::value(locked);

            return value;
        }

    private:
        bool locked;

    };
} //ProtocolCraft
#endif
