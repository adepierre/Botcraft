#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <string>

namespace ProtocolCraft 
{
    class GameProfileProperty : public NetworkType
    {
    public:

        GameProfileProperty()
        {

        }

        virtual ~GameProfileProperty() override
        {

        }

        void SetName(const std::string& name_)
        {
            name = name_;
        }

        void SetValue(const std::string& value_)
        {
            value = value_;
        }

        void SetSignature(const std::optional<std::string>& signature_)
        {
            signature = signature_;
        }


        const std::string& GetName() const
        {
            return name;
        }

        const std::string& GetValue() const
        {
            return value;
        }

        const std::optional<std::string>& GetSignature() const
        {
            return signature;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            name = ReadData<std::string>(iter, length);
            value = ReadData<std::string>(iter, length);
            signature = ReadOptional<std::string>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(name, container);
            WriteData<std::string>(value, container);
            WriteOptional<std::string>(signature, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["name"] = name;
            output["value"] = value;
            if (signature.has_value())
            {
                output["signature"] = signature.value();
            }


            return output;
        }

    private:
        std::string name;
        std::string value;
        std::optional<std::string> signature;
    };
} // ProtocolCraft
