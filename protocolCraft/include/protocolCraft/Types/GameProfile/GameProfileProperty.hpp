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

        void SetSignature(const std::string& signature_)
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

        const std::string& GetSignature() const
        {
            return signature;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            name = ReadData<std::string>(iter, length);
            value = ReadData<std::string>(iter, length);

            if (ReadData<bool>(iter, length))
            {
                signature = ReadData<std::string>(iter, length);
            }
            else
            {
                signature = "";
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::string>(name, container);
            WriteData<std::string>(value, container);
            if (signature.empty())
            {
                WriteData<bool>(false, container);
            }
            else
            {
                WriteData<bool>(true, container);
                WriteData<std::string>(signature, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["name"] = name;
            output["value"] = value;
            if (!signature.empty())
            {
                output["signature"] = signature;
            }


            return output;
        }

    private:
        std::string name;
        std::string value;
        std::string signature;
    };
} // ProtocolCraft
