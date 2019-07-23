#pragma once

#include <string>

#include "botcraft/Protocol/Type.hpp"

namespace Botcraft
{
    class PlayerProperty : public Type
    {
    public:
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

    private:
        std::string name;
        std::string value;
        bool is_signed;
        std::string signature;
    };
}