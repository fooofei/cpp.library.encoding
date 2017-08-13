

#include "encoding_win.h"

#ifdef WIN32
HRESULT _lasterror_2_hresult()
{
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

#endif // WIN32