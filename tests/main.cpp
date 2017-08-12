
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <stdint.h>
#include <stdlib.h>
#include "../include/encoding/hresult.h"
#include "encoding/encoding_std.h"
#include "encoding/u16string_bytes.h"

static
int test_u16string_bytes()
{
#ifdef WIN32
    std::wstring s(L"helloWorld\t");

    u16string_bytes_t a;
    u16string_bytes_t b(s.c_str(), s.size());

    ASSERT_EXCEPT(b.find(L"e", 0, 1) == s.find(L"e", 0, 1));

    ASSERT_EXCEPT(b.startswith(L'h') == true);
    ASSERT_EXCEPT(b.startswith(L'e') == false);
    ASSERT_EXCEPT(b.endswith(L'\t') == true);
    ASSERT_EXCEPT(b.startswith(L'd') == false);

    b.tolower();
    b.trim_tail(u16string_bytes_t(std::wstring(L"\t").c_str(), 1));
    ASSERT_EXCEPT(b.is(u16string_bytes_t(L"helloworld", 10)));
#endif
    printf("pass test_u16string_bytes()\n");

    return 0;
}

static
unsigned fsize(FILE * f)
{
    fseek(f, SEEK_SET, SEEK_END);
    long size = ftell(f);
    rewind(f);
    return (unsigned)size;
}

typedef std::vector<uint8_t> bytes_buffer_t;
void from_file(const char * filename, bytes_buffer_t & b)
{
    FILE * f = NULL;
    f = fopen(filename, "rb");
    ASSERT_EXCEPT(f != NULL);
    unsigned s = fsize(f);
    ASSERT_EXCEPT(s > 0);
    b.resize(s);
    size_t r = fread(&b[0], 1, s, f);
    ASSERT_EXCEPT(r == s);
    fclose(f);
}

static
int test_encoding_convert()
{

    bytes_buffer_t buf_gb18030;
    bytes_buffer_t buf_utf8;
    bytes_buffer_t buf_utf16le;

    from_file("data_gb18030.txt", buf_gb18030);
    from_file("data_utf8.txt", buf_utf8);
    from_file("data_utf16le.txt", buf_utf16le);


    std::string gb18030((const char *)&buf_gb18030[0], buf_gb18030.size());
    std::string utf8((const char *)&buf_utf8[0], buf_utf8.size());
    u16string_bytes_t utf16le((const u16string_bytes_t::char16_type *)&buf_utf16le[0]
        , buf_utf16le.size()/ sizeof(u16string_bytes_t::char16_type)
        );

    {
        std::string utf8_2;
        string_2_utf8(gb18030, utf8_2);
        ASSERT_EXCEPT(utf8_2.size() == utf8.size());
        ASSERT_EXCEPT(0 == memcmp(utf8.c_str(), utf8_2.c_str(), utf8.size()));
    }

    {
        std::string gb18030_2;
        utf8_2_string(utf8, gb18030_2);
        ASSERT_EXCEPT(gb18030.size() == gb18030_2.size());
        ASSERT_EXCEPT(0 == memcmp(gb18030_2.c_str(), gb18030.c_str(), gb18030_2.size()));

    }


    {
        u16string_bytes_t utf16le_2;
        string_2_u16string(gb18030, utf16le_2);
        ASSERT_EXCEPT(utf16le.size() == utf16le_2.size());
        ASSERT_EXCEPT(0 == memcmp(utf16le.c_str(), utf16le_2.c_str(),utf16le.size_of_bytes()) );
    }

    {
        std::string gb18030_2;
        u16string_2_string(utf16le, gb18030_2);
        ASSERT_EXCEPT(gb18030.size() == gb18030_2.size());
        ASSERT_EXCEPT(0 == memcmp(gb18030_2.c_str(), gb18030.c_str(), gb18030_2.size()));
    }

    printf("pass test_encoding_convert\n");

    return 0;
}

int main()
{
   
    test_u16string_bytes();

    test_encoding_convert();

    return 0;
}
