#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class NameItem : public BaseMessage<NameItem>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1C;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1E;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Name Item";
        }

        void SetItemName(const std::string& item_name_)
        {
            item_name = item_name_;
        }


        const std::string& GetItemName() const
        {
            return item_name;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            item_name = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(item_name, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["item_name"] = picojson::value(item_name);

            return value;
        }

    private:
        std::string item_name;

    };
} //ProtocolCraft
#endif
