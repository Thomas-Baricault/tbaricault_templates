# tbaricault::templates

[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![CMake](https://img.shields.io/badge/CMake-3.20%2B-blue)
![Header Only](https://img.shields.io/badge/header--only-yes-brightgreen)

## Description

This is a lightweight header-only C++23 library that provides utility functions to deal with templates.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
    - [Download and install](#download-and-install)
    - [Uninstall](#uninstall)
    - [CMake](#cmake)
    - [Include](#include)
    - [Environment](#environment)
- [Documentation](#documentation)
- [Examples](#examples)
    - [Container detection](#container-detection)
    - [Variadic template type detection](#variadic-template-type-detection)
    - [Compile time string usage](#compile-time-string-usage)
    - [Variadic template type find by name](#variadic-template-type-find-by-name)
- [License](#license)

## Features

- Container extraction trait
- Variadic template parameters contain check
- Variadic template parameters finder
- Compile-time fixed-size string wrapper

## Requirements

- C++23 or later
- CMake 3.20 or later

## Usage

### Download and install

```bash
git clone https://github.com/Thomas-Baricault/templates.git
cd templates
make install
```

### Uninstall

```bash
make uninstall
```

### CMake

Add the library to your project:

```cmake
find_package(tbaricault_templates REQUIRED)

target_link_libraries(
    my_target
    PRIVATE
        tbaricault::templates
)
```

### Include

```cpp
#include <tbaricault/templates.hpp>
```

### Environment

If you have a custom C++ installation, you can edit the `ENV` variable in the `Makefile` to specify your environment path.

Example on Windows with MSYS2/MinGW64:

```makefile
ENV = C:/msys64/mingw64
```

## Documentation

Read the complete documentation at [https://docs.thomas-baricault.fr/templates](https://docs.thomas-baricault.fr/templates).

## Examples

### Container detection

```cpp
#include <iostream>
#include <typeinfo>
#include <tbaricault/templates.hpp>


template<typename T>
void test(const T& value)
{
    using ContainerTraits = tbaricault::templates::ContainerTraits<T>;
    if constexpr (ContainerTraits::isContainer)
    {
        std::cout << "Container is detected" << std::endl;
        if constexpr (ContainerTraits::isAssociative)
        {
            std::cout << "Container is associative" << std::endl;
            std::cout << "Key type: " << typeid(typename ContainerTraits::KeyType).name() << std::endl;
        }
        std::cout << "Value type: " << typeid(typename ContainerTraits::ValueType).name() << std::endl;
    }
    else
        std::cout << "Not a container" << std::endl;
    std::cout << std::endl;
    return;
}


int main()
{
    test(int{73});
    test(std::vector<int>{73, 42, 37});
    test(std::map<std::string, int>{
        {"a", 73},
        {"b", 42},
        {"c", 37}
    });
    return (0);
}
```

Output:

```text
Not a container

Container is detected
Value type: i

Container is detected
Container is associative
Key type: NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
Value type: i
```

### Variadic template type detection

```cpp
#include <iostream>
#include <tbaricault/templates.hpp>


struct A {};

struct B {};

struct C {};


template<typename... List>
void test()
{
    if constexpr (tbaricault::templates::contains<A, List...>::value)
        std::cout << "A found" << std::endl;
    else
        std::cout << "A not found" << std::endl;
    return;
}


int main()
{
    test();
    test<A, B, C>();
    test<B, B, A>();
    test<B, C>();
    return (0);
}
```

Output:

```text
A not found
A found
A found
A not found
```

### Compile time string usage

```cpp
#include <iostream>
#include <tbaricault/templates.hpp>


template<tbaricault::templates::FixedString S>
void test()
{
    std::cout << "Default call" << std::endl;
    return;
}


template<>
void test<"a">()
{
    std::cout << "a override" << std::endl;
    return;
}


template<>
void test<"b">()
{
    std::cout << "b override" << std::endl;
    return;
}


int main()
{
    test<"a">();
    test<"b">();
    test<"c">();
    return (0);
}
```

Output:

```text
a override
b override
Default call
```

### Variadic template type find by name

```cpp
#include <iostream>
#include <tbaricault/templates.hpp>


template<tbaricault::templates::FixedString Name>
struct A
{

    static constexpr auto name = Name;

};


template<typename... List>
void test()
{
    using Result = tbaricault::templates::find<"test", List...>;
    if constexpr (std::is_same_v<typename Result::type, void>)
        std::cout << "test not found" << std::endl;
    else
        std::cout << "test found (index: " << Result::index << ")" << std::endl;
    return;
}


int main()
{
    test();
    test<A<"test">, A<"abc">>();
    test<A<"abc">, A<"def">, A<"test">>();
    test<A<"abc">, A<"def">>();
    return (0);
}
```

Output:

```text
test not found
test found (index: 0)
test found (index: 2)
test not found
```

## License

This project is licensed under the MIT License.

See [LICENSE](LICENSE) for details.
