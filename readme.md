
# Cpp Cross Platform Encoding [![Build Status](https://travis-ci.org/fooofei/cpp_cross_platform_encoding.svg?branch=master)](https://travis-ci.org/fooofei/cpp_cross_platform_encoding)

### use

```

1/2 
#include "encoding/encoding.h" // using for raw convert, using bytes
#include "encoding/encoding_std.h" // using for stl strings, std::string, std::wstring, std::u16string
#include "encoding/u16string_bytes.h"// using for lower than c++11, that not have std::u16string

2/2
add in CMakeLists.txt

if (NOT TARGET encoding)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../cpp_cross_platform_encoding  build_encoding)
endif ()
target_link_libraries(${BINARY_NAME} encoding)

```

### snippet

```c
// c language's helper function

static int
utf8_2_utf16le_windows(const char *src, size_t src_size, wchar_t *dst, size_t *dst_size)
{
    int r = MultiByteToWideChar(CP_UTF8, 0, src, (int)(src_size), dst, (int)(*dst_size));
    if (r <= 0)
    {
        return -1;
    }
    else
    {
        *dst_size = (size_t)(r);
        return 0;
    }
}

static int
utf8_2_utf16le_windows2(const char * src, size_t src_size, wchar_t ** out_dst, size_t * out_dst_size)
{
    int ret;
    wchar_t * dst = 0;
    size_t dst_size = 0;
    size_t rsize=0;

    ret = utf8_2_utf16le_windows(src, src_size, 0, &dst_size);
    if (0 == ret && dst_size < 0x10000)
    {
        // remember to call free()
        dst_size += 1;
        dst = (wchar_t *)calloc(1, sizeof(wchar_t)*dst_size);
        if (!dst) return -ENOMEM;
        rsize = dst_size;
        utf8_2_utf16le_windows(src, src_size, dst, &rsize);
        if(rsize>=dst_size)
        {
            free(dst);
            return -1;
        }
        *out_dst = dst;
        dst[rsize]=0;
        *out_dst_size = rsize;
        return 0;
    }
    return -1;
}

static int
utf16le_2_utf8_windows(const wchar_t *src, size_t src_size, char *dst, size_t *dst_size)
{
    int r = WideCharToMultiByte(CP_UTF8, 0, src, (int)(src_size), dst, (int)(*dst_size), NULL, NULL);
    if (r <= 0)
    {
        return -1;
    }
    else
    {
        *dst_size = (size_t)(r);
        return 0;
    }
}

static int
utf16le_2_utf8_windows2(const wchar_t *src, size_t src_size, char ** out_dst, size_t * out_dst_size)
{
    int ret;
    char * dst = 0;
    size_t dst_size = 0;
    size_t rsize=0;

    ret = utf16le_2_utf8_windows(src, src_size, 0, &dst_size);
    if (0 == ret && dst_size<0x10000)
    {
        // remember to call free()
        dst_size += 1;
        dst = (char *)calloc(1, dst_size);
        if (!dst) return -ENOMEM;
        rsize=dst_size;
        utf16le_2_utf8_windows(src, src_size, dst, &rsize);
        if(rsize>=dst_size)
        {
            free(dst);
            return -1;
        }
        *out_dst = dst;
        dst[rsize]=0;
        *out_dst_size = rsize;
        return 0;
    }
    return -1;
}

```

### refs

[UTF-8 遍地开花] http://utf8everywhere.org/zh-cn
