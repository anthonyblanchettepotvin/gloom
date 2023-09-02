# Coding Conventions For Gloom

## Const-correctness

### Getters/setters

Getter of member variable **copy** is const.

```c++
T Get() const;
```

Getter of const raw pointer or reference is const.

```c++
const T* Get() const;
const T& Get() const;
```

Getter of non-const raw pointer or reference is non-const.

```c++
T* Get();
T& Get();
```

Getter of vector of const raw pointers is const.

```c++
std::vector<const T*> Get() const; 
```

Getter of vector of non-const raw pointers is non-const.

```c++
std::vector<T*> Get();
```

#### Source(s)

- https://stackoverflow.com/questions/14505789/c-const-correctness-issue-with-getters
- https://stackoverflow.com/questions/27065617/const-vector-implies-const-elements
- https://stackoverflow.com/questions/77029040/const-correctness-with-getters-of-vector-of-non-pointers

## Return types

### Getters/setters

Getter for a **non-nullable** & **non-heavy-to-copy** member variable (e.g., `std::string`) should return a copy.

```c++
std::string Get() const;
```

Getter for a **non-nullable** & **heavy-to-copy** member variable (e.g., an image) should return a reference.

```c++
const HeavyObject& Get() const;
```

Getter for a **nullable** & **heavy-to-copy** member variable should return a pointer.

```c++
const HeavyObject* Get() const;
```

#### Source(s)

- https://stackoverflow.com/questions/494756/when-should-you-return-a-reference-to-a-object-from-a-class-method

## Classes

### Structure

Classes' member functions and member variables should follow this structure:

1. Public, protected then private constructors (order by ascending number of parameters)
1. Public, protected then private copy constructors
1. Public, protected then private destructors
1. Public member functions
1. Public **virtual** member functions
1. Public **pure virtual** member functions
1. Public **static** member functions
1. Public member **variables**
1. Protected member functions
1. Protected **virtual** member functions
1. Protected **pure virtual** member functions
1. Protected **static** member functions
1. Protected member **variables**
1. Private member functions
1. Private **virtual** member functions
1. Private **pure virtual** member functions
1. Private **static** member functions
1. Private member **variables**
1. Operator overloads
1. Friends

TODO Structure of forward declarations.

Private member variables should be prefixed with `m_`.

```c++
class Foo
{
private:
    std::string m_X;
};
```

Getters/setters defined in .h files should not end with `;`.

```c++
class Foo
{
public:
    std::string GetX() const { return n_X; } // Good.
    std::string GetX() const { return n_X; }; // Bad.

private:
    std::string m_X;
};
```

Getters/setters with more than one line should be defined in the .cpp.

TODO Definition of static member variables in .cpp files should appear before any member function definitions.

Given a member functions category, member functions are ordered by:  

- ascending number of parameters
- theme

```c++
void Foo(const T& a);
void Foo(const T& a, const U& b);
void Bar(const T& a, const U& b);
void Bar(const T& a, const U& b, const V& c);
```

Given a member functions category, the getters/setters should be the last member functions.

```c++
public:
    void Foo();

    virtual VirtualFoo();

    virtual PureVirtualFoo() = 0;

    static StaticFoo();

    void SetX(const T& x);
    const T& GetX() const;
```

Given a member variable, its setter should come before its getter.

```c++
void SetX(const T& x);
const T& GetX() const;
```

## Functions

Use early exit when possible.

```c++
// Good.
void Foo()
{
    if (!m_Bar)
    {
        return;
    }

    // ...
}

// Bad.
void Foo()
{
    if (m_Bar)
    {
        // ...
    }
}
```

TODO Always use curly braces.
## Includes and forward declarations

### Includes

Include what you use -- no less, no more.

## Exceptions and assertions

### Exceptions vs. assertions

Use assertions to catch:
- incorrect internal input/output
    - `nullptr` passed to a **private** function when it shouldn't
    - `nullptr` returned from a **private** function when it shouldn't
- programming errors
    - pointer deleted illegally

> Use assert statements to test for conditions during development that should never be true if all your code is correct. There's no point in handling such an error by using an exception, because the error indicates that something in the code has to be fixed. -- Microsoft Learn

Use exceptions to catch:
- incorrect external input/output
    - user input
- external influences
    - network issue
    - hardware issue

> Use exceptions to check error conditions that might occur at run time even if your code is correct, for example, "file not found" or "out of memory." -- Microsoft Learn

#### Source(s)

- https://learn.microsoft.com/en-us/cpp/cpp/errors-and-exception-handling-modern-cpp
- https://softwareengineering.stackexchange.com/questions/15515/when-to-use-assertions-and-when-to-use-exceptions

## `auto` keyword

### Usages

Use `auto` in template functions when `const` keyword presence needs to be infered.

```c++
template<class T, class Self>
T* GetImpl(Self& self, const std::string& arg)
{
    // GetImpl is called by a non-const implementation and a const implementation of Get. So, element may be non-const or const.
    auto element = self.GetElement();

    return *element;
}

Object* Get(const std::string& arg)
{
    return GetImpl<Object>(*this);
}

const Object* Get(const std::string& arg) const
{
    return GetImpl<const Object>(*this);
}
```

Use `auto` in range-based `for` loops.
```c++
for (const auto& element : elements)
{
    // ...
}
```

Use `auto` when declaring iterators.
```c++
auto it = std::find(elements.begin(), elements.end(), element);
```
