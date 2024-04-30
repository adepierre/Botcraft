#if PROTOCOL_VERSION < 393 /* < 1.13 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"

namespace ProtocolCraft
{
    class IconcrackParticleOptions : public ParticleOptions
    {
    public:
        IconcrackParticleOptions();

        virtual ~IconcrackParticleOptions();


        int GetArgument1() const;        
        int GetArgument2() const;


        void SetArgument1(const int argument1_);        
        void SetArgument2(const int argument2_);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override;
        virtual void WriteImpl(WriteContainer& container) const override;        
        virtual Json::Value SerializeImpl() const override;

    private:
        int argument1 = 0;
        int argument2 = 0; 
    };
}
#endif
