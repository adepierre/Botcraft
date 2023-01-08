#pragma once

namespace ProtocolCraft
{
    namespace Internal
    {
        // Concat two tuples in one big tuple
        template<typename ... input_t>
        using tuple_cat_t =
            decltype(std::tuple_cat(
                std::declval<input_t>()...
            ));
    }
}
