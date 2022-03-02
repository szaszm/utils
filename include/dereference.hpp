#ifndef DEREFERENCE_HPP
#define DEREFERENCE_HPP

#include <type_traits>
#include <gsl-lite/gsl-lite.hpp>

namespace utils {
namespace detail {
template<typename T>
struct is_not_null : std::false_type {};
template<typename T>
struct is_not_null<gsl::not_null<T>> : std::true_type {};

struct dereference_impl {
	template<typename T, typename = typename std::enable_if<is_not_null<T>::value>::type>
	constexpr decltype(auto) operator()(T&& ptr) const noexcept(noexcept(*std::forward<T>(ptr))) {
		return *std::forward<T>(ptr);
	}
};

struct unsafe_dereference_impl {
	template<typename T>
	constexpr decltype(auto) operator()(T&& ptr) const noexcept(noexcept(*std::forward<T>(ptr))) {
		return *std::forward<T>(ptr);
	}
};
} // namespace detail

inline constexpr detail::dereference_impl dereference;
inline constexpr detail::unsafe_dereference_impl unsafe_dereference;

} // namespace utils

static_assert(std::is_same_v(decltype(dereference(std::declval<gsl::not_null<int*>>())), int&));
static_assert(std::is_same_v(decltype(unsafe_dereference(std::declval<int*>())), int&));

#endif /* DEREFERENCE_HPP */
