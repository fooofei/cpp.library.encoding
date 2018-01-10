

#ifndef CORE_ENCODING_WIN_H
#define CORE_ENCODING_WIN_H

#ifdef WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#undef WIN32_LEAN_AND_MEAN

//
// if src is NULL terminate, then src_size can be -1, otherwise you must explicit give src_size.
// return size is need size, not include NULL terminate, and dst_size no need to include NULL terminate size,
//     no need to +1.


HRESULT
_lasterror_2_hresult();

HRESULT
utf16le_2_mbcs_windows(const wchar_t *src, size_t src_size, char *dst, size_t *dst_size);

HRESULT
mbcs_2_utf16le_windows(const char *src, size_t src_size, wchar_t *dst, size_t *dst_size);


HRESULT
utf8_2_utf16le_windows(const char *src, size_t src_size, wchar_t *dst, size_t *dst_size);


HRESULT
utf16le_2_utf8_windows(const wchar_t *src, size_t src_size, char *dst, size_t *dst_size);


#endif // WIN32
#endif //CORE_ENCODING_WIN_H