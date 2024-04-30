#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ItemParticleOptions : public ParticleOptions
    {
    public:
        ItemParticleOptions();
        virtual ~ItemParticleOptions();

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
