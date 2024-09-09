# Custom Vector Implementation

This repository contains a custom implementation of a vector class in C++. This class is designed to demonstrate dynamic array management principles and includes a variety of features and methods. The implementation also includes performance benchmarks comparing it to `std::vector`.

## Vector Implementation

### Constructors

- **Default Constructor**: Initializes with a default capacity of 10 elements. Allocates memory for the initial capacity to avoid frequent reallocations.
  
- **Iterator-Based Constructor**: Initializes the vector based on the provided range of iterators. Uses `std::distance` to determine the required capacity and calls `pushBackInternal()` for each element in the range.

- **Aggregate Initialization Constructor**: Initializes the vector from an initializer list by delegating to the Iterator-Based Constructor.

- **Copy Constructor**: Creates a new vector as a copy of an existing vector. Uses try-catch blocks to handle errors during copying and ensures correct exception safety.

- **Move Constructor**: Transfers ownership from a temporary vector to the new vector. Uses the `swap()` method to exchange contents, effectively resetting the moved vector.

### Operators

- **Element Access**:
  - `T& at(size_t index)`: Validated access to an element at a specified index.
  - `const T& at(size_t index) const`: Const validated access.
  - `T& operator[](size_t index)`: Non-validated access.
  - `const T& operator[](size_t index) const`: Const non-validated access.
  - `T& front()`: Access the first element.
  - `const T& front() const`: Const access to the first element.
  - `T& back()`: Access the last element.
  - `const T& back() const`: Const access to the last element.

- **Size and Capacity**:
  - `size_t VectorSize() const`: Returns the current number of elements.
  - `bool empty() const`: Checks if the vector is empty.
  - `size_t Capacity()`: Returns the current capacity.

- **Assignment Operators**:
  - `Vector operator=(Vector&& MoveVector)`: Move assignment operator.
  - `Vector& operator=(Vector const& copy)`: Copy assignment operator.
  - `bool operator==(Vector const& rhs) const`: Equality comparison operator.

- **Iterators**:
  - `T* begin()`: Returns an iterator to the beginning.
  - `const T* begin() const`: Const iterator to the beginning.
  - `T* end()`: Returns an iterator to the end.
  - `const T* end() const`: Const iterator to the end.

### Mutating Methods

- **Push Back**:
  - `void push_back(size_t const& value)`: Adds an element to the end of the vector, resizing if necessary.
  - `void push_back(size_t&& value)`: Overloaded for Rvalue values to move elements.

- **Pop Back**:
  - `void pop_back()`: Removes the last element and calls its destructor.

- **Swap**:
  - `void swap(Vector& SwapVector)`: Exchanges contents with another vector.

- **Reserve Capacity**:
  - `void reserve(size_t cappacityHigh)`: Reserves a specified amount of memory to accommodate future elements.

### Destructor

- `~Vector()`: Releases allocated memory using a custom deleter and ensures proper cleanup.

### SFINAE Optimizations

- **Simple Copy**:
  - Uses SFINAE (Substitution Failure Is Not An Error) to optimize copying and moving operations based on whether the type `T` is noexcept-move-constructible or trivially destructible.

### Benchmarks

#### STL Vector Benchmark

```cpp
void STLVectorBenchmark()
{
    using vector = std::vector<int>;
    clock_t start, end;
    start = clock();
    vector VectorTest;
    for (int i = 0; i < 50000000; i++)
    {
        VectorTest.push_back(rand() % 10);
    }
    end = clock();
    printf("Vector From STL: %lg seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}
```

#### Custom Vector Benchmark

```cpp
void CustomVectorBenchmark()
{
    using Vector = Vector<int>;
    clock_t start, end;
    start = clock();
    Vector VectorTest;
    for (int i = 0; i < 50000000; i++)
    {
        VectorTest.push_back(rand() % 10);
    }
    end = clock();
    printf("Custom Vector: %lg seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}
```

![screens](https://user-images.githubusercontent.com/111260358/211007639-0c1cf628-b433-4cb2-9dca-1024017e9872.PNG)

### TODO 
Future updates will include:
- Insert: Method to insert elements at a specific position.
- Emplace: Method to construct and insert elements in-place.
- Assign: Method to assign new values to the vector.
- Reverse Iterator: Support for reverse iteration over the vector.

### Usage
1. Clone the Repository:

```bash
git clone https://github.com/yourusername/custom-vector
```
2. Build the Project:
- Use your preferred C++ build system to compile the project.

3. Run Benchmarks:

- Execute the main program to compare performance between std::vector and the custom vector implementation.

### License
This project is open source and available under the MIT License.
