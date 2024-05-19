#pragma once

#include <map>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/CriterionProgress.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class AdvancementProgress : public NetworkType
    {
    public:
        virtual ~AdvancementProgress() override
        {

        }

        void SetCriteria(const std::map<Identifier, CriterionProgress>& criteria_)
        {
            criteria = criteria_;
        }


        const std::map<Identifier, CriterionProgress>& GetCriteria() const
        {
            return criteria;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            criteria = ReadData<std::map<Identifier, CriterionProgress>>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::map<Identifier, CriterionProgress>>(criteria, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["criteria"] = Json::Array();
            for (const auto& p : criteria)
            {
                Json::Value crit;

                crit["criterion_identifier"] = p.first.Serialize();
                crit["criterion_progress"] = p.second.Serialize();
                output["criteria"].push_back(crit);
            }

            return output;
        }

    private:
        std::map<Identifier, CriterionProgress> criteria;
    };
}