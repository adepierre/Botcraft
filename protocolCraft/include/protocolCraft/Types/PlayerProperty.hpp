#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class PlayerProperty : public NetworkType
    {
    public:
        virtual ~PlayerProperty() override
        {

        }

        const std::string& GetName() const
        {
            return name;
        }

        const std::string& GetValue() const
        {
            return value;
        }

        const bool GetIsSigned() const
        {
            return is_signed;
        }

        const std::string& GetSignature() const
        {
            return signature;
        }

        void SetName(const std::string &s)
        {
            name = s;
        }

        void SetValue(const std::string &s)
        {
            value = s;
        }

        void SetIsSigned(const bool b)
        {
            is_signed = b;
        }

        void SetSignature(const std::string &s)
        {
            signature = s;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            name = ReadString(iter, length);
            value = ReadString(iter, length);
            is_signed = ReadData<bool>(iter, length);
            if (is_signed)
            {
                signature = ReadString(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteString(name, container);
            WriteString(value, container);
            WriteData<bool>(is_signed, container);
            if (is_signed)
            {
                WriteString(signature, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value val(picojson::object_type, false);
            picojson::object& object = val.get<picojson::object>();

            object["name"] = picojson::value(name);
            object["value"] = picojson::value(value);
            object["is_signed"] = picojson::value(is_signed);
            object["signature"] = picojson::value(signature);

            return val;
        }

    private:
        std::string name;
        std::string value;
        bool is_signed;
        std::string signature;
    };
}