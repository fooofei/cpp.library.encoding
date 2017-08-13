
# Cpp Cross Platform Encoding [![Build Status](https://travis-ci.org/fooofei/cpp_cross_platform_encoding.svg?branch=master)](https://travis-ci.org/fooofei/cpp_cross_platform_encoding)

### use

```

1/2 
#include "encoding/encoding.h" // using for raw convert, useing bytes
#include "encoding/encoding_std.h" // using for stl strings, std::string, std::wstring, std::u16string
#include "encoding/u16string_bytes.h"// using for lower than c++11, that not have std::u16string

2/2
add in CMakeLists.txt

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../cpp_cross_platform_encoding  build_encoding)
target_link_libraries(${PROJECT_NAME} encoding)

```