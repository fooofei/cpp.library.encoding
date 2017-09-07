
#pragma once

#ifndef CORE_ENCODING_U16STRING_BYTES_H
#define CORE_ENCODING_U16STRING_BYTES_H

#include <string>
#include <vector>
#include <string.h>
#include "hresult.h"

//
// std::wstring is different on Windows and Linux.
// on Windows sizeof(wchar_t) is equal with sizeof(unsigned short) ==2,
// but on linux sizeof(wchat_t) is equal with sizeof(unsigned int) == 4.
// user the class u16string_bytes_t, to make sure all platform use same memory size.
// std::u16string is the same effect, but std::u16string is c++11 above.
class u16string_bytes_t
{
  public:
    typedef std::vector<unsigned char> u16string_bytes_type;

//for debug
//typedef std::wstring u16string_bytes_type;

#ifdef WIN32
    typedef wchar_t char16_type;
#else
    typedef unsigned short char16_type;
#endif

    typedef char16_type value_type;

  private:
    u16string_bytes_type buf_;

  public:
    u16string_bytes_t()
    {
        //assert sizeof(char16_type) >= sizeof(u16string_bytes_type::value_type);
    }

    explicit u16string_bytes_t(const u16string_bytes_t &rhs)
    {
        assign(rhs.c_str(), rhs.size());
    }

    u16string_bytes_t(const char16_type *p, size_t l)
    {
        assign(p, l);
    }

    ~u16string_bytes_t()
    {
        ;
    }

    const void *ptr() const
    {
        if (empty())
            return NULL;
        return &buf_[0];
    }

    size_t size_of_bytes() const
    {
        return buf_.size() * sizeof(u16string_bytes_type::value_type);
    }

    void *ptr()
    {
        if (empty())
            return NULL;
        return &buf_[0];
    }

    const char16_type *char16_ptr() const
    {
        return (const char16_type *)ptr();
    }

    size_t char16_size() const
    {
        return size_of_bytes() / sizeof(char16_type);
    }

    bool empty() const
    {
        return buf_.empty();
    }

    size_t size() const
    {
        return char16_size();
    }

    const char16_type *c_str() const
    {
        return char16_ptr();
    }

    HRESULT assign(const std::string &s);

    HRESULT assign(const char16_type *p, size_t l);

    HRESULT assign(const u16string_bytes_t &rhs)
    {
        return assign(rhs.c_str(), rhs.size());
    }

    HRESULT to_string(std::string &s) const;

    void clear()
    {
        buf_.clear();
    }

    void resize(size_t s)
    {
        buf_.resize(s * sizeof(value_type) / sizeof(u16string_bytes_type::value_type));
    }

    value_type &operator[](const size_t off)
    {
        return *((value_type *)ptr() + off);
    }

    const value_type &operator[](const size_t off) const
    {
        return *(char16_ptr() + off);
    }

    void tolower();

    // return char16 size, not bytes size.
    size_t find(const char16_type *substr, size_t off, size_t subsize) const;

    size_t find(const u16string_bytes_t &rhs, size_t off = 0) const
    {
        return find(rhs.c_str(), off, rhs.size());
    }

    bool endswith(const u16string_bytes_t &rhs) const
    {
        if (rhs.size() <= size())
        {
            return find(rhs, size() - rhs.size()) < size();
        }
        return false;
    }

    bool startswith(const u16string_bytes_t &rhs) const
    {
        if (rhs.size() <= size())
        {
            return 0 == memcmp(c_str(), rhs.c_str(), rhs.size_of_bytes());
        }
        return false;
    }

    bool startswith(char16_type c) const
    {
      u16string_bytes_t v(&c, 1);
        return startswith(v);
    }

    bool endswith(char16_type c) const
    {
      u16string_bytes_t v(&c, 1);
        return endswith(v);
    }

    bool is(const u16string_bytes_t &rhs) const
    {
        return rhs.size() == size() && startswith(rhs);
    }

    size_t find_first_not_of(const u16string_bytes_t &rhs) const;

    size_t find_last_not_of(const u16string_bytes_t &rhs) const;

    void lstrip(const u16string_bytes_t &s);

    void rstrip(const u16string_bytes_t &s);

    void trim_head(const u16string_bytes_t &s)
    {
        lstrip(s);
    }

    void trim_tail(const u16string_bytes_t &s)
    {
        return rstrip(s);
    }
};

#endif //CORE_ENCODING_U16STRING_BYTES_H

#ifndef ASSERT_EXCEPT
#define ASSERT_EXCEPT(exp)                                                      \
    do                                                                          \
    {                                                                           \
        if (!(exp))                                                             \
        {                                                                       \
            fprintf(stderr, "unexcept file:%s, line:%d\n", __FILE__, __LINE__); \
            exit(-1);                                                           \
        }                                                                       \
    } while (0);
#endif //ASSERT_EXCEPT
