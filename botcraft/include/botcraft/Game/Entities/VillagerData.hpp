#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#pragma once

namespace Botcraft
{
    struct VillagerData
    {
        int type;
        int profession;
        int level;
    };
}
#endif
