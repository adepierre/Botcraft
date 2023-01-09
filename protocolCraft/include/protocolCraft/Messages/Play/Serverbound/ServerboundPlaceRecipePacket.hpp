#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundPlaceRecipePacket : public BaseMessage<ServerboundPlaceRecipePacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.2
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x1A;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Place Recipe";

        virtual ~ServerboundPlaceRecipePacket() override
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

        void SetShiftDown(const bool shift_down_)
        {
            shift_down = shift_down_;
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

        bool GetShiftDown() const
        {
            return shift_down;
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
            shift_down = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(container_id, container);
#if PROTOCOL_VERSION < 348
            WriteData<VarInt>(recipe, container);
#else
            WriteData<Identifier>(recipe, container);
#endif
            WriteData<bool>(shift_down, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
#if PROTOCOL_VERSION < 348
            output["recipe"] = recipe;
#else
            output["recipe"] = recipe.Serialize();
#endif
            output["shift_down"] = shift_down;

            return output;
        }

    private:
        char container_id;
#if PROTOCOL_VERSION < 348
        int recipe;
#else
        Identifier recipe;
#endif
        bool shift_down;

    };
} //ProtocolCraft
