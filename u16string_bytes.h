

#include <string>
#include <vector>
#include <string.h>

//
// std::wstring is different in Windows and Linux. 
// in Windows sizeof(wchar_t) is equal with sizeof(unsigned short) ==2,
// but in linux sizeof(wchat_t) is equal with sizeof(unsigned int) == 4.
// user the class u16string_bytes_t, to make sure all platform use same memory size.
// std::u16string is the same effect, but std::u16string is c++11 above.
class u16string_bytes_t
{
public:
    typedef std::vector<unsigned char > u16string_bytes_type;

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
    u16string_bytes_t() {
        //assert sizeof(char16_type) >= sizeof(u16string_bytes_type::value_type);
    }
    explicit u16string_bytes_t(const u16string_bytes_t & rhs) {
        assign(rhs.c_str(), rhs.size());
    }
    u16string_bytes_t(const char16_type * p, size_t l) {
        assign(p, l);
    }

    ~u16string_bytes_t() {
        ;
    }

    const void * ptr() const {
        if (empty()) return NULL;
        return &buf_[0];
    }
    size_t size_of_bytes() const {
        return buf_.size() * sizeof(u16string_bytes_type::value_type);
    }
    void * ptr() {
        if (empty()) return NULL;
        return &buf_[0];
    }


    const char16_type * char16_ptr() const {
        return (const char16_type *)ptr();
    }
    size_t char16_size() const {
        return size_of_bytes() / sizeof(char16_type);
    }


    bool empty() const {
        return buf_.empty();
    }
    size_t size() const {
        return char16_size();
    }
    const char16_type * c_str() const {
        return char16_ptr();
    }


    HRESULT assign(const std::string & s) {
        // string_convert string_2_u16string
        return E_NOTIMPL;
    }

    HRESULT to_string(std::string & s) const {
        // string_convert u16string_2_string
        return E_NOTIMPL;
    }

    HRESULT assign(const char16_type * p, size_t l);
    HRESULT assign(const u16string_bytes_t & rhs) {
        return assign(rhs.c_str(), rhs.size());
    }

    void clear() {
        buf_.clear();
    }

    void resize(size_t s) {
        buf_.resize(s * sizeof(value_type)/ sizeof(u16string_bytes_type::value_type));
    }

    value_type &  operator[](const size_t off){
        return *((value_type *)ptr()+off);
    }

    const value_type & operator[](const size_t off) const {
        return *(char16_ptr() + off);
    }


    void tolower(){
        if (empty()) return;
        char16_type * b = (char16_type *)ptr();
        char16_type * e = b + size();

        for (;b<e;++b)
        {
            *b = (char16_type)::tolower(*b);
        }

    }

    // return char16 size, not bytes size.
    size_t find(const char16_type * substr, size_t off , size_t subsize) const ;


    size_t find(const u16string_bytes_t & rhs, size_t off=0) const {
        return find(rhs.c_str(),off,rhs.size());
    }

    bool endswith(const u16string_bytes_t & rhs) const {
        if (rhs.size()<=size()){
            return find(rhs,size()-rhs.size())<size();
        }
        return false;
    }

    bool startswith(const u16string_bytes_t & rhs) const {
        if (rhs.size() <= size()){
            return 0 == memcmp(c_str(),rhs.c_str(),rhs.size_of_bytes());
        }
        return false;
    }

    bool startswith(char16_type c) const {
        return startswith(u16string_bytes_t(&c,1));
    }
    bool endswith(char16_type c) const {
        return endswith(u16string_bytes_t(&c,1));
    }

    bool is (const u16string_bytes_t & rhs) const {
        return rhs.size() == size() && startswith(rhs);
    }

    size_t find_first_not_of(const u16string_bytes_t & rhs) const {
        size_t default_ = std::string::npos;
        if (empty()) return default_;
        const char16_type * end = c_str() + size();
        for (const char16_type * p = c_str();p<end; ++p)
        {
            if (!(rhs.find(p, 0, 1) < rhs.size())) {
                return p - c_str();
            }
        }
        return default_;
    }

    size_t find_last_not_of(const u16string_bytes_t & rhs) const {
        size_t default_ = std::string::npos;

        if (empty()) return default_;
        

        const char16_type * end = c_str()+size();

        for(const char16_type * p = end-1;;--p)
        {
            if (!(rhs.find(p,0,1)<rhs.size()))
            {
                return p-c_str();
            }
            else if(p == c_str()) break;
        }
        return default_;
    }



    void lstrip(const u16string_bytes_t & s) {
        if (empty()) return;
        size_t off = find_first_not_of(s);
        if (off<size())
        {
            // erase [0, off)
            off *= sizeof(char16_type) / sizeof(u16string_bytes_type::value_type);
            if (off<buf_.size()){
                buf_.erase(buf_.begin(), buf_.begin() + off);
            }
        }
    }

    void rstrip(const u16string_bytes_t & s){
        if (empty())  return ;
        

        size_t off = find_last_not_of(s);
        if (off<size())
        {
            off += 1;
            // erase [off, end)
            off *= sizeof(char16_type)/sizeof(u16string_bytes_type::value_type);
            if (off<buf_.size())
            {
                buf_.erase(buf_.begin()+off,buf_.end());
            }
        }
    }

    void trim_head(const u16string_bytes_t & s) {
        lstrip(s);
    }
    void trim_tail(const u16string_bytes_t & s) {
        return rstrip(s);
    }

};


#define ASSERT_EXCEPT(exp) \
    do \
{ \
    if(!(exp)){ \
    fprintf(stderr,"unexcept file:%s, line:%d\n",__FILE__,__LINE__); \
    exit(-1); \
    } \
} while (0);

