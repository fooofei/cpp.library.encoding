
#include "../include/encoding/hresult.h"
#include "../include/encoding/u16string_bytes.h"


HRESULT u16string_bytes_t::assign(const char16_type *p, size_t l) {
    if (!(p && l)) return E_INVALIDARG;
    const char16_type *e = p + l;
    buf_.assign(
            (u16string_bytes_type::const_pointer) p, (u16string_bytes_type::const_pointer) e
    );
    return S_OK;
}


size_t u16string_bytes_t::find(const char16_type *substr, size_t off, size_t subsize) const {

    const char16_type *b = c_str();
    const char16_type *e = b + size();
    size_t default_ = std::string::npos;

    if (!(!empty() && subsize && substr)) {
        return default_;
    }


    if (!(off < size()
          && subsize <= (size() - off))
            ) {
        return default_;
    }

    b += off;
    e = e - subsize + 1;

    for (; b < e; ++b) {
        if (*b == *substr
            && 0 == memcmp(b, substr, subsize * sizeof(char16_type))) {
            return b - c_str();
        }
    }

    return default_;
}


void u16string_bytes_t::tolower() {
    if (empty()) return;
    char16_type *b = (char16_type *) ptr();
    char16_type *e = b + size();

    for (; b < e; ++b) {
        *b = (char16_type) ::tolower(*b);
    }

}

size_t u16string_bytes_t::find_first_not_of(const u16string_bytes_t &rhs) const {
    size_t default_ = std::string::npos;
    if (empty()) return default_;
    const char16_type *end = c_str() + size();
    for (const char16_type *p = c_str(); p < end; ++p) {
        if (!(rhs.find(p, 0, 1) < rhs.size())) {
            return p - c_str();
        }
    }
    return default_;
}

size_t u16string_bytes_t::find_last_not_of(const u16string_bytes_t &rhs) const {
    size_t default_ = std::string::npos;

    if (empty()) return default_;


    const char16_type *end = c_str() + size();

    for (const char16_type *p = end - 1;; --p) {
        if (!(rhs.find(p, 0, 1) < rhs.size())) {
            return p - c_str();
        } else if (p == c_str()) break;
    }
    return default_;
}


void u16string_bytes_t::lstrip(const u16string_bytes_t &s) {
    if (empty()) return;
    size_t off = find_first_not_of(s);
    if (off < size()) {
        // erase [0, off)
        off *= sizeof(char16_type) / sizeof(u16string_bytes_type::value_type);
        if (off < buf_.size()) {
            buf_.erase(buf_.begin(), buf_.begin() + off);
        }
    }
}

void u16string_bytes_t::rstrip(const u16string_bytes_t &s) {
    if (empty()) return;


    size_t off = find_last_not_of(s);
    if (off < size()) {
        off += 1;
        // erase [off, end)
        off *= sizeof(char16_type) / sizeof(u16string_bytes_type::value_type);
        if (off < buf_.size()) {
            buf_.erase(buf_.begin() + off, buf_.end());
        }
    }
}