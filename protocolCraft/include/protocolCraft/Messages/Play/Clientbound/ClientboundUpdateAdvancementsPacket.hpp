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
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x4D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x51;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x57;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x62;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x63;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x64;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x67;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x65;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Update Advancements";

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


        bool GetReset() const
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
            added = ReadMap<Identifier, Advancement>(iter, length);
            removed = ReadVector<Identifier>(iter, length);
            progress = ReadMap<Identifier, AdvancementProgress, VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(reset, container);
            WriteMap<Identifier, Advancement>(added, container);
            WriteVector<Identifier>(removed, container);
            WriteMap<Identifier, AdvancementProgress>(progress, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["reset"] = reset;

            output["added"] = nlohmann::json::array();
            for (const auto& p : added)
            {
                nlohmann::json add;
                add["key"] = p.first.Serialize();
                add["value"] = p.second.Serialize();
                output["added"].push_back(add);
            }

            output["removed"] = nlohmann::json::array();
            for (const auto& r : removed)
            {
                output["removed"].push_back(r.Serialize());
            } 

            output["progress"] = nlohmann::json::array();
            for (const auto& p : progress)
            {
                nlohmann::json prog;
                prog["key"] = p.first.Serialize();
                prog["value"] = p.second.Serialize();
                output["progress"].push_back(prog);
            }

            return output;
        }

    private:
        bool reset;
        std::map<Identifier, Advancement> added;
        std::vector<Identifier> removed;
        std::map<Identifier, AdvancementProgress> progress;

    };
} //ProtocolCraft
