
#ifndef CORE_STD_WRAPPER_ENCODING_H_
#define CORE_STD_WRAPPER_ENCODING_H_

#include "encoding.h"
using base::encoding::string_2_wstring;
using base::encoding::wstring_2_string;

#include <string>

template<typename dest_string_type>
HRESULT string_convert( HRESULT (*func_convert)(const void *,size_t, void *, size_t *)
    ,const void * ptr, size_t size_of_bytes
    ,dest_string_type & dst, size_t dest_element_size)
{
    if(!(func_convert && ptr && size_of_bytes && dest_element_size)) return E_INVALIDARG;

    dst.clear();
    HRESULT hr;
    size_t out_size=0;
    hr = func_convert(ptr,size_of_bytes,NULL,&out_size);
    if(FAILED(hr)) return hr;
    if (out_size)
    {
        dst.resize(out_size / dest_element_size);
        return func_convert(ptr,size_of_bytes, &dst[0],&out_size);
    }
    return S_OK;
}

template<typename dest_string_type>
HRESULT string_convert(HRESULT(*func_convert)(const void *, size_t, void *, size_t *)
    ,const void * ptr, size_t size_of_bytes
    ,dest_string_type & dst)
{
    return string_convert(func_convert, ptr, size_of_bytes, dst, sizeof(typename dest_string_type::value_type));
}


inline 
    HRESULT string_2_wstring(const char* s , size_t l , std::wstring& dst)
{
    return string_convert(base::encoding::string_2_wstring
        , s, l, dst);
}

inline 
    HRESULT wstring_2_string(const wchar_t* s , size_t l , std::string& dst)
{
    return string_convert(base::encoding::wstring_2_string
        , s, l * sizeof(wchar_t), dst);
}

inline
    HRESULT string_2_wstring(const std::string & s, std::wstring & ws)
{
    return string_2_wstring(s.c_str(),s.size(),ws);
}

inline
    HRESULT wstring_2_string(const std::wstring & ws, std::string & s)
{
    return wstring_2_string(ws.c_str(),ws.size(),s);
}

inline HRESULT utf8_2_wstring(const char * s, size_t l, std::wstring & dst)
{
    return string_convert(base::encoding::utf8_2_wstring, s, l, dst);
}
inline HRESULT wstring_2_utf8(const wchar_t * s, size_t l, std::string & dst)
{
    return string_convert(base::encoding::wstring_2_utf8, s, l * sizeof(wchar_t), dst);
}
inline HRESULT utf8_2_wstring(const std::string & s, std::wstring & ws) 
{
    return utf8_2_wstring(s.c_str(), s.size(), ws);
}
inline HRESULT wstring_2_utf8(const std::wstring & ws, std::string & s)
{
    return wstring_2_utf8(ws.c_str(), ws.size(), s);
}

inline HRESULT string_2_utf8(const char * s, size_t l, std::string & dst)
{
    HRESULT hr;
    std::wstring ws;

    hr = string_2_wstring(s, l, ws);
    if (FAILED(hr)) return hr;
    return wstring_2_utf8(ws, dst);
}

inline HRESULT string_2_utf8_v2(const char * s, size_t l, std::string & dst)
{
    HRESULT hr;
    std::wstring ws;
#ifdef WIN32
    hr = string_2_wstring(s, l, ws);
    if (FAILED(hr)) return hr;
    return wstring_2_utf8(ws, dst);
#else
    return string_convert(base::encoding::ansi_2_utf8_posix, s, l, dst);
#endif
}


inline HRESULT utf8_2_string(const char * s, size_t l, std::string & dst)
{
    HRESULT hr;
    std::wstring ws;

    hr = utf8_2_wstring(s, l, ws);
    if (FAILED(hr)) return hr;
    return wstring_2_string(ws.c_str(), ws.size(), dst);
}

