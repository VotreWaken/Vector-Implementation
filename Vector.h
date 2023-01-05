#ifndef Vector_H
#define Vector_H

#include <memory>
#include <algorithm>

template <typename T>
class Vector
{
public:

												/*			Constructors			*/

	// Default Constructor 
	Vector(int capacity = 10) :
		capacity(capacity),
		size(0),
		ptr(static_cast<T*>(::operator new(sizeof(T)* capacity)))
	{

	};

	// Iterator-Based Constructor
	template<typename I>
	Vector(I begin, I end) :
		capacity(std::distance(begin, end)),
		size(0),
		ptr(static_cast<T*>(::operator new(sizeof(T)* capacity)))
	{
		for (auto pos = begin; pos != end; pos++)
		{
			pushBackInternal(*pos);
		}
	}

	// Aggregate Initialization Constructor
	// Initializes an aggregate from an initializer list
	Vector(std::initializer_list<T> const& list)
		: Vector(std::begin(list), std::end(list))
	{

	}

	// Copy Constructor
	Vector(Vector const& CopyVector) :
		capacity(CopyVector.size),
		size(0),
		ptr(static_cast<T*>(::operator new(sizeof(T)* capacity)))
	{
		try
		{
			for (size_t pos = 0; pos < CopyVector.size; pos++)
			{
				push_back(CopyVector.ptr[pos]);
			}
		}
		catch (const std::exception&)
		{
			std::unique_ptr<T, Deleter>     deleter(ptr, Deleter());
			clearElements<T>();

			throw;
		}
	}

	// Move Constructor 
	Vector(Vector&& MoveVector) noexcept
		: capacity(0)
		, size(0)
		, ptr(nullptr)
	{
		MoveVector.swap(*this);
	}

												/*			Operators			*/

	// Validated element access

	// 1. Reference
	T& at(size_t index) { validateIndex(index); return ptr[index]; }

	// 2. Const Reference
	const T& at(size_t index) const { validateIndex(index); return ptr[index]; }

	// Non-Validated element access

	// 1. Reference
	T& operator[](size_t index) { return ptr[index]; }

	// 2. Const Reference
	const T& operator[](size_t index) const { return ptr[index]; }

	// 3. front()
	T& front() { return ptr[0]; }

	// 4. Const front()
	const T& front() const { return ptr[0]; }

	// 5. back()
	T& back() { return ptr[size - 1]; }

	// 6. Const back()
	const T& back() const { return ptr[size - 1]; }


	// Size
	size_t VectorSize() const { return size; }

	// Empty 
	bool empty() const { return size == 0; }

	size_t Capacity() { return capacity; }

	// Rvalue operator " = "
	Vector operator=(Vector&& MoveVector)
	{
		MoveVector.swap(*this);
		return *this;
	}

	// Lvalue Operator " = " 
	Vector& operator=(Vector const& copy)
	{
		copyAssign<T>(copy);
		return *this;
	}

	// Comparasion Operator " == " 
	bool operator==(Vector const& rhs) const
	{
		return  (VectorSize() == rhs.VectorSize())
			&& std::equal(begin(), end(), rhs.begin());
	}

	// Iterators 

	// 1. Begin Iterator
	T* begin() { return ptr; }

	// 2. Begin Const Iterator
	const T* begin() const { return ptr; }

	// 3. End Iterator
	T* end() { return ptr + size; }

	// 4. End Const Iterator
	const T* end() const { return ptr + size; }

												/*			Mutating Methods			*/

	// 1. Push Back
	void push_back(size_t const& value)
	{
		ResizeIfRequire();
		pushBackInternal(value);
	}
	// Overload push back for rvalue int
	void push_back(size_t&& value)
	{
		ResizeIfRequire();
		moveBackInternal(std::move(value));
	}

	// 2. Pop Back
	void pop_back()
	{
		size--;
		ptr[size].~T();
	}

	// 3. Swap 
	void swap(Vector& SwapVector)
	{
		using std::swap;
		swap(capacity, SwapVector.capacity);
		swap(size, SwapVector.size);
		swap(ptr, SwapVector.ptr);
	}

	// 4. Reserve Capacity 
	void reserve(size_t cappacityHigh)
	{
		if (cappacityHigh > capacity)
		{
			reserveCapacity(cappacityHigh);
		}
	}

	// Destructor
	~Vector()
	{
		std::unique_ptr<T, Deleter> deleter(ptr, Deleter());
		clearElements<T>();
	};

private:

