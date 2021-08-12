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

        void SetSize(const int size_)
        {
            size = size_;
        }

        void SetCriteria(const std::map<Identifier, CriterionProgress>& criteria_)
        {
            criteria = criteria_;
        }


        const int GetSize() const
        {
            return size;
        }

        const std::map<Identifier, CriterionProgress>& GetCriteria() const
        {
            return criteria;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            size = ReadData<VarInt>(iter, length);
            criteria.clear();
            for (int i = 0; i < size; ++i)
            {
                Identifier identifier;
                identifier.Read(iter, length);
                criteria[identifier].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(size, container);
            for (auto it = criteria.begin(); it != criteria.end(); it++)
            {
                it->first.Write(container);
                it->second.Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["size"] = size;

            output["criteria"] = nlohmann::json::array();
            for (auto it = criteria.begin(); it != criteria.end(); ++it)
            {
                nlohmann::json crit;

                crit["criterion_identifier"] = it->first.Serialize();
                crit["criterion_progress"] = it->second.Serialize();
                output["criteria"].push_back(crit);
            }

            return output;
        }

    private:
        int size;
        std::map<Identifier, CriterionProgress> criteria;
    };
}