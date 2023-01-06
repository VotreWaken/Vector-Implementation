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
вызывает метод pushBackInternal() для каждого элемента 

4. Copy Constructor
Выполняет инструции try catch 
с обнаружением ошибок при копировании 
При правильном выполнении вызывает метод push_back() для каждого коприуемого элемента 

5. Move Constructor 
Принимает Rvalue обьект типа Vector
Обнуляет все свои поля и вызывает метод swap(*this)
у перемещаемого Vector и благодаря этому 
все обнуленные поля для которого вызывался этот конструктор
просто меняются местами с перемещаемым Vector

# Mutating Methods

1. Push Back
Вызывает метод ResizeIfRequire() который переопределяет размер, если он превышает объем выделенной памяти
Затем вызывает метод pushBackInternal() для значение которое было передано, создает шаблонный экземпляр обьекта который будет содержаться в Vector
Также имеется перегрузка к методу push_back() для Rvalue значения которое вызывает moveBackInternal() метод 

2. Pop Back 
Вызывает деструктор для обьекта находящимися в последнем индексе 

3. swap
Принимает обьект типа Vector и с помощью std::swap() меняет местами значения
( Преимущество std::swap если будут сложные объекты, перемещение будет быстрее, нежели просто обмен значениями )

4. Reserve Capacity 
Принимает желаемое значение для выделения памяти и резервирует новое количество памяти  

Деструктор в своей реализации использует Custom Deleter который с помощью unique_ptr удаляет выдяляемую память 
Также используется SFINAE которое если у элементов нет своего деструктора удаляет их  

# SFINAE ( substitution failure is not an error )


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
