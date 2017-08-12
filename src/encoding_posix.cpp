


#ifndef WIN32

#include <iconv.h>
#include <errno.h>
#include <locale.h>
#include <stdlib.h>
#include "encoding_posix.h"

HRESULT encoding_convt_cbsize(const char *srccode, const char *dstcode, const char *src, size_t src_cbsize,
                              size_t *dst_cbsize) {
    iconv_t cd;
    char buffer[0x100] = {};
    size_t buffer_size = 0x100;
    char *inbuf = (const_cast<char *>(src));
    const char *inbuf_end = inbuf + src_cbsize;
    char *outbuf = buffer;
    HRESULT hr = S_OK;
    size_t insize = src_cbsize;
    size_t outbytesleft = buffer_size;
    size_t retsize = 0;
    bool berror = false;

    cd = iconv_open(dstcode, srccode);
    if (cd == (iconv_t) (-1)) return E_FAIL;

    while (iconv(cd, &inbuf, &insize, &outbuf, &outbytesleft) == (size_t) (-1)) {
        // if use global variable `errno`, so I don't think iconv() is thread safe.
        if (errno == E2BIG) {
            retsize += buffer_size - outbytesleft;
            outbuf = buffer;
            outbytesleft = buffer_size;
        } else if ((errno == EILSEQ) && (insize > 0) && inbuf < inbuf_end) {
            // invalid multibyte sequence, then skip it.
            ++inbuf;
            --insize;
            continue;
        } else {
            berror = true;
            break;
        }
    }
    if (berror || (insize != 0)) hr = E_FAIL;
    else {
        retsize += buffer_size - outbytesleft;
        *dst_cbsize = retsize;
        hr = S_OK;
    }
    iconv_close(cd);
    return hr;
}

HRESULT encoding_convt(const char *srccode, const char *dstcode, const char *src, size_t src_cbsize, char *dst,
                       size_t *dst_cbsize) {
    iconv_t cd;
    char *inbuf = const_cast<char *>(src);
    const char *inbuf_end = inbuf + src_cbsize;
    char *outbuf = dst;
    HRESULT hr = S_OK;
    size_t insize = src_cbsize;
    size_t outbytesleft = *dst_cbsize;
    size_t retsize = 0;
    bool berror = false;

    cd = iconv_open(dstcode, srccode);
    if (cd == (iconv_t) (-1)) return E_FAIL;


    while (iconv(cd, &inbuf, &insize, &outbuf, &outbytesleft) == (size_t) (-1)) {
        if ((errno == EILSEQ) && (insize > 0) && (inbuf < inbuf_end)) {
            ++inbuf;
            --insize;
            continue;
        } else {
            berror = true;
            break;
        }
    }
    if (berror) hr = E_FAIL;
    else {
        retsize = *dst_cbsize - outbytesleft;
        *dst_cbsize = retsize;
        hr = S_OK;
    }
    iconv_close(cd);
    return hr;
}

//
// !!! src must be NULL terminate.
HRESULT utf32le_2_mbcs_posix2(const void *src, size_t, void *dst, size_t *dst_size) {
    char *restore_val = setlocale(LC_ALL,
                                  NULL); // not thread safe, `restore_val`'s memory may be allocated in static storage.
    char *restore_val2 = strdup(restore_val);
    HRESULT hr = S_OK;
    size_t z;

    setlocale(LC_ALL, "zh_CN.GBK");

    if (dst) z = wcstombs((char *) dst, (const wchar_t *) src, *dst_size);
    else z = wcstombs(NULL, (const wchar_t *) src, 0);

    if (z == size_t(-1)) hr = E_FAIL;
    else *dst_size = z;

    setlocale(LC_ALL, restore_val2);
    free(restore_val2);
    return hr;
}

//
// !!! src must be NULL terminate.
HRESULT mbcs_2_utf32le_posix2(const void *src, size_t src_size, void *dst, size_t *dst_size) {
    char *restore_val = setlocale(LC_ALL, NULL);
    char *restore_val2 = strdup(restore_val);
    HRESULT hr = S_OK;
    size_t z;

    setlocale(LC_ALL, "zh_CN.GBK");
    if (dst) z = mbstowcs((wchar_t *) dst, (const char *) src, *dst_size >> 1);
    else z = mbstowcs(NULL, (const char *) src, 0);
    if (z == size_t(-1)) hr = E_FAIL;
    else *dst_size = z << 1;
    setlocale(LC_ALL, restore_val2);
    free(restore_val2);
    return hr;
}

#endif
