#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class Response : public BaseMessage<Response>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Response";
        }

        void SetJSONResponse(const std::string& json_response_)
        {
            json_response = json_response_;
        }

        const std::string& GetJSONResponse() const
        {
            return json_response;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            json_response = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteString(json_response, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["json_response"] = picojson::value(json_response);

            return value;
        }

    private:
        std::string json_response;
    };
} //ProtocolCraft