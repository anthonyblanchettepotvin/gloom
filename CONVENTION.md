# Coding Conventions For Gloom

## Const-correctness

### Getters/setters

Getter of member variable **copy** is const.

```c++
T Get() const;
```

Getter of const raw pointer is const.

```c++
const T* Get() const;
```

Getter of non-const raw pointer is non-const.

```c++
T* Get();
```

#### Source(s)

- https://stackoverflow.com/questions/14505789/c-const-correctness-issue-with-getters

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

TODO Member functions should be ordered by theme (merge with the following one).

Given a member functions category, member functions are ordered by ascending number of parameters.

```c++
void Foo(const T& a, const U& b);
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

## Exceptions and assertions

TODO Define when to use exceptions and when to use assertions for null-checks.
