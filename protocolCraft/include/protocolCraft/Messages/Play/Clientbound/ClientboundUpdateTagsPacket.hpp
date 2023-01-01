#pragma once

#if PROTOCOL_VERSION > 348
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/BlockEntityTag.hpp"
#if PROTOCOL_VERSION > 754
#include <map>
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundUpdateTagsPacket : public BaseMessage<ClientboundUpdateTagsPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x55;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x5B;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x5C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x5B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x5B;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x66;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x67;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x68;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x6B;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x6A;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Tags";
        }

        virtual ~ClientboundUpdateTagsPacket() override
        {

        }

#if PROTOCOL_VERSION < 755
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

#if PROTOCOL_VERSION > 440
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

#if PROTOCOL_VERSION < 755
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

#if PROTOCOL_VERSION > 440
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
#if PROTOCOL_VERSION < 755
            int block_tags_length = ReadData<VarInt>(iter, length);
            block_tags = std::vector<BlockEntityTag>(block_tags_length);
            for (int i = 0; i < block_tags_length; ++i)
            {
                block_tags[i].Read(iter, length);
            }
            int item_tags_length = ReadData<VarInt>(iter, length);
            item_tags = std::vector<BlockEntityTag>(item_tags_length);
            for (int i = 0; i < item_tags_length; ++i)
            {
                item_tags[i].Read(iter, length);
            }
            int fluid_tags_length = ReadData<VarInt>(iter, length);
            fluid_tags = std::vector<BlockEntityTag>(fluid_tags_length);
            for (int i = 0; i < fluid_tags_length; ++i)
            {
                fluid_tags[i].Read(iter, length);
            }
#if PROTOCOL_VERSION > 440
            int entity_tags_length = ReadData<VarInt>(iter, length);
            entity_tags = std::vector<BlockEntityTag>(entity_tags_length);
            for (int i = 0; i < entity_tags_length; ++i)
            {
                entity_tags[i].Read(iter, length);
            }
#endif
#else
            tags.clear();
            const int tags_size = ReadData<VarInt>(iter, length);
            for (int i = 0; i < tags_size; ++i)
            {
                Identifier tag_type;
                tag_type = ReadData<Identifier>(iter, length);
                const int tags_array_size = ReadData<VarInt>(iter, length);
                std::vector<BlockEntityTag> tags_array = std::vector<BlockEntityTag>(tags_array_size);
                for (int j = 0; j < tags_array_size; ++j)
                {
                    tags_array[j].Read(iter, length);
                }
                tags[tag_type] = tags_array;
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 755
            WriteData<VarInt>(static_cast<int>(block_tags.size()), container);
            for (int i = 0; i < block_tags.size(); ++i)
            {
                block_tags[i].Write(container);
            }
            WriteData<VarInt>(static_cast<int>(item_tags.size()), container);
            for (int i = 0; i < item_tags.size(); ++i)
            {
                item_tags[i].Write(container);
            }
            WriteData<VarInt>(static_cast<int>(fluid_tags.size()), container);
            for (int i = 0; i < fluid_tags.size(); ++i)
            {
                fluid_tags[i].Write(container);
            }
#if PROTOCOL_VERSION > 440
            WriteData<VarInt>(static_cast<int>(entity_tags.size()), container);
            for (int i = 0; i < entity_tags.size(); ++i)
            {
                entity_tags[i].Write(container);
            }
#endif
#else
            WriteData<VarInt>(static_cast<int>(tags.size()), container);
            for (auto it = tags.begin(); it != tags.end(); ++it)
            {
                it->first.Write(container);
                WriteData<VarInt>(static_cast<int>(it->second.size()), container);
                for (int j = 0; j < it->second.size(); ++j)
                {
                    it->second[j].Write(container);
                }
            }
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION < 755
            output["block_tags"] = nlohmann::json::array();
            for (int i = 0; i < block_tags.size(); ++i)
            {
                output["block_tags"].push_back(block_tags[i].Serialize());
            }
            
            output["item_tags"] = nlohmann::json::array();
            for (int i = 0; i < item_tags.size(); ++i)
            {
                output["item_tags"].push_back(item_tags[i].Serialize());
            }
            
            output["fluid_tags"] = nlohmann::json::array();
            for (int i = 0; i < fluid_tags.size(); ++i)
            {
                output["fluid_tags"].push_back(fluid_tags[i].Serialize());
            }
#if PROTOCOL_VERSION > 440
            output["entity_tags"] = nlohmann::json::array();
            for (int i = 0; i < entity_tags.size(); ++i)
            {
                output["entity_tags"].push_back(entity_tags[i].Serialize());
            }
#endif
#else
            output["tags"] = nlohmann::json::object();
            
            for (auto it = tags.begin(); it != tags.end(); ++it)
            {
                output["tags"][it->first.GetFull()] = nlohmann::json::array();
                for (int i = 0; i < it->second.size(); ++it)
                {
                    output["tags"][it->first.GetFull()].push_back(it->second[i].Serialize());
                }
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 755
        std::vector<BlockEntityTag> block_tags;
        std::vector<BlockEntityTag> item_tags;
        std::vector<BlockEntityTag> fluid_tags;
#if PROTOCOL_VERSION > 440
        std::vector<BlockEntityTag> entity_tags;
#endif
#else
        std::map<Identifier, std::vector<BlockEntityTag> > tags;
#endif

    };
} //ProtocolCraft
#endif
