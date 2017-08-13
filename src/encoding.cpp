

#include "../include/encoding/encoding.h"

#ifdef WIN32
#include "encoding_win.h"
#else

#include "encoding_posix.h"

#endif //WIN32

// sample : 00fe316d3e96a0d4964a0fa60bbd7ae7  size is not even.
#define _CHECKSIZE(size)                 \
        do                               \
        {                                \
                if (!is_even_size(size)) \
                {                        \
                        if (size)        \
                        {                \
                                --size;  \
                        }                \
                }                        \
        } while (0);
#define _UNUSED_PARAM ((void)src; (void)src_size; (void)dst; (void)dst_size;);

namespace encoding
{

static bool is_even_size(size_t size)
{
        return (((size & 0x1) ^ 0x1) == 1);
}

HRESULT mbcs_2_utf16le(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
        _CHECKSIZE(*dst_size);
#ifdef WIN32
        size_t dst_cbsize = *dst_size;
        dst_cbsize = dst_cbsize >> 1;
        HRESULT hr;
        hr = mbcs_2_utf16le_windows((const char *)src, src_size, (wchar_t *)dst, &dst_cbsize);
        *dst_size = dst_cbsize << 1;
        return hr;
#else
        return mbcs_2_utf16le_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT utf16le_2_mbcs(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
        _CHECKSIZE(src_size);
#ifdef WIN32
        return utf16le_2_mbcs_windows((const wchar_t *)src, src_size >> 1, (char *)dst, dst_size);
#else
        return utf16le_2_mbcs_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT mbcs_2_utf32le(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
#ifdef WIN32
        _UNUSED_PARAM;
        return E_NOTIMPL;
#else
        return mbcs_2_utf32le_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT utf32le_2_mbcs(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
#ifdef WIN32
        _UNUSED_PARAM;
        return E_NOTIMPL;
#else
        return utf32le_2_mbcs_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT mbcs_2_utf8(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
#ifdef WIN32
        _UNUSED_PARAM;
        return E_NOTIMPL;
#else
        return mbcs_2_utf8_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT utf8_2_mbcs(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
#ifdef WIN32
        _UNUSED_PARAM;
        return E_NOTIMPL;
#else
        return utf8_2_mbcs_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT utf8_2_utf16le(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
        _CHECKSIZE(*dst_size);
#ifdef WIN32
        size_t z = *dst_size;
        z = z >> 1;
        HRESULT hr;
        hr = utf8_2_utf16le_windows((const char *)src, src_size, (wchar_t *)dst, &z);
        *dst_size = z << 1;
        return hr;
#else
        return utf8_2_utf16le_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT utf16le_2_utf8(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
        _CHECKSIZE(src_size);
#ifdef WIN32
        return utf16le_2_utf8_windows((const wchar_t *)src, src_size >> 1, (char *)dst, dst_size);
#else
        return utf16le_2_utf8_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT utf8_2_utf32le(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
#ifdef WIN32
        _UNUSED_PARAM;
        return E_NOTIMPL;
#else
        return utf8_2_utf32le_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT utf32le_2_utf8(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
#ifdef WIN32
        _UNUSED_PARAM;
        return E_NOTIMPL;
#else
        return utf32le_2_utf8_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT utf16le_2_utf32le(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
#ifdef WIN32
        _UNUSED_PARAM;
        return E_NOTIMPL;
#else
        return utf16le_2_utf32le_posix(src, src_size, dst, dst_size);
#endif
}

HRESULT utf32le_2_utf16le(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
#ifdef WIN32
        _UNUSED_PARAM;
        return E_NOTIMPL;
#else
        return utf32le_2_utf16le_posix(src, src_size, dst, dst_size);
#endif
}

}; // namespace encoding

//static const char* kEncodeUtf8Header = "\xEF\xBB\xBF";
//static const char* kEncodeUtf16LittleEndianHeader="\xFF\xFE";
//static const char* kEncodeUtf16BigEndianHeader = "\xFE\xFF";
//static const char* kEncodeUtf32LittleEndianHeader= "\xFF\xFE\x00\x00";
//static const char* kEncodeUtf32BigEndianHeader = "\x00\x00\xFE\xFF";
