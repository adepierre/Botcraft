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
            name = ReadData<std::string>(iter, length);
            value = ReadData<std::string>(iter, length);
            is_signed = ReadData<bool>(iter, length);
            if (is_signed)
            {
                signature = ReadData<std::string>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<std::string>(name, container);
            WriteData<std::string>(value, container);
            WriteData<bool>(is_signed, container);
            if (is_signed)
            {
                WriteData<std::string>(signature, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["name"] = name;
            output["value"] = value;
            output["is_signed"] = is_signed;
            output["signature"] = signature;

            return output;
        }

    private:
        std::string name;
        std::string value;
        bool is_signed;
        std::string signature;
    };
}