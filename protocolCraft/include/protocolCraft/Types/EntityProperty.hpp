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

        double GetValue() const
        {
            return value;
        }
        
        const std::vector<EntityModifierData>& GetModifiers() const
        {
            return modifiers;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
#if PROTOCOL_VERSION > 709
            key = ReadData<Identifier>(iter, length);
#else
            key = ReadData<std::string>(iter, length);
#endif
            value = ReadData<double>(iter, length);
            modifiers = ReadVector<EntityModifierData>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
#if PROTOCOL_VERSION > 709
            WriteData<Identifier>(key, container);
#else
            WriteData<std::string>(key, container);
#endif
            WriteData<double>(value, container);
            WriteVector<EntityModifierData>(modifiers, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["key"] = key;
            output["value"] = value;
            output["modifiers"] = modifiers;

            return output;
        }

    private:
#if PROTOCOL_VERSION > 709
        Identifier key;
#else
        std::string key;
#endif
        double value = 0.0;
        std::vector<EntityModifierData> modifiers;
    };
}
