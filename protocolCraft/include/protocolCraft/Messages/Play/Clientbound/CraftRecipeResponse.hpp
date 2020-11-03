#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class CraftRecipeResponse : public BaseMessage<CraftRecipeResponse>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x2B;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x2D;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x30;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x31;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x30;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x2F;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Craft Recipe Response";
        }

        void SetWindowId(const char window_id_)
        {
            window_id = window_id_;
        }

#if PROTOCOL_VERSION < 348
        void SetRecipe(const int recipe_)
        {
            recipe = recipe_;
        }
#else
        void SetRecipe(const Identifier& recipe_)
        {
            recipe = recipe_;
        }
#endif


        const char GetWindowId() const
        {
            return window_id;
        }

#if PROTOCOL_VERSION < 348
        const int GetRecipe() const
        {
            return recipe;
        }
#else
        const Identifier& GetRecipe() const
        {
            return recipe;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            window_id = ReadData<char>(iter, length);
#if PROTOCOL_VERSION < 348
            recipe = ReadVarInt(iter, length);
#else
            recipe = ReadString(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(window_id, container);
#if PROTOCOL_VERSION < 348
            WriteVarInt(recipe, container);
#else
            WriteString(recipe, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["window_id"] = picojson::value((double)window_id);
#if PROTOCOL_VERSION < 348
            object["recipe"] = picojson::value((double)recipe);
#else
            object["recipe"] = picojson::value(recipe);
#endif

            return value;
        }

    private:
        char window_id;
#if PROTOCOL_VERSION < 348
        int recipe;
#else
        Identifier recipe;
#endif

    };
} //ProtocolCraft