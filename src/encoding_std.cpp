
#include "../include/encoding/encoding_std.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "../include/encoding/encoding.h"
#ifdef __cplusplus
}
#endif


template <typename dest_string_type>
HRESULT
string_convert(HRESULT (*func_convert)(const void *, size_t, void *, size_t *), const void *ptr, size_t size_of_bytes,
               dest_string_type &dst, size_t dest_element_size)
{
    if (!(func_convert && ptr && size_of_bytes && dest_element_size))
        return E_INVALIDARG;

    dst.clear();
    HRESULT hr;
    size_t out_size = 0;
    hr = func_convert(ptr, size_of_bytes, NULL, &out_size);
    if (FAILED(hr))
        return hr;
    if (out_size)
    {
        dst.resize(out_size / dest_element_size);
        return func_convert(ptr, size_of_bytes, &dst[0], &out_size);
    }
    return S_OK;
}

template <typename dest_string_type>
HRESULT
string_convert(HRESULT (*func_convert)(const void *, size_t, void *, size_t *), const void *ptr, size_t size_of_bytes,
               dest_string_type &dst)
{
    return string_convert(func_convert, ptr, size_of_bytes, dst, sizeof(typename dest_string_type::value_type));
}

HRESULT 
string_2_wstring(const char *src, size_t src_size, std::wstring &dst)
{

#ifdef WIN32
    return string_convert(mbcs_2_utf16le, src, src_size, dst);
#else
    return string_convert(mbcs_2_utf32le, src, src_size, dst);
#endif
}

HRESULT 
string_2_wstring(const std::string &src, std::wstring &dst)
{
    return string_2_wstring(src.c_str(), src.size(), dst);
}

HRESULT 
wstring_2_string(const wchar_t *src, size_t src_size, std::string &dst)
{
#ifdef WIN32
    return string_convert(utf16le_2_mbcs, src, src_size * sizeof(wchar_t), dst);
#else
    return string_convert(utf32le_2_mbcs, src, src_size * sizeof(wchar_t), dst);
#endif
}

HRESULT 
wstring_2_string(const std::wstring &src, std::string &dst)
{
    return wstring_2_string(src.c_str(), src.size(), dst);
}

// string <-> utf8
HRESULT 
string_2_utf8(const char *src, size_t src_size, std::string &dst)
{

#ifdef WIN32
    std::wstring ws;
    HRESULT hr;

    hr = string_2_wstring(src, src_size, ws);
    if (FAILED(hr))
        return hr;
    return wstring_2_utf8(ws, dst);
#else
    return string_convert(mbcs_2_utf8, src, src_size, dst);
#endif
}

HRESULT 
string_2_utf8(const std::string &src, std::string &dst)
{
    return string_2_utf8(src.c_str(), src.size(), dst);
}

HRESULT 
utf8_2_string(const char *src, size_t src_size, std::string &dst)
{
#ifdef WIN32
    std::wstring ws;
    HRESULT hr;

    hr = utf8_2_wstring(src, src_size, ws);
    if (FAILED(hr))
        return hr;
    return wstring_2_string(ws, dst);
#else
    return string_convert(utf8_2_mbcs, src, src_size, dst);
#endif
}

HRESULT 
utf8_2_string(const std::string &src, std::string &dst)
{
    return utf8_2_string(src.c_str(), src.size(), dst);
}

// wstring <-> utf8

HRESULT 
wstring_2_utf8(const wchar_t *src, size_t src_size, std::string &dst)
{
#ifdef WIN32
    return string_convert(utf16le_2_utf8, src, src_size * sizeof(wchar_t), dst);
#else
    return string_convert(utf32le_2_utf8, src, src_size * sizeof(wchar_t), dst);
#endif
}

HRESULT 
wstring_2_utf8(const std::wstring &src, std::string &dst)
{
    return wstring_2_utf8(src.c_str(), src.size(), dst);
}

HRESULT utf8_2_wstring(const char *src, size_t src_size, std::wstring &dst)
{
#ifdef WIN32
    return string_convert(utf8_2_utf16le, src, src_size, dst);
#else
    return string_convert(utf8_2_utf32le, src, src_size, dst);
#endif
}

HRESULT utf8_2_wstring(const std::string &src, std::wstring &dst)
{
    return utf8_2_wstring(src.c_str(), src.size(), dst);
}

// string <-> u16string
HRESULT string_2_u16string(const char *src, size_t src_size, my_u16string &dst)
{
    return string_convert(mbcs_2_utf16le, src, src_size, dst);
}

HRESULT string_2_u16string(const std::string &src, my_u16string &dst)
{
    return string_2_u16string(src.c_str(), src.size(), dst);
}

HRESULT u16string_2_string(const unsigned short *src, size_t src_size, std::string &dst)
{
    return string_convert(utf16le_2_mbcs, src, src_size * sizeof(unsigned short), dst);
}

HRESULT u16string_2_string(const my_u16string &src, std::string &dst)
{
    return u16string_2_string((const unsigned short *)src.c_str(), src.size(), dst);
}

// wstring <-> u16string
HRESULT wstring_2_u16string(const wchar_t *src, size_t src_size, my_u16string &dst)
{
#ifdef WIN32
    if (!(src && src_size))
        return E_INVALIDARG;
    dst.assign((const my_u16string::value_type *)src, src_size);
    return S_OK;
#else
    return string_convert(utf32le_2_utf16le, src, src_size * sizeof(wchar_t), dst);
#endif
}

HRESULT wstring_2_u16string(const std::wstring &src, my_u16string &dst)
{
    return wstring_2_u16string(src.c_str(), src.size(), dst);
}

HRESULT u16string_2_wstring(const unsigned short *src, size_t src_size, std::wstring &dst)
{
#ifdef WIN32
    if (!(src && src_size))
        return E_INVALIDARG;
    dst.assign((const wchar_t *)src, src_size);
    return S_OK;
#else
    return string_convert(utf16le_2_utf32le, src, src_size * sizeof(wchar_t), dst);
#endif
}

HRESULT u16string_2_wstring(const my_u16string &src, std::wstring &dst)
{
    return u16string_2_wstring((const unsigned short *)src.c_str(), src.size(), dst);
}

// utf8 <-> u16string
HRESULT utf8_2_u16string(const char *src, size_t src_size, my_u16string &dst)
{
    return string_convert(utf8_2_utf16le, src, src_size, dst);
}

HRESULT utf8_2_u16string(const std::string &src, my_u16string &dst)
{
    return utf8_2_u16string(src.c_str(), src.size(), dst);
}

HRESULT u16string_2_utf8(const unsigned short *src, size_t src_size, std::string &dst)
{
    return string_convert(utf16le_2_utf8, src, src_size, dst);
}

HRESULT u16string_2_utf8(const my_u16string &src, std::string &dst)
{
    return u16string_2_utf8((const unsigned short *)src.c_str(), src.size(), dst);
}
