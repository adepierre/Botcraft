#pragma once

#include "botcraft/Game/Entities/entities/vehicle/minecart/AbstractMinecartEntity.hpp"

namespace Botcraft
{
    class AbstractMinecartContainerEntity : public AbstractMinecartEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractMinecartEntity::metadata_count + AbstractMinecartEntity::hierarchy_metadata_count;

    public:
        AbstractMinecartContainerEntity();
        virtual ~AbstractMinecartContainerEntity();

        virtual bool IsAbstractMinecartContainer() const override;
    };
}
