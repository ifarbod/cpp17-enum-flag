# cpp17-enum-flag
Enable bitwise operators on scoped enums.

Library compiles with no warnings (`-std=c++17 -Wall -Wshadow -Wextra -Wnon-virtual-dtor -pedantic`) on Clang 14.


## Example usage

```cpp
enum class TestEnum
{
    Baz = 1 << 0,
    Fou = 1 << 1,
    Moo = 1 << 2,
    Foo = 1 << 3,
    Bar = 1 << 4,
};

template <>
struct zsl::EnumFlags<TestEnum>
{
    static constexpr bool is_flags = true;
};

// ...

auto main() -> int
{
    TestEnum e{TestEnum::Baz};
    auto b = zsl::EnumIsSet(e & TestEnum::Baz);
    std::cout << (b ? "true" : "false");
    
    e = TestEnum::Foo | TestEnum::Baz;
}
```