inline HRESULT utf8_2_string_v2(const char * s, size_t l, std::string & dst)
{
    HRESULT hr;
    std::wstring ws;

#ifdef WIN32
    hr = utf8_2_wstring(s, l, ws);
    if (FAILED(hr)) return hr;
    return wstring_2_string(ws.c_str(), ws.size(), dst);
#else
    return string_convert(base::encoding::utf8_2_ansi_posix, s, l, dst);
#endif
}


inline HRESULT string_2_utf8(const std::string & s, std::string & utf8)
{
    return string_2_utf8(s.c_str(), s.size(), utf8);
}
inline HRESULT string_2_utf8_v2(const std::string & s, std::string & utf8)
{
    return string_2_utf8_v2(s.c_str(), s.size(), utf8);
}

inline HRESULT utf8_2_string(const std::string & utf8, std::string & s)
{
    return utf8_2_string(utf8.c_str(), utf8.size(), s);
}

inline HRESULT utf8_2_string_v2(const std::string & utf8, std::string & s)
{
    return utf8_2_string_v2(utf8.c_str(), utf8.size(), s);
}


template<typename u16string_type>
inline HRESULT string_2_u16string(const char * s, size_t l, u16string_type & dst)
{
    return string_convert(base::encoding::string_2_u16string
        , s, l * sizeof(char), dst);
}

template<typename u16string_type>
inline HRESULT string_2_u16string(const std::string & s, u16string_type & dst)
{
    return string_2_u16string(s.c_str(), s.size(), dst);
}

inline HRESULT u16string_2_string(const unsigned short * s, size_t l, std::string & dst)
{
    return string_convert(base::encoding::u16string_2_string
        , s, l * sizeof(unsigned short), dst);
}

template<typename u16string_type>
inline HRESULT u16string_2_string(const u16string_type & s, std::string & dst)
{
    return u16string_2_string((const unsigned short *)s.c_str(), s.size(), dst);
}

#if __cplusplus >= 201103L
typedef std::u16string my_u16string;
#else
#endif



#ifndef _tstring
#ifdef UNICODE
namespace base
{
    typedef std::wstring string_t;
};
#else
namespace base
{
    typedef std::string string_t;
};
#endif
#endif // !_tstring

#ifndef _TCHAR_DEFINED
#define _TCHAR_DEFINED
#ifdef UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif
#endif

inline 
    HRESULT string_2_tstring(const char * s, size_t l, base::string_t & dst)
{
    #ifdef UNICODE
    return string_2_wstring(s, l, dst);
    #else
    dst.assign(s, l);
    return S_OK;
    #endif
}

inline 
    HRESULT string_2_tstring(const std::string & s, base::string_t & dst)
{
    return string_2_tstring(s.c_str(),s.size(),dst);
}

inline 
    HRESULT wstring_2_tstring(const wchar_t * s, size_t l, base::string_t & dst)
{
    #ifdef UNICODE
    dst.assign(s, l);
    return S_OK;
    #else
    return wstring_2_string(s, l, dst);
    #endif
}

inline
    HRESULT wstring_2_tstring(const std::wstring & ws, base::string_t & dst)
{
    return wstring_2_tstring(ws.c_str(),ws.size(),dst);
}

inline 
    HRESULT tstring_2_string(const TCHAR * s, size_t l, std::string & dst)
{
    #ifdef UNICODE
    return wstring_2_string(s,l,dst);
    #else
    dst.assign(s,l);
    return S_OK;
    #endif
}

inline
    HRESULT tstring_2_string(const base::string_t & src, std::string & s)
{
    return tstring_2_string(src.c_str(),src.size(),s);
}

inline 
    HRESULT tstring_2_wstring(const TCHAR * s, size_t l, std::wstring & dst)
{
    #ifdef UNICODE
    dst.assign(s,l);
    return S_OK;
    #else
    return string_2_wstring(s,l,dst);
    #endif
}

inline 
    HRESULT tstring_2_wstring(const base::string_t & src, std::wstring & ws)
{
    return tstring_2_wstring(src.c_str(),src.size(),ws);
}

#endif //CORE_STD_WRAPPER_ENCODING_H_