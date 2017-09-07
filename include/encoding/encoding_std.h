
#ifndef CORE_ENCODING_ENCODING_STD_H
#define CORE_ENCODING_ENCODING_STD_H

#include <string>
#include "hresult.h"

// string <-> wstring
HRESULT string_2_wstring(const char *, size_t, std::wstring &);

HRESULT string_2_wstring(const std::string &, std::wstring &);

HRESULT wstring_2_string(const wchar_t *, size_t, std::string &);

HRESULT wstring_2_string(const std::wstring &, std::string &);



// string <-> utf8
HRESULT string_2_utf8(const char *, size_t, std::string &);

HRESULT string_2_utf8(const std::string &, std::string &);

HRESULT utf8_2_string(const char *, size_t, std::string &);

HRESULT utf8_2_string(const std::string &, std::string &);



// wstring <-> utf8

HRESULT wstring_2_utf8(const wchar_t *, size_t, std::string &);

HRESULT wstring_2_utf8(const std::wstring &, std::string &);

HRESULT utf8_2_wstring(const char *, size_t, std::wstring &);

HRESULT utf8_2_wstring(const std::string &, std::wstring &);


#if __cplusplus >= 201103L
typedef std::u16string my_u16string;
#else

#include "../encoding/u16string_bytes.h"

typedef u16string_bytes_t my_u16string;
#endif


// string <-> u16string
HRESULT string_2_u16string(const char *, size_t, my_u16string &);

HRESULT string_2_u16string(const std::string &, my_u16string &);

HRESULT u16string_2_string(const unsigned short *, size_t, std::string &);

HRESULT u16string_2_string(const my_u16string &, std::string &);



// wstring <-> u16string
HRESULT wstring_2_u16string(const wchar_t *, size_t, my_u16string &);

HRESULT wstring_2_u16string(const std::wstring &, my_u16string &);

HRESULT u16string_2_wstring(const unsigned short *, size_t, std::wstring &);

HRESULT u16string_2_wstring(const my_u16string &, std::wstring &);



// utf8 <-> u16string
HRESULT utf8_2_u16string(const char *, size_t, my_u16string &);

HRESULT utf8_2_u16string(const std::string &, my_u16string &);

HRESULT u16string_2_utf8(const unsigned short *, size_t, std::string &);

HRESULT u16string_2_utf8(const my_u16string &, std::string &);


#endif //CORE_ENCODING_ENCODING_STD_H
