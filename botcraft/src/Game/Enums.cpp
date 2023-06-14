#include "botcraft/Game/Enums.hpp"
#include "botcraft/Utilities/EnumUtilities.hpp"

namespace Botcraft
{
    DEFINE_ENUM_STRINGIFYER_RANGE(PlayerDiggingFace, PlayerDiggingFace::Down, PlayerDiggingFace::East);
    DEFINE_ENUM_STRINGIFYER_RANGE(Hand, Hand::Right, Hand::Left);
}
