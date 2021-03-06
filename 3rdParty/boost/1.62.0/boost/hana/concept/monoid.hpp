/*!
@file
Defines `boost::hana::Monoid`.

@copyright Louis Dionne 2013-2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONOID_HPP
#define BOOST_HANA_CONCEPT_MONOID_HPP

#include <boost/hana/fwd/concept/monoid.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/zero.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monoid {
        using Tag = typename tag_of<M>::type;
        static constexpr bool value = !is_default<zero_impl<Tag>>::value &&
                                      !is_default<plus_impl<Tag, Tag>>::value;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONOID_HPP
