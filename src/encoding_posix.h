
#ifndef CORE_ENCODING_POSIX_H
#define CORE_ENCODING_POSIX_H

#ifndef WIN32

#include <stdint.h>
#include <stdlib.h>

#include "../include/encoding/hresult.h"

static size_t kInvalidSize = (size_t)(-1);


HRESULT
encoding_convt_cbsize(const char *srccode, const char *dstcode,
  const char *src, size_t src_cbsize, size_t *);

HRESULT
encoding_convt(const char *srccode, const char *dstcode, const char *src, size_t srcCbsize,
  char *, size_t *);



// even if inline, here will have multi define link error.
HRESULT
iconv_posix(const char *code1, const char *code2,
    const void *src, size_t src_size,
    void *dst, size_t *dst_size);

#define ICONV_CODE_UTF16LE "utf-16le"
#define ICONV_CODE_MBCS "gb18030//IGNORE" // the new version of GBK, recommand
//#define ICONV_CODE_ANSI "gbk" // the subset of gb18030, not recommand
#define ICONV_CODE_UTF8 "utf-8"
#define ICONV_CODE_UTF32LE "utf-32le"


HRESULT
utf16le_2_mbcs_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);


HRESULT
mbcs_2_utf16le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);


HRESULT
utf8_2_utf16le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);

HRESULT
utf16le_2_utf8_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);


HRESULT
mbcs_2_utf32le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);


HRESULT
utf32le_2_mbcs_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);

HRESULT
utf32le_2_utf8_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);

HRESULT
utf8_2_utf32le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);


HRESULT
utf32le_2_utf16le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);


HRESULT
utf16le_2_utf32le_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);


HRESULT
mbcs_2_utf8_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);


HRESULT
utf8_2_mbcs_posix(const void *src, size_t src_size, void *dst, size_t *dst_size);

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
