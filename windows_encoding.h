

#ifndef CORE_WINDOWS_ENCODING_H_
#define CORE_WINDOWS_ENCODING_H_

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN	

namespace base { 
    namespace encoding{
        //
        // if src is NULL terminate, then src_size can be -1, otherwise you must explicit give src_size.
        // return size is need size, not include NULL terminate, and dst_size no need to include NULL terminate size,
        //     no need to +1.

        inline
        HRESULT _lasterror_2_hresult()
    {
        DWORD v = GetLastError();
        switch (v)
        {
        case ERROR_NO_UNICODE_TRANSLATION:
        case ERROR_INVALID_PARAMETER: return E_INVALIDARG;
        case ERROR_INSUFFICIENT_BUFFER: return E_OUTOFMEMORY;
        default: break;
        }
        return HRESULT_FROM_WIN32(v);
        }

    inline
        HRESULT utf16le_2_ansi_windows(const wchar_t * src, size_t src_size, char * dst, size_t * dst_size)
    {
        int r = WideCharToMultiByte(CP_OEMCP, 0, src , (int)(src_size),dst,(int)*dst_size, NULL, NULL);
        if (r<=0) { return _lasterror_2_hresult(); }
        else{  *dst_size = size_t(r); return S_OK; }
    }

    inline
        HRESULT ansi_2_utf16le_windows(const char * src, size_t src_size, wchar_t * dst, size_t * dst_size)
    {
        int r = MultiByteToWideChar(CP_OEMCP, 0, src , int(src_size) , dst ,int(*dst_size));
        if (r<=0) { return _lasterror_2_hresult(); }
        else{  *dst_size = size_t(r); return S_OK; }
    }

    inline
        HRESULT utf8_2_utf16le_windows(const char * src, size_t src_size, wchar_t * dst, size_t * dst_size)
    {
        int r = MultiByteToWideChar(CP_UTF8, 0 ,src,(int)(src_size),dst,int(*dst_size));
        if (r<=0) { return _lasterror_2_hresult(); }
        else{  *dst_size = size_t(r); return S_OK; }
    }
    inline
        HRESULT utf16le_2_utf8_windows(const wchar_t * src, size_t src_size, char * dst, size_t * dst_size)
    {
        int r = WideCharToMultiByte(CP_UTF8 , 0 , src, int(src_size),dst , int(*dst_size),NULL,NULL);
        if (r<=0) { return _lasterror_2_hresult(); }
        else{  *dst_size = size_t(r); return S_OK; }
    }

    };
}; 

#endif // _WIN32
#endif //CORE_WINDOWS_ENCODING_H_