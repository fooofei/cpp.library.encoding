
#ifndef CORE_POSIX_ENCODING_H_
#define CORE_POSIX_ENCODING_H_


#ifndef WIN32
#include <string.h>

namespace base { 
    namespace encoding {

        typedef int HRESULT;
        #ifndef E_INVALIDARG 
        #define E_INVALIDARG  (HRESULT)0x80070057L
        #endif
        #ifndef E_OUTOFMEMORY
        #define E_OUTOFMEMORY (HRESULT)0x8007000EL
        #endif
        #ifndef S_OK
        #define S_OK    (HRESULT)0L
        #endif
        #ifndef E_FAIL
        #define E_FAIL  (HRESULT)0x80004005L
        #endif
        #ifndef FAILED
        #define FAILED(hr) (((HRESULT)(hr)) < 0)
        #endif
        


        static const size_t	 kInvalidSize = size_t(-1);


        HRESULT encoding_convt_cbsize(const char * srccode, const char * dstcode
            ,const char * src , size_t src_cbsize
            ,size_t * out_size);
        HRESULT encoding_convt(const char * srccode, const char * dstcode, const char * src, size_t srcCbsize
            ,char * dst, size_t * dstCbSize);

        inline
            HRESULT iconv_posix(const char * code1, const char * code2, 
            const void * src, size_t src_size, 
            void * dst, size_t * dst_size)
        {
            if (dst)
            {
                return encoding_convt(code1,code2,(const char*)src,src_size,(char*)dst,dst_size);

            }
            else
            {
                return encoding_convt_cbsize(code1,code2,(const char *)src,src_size,dst_size);
            }
        }

#define ICONV_CODE_UTF16LE "utf-16le"
#define ICONV_CODE_ANSI "gb18030//IGNORE"  // the new version of GBK, recommand
//#define ICONV_CODE_ANSI "gbk" // the subset of gb18030, not recommand
#define ICONV_CODE_UTF8 "utf-8"
#define ICONV_CODE_UTF32LE "utf-32le"
    inline
        HRESULT utf16le_2_ansi_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
    {
            return iconv_posix(ICONV_CODE_UTF16LE,ICONV_CODE_ANSI,src,src_size,dst,dst_size);
        }
        inline
            HRESULT ansi_2_utf16le_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_ANSI,ICONV_CODE_UTF16LE,src,src_size,dst,dst_size);
        }

        inline
            HRESULT utf8_2_utf16le_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_UTF8,ICONV_CODE_UTF16LE,src,src_size,dst,dst_size);
        }
        inline
            HRESULT utf16le_2_utf8_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_UTF16LE,ICONV_CODE_UTF8,src,src_size,dst,dst_size);
        }

        inline
            HRESULT ansi_2_utf32le_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_ANSI,ICONV_CODE_UTF32LE,src,src_size,dst,dst_size);
        }
        inline
            HRESULT utf32le_2_ansi_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_UTF32LE,ICONV_CODE_ANSI,src,src_size,dst,dst_size);
        }

        inline
            HRESULT utf32le_2_utf8_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_UTF32LE,ICONV_CODE_UTF8,src,src_size,dst,dst_size);
        }
        inline
            HRESULT utf8_2_utf32le_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_UTF8,ICONV_CODE_UTF32LE,src,src_size,dst,dst_size);
        }

        inline
            HRESULT utf32le_2_utf16le_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_UTF32LE, ICONV_CODE_UTF16LE, src, src_size, dst, dst_size);
        }

        inline 
            HRESULT utf16le_2_utf32le_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_UTF16LE, ICONV_CODE_UTF32LE, src, src_size, dst, dst_size);
        }

        inline 
            HRESULT ansi_2_utf8_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_ANSI, ICONV_CODE_UTF8, src, src_size, dst, dst_size);
        }

        inline 
            HRESULT utf8_2_ansi_posix(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return iconv_posix(ICONV_CODE_UTF8, ICONV_CODE_ANSI,src, src_size, dst, dst_size);
        }

        //
        // !!! src must be NULL terminate.
        HRESULT utf32le_2_ansi_posix2(const void * src, size_t , void * dst, size_t * dst_size);

        //
        // !!! src must be NULL terminate.
        HRESULT ansi_2_utf32le_posix2(const void * src, size_t src_size, void * dst, size_t * dst_size);
    };
} ; 

#endif

#endif //CORE_POSIX_ENCODING_H_