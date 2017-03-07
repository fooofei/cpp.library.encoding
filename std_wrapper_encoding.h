
#ifndef CORE_STD_WRAPPER_ENCODING_H_
#define CORE_STD_WRAPPER_ENCODING_H_

#include "encoding.h"

#include <string>

template<typename string_type>
inline typename string_type::pointer pointer_begin(string_type& str)
{
    return &str[0];
}

using base::encoding::string_2_wstring;
using base::encoding::wstring_2_string;
inline 
    HRESULT string_2_wstring(const char* s , size_t l , std::wstring& dst)
{
    dst.clear();
    HRESULT hr;
    size_t lu=0;
    hr = string_2_wstring(s,l,NULL,&lu);
    if(FAILED(hr)) return hr;
    if (lu)
    {
        dst.resize(lu / sizeof(wchar_t));
        return string_2_wstring(s,l,pointer_begin(dst),&lu);
    }
    return S_OK;
}

inline 
    HRESULT wstring_2_string(const wchar_t* s , size_t l , std::string& dst)
{
    dst.clear();
    HRESULT hr;
    size_t l1 = 0;
    hr = wstring_2_string(s, l*sizeof(wchar_t),NULL,&l1);
    if(FAILED(hr)) return hr;
    if (l1)
    {
        dst.resize(l1);
        return wstring_2_string(s, l*sizeof(wchar_t), pointer_begin(dst), &l1);
    }
    return S_OK;
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