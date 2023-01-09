#if PROTOCOL_VERSION > 392
#include "protocolCraft/Types/Particles/ItemParticle.hpp"

namespace ProtocolCraft
{
    ItemParticle::ItemParticle()
    {
        
    }
    
    ItemParticle::~ItemParticle()
    {
        
    }
    
    std::string ItemParticle::GetName() const
    {
        return "item";
    }
    
    ParticleType ItemParticle::GetType() const
    {
        return ParticleType::Item;
    }

    const Slot& ItemParticle::GetItemStack() const
    {
        return item_stack;
    }
    
    void ItemParticle::SetItemStack(const Slot& item_stack_)
    {
        item_stack = item_stack_;
    }

    void ItemParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {
        item_stack = ReadData<Slot>(iter, length);
    }
    
    void ItemParticle::WriteImpl(WriteContainer& container) const
    {
        WriteData<Slot>(item_stack, container);
    }
    
    Json::Value ItemParticle::SerializeImpl() const
    {
        Json::Value output;

        output["item_stack"] = item_stack.Serialize();

        return output;
    }
}
#endif