	// Custom Deleter 
	struct Deleter
	{
		void operator()(T* ptr) const
		{
			::operator delete(ptr);
		}
	};

	// PushBack
	void pushBackInternal(T const& value)
	{
		new (ptr + size) T(value);
		size++;
	};

	// Rvalue Move Back
	void moveBackInternal(T&& value)
	{
		new (ptr + size) T(std::move(value));
		++size;
	}

	// Error when out of range of elements
	void validateIndex(size_t index)
	{
		if (index >= size)
		{
			throw std::out_of_range("Out of Range");
		}
	}

	// Redefining the Size if it exceeds the amount of allocated memory
	void ResizeIfRequire()
	{
		if (size == capacity)
		{
			size_t newCapacity = std::max(2.0, capacity * 1.5);
			reserveCapacity(newCapacity);
		}
	}

	// Reserves a new amount of memory
	void reserveCapacity(size_t newCapacity)
	{
		Vector<T> temp(newCapacity);
		SimpleCopy<T>(temp);
		temp.swap(*this);
	}

											/*			SFINAE optimisation 		*/

	// SimpleCopy - ≈сли есть возможность без исключений переместить вектор избежав копирование
	// ¬ противном случае копирует 


	// ѕеремещает, когда исключений не гарантируетс€,
	// в противном случае копирует.
	template<typename U>
	typename std::enable_if<std::is_nothrow_move_constructible<U>::value == false>::type
		SimpleCopy(Vector<T>& dst)
	{
		std::for_each(ptr, ptr + size,
			[&dst](T const& v) {dst.moveBackInternal(std::move(v));}
		);
	}

	template<typename U>
	typename std::enable_if<std::is_nothrow_move_constructible<U>::value == true>::type
		SimpleCopy(Vector<T>& dst)
	{
		std::for_each(ptr, ptr + size,
			[&dst](T& v) {dst.moveBackInternal(std::move(v));}
		);
	}

	//  ласс признаков, который определ€ет, €вл€етс€ ли T тривиально разрушаемым типом.
	//   тривиально разрушаемым типам относ€тс€ скал€рные типы , тривиально копирующие конструируемые классы 
	// и массивы таких типов.
	// 
	// “ривиально разрушаемый класс Ч это класс(определенный с помощью class, struct или union), который:
	// использует не€вно определенный деструктор.


	//  огда у элементов нет своего деструктора вручную с помощью цикла их удал€ем
	template<typename U>
	typename std::enable_if<std::is_trivially_destructible<U>::value == false>::type
		clearElements()
	{
		// Call the destructor on all the members in reverse order
		for (int pos = 0; pos < size; ++pos)
		{
			// Note we destroy the elements in reverse order.
			ptr[size - 1 - pos].~T();
		}
	}

	template<typename U>
	typename std::enable_if<std::is_trivially_destructible<U>::value == true>::type
		clearElements()
	{
		// Trivially destructible objects can be reused without using the destructor.
	}

	// »збегайте выделени€ ресурсов, когда исключений не гарантировано.
	// т.е. ѕри копировании целых чисел повторно используйте буфер,
	// если это возможно, чтобы избежать дорогосто€щего выделени€
	// ресурсов.
	template<typename U>
	typename std::enable_if<(std::is_nothrow_copy_constructible<U>::value
		&& std::is_nothrow_destructible<U>::value) == true>::type
		copyAssign(Vector<U>& copy)
	{
		if (this == &copy)
		{
			return;
		}

		if (capacity <= copy.size)
		{
			// If we have enough space to copy then reuse the space we currently
			// have to avoid the need to perform an expensive resource allocation.

			clearElements<T>();
			// Potentially does nothing (see above)
			// But if required will call the destructor of
			// all elements.

			// buffer now ready to get a copy of the data.
			size = 0;
			for (int pos = 0; pos < copy.size; ++pos)
			{
				pushBackInternal(copy[pos]);
			}
		}
		else
		{
			// Fallback to copy and swap if we need to more space anyway
			Vector<T> tmp(copy);
			tmp.swap(*this);
		}
	}

	template<typename U>
	typename std::enable_if<(std::is_nothrow_copy_constructible<U>::value
		&& std::is_nothrow_destructible<U>::value) == false>::type
		copyAssign(Vector<U>& copy)
	{
		// Copy and Swap idiom
		Vector<T> tmp(copy);
		tmp.swap(*this);
	}

	size_t capacity;
	size_t size;
	T* ptr;
};

#endif