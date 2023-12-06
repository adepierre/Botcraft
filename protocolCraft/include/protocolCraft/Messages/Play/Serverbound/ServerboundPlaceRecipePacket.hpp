#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundPlaceRecipePacket : public BaseMessage<ServerboundPlaceRecipePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x1F;
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

#if PROTOCOL_VERSION < 348 /* < 1.13 */
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

#if PROTOCOL_VERSION < 348 /* < 1.13 */
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
#if PROTOCOL_VERSION < 348 /* < 1.13 */
            recipe = ReadData<VarInt>(iter, length);
#else
            recipe = ReadData<Identifier>(iter, length);
#endif
            shift_down = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(container_id, container);
#if PROTOCOL_VERSION < 348 /* < 1.13 */
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
#if PROTOCOL_VERSION < 348 /* < 1.13 */
            output["recipe"] = recipe;
#else
            output["recipe"] = recipe;
#endif
            output["shift_down"] = shift_down;

            return output;
        }

    private:
        char container_id = 0;
#if PROTOCOL_VERSION < 348 /* < 1.13 */
        int recipe = 0;
#else
        Identifier recipe;
#endif
        bool shift_down = false;

    };
} //ProtocolCraft
