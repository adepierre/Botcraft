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
        
#if PROTOCOL_VERSION > 356
        void SetIsFurnaceGuiOpen(const bool is_furnace_gui_open_)
        {
            is_furnace_gui_open = is_furnace_gui_open_;
        }
        
        void SetIsFurnaceFilteringCraftable(const bool is_furnace_filtering_craftable_)
        {
            is_furnace_filtering_craftable = is_furnace_filtering_craftable_;
        }
#endif


#if PROTOCOL_VERSION > 736
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
        
        
        const bool GetIsGuiOpen()
        {
            return is_gui_open;
        }
        
        const bool GetIsFilteringCraftable()
        {
            return is_filtering_craftable;
        }
        
#if PROTOCOL_VERSION > 356
        const bool GetIsFurnaceGuiOpen()
        {
            return is_furnace_gui_open;
        }
        
        const bool GetIsFurnaceFilteringCraftable()
        {
            return is_furnace_filtering_craftable;
        }
#endif


#if PROTOCOL_VERSION > 736
        const bool GetIsBlastingFurnaceGuiOpen()
        {
            return is_blasting_furnace_gui_open;
        }
        
        const bool GetIsBlastingFurnaceFilteringCraftable()
        {
            return is_blasting_furnace_filtering_craftable;
        }
        
        const bool GetIsSmokerGuiOpen()
        {
            return is_smoker_gui_open;
        }
        
        const bool GetIsSmokerFilteringCraftable()
        {
            return is_smoker_filtering_craftable;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            is_gui_open = ReadData<bool>(iter, length);
            is_filtering_craftable = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 356
            is_furnace_gui_open = ReadData<bool>(iter, length);
            is_furnace_filtering_craftable = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 736
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
#if PROTOCOL_VERSION > 356
            WriteData<bool>(is_furnace_gui_open, container);
            WriteData<bool>(is_furnace_filtering_craftable, container);
#endif
#if PROTOCOL_VERSION > 736
            WriteData<bool>(is_blasting_furnace_gui_open, container);
            WriteData<bool>(is_blasting_furnace_filtering_craftable, container);
            WriteData<bool>(is_smoker_gui_open, container);
            WriteData<bool>(is_smoker_filtering_craftable, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["is_gui_open"] = picojson::value((double)is_gui_open);
            object["is_filtering_craftable"] = picojson::value((double)is_filtering_craftable);
#if PROTOCOL_VERSION > 356
            object["is_furnace_gui_open"] = picojson::value(is_furnace_gui_open);
            object["is_furnace_filtering_craftable"] = picojson::value(is_furnace_filtering_craftable);
#endif
#if PROTOCOL_VERSION > 736
            object["is_blasting_furnace_gui_open"] = picojson::value(is_blasting_furnace_gui_open);
            object["is_blasting_furnace_filtering_craftable"] = picojson::value(is_blasting_furnace_filtering_craftable);
            object["is_smoker_gui_open"] = picojson::value(is_smoker_gui_open);
            object["is_smoker_filtering_craftable"] = picojson::value(is_smoker_filtering_craftable);
#endif

            return value;
        }

    private:
        bool is_gui_open;
        bool is_filtering_craftable;
#if PROTOCOL_VERSION > 356
        bool is_furnace_gui_open;
        bool is_furnace_filtering_craftable;
#endif
#if PROTOCOL_VERSION > 736
        bool is_blasting_furnace_gui_open;
        bool is_blasting_furnace_filtering_craftable;
        bool is_smoker_gui_open;
        bool is_smoker_filtering_craftable;
#endif
    };
}
