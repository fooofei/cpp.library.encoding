

#include <string>
#include <vector>

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
private:
    u16string_bytes_type buf_;
public:
    u16string_bytes_t(){
        ;
    }
    explicit u16string_bytes_t(const u16string_bytes_t & rhs){
        from_u16string(rhs.c_str(),rhs.size());
    }
    u16string_bytes_t(const char16_type * p, size_t l){
        from_u16string(p,l);
    }

    ~u16string_bytes_t(){
        ;
    }

    const void * ptr() const {
        return &buf_[0];
    }
    size_t size_of_bytes() const {
        return buf_.size() * sizeof(u16string_bytes_type::value_type);
    }
    void * ptr(){
        return &buf_[0];
    }


    const char16_type * char16_ptr() const {
        return (const char16_type *)ptr();
    }
    size_t char16_size() const {
        return size_of_bytes()/sizeof(char16_type);
    }


    bool empty() const {
        return buf_.empty();
    }
    size_t size() const{
        return char16_size();
    }
    const char16_type * c_str() const {
        return char16_ptr();
    }


    HRESULT from_string(const std::string & s){
        // string_convert string_2_u16string
        return E_NOTIMPL;
    }

    HRESULT to_string(std::string & s) const{
        // string_convert u16string_2_string
        return E_NOTIMPL;
    }

    HRESULT from_u16string(const char16_type * p, size_t l){
        const char16_type * e = p+l;
        buf_.assign(
            (u16string_bytes_type::const_pointer)p
            ,(u16string_bytes_type::const_pointer)e
            );
        return S_OK;
    }

    void tolower(){
        char16_type * b = (char16_type *)ptr();
        char16_type * e = b + size();

        for (;b<e;++b)
        {
            *b = (char16_type)::tolower(*b);
        }

    }

    // return char16 size, not bytes size.
    size_t find(const char16_type * substr, size_t off , size_t subsize) const {

        const char16_type * b = c_str();
        const char16_type * e = b + size();
        size_t default_ = std::string::npos;

        if (!(!empty() && subsize && substr))
        {
            default_;
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


    size_t find_last_not_of(const u16string_bytes_t & rhs) const {
        size_t default_ = std::string::npos;

        if (empty())
        {
            return default_;
        }

        const char16_type * end = c_str()+size();

        for(const char16_type * p = end-1;;--p){
            if (!(rhs.find(p,0,1)<rhs.size()))
            {
                return p-c_str();
            }
            else if(p == c_str()) break;
        }
        return default_;
    }

    void trim_tail(const u16string_bytes_t & s){
        if (empty())
        {
            return ;
        }

        size_t off = find_last_not_of(s);
        if (off<size())
        {
            off += 1;
            off *= sizeof(char16_type)/sizeof(u16string_bytes_type::value_type);
            if (off<buf_.size())
            {
                buf_.erase(buf_.begin()+off,buf_.end());
            }
        }
    }

};


#define ASSERT_EXCEPT(exp) \
    do \
{ \
    if(!(exp)){ \
    fprintf(stderr,"unexcept file:%s, line:%d\n",__FILE__,__LINE__); \
    exit(0); \
    } \
} while (0);

int test_u16string_bytes()
{

    std::wstring s(L"helloWorld\t");

    u16string_bytes_t a;
    u16string_bytes_t b(s.c_str(),s.size());

    ASSERT_EXCEPT(b.find(L"e",0,1) == s.find(L"e",0,1));

    ASSERT_EXCEPT(b.startswith(L'h') == true);
    ASSERT_EXCEPT(b.startswith(L'e') == false);
    ASSERT_EXCEPT(b.endswith(L'\t') == true);
    ASSERT_EXCEPT(b.startswith(L'd') == false);

    b.tolower();
    b.trim_tail(u16string_bytes_t(std::wstring(L"\t").c_str(),1));
    ASSERT_EXCEPT(b.is(u16string_bytes_t(L"helloworld",10)));

    printf("pass test_u16string_bytes()\n");

    return 0;
}