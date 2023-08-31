#pragma once

#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/BlockEntityTag.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
#include <map>
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundUpdateTagsPacket : public BaseMessage<ClientboundUpdateTagsPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x5C;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */
        static constexpr int packet_id = 0x66;
#elif PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x67;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x68;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x6B;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x6A;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x6E;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Update Tags";

        virtual ~ClientboundUpdateTagsPacket() override
        {

        }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        void SetBlockTags(const std::vector<BlockEntityTag>& block_tags_)
        {
            block_tags = block_tags_;
        }

        void SetItemTags(const std::vector<BlockEntityTag>& item_tags_)
        {
            item_tags = item_tags_;
        }

        void SetFluidTags(const std::vector<BlockEntityTag>& fluid_tags_)
        {
            fluid_tags = fluid_tags_;
        }

#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
        void SetEntityTags(const std::vector<BlockEntityTag>& entity_tags_)
        {
            entity_tags = entity_tags_;
        }
#endif
#else
        void SetTags(const std::map<Identifier, std::vector<BlockEntityTag> >& tags_)
        {
            tags = tags_;
        }
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        const std::vector<BlockEntityTag>& GetBlockTags() const
        {
            return block_tags;
        }

        const std::vector<BlockEntityTag>& GetItemTags() const
        {
            return item_tags;
        }

        const std::vector<BlockEntityTag>& GetFluidTags() const
        {
            return fluid_tags;
        }

#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
        const std::vector<BlockEntityTag>& GetEntityTags() const
        {
            return entity_tags;
        }
#endif
#else
        const std::map<Identifier, std::vector<BlockEntityTag> >& GetTags() const
        {
            return tags;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            block_tags = ReadVector<BlockEntityTag>(iter, length);
            item_tags = ReadVector<BlockEntityTag>(iter, length);
            fluid_tags = ReadVector<BlockEntityTag>(iter, length);
#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
            entity_tags = ReadVector<BlockEntityTag>(iter, length);
#endif
#else
            tags = ReadMap<Identifier, std::vector<BlockEntityTag>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    const Identifier key = ReadData<Identifier>(i, l);
                    const std::vector<BlockEntityTag> val = ReadVector<BlockEntityTag>(i, l);

                    return std::make_pair(key, val);
                }
            );
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteVector<BlockEntityTag>(block_tags, container);
            WriteVector<BlockEntityTag>(item_tags, container);
            WriteVector<BlockEntityTag>(fluid_tags, container);
#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
            WriteVector<BlockEntityTag>(entity_tags, container);
#endif
#else
            WriteMap<Identifier, std::vector<BlockEntityTag>>(tags, container,
                [](const std::pair<const Identifier, std::vector<BlockEntityTag>>& p, WriteContainer& c)
                {
                    WriteData<Identifier>(p.first, c);
                    WriteVector<BlockEntityTag>(p.second, c);
                }
            );
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 755 /* < 1.17 */
            output["block_tags"] = block_tags;            
            output["item_tags"] = item_tags;            
            output["fluid_tags"] = fluid_tags;
#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
            output["entity_tags"] = entity_tags;
#endif
#else
            output["tags"] = Json::Object();
            
            for (const auto& p : tags)
            {
                output["tags"][p.first.GetFull()] = p.second;
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        std::vector<BlockEntityTag> block_tags;
        std::vector<BlockEntityTag> item_tags;
        std::vector<BlockEntityTag> fluid_tags;
#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
        std::vector<BlockEntityTag> entity_tags;
#endif
#else
        std::map<Identifier, std::vector<BlockEntityTag> > tags;
#endif

    };
} //ProtocolCraft
#endif
