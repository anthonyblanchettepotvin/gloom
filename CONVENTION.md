# Coding Convention

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

### Member functions

Member functions that modify the state of an external resource (e.g., OpenGL's internal state machine) or produce a side effect should be non-const.

```c++
// Shader.h
class Shader
{
public:
    void Render();
};
```

```c++
// Shader.cpp
void Shader::Render()
{
    // The following doesn't modify any members of Shader, but may modify the OpenGL's internal state machine.
    // OpenGL calls...
}
```

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

1. Public, protected then private constructors (ordered by ascending number of parameters)
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

Private member variables' name should be prefixed with `m_`.

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
    std::string GetX() const { return m_X; } // Good.
    std::string GetX() const { return m_X; }; // Bad.

private:
    std::string m_X;
};
```

Getters/setters with more than one line should be defined in the .cpp.

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

    void SetX(const T& x);
    const T& GetX() const;

    virtual VirtualFoo();

    virtual PureVirtualFoo() = 0;

    static StaticFoo();
```

Given a member variable, its setter should come before its getter.

```c++
void SetX(const T& x);
const T& GetX() const;
```

Definition of static member variables in .cpp files should appear before all member functions' definition.

```c++
// Foo.h
class Foo
{
public:
    void DoA();
    void DoB();

private:
    static std::string m_Bar;
};
```

```c++
// Foo.cpp
// Includes...
// Defines...

std::string Foo::m_Bar;

void Foo::DoA()
{
    // ...
}

void Foo::DoB()
{
    // ...
}
```

## Functions

### Structure

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

Always use curly braces to define scopes, even for single-statement scopes.

```c++
// Good.
if (!m_Foo)
{
    // ...
}

// Bad.
if (!m_Foo)
    // ...
```

## Includes, defines, forward declarations, constants and global variables

### Structure

Includes, defines, forward declarations, constants and global variables should follow this structure:

1. `#pragma once`
1. Includes
    1. STL includes
    1. Third party library includes
    1. Different internal library includes
    1. Current internal library includes
1. Defines
1. Forward declarations
    1. typedefs
    1. enums
    1. structs
    1. classes
1. Constants
1. Global variables

```c++
#pragma once

// STL includes
#include <vector>
// ...

// Third party library includes
#include <glm/glm.hpp>
// ...

// Different internal library includes
#include "../../../engine/graphics/mesh/Mesh.h"
// ...

// Current internal library includes
#include "Foo.h"
// ...

// Defines
#define FOO "I am foo!"
// ...

// Forward declarations
typedef unsigned int MyTypedef;
// ...

enum MyEnum;
// ...

struct MyStruct;
// ...

class MyClass;
// ...

// Constants
const std::string MY_CONSTANT = "Lorem ipsum...";
// ...

// Global variables
bool g_MyGlobalVariable = true;
// ...
```

### Defines

Function macros should be written using the camel case convention and should be prefixed with `g`.

```c++
#define gMyFunctionMacro(x) // ...
```

Non-function macros should be written using the screaming snake case convention.

```c++
#define MY_NON_FUNCTION_MACRO // ...
```

### Constants

Constants' name should be written using the screaming snake case convention.

```c++
const std::string MY_CONSTANT = "Lorem ipsum..."; // Good.
const std::string MyConstant = "Lorem ipsum..."; // Bad.
```

### Global variables

Global variables' name should be prefixed with `g_`.

```c++
bool g_IsGlobal = true;

class Foo
{
    // ...
};
```

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
