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

        void SetHasParent(const bool has_parent_)
        {
            has_parent = has_parent_;
        }

        void SetParentId(const Identifier& parent_id_)
        {
            parent_id = parent_id_;
        }

        void SetHasDisplay(const bool has_display_)
        {
            has_display = has_display_;
        }

        void SetDisplayData(const AdvancementDisplay& display_data_)
        {
            display_data = display_data_;
        }

        void SetNumberOfCriteria(const int number_of_criteria_)
        {
            number_of_criteria = number_of_criteria_;
        }

        void SetCriteria(const std::vector<Identifier>& criteria_)
        {
            criteria = criteria_;
        }

        void SetArrayLength(const int array_length_)
        {
            array_length = array_length_;
        }
        
        void SetRequirements(const std::vector<std::vector<std::string> >& requirements_)
        {
            requirements = requirements_;
        }


        const bool GetHasParent() const
        {
            return has_parent;
        }

        const Identifier& GetParentId() const
        {
            return parent_id;
        }

        const bool GetHasDisplay() const
        {
            return has_display;
        }

        const AdvancementDisplay& GetDisplayData() const
        {
            return display_data;
        }

        const int GetNumberOfCriteria() const
        {
            return number_of_criteria;
        }

        const std::vector<Identifier>& GetCriteria() const
        {
            return criteria;
        }

        const int GetArrayLength() const
        {
            return array_length;
        }
        
        const std::vector<std::vector<std::string> >& GetRequirements() const
        {
            return requirements;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            has_parent = ReadData<bool>(iter, length);
            if (has_parent)
            {
                parent_id.Read(iter, length);
            }
            has_display = ReadData<bool>(iter, length);
            if (has_display)
            {
                display_data.Read(iter, length);
            }
            number_of_criteria = ReadVarInt(iter, length);
            criteria = std::vector<Identifier>(number_of_criteria);
            for (int i = 0; i < number_of_criteria; ++i)
            {
                criteria[i].Read(iter, length);
            }
            array_length = ReadVarInt(iter, length);
            requirements = std::vector<std::vector<std::string> >(array_length);
            for (int i = 0; i < array_length; ++i)
            {
                const int array_length2 = ReadVarInt(iter, length);
                requirements[i] = std::vector<std::string>(array_length2);
                for (int j = 0; j < array_length2; ++j)
                {
                    requirements[i][j] = ReadString(iter, length);
                }
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<bool>(has_parent, container);
            if (has_parent)
            {
                parent_id.Write(container);
            }
            WriteData<bool>(has_display, container);
            if (has_display)
            {
                display_data.Write(container);
            }
            WriteVarInt(number_of_criteria, container);
            for (int i = 0; i < number_of_criteria; ++i)
            {
                criteria[i].Write(container);
            }
            WriteVarInt(array_length, container);
            for (int i = 0; i < array_length; ++i)
            {
                WriteVarInt(requirements[i].size(), container);
                for (int j = 0; j < requirements[i].size(); ++j)
                {
                    WriteString(requirements[i][j], container);
                }
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["has_parent"] = picojson::value(has_parent);
            if (has_parent)
            {
                object["parent_id"] = parent_id.Serialize();
            }
            object["has_display"] = picojson::value(has_display);
            if (has_display)
            {
                object["display_data"] = display_data.Serialize();
            }
            object["number_of_criteria"] = picojson::value((double)number_of_criteria);
            
            object["criteria"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["criteria"].get<picojson::array>();
            for (int i = 0; i < number_of_criteria; ++i)
            {
                array.push_back(criteria[i].Serialize());
            }

            object["array_length"] = picojson::value((double)array_length);
            
            object["requirements"] = picojson::value(picojson::array_type, false);
            array = object["requirements"].get<picojson::array>();
            for (int i = 0; i < array_length; ++i)
            {
                picojson::value sub_array = picojson::value(picojson::array_type, false);
                picojson::array& array2 = sub_array.get<picojson::array>();
                for (int j = 0; j < requirements[i].size(); ++j)
                {
                    array2.push_back(picojson::value(requirements[i][j]));
                }
                array.push_back(sub_array);
            }

            return value;
        }

    private:
        bool has_parent;
        Identifier parent_id;
        bool has_display;
        AdvancementDisplay display_data;
        int number_of_criteria;
        std::vector<Identifier> criteria;
        int array_length;
        std::vector<std::vector<std::string> > requirements;
    };
}