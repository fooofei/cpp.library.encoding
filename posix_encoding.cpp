
#include "posix_encoding.h"

#ifndef WIN32

#include <errno.h>
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


    };
};

#endif
