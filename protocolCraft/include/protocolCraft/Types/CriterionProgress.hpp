#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class CriterionProgress : public NetworkType
    {
    public:
        virtual ~CriterionProgress() override
        {

        }

        
        void SetDateOfAchieving(const std::optional<long long int>& date_of_achieving_)
        {
            date_of_achieving = date_of_achieving_;
        }


        const std::optional<long long int>& GetDateOfAchieving() const
        {
            return date_of_achieving;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            date_of_achieving = ReadOptional<long long int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteOptional<long long int>(date_of_achieving, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            if (date_of_achieving.has_value())
            {
                output["date_of_achieving"] = date_of_achieving.value();
            }

            return output;
        }

    private:
        std::optional<long long int> date_of_achieving;
    };
}
