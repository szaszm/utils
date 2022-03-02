#ifndef SPECIALIZATION_OF_HPP
#define SPECIALIZATION_OF_HPP

#include <type_traits>

namespace utils {
namespace detail {
template<typename T, template<typename...> typename Base>
struct is_specialization_of_impl : std::false_type {};
template<typename T, template<typename...> typename Base, typename... Rest>
struct is_specialization_of_impl<Base<T, Rest...>, Base> : std::true_type {};
} // namespace detail

template<typename T, template<typename...> typename Base>
concept specialization_of = detail::is_specialization_of_impl<std::remove_cvref_t<T>, Base>::value;
} // namespace utils

#endif /* SPECIALIZATION_OF_HPP */
