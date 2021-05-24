#pragma once

#include <map>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Advancement.hpp"
#include "protocolCraft/Types/AdvancementProgress.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateAdvancementsPacket : public BaseMessage<ClientboundUpdateAdvancementsPacket>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x57;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x57;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Advancements";
        }

        virtual ~ClientboundUpdateAdvancementsPacket() override
        {

        }

        void SetReset(const bool reset_)
        {
            reset = reset_;
        }

        void SetAdded(const std::map<Identifier, Advancement>& added_)
        {
            added = added_;
        }

        void SetRemoved(const std::vector<Identifier>& removed_)
        {
            removed = removed_;
        }

        void SetProgress(const std::map<Identifier, AdvancementProgress>& progress_)
        {
            progress = progress_;
        }


        const bool GetReset() const
        {
            return reset;
        }

        const std::map<Identifier, Advancement>& GetAdded() const
        {
            return added;
        }

        const std::vector<Identifier>& GetRemoved() const
        {
            return removed;
        }

        const std::map<Identifier, AdvancementProgress>& GetProgress() const
        {
            return progress;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            reset = ReadData<bool>(iter, length);
            const int added_size = ReadVarInt(iter, length);
            added.clear();
            for (int i = 0; i < added_size; ++i)
            {
                Identifier key;
                key.Read(iter, length);
                added[key].Read(iter, length);
            }
            const int removed_size = ReadVarInt(iter, length);
            removed = std::vector<Identifier>(removed_size);
            for (int i = 0; i < removed_size; ++i)
            {
                removed[i].Read(iter, length);
            }
            const int progress_size = ReadVarInt(iter, length);
            progress.clear();
            for (int i = 0; i < progress_size; ++i)
            {
                Identifier key;
                key.Read(iter, length);
                progress[key].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(reset, container);
            WriteVarInt(added.size(), container);
            for (auto it = added.begin(); it != added.end(); it++)
            {
                it->first.Write(container);
                it->second.Write(container);
            }
            WriteVarInt(removed.size(), container);
            for (int i = 0; i < removed.size(); ++i)
            {
                removed[i].Write(container);
            }
            WriteVarInt(progress.size(), container);
            for (auto it = progress.begin(); it != progress.end(); it++)
            {
                it->first.Write(container);
                it->second.Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["reset"] = picojson::value(reset);
            object["added"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["added"].get<picojson::array>();
            for (auto it = added.begin(); it != added.end(); ++it)
            {
                picojson::value value2(picojson::object_type, false);
                picojson::object& object2 = value2.get<picojson::object>();
                object2["key"] = it->first.Serialize();
                object2["value"] = it->second.Serialize();
                array.push_back(value2);
            }
            object["removed"] = picojson::value(picojson::array_type, false); 
            array = object["removed"].get<picojson::array>();
            for (int i = 0; i < removed.size(); ++i)
            {
                array.push_back(removed[i].Serialize());
            } 
            object["progress"] = picojson::value(picojson::array_type, false);
            array = object["progress"].get<picojson::array>();
            for (auto it = progress.begin(); it != progress.end(); ++it)
            {
                picojson::value value2(picojson::object_type, false);
                picojson::object& object2 = value2.get<picojson::object>();
                object2["key"] = it->first.Serialize();
                object2["value"] = it->second.Serialize();
                array.push_back(value2);
            }

            return value;
        }

    private:
        bool reset;
        std::map<Identifier, Advancement> added;
        std::vector<Identifier> removed;
        std::map<Identifier, AdvancementProgress> progress;

    };
} //ProtocolCraft