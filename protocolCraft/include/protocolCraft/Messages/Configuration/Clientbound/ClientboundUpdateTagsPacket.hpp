#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/BlockEntityTag.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateTagsConfigurationPacket : public BaseMessage<ClientboundUpdateTagsConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 765 /* < 1.20.3 */
        static constexpr int packet_id = 0x08;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x09;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x0D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Update Tags (Configuration)";

        virtual ~ClientboundUpdateTagsConfigurationPacket() override
        {

        }

        void SetTags(const std::map<Identifier, std::vector<BlockEntityTag> >& tags_)
        {
            tags = tags_;
        }

        const std::map<Identifier, std::vector<BlockEntityTag> >& GetTags() const
        {
            return tags;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            tags = ReadData<std::map<Identifier, std::vector<BlockEntityTag>>>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<std::map<Identifier, std::vector<BlockEntityTag>>>(tags, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["tags"] = Json::Object();
            for (const auto& p : tags)
            {
                output["tags"][p.first.GetFull()] = p.second;
            }

            return output;
        }

    private:
        std::map<Identifier, std::vector<BlockEntityTag> > tags;
    };
} //ProtocolCraft
#endif
