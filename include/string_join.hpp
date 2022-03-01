#ifndef STRING_JOIN_HPP
#define STRING_JOIN_HPP

#include <concepts>
#include <string_view>
#include <string>

namespace utils {
template<typename CharT, std::convertible_to<std::basic_string_view<CharT>>... Strs>
std::basic_string<CharT> join(std::basic_string_view<CharT> head, const Strs&... tail) {
	std::basic_string<CharT> result;
	result.reserve(head.size() + (std::basic_string_view<CharT>{tail}.size() + ...));
	result.append(head);
	(result.append(std::basic_string_view<CharT>{tail}), ...);
	return result;
}
} // namespace utils

#endif /* STRING_JOIN_HPP */
