#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/AdvancementDisplay.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class Advancement : public NetworkType
    {
    public:
        virtual ~Advancement() override
        {

        }


        void SetParentId(const std::optional<Identifier>& parent_id_)
        {
            parent_id = parent_id_;
        }

        void SetDisplayData(const std::optional<AdvancementDisplay>& display_data_)
        {
            display_data = display_data_;
        }

        void SetCriteria(const std::vector<Identifier>& criteria_)
        {
            criteria = criteria_;
        }
        
        void SetRequirements(const std::vector<std::vector<std::string> >& requirements_)
        {
            requirements = requirements_;
        }


        const std::optional<Identifier>& GetParentId() const
        {
            return parent_id;
        }

        const std::optional<AdvancementDisplay>& GetDisplayData() const
        {
            return display_data;
        }

        const std::vector<Identifier>& GetCriteria() const
        {
            return criteria;
        }
        
        const std::vector<std::vector<std::string> >& GetRequirements() const
        {
            return requirements;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            parent_id = ReadOptional<Identifier>(iter, length);
            display_data = ReadOptional<AdvancementDisplay>(iter, length);
            criteria = ReadVector<Identifier>(iter, length);
            requirements = ReadVector<std::vector<std::string>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadVector<std::string>(i, l);
                }
            );
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteOptional<Identifier>(parent_id, container);
            WriteOptional<AdvancementDisplay>(display_data, container);
            WriteVector<Identifier>(criteria, container);
            WriteVector<std::vector<std::string>>(requirements, container,
                [](const std::vector<std::string>& v, WriteContainer& c)
                {
                    WriteVector<std::string>(v, c);
                }
            );
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            if (parent_id.has_value())
            {
                output["parent_id"] = parent_id.value().Serialize();
            }

            if (display_data.has_value())
            {
                output["display_data"] = display_data.value().Serialize();
            }
            
            output["criteria"] = Json::Array();
            for (const auto& c : criteria)
            {
                output["criteria"].push_back(c.Serialize());
            }
            
            output["requirements"] = Json::Array();
            for (const auto& r : requirements)
            {
                Json::Value current_array = Json::Array();
                for (const auto& r2 : r)
                {
                    current_array.push_back(r2);
                }
                output.push_back(current_array);
            }

            return output;
        }

    private:
        std::optional<Identifier> parent_id;
        std::optional<AdvancementDisplay> display_data;
        std::vector<Identifier> criteria;
        std::vector<std::vector<std::string> > requirements;
    };
}