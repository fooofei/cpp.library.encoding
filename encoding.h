
#ifndef ENCODING_H_
#define ENCODING_H_

#ifdef _WIN32
#include "windows_encoding.h"
#else
#include "posix_encoding.h"
#endif //_WIN32

namespace base { 
    namespace encoding{

        // 是否是偶数
        inline 
            bool is_even_size(size_t size)
        {
            return (((size & 0x1)^0x1) == 1);
        }

        // 00fe316d3e96a0d4964a0fa60bbd7ae7 尾部有垃圾数据 导致 size 没对齐
        #define CHECKSIZE(size) do {if( !is_even_size(size))	{ if(size) {--size;}} } while(0);

        inline
            HRESULT ansi_2_utf16le(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            CHECKSIZE(*dst_size);
            #ifdef WIN32
            size_t dst_cbsize = *dst_size; dst_cbsize = dst_cbsize >> 1;
            HRESULT hr;
            hr = ansi_2_utf16le_windows((const char *)src,src_size,(wchar_t*)dst,&dst_cbsize);
            *dst_size = dst_cbsize<<1;
            return hr;
            #else
            return ansi_2_utf16le_posix(src,src_size,dst,dst_size);
            #endif
        }
        inline
            HRESULT utf16le_2_ansi(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            CHECKSIZE(src_size);
            #ifdef WIN32
            return utf16le_2_ansi_windows((const wchar_t *)src,src_size>>1,(char*)dst,dst_size);
            #else
            return utf16le_2_ansi_posix(src,src_size,dst,dst_size);
            #endif
        }

        inline
            HRESULT utf8_2_utf16le(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            CHECKSIZE(*dst_size);
            #ifdef WIN32
            size_t z = *dst_size; z =  z >> 1;
            HRESULT hr;
            hr = utf8_2_utf16le_windows((const char *)src, src_size,(wchar_t*)dst,&z);
            *dst_size = z << 1;
            return hr;
            #else
            return utf8_2_utf16le_posix(src,src_size,dst,dst_size);
            #endif
        }

        inline 
            HRESULT utf16le_2_utf8(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            CHECKSIZE(src_size);
            #ifdef WIN32
            return utf16le_2_utf8_windows((const wchar_t *)src,src_size>>1,(char*)dst,dst_size);
            #else
            return utf16le_2_utf8_posix(src,src_size,dst,dst_size);
            #endif
        }


        

        //
        // type redefines
        //

        inline
            HRESULT string_2_wstring(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            #ifdef WIN32
            return ansi_2_utf16le(src,src_size,dst,dst_size);
            #else
            return ansi_2_utf32le_posix(src,src_size,dst,dst_size);
            #endif
        }
        inline
            HRESULT wstring_2_string(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            #ifdef WIN32
            return utf16le_2_ansi(src,src_size,dst,dst_size);
            #else
            return utf32le_2_ansi_posix(src,src_size,dst,dst_size);
            #endif
        }

        inline
            HRESULT wstring_2_utf8(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            #ifdef WIN32
            return utf16le_2_utf8(src,src_size,dst,dst_size);
            #else
            return utf32le_2_utf8_posix(src,src_size,dst,dst_size);
            #endif
        }
        inline
            HRESULT utf8_2_wstring(const void * src, size_t src_size, void * dst, size_t  * dst_size)
        {
            #ifdef WIN32
            return utf8_2_utf16le(src,src_size,dst,dst_size);
            #else
            return utf8_2_utf32le_posix(src,src_size,dst,dst_size);
            #endif
        }

        inline 
            HRESULT string_2_u16string(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return ansi_2_utf16le(src, src_size, dst, dst_size);
        }
        inline 
            HRESULT u16string_2_string(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            return utf16le_2_ansi(src, src_size, dst, dst_size);
        }
        
        inline 
            HRESULT wstring_2_u16string(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            // Not include NULL terminate.
            #ifdef WIN32
            if (!dst_size) return E_INVALIDARG;
            if (dst)
            {
                if (*dst_size < src_size) return E_OUTOFMEMORY;
                memcpy(dst, src, src_size);
            }
            *dst_size = src_size;
            return S_OK;
            #else
            return utf32le_2_utf16le_posix(src, src_size, dst, dst_size);
            #endif
        }

        inline 
            HRESULT u16string_2_wstring(const void * src, size_t src_size, void * dst, size_t * dst_size)
        {
            #ifdef WIN32
            if (!dst_size) return E_INVALIDARG;
            if (dst)
            {
                if (*dst_size < src_size) return E_OUTOFMEMORY;
                memcpy(dst, src, src_size);
            }
            *dst_size = src_size;
            return S_OK;
            #else
            return utf16le_2_utf32le_posix(src, src_size, dst, dst_size);
            #endif
        }

        //static const char* kEncodeUtf8Header = "\xEF\xBB\xBF";
        //static const char* kEncodeUtf16LittleEndianHeader="\xFF\xFE";
        //static const char* kEncodeUtf16BigEndianHeader = "\xFE\xFF";
        //static const char* kEncodeUtf32LittleEndianHeader= "\xFF\xFE\x00\x00";
        //static const char* kEncodeUtf32BigEndianHeader = "\x00\x00\xFE\xFF";

    }; //namespace 
}; // namespace 

#endif // ENCODING_H_