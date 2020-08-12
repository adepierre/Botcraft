#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SelectAdvancementTab : public BaseMessage<SelectAdvancementTab>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x37;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x3A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x3C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x3D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x3C;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x3C;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Select Advancement Tab";
        }

        void SetHasId(const bool has_id_)
        {
            has_id = has_id_;
        }

        void SetIdentifier(const std::string& identifier_)
        {
            identifier = identifier_;
        }


        const bool GetHasId() const
        {
            return has_id;
        }

        const std::string& GetIdentifier() const
        {
            return identifier;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            has_id = ReadData<bool>(iter, length);
            if (has_id)
            {
                identifier = ReadString(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(has_id, container);
            if (has_id)
            {
                WriteString(identifier, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["has_id"] = picojson::value((double)has_id);
            if (has_id)
            {
                object["identifier"] = picojson::value(identifier);
            }

            return value;
        }

    private:
        bool has_id;
        std::string identifier;

    };
} //ProtocolCraft