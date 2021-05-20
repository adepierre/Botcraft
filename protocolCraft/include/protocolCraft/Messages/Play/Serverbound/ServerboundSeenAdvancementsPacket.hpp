#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundSeenAdvancementsPacket : public BaseMessage<ServerboundSeenAdvancementsPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x19;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x20;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x20;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x21;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x22;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Seen Advancement";
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetTab(const Identifier& tab_)
        {
            tab = tab_;
        }


        const int GetAction() const
        {
            return action;
        }

        const Identifier& GetTab() const
        {
            return tab;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            action = ReadVarInt(iter, length);
            if (action == 0)
            {
                tab.Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(action, container);
            if (action == 0)
            {
                tab.Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["action"] = picojson::value((double)action);
            if (action == 0)
            {
                object["tab"] = tab.Serialize();
            }

            return value;
        }

    private:
        int action;
        Identifier tab;

    };
} //ProtocolCraft