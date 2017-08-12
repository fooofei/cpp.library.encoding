
#ifndef CORE_ENCODING_H
#define CORE_ENCODING_H

#include <cstddef>
#include "hresult.h"


namespace encoding{

    // Note: All size are bytes size.

    // mbcs <-> utf16le
    HRESULT mbcs_2_utf16le(const void * , size_t , void * , size_t * );
    HRESULT utf16le_2_mbcs(const void * , size_t , void * , size_t * );

    // mbcs <-> utf32le / only posix
    HRESULT mbcs_2_utf32le(const void * , size_t , void * , size_t * );
    HRESULT utf32le_2_mbcs(const void * , size_t , void * , size_t * );

    // mbcs <-> utf8 / only posix
    HRESULT mbcs_2_utf8(const void * , size_t , void * , size_t * );
    HRESULT utf8_2_mbcs(const void * , size_t , void * , size_t * );

    // utf8 <-> utf16le
    HRESULT utf8_2_utf16le(const void * , size_t , void * , size_t * );
    HRESULT utf16le_2_utf8(const void * , size_t , void * , size_t * );

    // utf8 <-> utf32le / only posix
    HRESULT utf8_2_utf32le(const void * , size_t , void * , size_t * );
    HRESULT utf32le_2_utf8(const void * , size_t , void * , size_t * );

    // utf16le <-> utf32le / only posix
    HRESULT utf16le_2_utf32le(const void * , size_t , void * , size_t * );
    HRESULT utf32le_2_utf16le(const void * , size_t , void * , size_t * );


};

#endif // CORE_ENCODING_H