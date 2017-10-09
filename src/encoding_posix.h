
#ifndef CORE_ENCODING_POSIX_H
#define CORE_ENCODING_POSIX_H

#ifndef WIN32

#include <string.h>
#include "../include/encoding/hresult.h"

static size_t kInvalidSize = (size_t)(-1);

#ifdef __cplusplus
extern "C" {
#endif

HRESULT
encoding_convt_cbsize(const char *srccode, const char *dstcode,
  const char *src, size_t src_cbsize, size_t *);

HRESULT
encoding_convt(const char *srccode, const char *dstcode, const char *src, size_t srcCbsize,
  char *, size_t *);
#ifdef __cplusplus
}
#endif

inline
HRESULT
iconv_posix(const char *code1, const char *code2,
  const void *src, size_t src_size,
  void *dst, size_t *dst_size)
{
  if (dst)
  {
    return encoding_convt(code1, code2, (const char *)src, src_size, (char *)dst, dst_size);
  }
  else
  {
    return encoding_convt_cbsize(code1, code2, (const char *)src, src_size, dst_size);
  }
}

#define ICONV_CODE_UTF16LE "utf-16le"
#define ICONV_CODE_MBCS "gb18030//IGNORE" // the new version of GBK, recommand
//#define ICONV_CODE_ANSI "gbk" // the subset of gb18030, not recommand
#define ICONV_CODE_UTF8 "utf-8"
#define ICONV_CODE_UTF32LE "utf-32le"

inline
HRESULT
utf16le_2_mbcs_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_UTF16LE, ICONV_CODE_MBCS, src, src_size, dst, dst_size);
}

inline
HRESULT
mbcs_2_utf16le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_MBCS, ICONV_CODE_UTF16LE, src, src_size, dst, dst_size);
}

inline
HRESULT
utf8_2_utf16le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_UTF8, ICONV_CODE_UTF16LE, src, src_size, dst, dst_size);
}

inline
HRESULT
utf16le_2_utf8_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_UTF16LE, ICONV_CODE_UTF8, src, src_size, dst, dst_size);
}

inline
HRESULT
mbcs_2_utf32le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_MBCS, ICONV_CODE_UTF32LE, src, src_size, dst, dst_size);
}

inline
HRESULT
utf32le_2_mbcs_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_UTF32LE, ICONV_CODE_MBCS, src, src_size, dst, dst_size);
}

inline
HRESULT
utf32le_2_utf8_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_UTF32LE, ICONV_CODE_UTF8, src, src_size, dst, dst_size);
}

inline
HRESULT
utf8_2_utf32le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_UTF8, ICONV_CODE_UTF32LE, src, src_size, dst, dst_size);
}

inline
HRESULT
utf32le_2_utf16le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_UTF32LE, ICONV_CODE_UTF16LE, src, src_size, dst, dst_size);
}

inline
HRESULT
utf16le_2_utf32le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_UTF16LE, ICONV_CODE_UTF32LE, src, src_size, dst, dst_size);
}

inline
HRESULT
mbcs_2_utf8_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_MBCS, ICONV_CODE_UTF8, src, src_size, dst, dst_size);
}

inline
HRESULT
utf8_2_mbcs_posix(const void *src, size_t src_size, void *dst, size_t *dst_size)
{
  return iconv_posix(ICONV_CODE_UTF8, ICONV_CODE_MBCS, src, src_size, dst, dst_size);
}

//
// !!! src must be NULL terminate.
HRESULT
utf32le_2_mbcs_posix2(const void *src, size_t, void *dst, size_t *dst_size);

//
// !!! src must be NULL terminate.
HRESULT
mbcs_2_utf32le_posix2(const void *src, size_t src_size, void *dst, size_t *dst_size);

#endif // !WIN32

#endif //CORE_ENCODING_POSIX_H
