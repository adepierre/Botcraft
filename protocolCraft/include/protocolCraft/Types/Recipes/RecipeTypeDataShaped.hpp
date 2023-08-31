#pragma once

#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataShaped : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataShaped() override
        {

        }

        void SetWidth(const int width_)
        {
            width = width_;
        }

        void SetHeight(const int height_)
        {
            height = height_;
        }
        
        void SetGroup(const std::string& group_)
        {
            group = group_;
        }

#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
        void SetCookingBookCategory(const int cooking_book_category_)
        {
            cooking_book_category = cooking_book_category_;
        }
#endif
        
        void SetIngredients(const std::vector<Ingredient>& ingredients_)
        {
            ingredients = ingredients_;
        }

        void SetResult(const Slot& result_)
        {
            result = result_;
        }

#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        void SetShowNotification(const bool show_notification_)
        {
            show_notification = show_notification_;
        }
#endif


        int GetWidth() const
        {
            return width;
        }

        int GetHeight() const
        {
            return height;
        }

        const std::string& GetGroup() const
        {
            return group;
        }

#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
        int GetCookingBookCategory() const
        {
            return cooking_book_category;
        }
#endif

        const std::vector<Ingredient>& GetIngredients() const
        {
            return ingredients;
        }

        const Slot& GetResult() const
        {
            return result;
        }

#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        bool GetShowNotification() const
        {
            return show_notification;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            
            width = ReadData<VarInt>(iter, length);
            height = ReadData<VarInt>(iter, length);
            group = ReadData<std::string>(iter, length);
#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
            cooking_book_category = ReadData<VarInt>(iter, length);
#endif
            ingredients = std::vector<Ingredient>(width * height);
            for (int i = 0; i < width * height; ++i)
            {
                ingredients[i] = ReadData<Ingredient>(iter, length);
            }
            result = ReadData<Slot>(iter, length);
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
            show_notification = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(width, container);
            WriteData<VarInt>(height, container);
            WriteData<std::string>(group, container);
#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
            WriteData<VarInt>(cooking_book_category, container);
#endif
            for (int i = 0; i < width * height; ++i)
            {
                WriteData<Ingredient>(ingredients[i], container);
            }
            WriteData<Slot>(result, container);
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
            WriteData<bool>(show_notification, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["width"] = width;
            output["height"] = height;
            output["group"] = group;
#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
            output["cooking_book_category"] = cooking_book_category;
#endif
            output["ingredients"] = ingredients;
            output["result"] = result;
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
            output["show_notification"] = show_notification;
#endif

            return output;
        }

    private:
        int width = 0;
        int height = 0;
        std::string group;
#if PROTOCOL_VERSION > 760 /* > 1.19.1/2 */
        int cooking_book_category = 0;
#endif
        std::vector<Ingredient> ingredients;
        Slot result;
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        bool show_notification = false;
#endif
    };
}
#endif
