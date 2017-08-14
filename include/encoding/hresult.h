
#pragma once

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
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
#ifndef E_NOTIMPL
#define E_NOTIMPL (HRESULT)0x80004001L
#endif

#endif