#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Particles/Particle.hpp"

#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ItemParticle : public Particle
    {
    public:
        ItemParticle();
        
        virtual ~ItemParticle();
        
        virtual std::string GetName() const override;
        
        virtual ParticleType GetType() const override;

        const Slot& GetItemStack() const;

        void SetItemStack(const Slot& item_stack_);
        
    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        
        virtual void WriteImpl(WriteContainer& container) const override;
        
        virtual Json::Value SerializeImpl() const override;

    private:
        Slot item_stack;
        
    };
}
#endif
