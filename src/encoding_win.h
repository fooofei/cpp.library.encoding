

#ifndef CORE_ENCODING_WIN_H
#define CORE_ENCODING_WIN_H

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

//
// if src is NULL terminate, then src_size can be -1, otherwise you must explicit give src_size.
// return size is need size, not include NULL terminate, and dst_size no need to include NULL terminate size,
//     no need to +1.

HRESULT _lasterror_2_hresult();

inline HRESULT utf16le_2_mbcs_windows(const wchar_t *src, size_t src_size, char *dst, size_t *dst_size)
{
    int r = WideCharToMultiByte(CP_OEMCP, 0, src, (int)(src_size), dst, (int)*dst_size, NULL, NULL);
    if (r <= 0)
    {
        return _lasterror_2_hresult();
    }
    else
    {
        *dst_size = size_t(r);
        return S_OK;
    }
}

inline HRESULT mbcs_2_utf16le_windows(const char *src, size_t src_size, wchar_t *dst, size_t *dst_size)
{
    int r = MultiByteToWideChar(CP_OEMCP, 0, src, int(src_size), dst, int(*dst_size));
    if (r <= 0)
    {
        return _lasterror_2_hresult();
    }
    else
    {
        *dst_size = size_t(r);
        return S_OK;
    }
}

inline HRESULT utf8_2_utf16le_windows(const char *src, size_t src_size, wchar_t *dst, size_t *dst_size)
{
    int r = MultiByteToWideChar(CP_UTF8, 0, src, (int)(src_size), dst, int(*dst_size));
    if (r <= 0)
    {
        return _lasterror_2_hresult();
    }
    else
    {
        *dst_size = size_t(r);
        return S_OK;
    }
}

inline HRESULT utf16le_2_utf8_windows(const wchar_t *src, size_t src_size, char *dst, size_t *dst_size)
{
    int r = WideCharToMultiByte(CP_UTF8, 0, src, int(src_size), dst, int(*dst_size), NULL, NULL);
    if (r <= 0)
    {
        return _lasterror_2_hresult();
    }
    else
    {
        *dst_size = size_t(r);
        return S_OK;
    }
}

#endif // WIN32
#endif //CORE_ENCODING_WIN_H