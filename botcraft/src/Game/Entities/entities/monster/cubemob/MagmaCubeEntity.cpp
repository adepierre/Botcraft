#include "botcraft/Game/Entities/entities/monster/cubemob/MagmaCubeEntity.hpp"
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
#include "botcraft/Utilities/Logger.hpp"
#endif

namespace Botcraft
{
    MagmaCubeEntity::MagmaCubeEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
        // As MagmaCube don't inherit from MonsterEntity, AttackDamage is not initialized in parent constructor
        // It is overwritten when size is set, but it needs to be initialized before
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 1.0) });
#endif
    }

    MagmaCubeEntity::~MagmaCubeEntity()
    {

    }


    std::string MagmaCubeEntity::GetName() const
    {
        return "magma_cube";
    }

    EntityType MagmaCubeEntity::GetType() const
    {
        return EntityType::MagmaCube;
    }


    std::string MagmaCubeEntity::GetClassName()
    {
        return "magma_cube";
    }

    EntityType MagmaCubeEntity::GetClassType()
    {
        return EntityType::MagmaCube;
    }


#if PROTOCOL_VERSION > 775 /* > 26.1.2 */
    void MagmaCubeEntity::SizeChanged(const int new_size)
    {
        AbstractCubeMobEntity::SizeChanged(new_size);
        auto it = attributes.find(EntityAttribute::Type::AttackDamage);
        if (it != attributes.end())
        {
            it->second.SetBaseValue(static_cast<double>(new_size));
        }
        else
        {
            LOG_WARNING("Trying to set attribute base value for " << EntityAttribute::Type::AttackDamage << " for a slime but it doesn't have this attribute");
        }
        it = attributes.find(EntityAttribute::Type::Armor);
        if (it != attributes.end())
        {
            it->second.SetBaseValue(static_cast<double>(new_size) * 3.0);
        }
        else
        {
            LOG_WARNING("Trying to set attribute base value for " << EntityAttribute::Type::AttackDamage << " for a slime but it doesn't have this attribute");
        }
    }

    double MagmaCubeEntity::GetWidthImpl() const
    {
        return 0.52 * GetIdSizeImpl();
    }

    double MagmaCubeEntity::GetHeightImpl() const
    {
        return 0.52 * GetIdSizeImpl();
    }
#endif

}
