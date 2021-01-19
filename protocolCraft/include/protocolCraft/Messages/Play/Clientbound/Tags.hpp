#pragma once

#if PROTOCOL_VERSION > 348
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/BlockEntityTag.hpp"

namespace ProtocolCraft
{
    class Tags : public BaseMessage<Tags>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x5B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x5B;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Tags";
        }

        void SetBlockTagsLength(const int block_tags_length_)
        {
            block_tags_length = block_tags_length_;
        }

        void SetBlockTags(const std::vector<BlockEntityTag>& block_tags_)
        {
            block_tags = block_tags_;
        }

        void SetItemTagsLength(const int item_tags_length_)
        {
            item_tags_length = item_tags_length_;
        }

        void SetItemTags(const std::vector<BlockEntityTag>& item_tags_)
        {
            item_tags = item_tags_;
        }

        void SetFluidTagsLength(const int fluid_tags_length_)
        {
            fluid_tags_length = fluid_tags_length_;
        }

        void SetFluidTags(const std::vector<BlockEntityTag>& fluid_tags_)
        {
            fluid_tags = fluid_tags_;
        }

#if PROTOCOL_VERSION > 440
        void SetEntityTagsLength(const int entity_tags_length_)
        {
            entity_tags_length = entity_tags_length_;
        }

        void SetEntityTags(const std::vector<BlockEntityTag>& entity_tags_)
        {
            entity_tags = entity_tags_;
        }
#endif

        const int GetBlockTagsLength() const
        {
            return block_tags_length;
        }

        const std::vector<BlockEntityTag>& GetBlockTags() const
        {
            return block_tags;
        }

        const int GetItemTagsLength() const
        {
            return item_tags_length;
        }

        const std::vector<BlockEntityTag>& GetItemTags() const
        {
            return item_tags;
        }

        const int GetFluidTagsLength() const
        {
            return fluid_tags_length;
        }

        const std::vector<BlockEntityTag>& GetFluidTags() const
        {
            return fluid_tags;
        }

#if PROTOCOL_VERSION > 440
        const int GetEntityTagsLength() const
        {
            return entity_tags_length;
        }

        const std::vector<BlockEntityTag>& GetEntityTags() const
        {
            return entity_tags;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            block_tags_length = ReadVarInt(iter, length);
            block_tags = std::vector<BlockEntityTag>(block_tags_length);
            for (int i = 0; i < block_tags_length; ++i)
            {
                block_tags[i].Read(iter, length);
            }
            item_tags_length = ReadVarInt(iter, length);
            item_tags = std::vector<BlockEntityTag>(item_tags_length);
            for (int i = 0; i < item_tags_length; ++i)
            {
                item_tags[i].Read(iter, length);
            }
            fluid_tags_length = ReadVarInt(iter, length);
            fluid_tags = std::vector<BlockEntityTag>(fluid_tags_length);
            for (int i = 0; i < fluid_tags_length; ++i)
            {
                fluid_tags[i].Read(iter, length);
            }
#if PROTOCOL_VERSION > 440
            entity_tags_length = ReadVarInt(iter, length);
            entity_tags = std::vector<BlockEntityTag>(entity_tags_length);
            for (int i = 0; i < entity_tags_length; ++i)
            {
                entity_tags[i].Read(iter, length);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(block_tags_length, container);
            for (int i = 0; i < block_tags_length; ++i)
            {
                block_tags[i].Write(container);
            }
            WriteVarInt(item_tags_length, container);
            for (int i = 0; i < item_tags_length; ++i)
            {
                item_tags[i].Write(container);
            }
            WriteVarInt(fluid_tags_length, container);
            for (int i = 0; i < fluid_tags_length; ++i)
            {
                fluid_tags[i].Write(container);
            }
#if PROTOCOL_VERSION > 440
            WriteVarInt(entity_tags_length, container);
            for (int i = 0; i < entity_tags_length; ++i)
            {
                entity_tags[i].Write(container);
            }
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["block_tags_length"] = picojson::value((double)block_tags_length);
            object["block_tags"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["block_tags"].get<picojson::array>();
            for (int i = 0; i < block_tags_length; ++i)
            {
                array.push_back(block_tags[i].Serialize());
            }
            object["item_tags_length"] = picojson::value((double)item_tags_length);
            object["item_tags"] = picojson::value(picojson::array_type, false);
            array = object["item_tags"].get<picojson::array>();
            for (int i = 0; i < item_tags_length; ++i)
            {
                array.push_back(item_tags[i].Serialize());
            }
            object["fluid_tags_length"] = picojson::value((double)fluid_tags_length);
            object["fluid_tags"] = picojson::value(picojson::array_type, false);
            array = object["fluid_tags"].get<picojson::array>();
            for (int i = 0; i < fluid_tags_length; ++i)
            {
                array.push_back(fluid_tags[i].Serialize());
            }
#if PROTOCOL_VERSION > 440
            object["entity_tags_length"] = picojson::value((double)entity_tags_length);
            object["entity_tags"] = picojson::value(picojson::array_type, false);
            array = object["entity_tags"].get<picojson::array>();
            for (int i = 0; i < entity_tags_length; ++i)
            {
                array.push_back(entity_tags[i].Serialize());
            }
#endif

            return value;
        }

    private:
        int block_tags_length;
        std::vector<BlockEntityTag> block_tags;
        int item_tags_length;
        std::vector<BlockEntityTag> item_tags;
        int fluid_tags_length;
        std::vector<BlockEntityTag> fluid_tags;
#if PROTOCOL_VERSION > 440
        int entity_tags_length;
        std::vector<BlockEntityTag> entity_tags;
#endif

    };
} //ProtocolCraft
#endif
