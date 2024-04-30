#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#include "protocolCraft/Types/Particles/ItemParticleOptions.hpp"

namespace ProtocolCraft
{
    ItemParticleOptions::ItemParticleOptions()
    {
        
    }
    
    ItemParticleOptions::~ItemParticleOptions()
    {
        
    }

    const Slot& ItemParticleOptions::GetItemStack() const
    {
        return item_stack;
    }
    
    void ItemParticleOptions::SetItemStack(const Slot& item_stack_)
    {
        item_stack = item_stack_;
    }

    void ItemParticleOptions::ReadImpl(ReadIterator& iter, size_t& length)
    {
        item_stack = ReadData<Slot>(iter, length);
    }
    
    void ItemParticleOptions::WriteImpl(WriteContainer& container) const
    {
        WriteData<Slot>(item_stack, container);
    }
    
    Json::Value ItemParticleOptions::SerializeImpl() const
    {
        Json::Value output;

        output["item_stack"] = item_stack;

        return output;
    }
}
#endif
