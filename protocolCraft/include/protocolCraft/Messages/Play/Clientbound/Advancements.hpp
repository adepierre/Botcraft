#pragma once

#include <map>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Advancement.hpp"
#include "protocolCraft/Types/AdvancementProgress.hpp"

namespace ProtocolCraft
{
    class Advancements : public BaseMessage<Advancements>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x4D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x51;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x57;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x58;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Advancements";
        }

        void SetResetClear(const bool reset_clear_)
        {
            reset_clear = reset_clear_;
        }

        void SetMappingSize(const int mapping_size_)
        {
            mapping_size = mapping_size_;
        }

        void SetAdvancementMapping(const std::map<Identifier, Advancement>& advancement_mapping_)
        {
            advancement_mapping = advancement_mapping_;
        }

        void SetListSize(const int list_size_)
        {
            list_size = list_size_;
        }

        void SetIdentifiers(const std::vector<Identifier>& identifiers_)
        {
            identifiers = identifiers_;
        }

        void SetProgressSize(const int progress_size_)
        {
            progress_size = progress_size_;
        }

        void SetProgressMapping(const std::map<Identifier, AdvancementProgress>& progress_mapping_)
        {
            progress_mapping = progress_mapping_;
        }


        const bool GetResetClear() const
        {
            return reset_clear;
        }

        const int GetMappingSize() const
        {
            return mapping_size;
        }

        const std::map<Identifier, Advancement>& GetAdvancementMapping() const
        {
            return advancement_mapping;
        }

        const int GetListSize() const
        {
            return list_size;
        }

        const std::vector<Identifier>& GetIdentifiers() const
        {
            return identifiers;
        }

        const int GetProgressSize() const
        {
            return progress_size;
        }

        const std::map<Identifier, AdvancementProgress>& GetProgressMapping() const
        {
            return progress_mapping;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            reset_clear = ReadData<bool>(iter, length);
            mapping_size = ReadVarInt(iter, length);
            advancement_mapping.clear();
            for (int i = 0; i < mapping_size; ++i)
            {
                const Identifier key = ReadString(iter, length);
                advancement_mapping[key].Read(iter, length);
            }
            list_size = ReadVarInt(iter, length);
            identifiers = std::vector<Identifier>(list_size);
            for (int i = 0; i < list_size; ++i)
            {
                identifiers[i] = ReadString(iter, length);
            }
            progress_size = ReadVarInt(iter, length);
            progress_mapping.clear();
            for (int i = 0; i < progress_size; ++i)
            {
                const Identifier key = ReadString(iter, length);
                progress_mapping[key].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(reset_clear, container);
            WriteVarInt(mapping_size, container);
            for (auto it = advancement_mapping.begin(); it != advancement_mapping.end(); it++)
            {
                WriteString(it->first, container);
                it->second.Write(container);
            }
            WriteVarInt(list_size, container);
            for (int i = 0; i < list_size; ++i)
            {
                WriteString(identifiers[i], container);
            }
            WriteVarInt(progress_size, container);
            for (auto it = progress_mapping.begin(); it != progress_mapping.end(); it++)
            {
                WriteString(it->first, container);
                it->second.Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["reset_clear"] = picojson::value(reset_clear);
            object["mapping_size"] = picojson::value((double)mapping_size);
            object["advancement_mapping"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["advancement_mapping"].get<picojson::array>();
            for (auto it = advancement_mapping.begin(); it != advancement_mapping.end(); ++it)
            {
                picojson::value value2(picojson::object_type, false);
                picojson::object& object2 = value2.get<picojson::object>();
                object2["key"] = picojson::value(it->first);
                object2["value"] = it->second.Serialize();
                array.push_back(value2);
            }
            object["list_size"] = picojson::value((double)list_size);
            object["identifiers"] = picojson::value(picojson::array_type, false); 
            array = object["identifiers"].get<picojson::array>();
            for (int i = 0; i < list_size; ++i)
            {
                array.push_back(picojson::value(identifiers[i]));
            }
            object["progress_size"] = picojson::value((double)progress_size); 
            object["progress_mapping"] = picojson::value(picojson::array_type, false);
            array = object["progress_mapping"].get<picojson::array>();
            for (auto it = progress_mapping.begin(); it != progress_mapping.end(); ++it)
            {
                picojson::value value2(picojson::object_type, false);
                picojson::object& object2 = value2.get<picojson::object>();
                object2["key"] = picojson::value(it->first);
                object2["value"] = it->second.Serialize();
                array.push_back(value2);
            }

            return value;
        }

    private:
        bool reset_clear;
        int mapping_size;
        std::map<Identifier, Advancement> advancement_mapping;
        int list_size;
        std::vector<Identifier> identifiers;
        int progress_size;
        std::map<Identifier, AdvancementProgress> progress_mapping;

    };
} //ProtocolCraft