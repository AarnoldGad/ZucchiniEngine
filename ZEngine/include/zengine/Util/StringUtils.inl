template<>
constexpr char const* ze::StringLiteral(char const* str, [[maybe_unused]] wchar_t const* wstr, [[maybe_unused]] char16_t const* ustr, [[maybe_unused]] char32_t const* Ustr)
{
   return str;
}

template<>
constexpr wchar_t const* ze::StringLiteral([[maybe_unused]] char const* str, wchar_t const* wstr, [[maybe_unused]] char16_t const* ustr, [[maybe_unused]] char32_t const* Ustr)
{
   return wstr;
}

template<>
constexpr char16_t const* ze::StringLiteral([[maybe_unused]] char const* str, [[maybe_unused]] wchar_t const* wstr, char16_t const* ustr, [[maybe_unused]] char32_t const* Ustr)
{
   return ustr;
}

template<>
constexpr char32_t const* ze::StringLiteral([[maybe_unused]] char const* str, [[maybe_unused]] wchar_t const* wstr, [[maybe_unused]] char16_t const* ustr, char32_t const* Ustr)
{
   return Ustr;
}
