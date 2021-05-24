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

        void SetAchieved(const bool achieved_)
        {
            achieved = achieved_;
        }
        
        void SetDateOfAchieving(const long long int date_of_achieving_)
        {
            date_of_achieving = date_of_achieving_;
        }
    

        const bool GetAchieved() const
        {
            return achieved;
        }
        
        const long long int GetDateOfAchieving() const
        {
            return date_of_achieving;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            achieved = ReadData<bool>(iter, length);
            if (achieved)
            {
                date_of_achieving = ReadData<long long int>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<bool>(achieved, container);
            if (achieved)
            {
                WriteData<long long int>(date_of_achieving, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["achieved"] = picojson::value(achieved);
            if (achieved)
            {
                object["date_of_achieving"] = picojson::value((double)date_of_achieving);
            }

            return value;
        }

    private:
        bool achieved;
        long long int date_of_achieving;
    };
}