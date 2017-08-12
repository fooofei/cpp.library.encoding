
#include "hresult.h"
#include "u16string_bytes.h"


HRESULT u16string_bytes_t::assign(const char16_type * p, size_t l) {
    if (!(p && l)) return E_INVALIDARG;
    const char16_type * e = p + l;
    buf_.assign(
            (u16string_bytes_type::const_pointer)p
            , (u16string_bytes_type::const_pointer)e
    );
    return S_OK;
}


size_t u16string_bytes_t::find(const char16_type * substr, size_t off , size_t subsize) const {

    const char16_type * b = c_str();
    const char16_type * e = b + size();
    size_t default_ = std::string::npos;

    if (!(!empty() && subsize && substr))
    {
        return default_;
    }


    if (!(off<size()
          && subsize <= (size()-off))
            )
    {
        return default_;
    }

    b += off;
    e = e-subsize+1;

    for (;b<e;++b)
    {
        if (*b == *substr
            && 0 == memcmp(b,substr,subsize*sizeof(char16_type)))
        {
            return b-c_str();
        }
    }

    return default_;
}
