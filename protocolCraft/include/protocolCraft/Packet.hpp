#pragma once

#include <vector>
#include <memory>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Handler;

    class Packet : public NetworkType
    {
    public:
        virtual ~Packet()
        {

        }

        virtual void Write(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetId(), container);
            return WriteImpl(container);
        }

        void Dispatch(Handler *handler)
        {
            return DispatchImpl(handler);
        }

        virtual int GetId() const = 0;

        virtual std::string_view GetName() const = 0;

#ifdef PROTOCOLCRAFT_DETAILED_PARSING
        /// @brief Get a default initialized copy of this type
        /// @return A shared ptr to the same derived type of this Packet
        virtual std::shared_ptr<Packet> CopyTypeOnly() const = 0;
#endif

    protected:
        virtual void DispatchImpl(Handler *handler) = 0;
    };
} // ProtocolCraft
