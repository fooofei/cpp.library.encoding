

#include "encoding_win.h"

#ifdef WIN32
HRESULT
_lasterror_2_hresult()
{
  // thread safe
  DWORD v = GetLastError();
  switch (v)
  {
  case ERROR_NO_UNICODE_TRANSLATION:
  case ERROR_INVALID_PARAMETER:
    return E_INVALIDARG;
  case ERROR_INSUFFICIENT_BUFFER:
    return E_OUTOFMEMORY;
  default:
    break;
  }
  return HRESULT_FROM_WIN32(v);
}

HRESULT
utf16le_2_mbcs_windows(const wchar_t *src, size_t src_size, char *dst, size_t *dst_size)
{
  int r = WideCharToMultiByte(CP_OEMCP, 0, src, (int)(src_size), dst, (int)*dst_size, NULL, NULL);
  if (r <= 0)
  {
    return _lasterror_2_hresult();
  }
  else
  {
    *dst_size = (size_t)(r);
    return S_OK;
  }
}


HRESULT
mbcs_2_utf16le_windows(const char *src, size_t src_size, wchar_t *dst, size_t *dst_size)
{
  int r = MultiByteToWideChar(CP_OEMCP, 0, src, (int)(src_size), dst, (int)(*dst_size));
  if (r <= 0)
  {
    return _lasterror_2_hresult();
  }
  else
  {
    *dst_size = (size_t)(r);
    return S_OK;
  }
}


HRESULT
utf8_2_utf16le_windows(const char *src, size_t src_size, wchar_t *dst, size_t *dst_size)
{
  int r = MultiByteToWideChar(CP_UTF8, 0, src, (int)(src_size), dst, (int)(*dst_size));
  if (r <= 0)
  {
    return _lasterror_2_hresult();
  }
  else
  {
    *dst_size = (size_t)(r);
    return S_OK;
  }
}


HRESULT
utf16le_2_utf8_windows(const wchar_t *src, size_t src_size, char *dst, size_t *dst_size)
{
  int r = WideCharToMultiByte(CP_UTF8, 0, src, (int)(src_size), dst, (int)(*dst_size), NULL, NULL);
  if (r <= 0)
  {
    return _lasterror_2_hresult();
  }
  else
  {
    *dst_size = (size_t)(r);
    return S_OK;
  }
}


#endif // WIN32