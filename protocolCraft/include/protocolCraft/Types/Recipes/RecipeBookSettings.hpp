#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class RecipeBookSettings : public NetworkType
    {
    public:
        virtual ~RecipeBookSettings() override
        {

        }

        void SetIsGuiOpen(const bool is_gui_open_)
        {
            is_gui_open = is_gui_open_;
        }
        
        void SetIsFilteringCraftable(const bool is_filtering_craftable_)
        {
            is_filtering_craftable = is_filtering_craftable_;
        }
        
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        void SetIsFurnaceGuiOpen(const bool is_furnace_gui_open_)
        {
            is_furnace_gui_open = is_furnace_gui_open_;
        }
        
        void SetIsFurnaceFilteringCraftable(const bool is_furnace_filtering_craftable_)
        {
            is_furnace_filtering_craftable = is_furnace_filtering_craftable_;
        }
#endif


#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        void SetIsBlastingFurnaceGuiOpen(const bool is_blasting_furnace_gui_open_)
        {
            is_blasting_furnace_gui_open = is_blasting_furnace_gui_open_;
        }
        
        void SetIsBlastingFurnaceFilteringCraftable(const bool is_blasting_furnace_filtering_craftable_)
        {
            is_blasting_furnace_filtering_craftable = is_blasting_furnace_filtering_craftable_;
        }
        
        void SetIsSmokerGuiOpen(const bool is_smoker_gui_open_)
        {
            is_smoker_gui_open = is_smoker_gui_open_;
        }
        
        void SetIsSmokerFilteringCraftable(const bool is_smoker_filtering_craftable_)
        {
            is_smoker_filtering_craftable = is_smoker_filtering_craftable_;
        }
#endif
        
        
        bool GetIsGuiOpen()
        {
            return is_gui_open;
        }
        
        bool GetIsFilteringCraftable()
        {
            return is_filtering_craftable;
        }
        
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        bool GetIsFurnaceGuiOpen()
        {
            return is_furnace_gui_open;
        }
        
        bool GetIsFurnaceFilteringCraftable()
        {
            return is_furnace_filtering_craftable;
        }
#endif


#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        bool GetIsBlastingFurnaceGuiOpen()
        {
            return is_blasting_furnace_gui_open;
        }
        
        bool GetIsBlastingFurnaceFilteringCraftable()
        {
            return is_blasting_furnace_filtering_craftable;
        }
        
        bool GetIsSmokerGuiOpen()
        {
            return is_smoker_gui_open;
        }
        
        bool GetIsSmokerFilteringCraftable()
        {
            return is_smoker_filtering_craftable;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            is_gui_open = ReadData<bool>(iter, length);
            is_filtering_craftable = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
            is_furnace_gui_open = ReadData<bool>(iter, length);
            is_furnace_filtering_craftable = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
            is_blasting_furnace_gui_open = ReadData<bool>(iter, length);
            is_blasting_furnace_filtering_craftable = ReadData<bool>(iter, length);
            is_smoker_gui_open = ReadData<bool>(iter, length);
            is_smoker_filtering_craftable = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(is_gui_open, container);
            WriteData<bool>(is_filtering_craftable, container);
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
            WriteData<bool>(is_furnace_gui_open, container);
            WriteData<bool>(is_furnace_filtering_craftable, container);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
            WriteData<bool>(is_blasting_furnace_gui_open, container);
            WriteData<bool>(is_blasting_furnace_filtering_craftable, container);
            WriteData<bool>(is_smoker_gui_open, container);
            WriteData<bool>(is_smoker_filtering_craftable, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["is_gui_open"] = is_gui_open;
            output["is_filtering_craftable"] = is_filtering_craftable;
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
            output["is_furnace_gui_open"] = is_furnace_gui_open;
            output["is_furnace_filtering_craftable"] = is_furnace_filtering_craftable;
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
            output["is_blasting_furnace_gui_open"] = is_blasting_furnace_gui_open;
            output["is_blasting_furnace_filtering_craftable"] = is_blasting_furnace_filtering_craftable;
            output["is_smoker_gui_open"] = is_smoker_gui_open;
            output["is_smoker_filtering_craftable"] = is_smoker_filtering_craftable;
#endif

            return output;
        }

    private:
        bool is_gui_open = false;
        bool is_filtering_craftable = false;
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */
        bool is_furnace_gui_open = false;
        bool is_furnace_filtering_craftable = false;
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        bool is_blasting_furnace_gui_open = false;
        bool is_blasting_furnace_filtering_craftable = false;
        bool is_smoker_gui_open = false;
        bool is_smoker_filtering_craftable = false;
#endif
    };
}
