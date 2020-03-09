#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class LoginStart : public BaseMessage<LoginStart>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x00;
        }

        virtual const std::string GetName() const override
        {
            return "Login Start";
        }

        void SetName_(const std::string &n)
        {
            name_ = n;
        }

        const std::string& GetName_() const
        {
            return name_;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            name_ = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteString(name_, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["name_"] = picojson::value(name_);

            return value;
        }

    private:
        std::string name_;
    };
} // Botcraft