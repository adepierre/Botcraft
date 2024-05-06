#if PROTOCOL_VERSION < 393 /* < 1.13 */
#include "protocolCraft/Types/Particles/IconcrackParticleOptions.hpp"

namespace ProtocolCraft
{
    IconcrackParticleOptions::IconcrackParticleOptions()
    {

    }
    
    IconcrackParticleOptions::~IconcrackParticleOptions()
    {

    }


    int IconcrackParticleOptions::GetArgument1() const
    {
        return argument1;
    }

    int IconcrackParticleOptions::GetArgument2() const
    {
        return argument2;
    }


    void IconcrackParticleOptions::SetArgument1(const int argument1_)
    {
        argument1 = argument1_;
    }

    void IconcrackParticleOptions::SetArgument2(const int argument2_)
    {
        argument2 = argument2_;
    }


    void IconcrackParticleOptions::ReadImpl(ReadIterator& iter, size_t& length)
    {
        argument1 = ReadData<VarInt>(iter, length);
        argument2 = ReadData<VarInt>(iter, length);
    }

    void IconcrackParticleOptions::WriteImpl(WriteContainer& container) const
    {
        WriteData<VarInt>(argument1, container);
        WriteData<VarInt>(argument2, container);
    }

    Json::Value IconcrackParticleOptions::SerializeImpl() const
    {
        Json::Value output;

        output["argument1"] = argument1;
        output["argument2"] = argument2;

        return output;
    }
}
#endif
