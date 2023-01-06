# Vector Implementation

# Constructors 

1. Default Constructor
По умолчанию выделяет памяти на 10 элементов 
Чтобы избежать многократного пересоздания

2. Agregate Init (initializer list)
При вызове делегирует 
Iterator-Based Constructor

3. Iterator-Based Constructor
С помощью std::distance Вычисляет количество выделяемой памяти и заполняет ею поле capacity 


При тестах обнаружил что метод push_back работает быстрее чем в vector из STL 

![screens](https://user-images.githubusercontent.com/111260358/211007639-0c1cf628-b433-4cb2-9dca-1024017e9872.PNG)

```
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
};

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
};

int main()
{
	STLVectorBenchmark();
	std::cout << std::endl;
	CustomVectorBenchmark();
}
```

# Updates
Добавить методы:
1. Insert 
2. Emplace
3. Assign
Также добавить возможность работы с Reverse Iterator 
