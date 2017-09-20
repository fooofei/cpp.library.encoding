
#include "../include/encoding/hresult.h"
#include "../include/encoding/u16string_bytes.h"
#include "../include/encoding/encoding_std.h"
#include <string.h>

u16string_bytes_t::u16string_bytes_t()
{
  //assert sizeof(char16_type) >= sizeof(u16string_bytes_type::value_type);
}

u16string_bytes_t::u16string_bytes_t(const u16string_bytes_t &rhs)
{
  assign(rhs.c_str(), rhs.size());
}

u16string_bytes_t::u16string_bytes_t(const char16_type *p, size_t l)
{
  assign(p, l);
}

u16string_bytes_t::~u16string_bytes_t()
{
  ;
}

const void * u16string_bytes_t::ptr() const
{
  if (empty())
    return NULL;
  return &buf_[0];
}

size_t u16string_bytes_t::size_of_bytes() const
{
  return buf_.size() * sizeof(u16string_bytes_type::value_type);
}

void * u16string_bytes_t::ptr()
{
  if (empty())
    return NULL;
  return &buf_[0];
}

const u16string_bytes_t::char16_type * u16string_bytes_t::char16_ptr() const
{
  return (const char16_type *)ptr();
}

size_t u16string_bytes_t::char16_size() const
{
  return size_of_bytes() / sizeof(char16_type);
}

bool u16string_bytes_t::empty() const
{
  return buf_.empty();
}

size_t u16string_bytes_t::size() const
{
  return char16_size();
}

const u16string_bytes_t::char16_type * u16string_bytes_t::c_str() const
{
  return char16_ptr();
}

HRESULT u16string_bytes_t::assign(const u16string_bytes_t &rhs)
{
  return assign(rhs.c_str(), rhs.size());
}

size_t u16string_bytes_t::find(const u16string_bytes_t &rhs, size_t off) const
{
  return find(rhs.c_str(), off, rhs.size());
}

bool u16string_bytes_t::endswith(const u16string_bytes_t &rhs) const
{
  if (rhs.size() <= size())
  {
    return find(rhs, size() - rhs.size()) < size();
  }
  return false;
}

bool u16string_bytes_t::startswith(const u16string_bytes_t &rhs) const
{
  if (rhs.size() <= size())
  {
    return 0 == memcmp(c_str(), rhs.c_str(), rhs.size_of_bytes());
  }
  return false;
}

bool u16string_bytes_t::startswith(char16_type c) const
{
  u16string_bytes_t v(&c, 1);
  return startswith(v);
}

bool u16string_bytes_t::endswith(char16_type c) const
{
  u16string_bytes_t v(&c, 1);
  return endswith(v);
}

bool u16string_bytes_t::is(const u16string_bytes_t &rhs) const
{
  return rhs.size() == size() && startswith(rhs);
}

HRESULT u16string_bytes_t::assign(const char16_type *p, size_t l)
{
  if (!(p && l))
    return E_INVALIDARG;
  const char16_type *e = p + l;
  buf_.assign(
    (u16string_bytes_type::const_pointer)p, (u16string_bytes_type::const_pointer)e);
  return S_OK;
}

HRESULT u16string_bytes_t::assign(const std::string &s)
{
  // string_convert string_2_u16string
  my_u16string ss;
  HRESULT hr;
  hr = string_2_u16string(s, ss);
  if (FAILED(hr)){
    return hr;
  }
  return assign((const char16_type *)ss.c_str(), ss.size());
}

HRESULT u16string_bytes_t::to_string(std::string &s) const
{
  // string_convert u16string_2_string
  my_u16string ss;
  ss.assign((const my_u16string::value_type *)c_str(), size());
  return u16string_2_string(ss, s);
}

size_t u16string_bytes_t::find(const char16_type *substr, size_t off, size_t subsize) const
{

  const char16_type *b = c_str();
  const char16_type *e = b + size();
  size_t default_ = std::string::npos;

  if (!(!empty() && subsize && substr))
  {
    return default_;
  }

  if (!(off < size() && subsize <= (size() - off)))
  {
    return default_;
  }

  b += off;
  e = e - subsize + 1;

  for (; b < e; ++b)
  {
    if (*b == *substr && 0 == memcmp(b, substr, subsize * sizeof(char16_type)))
    {
      return b - c_str();
    }
  }

  return default_;
}

void u16string_bytes_t::tolower()
{
  if (empty())
    return;
  char16_type *b = (char16_type *)ptr();
  char16_type *e = b + size();

  for (; b < e; ++b)
  {
    *b = (char16_type)::tolower(*b);
  }
}

size_t u16string_bytes_t::find_first_not_of(const u16string_bytes_t &rhs) const
{
  size_t default_ = std::string::npos;
  if (empty())
    return default_;
  const char16_type *end = c_str() + size();
  for (const char16_type *p = c_str(); p < end; ++p)
  {
    if (!(rhs.find(p, 0, 1) < rhs.size()))
    {
      return p - c_str();
    }
  }
  return default_;
}

size_t u16string_bytes_t::find_last_not_of(const u16string_bytes_t &rhs) const
{
  size_t default_ = std::string::npos;

  if (empty())
    return default_;

  const char16_type *end = c_str() + size();

  for (const char16_type *p = end - 1;; --p)
  {
    if (!(rhs.find(p, 0, 1) < rhs.size()))
    {
      return p - c_str();
    }
    else if (p == c_str())
      break;
  }
  return default_;
}

void u16string_bytes_t::lstrip(const u16string_bytes_t &s)
{
  if (empty())
    return;
  size_t off = find_first_not_of(s);
  if (off < size())
  {
    // erase [0, off)
    off *= sizeof(char16_type) / sizeof(u16string_bytes_type::value_type);
    if (off < buf_.size())
    {
      buf_.erase(buf_.begin(), buf_.begin() + off);
    }
  }
}

void
u16string_bytes_t::rstrip(const u16string_bytes_t &s)
{
  if (empty())
    return;

  size_t off = find_last_not_of(s);
  if (off < size())
  {
    off += 1;
    // erase [off, end)
    off *= sizeof(char16_type) / sizeof(u16string_bytes_type::value_type);
    if (off < buf_.size())
    {
      buf_.erase(buf_.begin() + off, buf_.end());
    }
  }
}

void
u16string_bytes_t::trim_head(const u16string_bytes_t &s)
{
  lstrip(s);
}

void
u16string_bytes_t::trim_tail(const u16string_bytes_t &s)
{
  return rstrip(s);
}

void
u16string_bytes_t::clear()
{
  buf_.clear();
}

void
u16string_bytes_t::resize(size_t s)
{
  buf_.resize(s * sizeof(value_type) / sizeof(u16string_bytes_type::value_type));
}

u16string_bytes_t::value_type &
u16string_bytes_t::operator[](const size_t off)
{
  return *((value_type *)ptr() + off);
}

const u16string_bytes_t::value_type &
u16string_bytes_t::operator[](const size_t off) const
{
  return *(char16_ptr() + off);
}


