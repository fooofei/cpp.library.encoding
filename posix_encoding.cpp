
#include "posix_encoding.h"

#ifndef WIN32
#include <iconv.h>
#include <errno.h>
#include <locale.h>

#include <stdlib.h>

namespace base { 
    namespace encoding {

        HRESULT encoding_convt_cbsize(const char* srccode,const char* dstcode,
            const char* src , size_t src_cbsize,
            size_t * out_size)
        {
            iconv_t cd;
            char dst[0x100]={};
            size_t dst_cbsize=0x100;
            char* inbuf(const_cast<char*>(src));
            char *outbuf (dst);

            cd = iconv_open(dstcode, srccode);
            if (cd == (iconv_t)(-1)) return E_FAIL;

            size_t insize = src_cbsize;
            size_t outbytesleft = dst_cbsize;
            size_t rtsize = 0;
            bool berror = false;
            while(iconv(cd, &inbuf, &insize, &outbuf, &outbytesleft) == kInvalidSize)
            {
				// if use global variable `errno`, so I don't think iconv() is thread safe.
                if( errno == E2BIG )
                {
                    outbuf=dst;
                    rtsize += dst_cbsize-outbytesleft;
                    outbytesleft=dst_cbsize;
                }
                else if (errno == EILSEQ && insize>0)
                {
					// invalid multibyte sequence, then skip it.
                    ++inbuf;
                    --insize;
                    continue;
                }
                else
                {
                    berror = true;
                    break;
                }
            }
            if( berror ) 
            {
                return E_FAIL;
            }
            else rtsize += dst_cbsize-outbytesleft;
            iconv_close(cd);
            *out_size = dst_cbsize;
            return S_OK;
        }

        HRESULT encoding_convt(const char* srccode,const char* dstcode,const char* src , size_t srcCbsize ,
            char* dst , size_t * dstCbSize)
        {
            iconv_t cd;
            char* inbuf(const_cast<char*>(src));
            char *outbuf (dst);

            cd = iconv_open(dstcode,srccode);
            if (cd == (iconv_t)(-1)) return E_FAIL;

            size_t insize = srcCbsize;
            size_t outbytesleft = *dstCbSize;
            size_t rtsize = 0;
            bool berror = false;
            while (iconv(cd, &inbuf, &insize, &outbuf, &outbytesleft) == kInvalidSize )
            {
                if( errno == EILSEQ && insize>0)
                {
                    ++inbuf;
                    --insize;
                    continue;
                }
                else
                {
                    berror = true;
                    break;
                }
            }
            if( berror ) return E_FAIL;
            else rtsize = *dstCbSize - outbytesleft;
            iconv_close(cd);
            *dstCbSize = rtsize;
            return S_OK;
        }

        //
        // !!! src must be NULL terminate.
        HRESULT utf32le_2_ansi_posix2(const void * src, size_t , void * dst, size_t * dst_size)
        {
            char * restore_val = setlocale (LC_ALL, NULL); // not thread safe, `restore_val`'s memory may be allocated in static storage.
            char * restore_val2 = strdup (restore_val);
            HRESULT hr=S_OK;
            size_t z;

            setlocale(LC_ALL, "zh_CN.GBK");

            if (dst) z = wcstombs((char *)dst,(const wchar_t *)src,*dst_size); 
            else z = wcstombs(NULL,(const wchar_t *)src,0);

            if(z == size_t(-1)) hr = E_FAIL;
            else *dst_size = z;

            setlocale(LC_ALL, restore_val2);
            free(restore_val2);
            return hr;
        }

        //
        // !!! src must be NULL terminate.
        HRESULT ansi_2_utf32le_posix2(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            char * restore_val = setlocale (LC_ALL, NULL);
            char * restore_val2 = strdup (restore_val);
            HRESULT hr=S_OK;
            size_t z;

            setlocale(LC_ALL, "zh_CN.GBK");
            if (dst) z = mbstowcs((wchar_t *)dst,(const char *)src,*dst_size>>1);
            else z = mbstowcs(NULL,(const char *)src,0);
            if (z == size_t(-1)) hr = E_FAIL;
            else  *dst_size = z<<1; 
            setlocale(LC_ALL, restore_val2);
            free(restore_val2);
            return hr;
        }
    };
};

#endif
