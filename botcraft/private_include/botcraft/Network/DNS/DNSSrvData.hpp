#pragma once

#include "protocolCraft/NetworkType.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    class DNSSrvData : public NetworkType
    {
    public:
        const unsigned short GetPriority() const
        {
            return priority;
        }

        const unsigned short GetWeight() const
        {
            return weight;
        }

        const unsigned short GetPort() const
        {
            return port;
        }

        const std::vector<std::string>& GetNameLabels() const
        {
            return name_labels;
        }


        void SetPriority(const unsigned short priority_)
        {
            priority = priority_;
        }

        void SetWeight(const unsigned short weight_)
        {
            weight = weight_;
        }

        void SetPort(const unsigned short port_)
        {
            port = port_;
        }

        void SetNameLabels(const std::vector<std::string>& name_labels_)
        {
            name_labels = name_labels_;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            priority = ReadData<unsigned short>(iter, length);
            weight = ReadData<unsigned short>(iter, length);
            port = ReadData<unsigned short>(iter, length);

            // There is no compression for srv answer data
            std::string label;
            unsigned char label_len = ReadData<unsigned char>(iter, length);
            while (label_len != 0)
            {
                label = ReadRawString(iter, length, label_len);
                label_len = ReadData<unsigned char>(iter, length);
                name_labels.push_back(label);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

            WriteData<unsigned short>(priority, container);
            WriteData<unsigned short>(weight, container);
            WriteData<unsigned short>(port, container);

            for (int i = 0; i < name_labels.size(); ++i)
            {
                WriteData<unsigned char>(static_cast<unsigned char>(name_labels[i].size()), container);
                WriteRawString(name_labels[i], container);
            }
            WriteData<unsigned char>(0, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["priority"] = priority;
            output["weight"] = weight;
            output["port"] = port;

            std::string name = "";
            for (int i = 0; i < name_labels.size(); ++i)
            {
                name += name_labels[i] + ".";
            }
            output["target"] = name;

            return output;
        }

    private:
        unsigned short priority;
        unsigned short weight;
        unsigned short port;
        std::vector<std::string> name_labels;
    };
}
