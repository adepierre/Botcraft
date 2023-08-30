#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundPlaceGhostRecipePacket : public BaseMessage<ClientboundPlaceGhostRecipePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x2F;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x2F;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x33;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Place Ghost Recipe";

        virtual ~ClientboundPlaceGhostRecipePacket() override
        {

        }

        void SetContainerId(const char container_id_)
        {
            container_id = container_id_;
        }

#if PROTOCOL_VERSION < 348
        void SetRecipe(const int recipe_)
#else
        void SetRecipe(const Identifier& recipe_)
#endif
        {
            recipe = recipe_;
        }


        char GetContainerId() const
        {
            return container_id;
        }

#if PROTOCOL_VERSION < 348
        int GetRecipe() const
#else
        const Identifier& GetRecipe() const
#endif
        {
            return recipe;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<char>(iter, length);
#if PROTOCOL_VERSION < 348
            recipe = ReadData<VarInt>(iter, length);
#else
            recipe = ReadData<Identifier>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(container_id, container);
#if PROTOCOL_VERSION < 348
            WriteData<VarInt>(recipe, container);
#else
            WriteData<Identifier>(recipe, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
#if PROTOCOL_VERSION < 348
            output["recipe"] = recipe;
#else
            output["recipe"] = recipe;
#endif

            return output;
        }

    private:
        char container_id = 0;
#if PROTOCOL_VERSION < 348
        int recipe = 0;
#else
        Identifier recipe;
#endif

    };
} //ProtocolCraft
