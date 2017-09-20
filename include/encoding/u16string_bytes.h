

#ifndef CORE_ENCODING_U16STRING_BYTES_H
#define CORE_ENCODING_U16STRING_BYTES_H
#pragma once

#include <string>
#include <vector>
#include <stdint.h>
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
  typedef std::vector<uint8_t> u16string_bytes_type;

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
  u16string_bytes_t();
  explicit u16string_bytes_t(const u16string_bytes_t &rhs);
  u16string_bytes_t(const char16_type *p, size_t l);
  ~u16string_bytes_t();

  const void *ptr() const;
  size_t size_of_bytes() const;

  void *ptr();
  const char16_type *char16_ptr() const;
  size_t char16_size() const;
  bool empty() const;

  size_t size() const;
  const char16_type *c_str() const;
  HRESULT assign(const std::string &s);

  HRESULT assign(const char16_type *p, size_t l);

  HRESULT assign(const u16string_bytes_t &rhs);

  HRESULT to_string(std::string &s) const;

  void clear();

  void resize(size_t s);

  value_type &operator[](const size_t off);

  const value_type &operator[](const size_t off) const;
  void tolower();

  // return char16 size, not bytes size.
  size_t find(const char16_type *substr, size_t off, size_t subsize) const;

  size_t find(const u16string_bytes_t &rhs, size_t off = 0) const;

  bool endswith(const u16string_bytes_t &rhs) const;

  bool startswith(const u16string_bytes_t &rhs) const;
  bool startswith(char16_type c) const;

  bool endswith(char16_type c) const;

  bool is(const u16string_bytes_t &rhs) const;
  size_t find_first_not_of(const u16string_bytes_t &rhs) const;

  size_t find_last_not_of(const u16string_bytes_t &rhs) const;

  void lstrip(const u16string_bytes_t &s);
  void rstrip(const u16string_bytes_t &s);
  void trim_head(const u16string_bytes_t &s);
  void trim_tail(const u16string_bytes_t &s);
};

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


#endif //CORE_ENCODING_U16STRING_BYTES_H

