#pragma once

#include <vector>
#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/EntityModifierData.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class EntityProperty : public NetworkType
    {
    public:
        virtual ~EntityProperty() override
        {

        }

#if PROTOCOL_VERSION > 709
        void SetKey(const Identifier& key_)
        {
            key = key_;
        }
#else
        void SetKey(const std::string& key_)
        {
            key = key_;
        }
#endif

        void SetValue(const double value_)
        {
            value = value_;
        }

        void SetNumberOfModifiers(const int number_of_modifiers_)
        {
            number_of_modifiers = number_of_modifiers_;
        }
        
        void SetModifiers(const std::vector<EntityModifierData>& modifiers_)
        {
            modifiers = modifiers_;
        }


#if PROTOCOL_VERSION > 709
        const Identifier& GetKey() const
        {
            return key;
        }
#else
        const std::string& GetKey() const
        {
            return key;
        }
#endif

        const double GetValue() const
        {
            return value;
        }

        const int GetNumberOfModifiers() const
        {
            return number_of_modifiers;
        }
        
        const std::vector<EntityModifierData>& GetModifiers() const
        {
            return modifiers;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION > 709
            key.Read(iter, length);
#else
            key = ReadData<std::string>(iter, length);
#endif
            value = ReadData<double>(iter, length);
            number_of_modifiers = ReadData<VarInt>(iter, length);
            modifiers = std::vector<EntityModifierData>(number_of_modifiers);
            for (int i = 0; i < number_of_modifiers; ++i)
            {
                modifiers[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION > 709
            key.Write(container);
#else
            WriteData<std::string>(key, container);
#endif
            WriteData<double>(value, container);
            WriteData<VarInt>(number_of_modifiers, container);
            for (int i = 0; i < number_of_modifiers; ++i)
            {
                modifiers[i].Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value val(picojson::object_type, false);
            picojson::object& object = val.get<picojson::object>();

#if PROTOCOL_VERSION > 709
            object["key"] = key.Serialize();
#else
            object["key"] = picojson::value(key);
#endif
            object["value"] = picojson::value((double)value);
            object["number_of_modifiers"] = picojson::value((double)number_of_modifiers);

            object["modifiers"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["modifiers"].get<picojson::array>();
            for (int i = 0; i < number_of_modifiers; ++i)
            {
                array.push_back(modifiers[i].Serialize());
            }

            return val;
        }

    private:
#if PROTOCOL_VERSION > 709
        Identifier key;
#else
        std::string key;
#endif
        double value;
        int number_of_modifiers;
        std::vector<EntityModifierData> modifiers;
    };
}