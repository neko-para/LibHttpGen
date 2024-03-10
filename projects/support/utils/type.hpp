#pragma once

#include <tuple>

namespace lhg
{

namespace help
{

    namespace pri
    {

        template <typename Tuple, template <typename> class Transformer, typename Seq>
        struct transform_tuple_impl;

        template <typename... Types, template <typename> class Transformer, std::size_t... I>
        struct transform_tuple_impl<std::tuple<Types...>, Transformer, std::index_sequence<I...>>
        {
            using type = std::tuple<typename Transformer<Types>::type...>;
        };

    }

    template <typename Tuple, template <typename> class Transformer>
    using transform_tuple =
        typename pri::transform_tuple_impl<Tuple, Transformer,
                                           std::make_index_sequence<std::tuple_size_v<Tuple>>>::type;

}

}
