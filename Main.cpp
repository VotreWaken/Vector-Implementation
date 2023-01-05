#include <iostream>
#include "Vector.h"

// Function to Demonstrate Move Constructor
template <typename T>
Vector<T> MoveConstructorFunc(Vector<T> value)
{
	return value;
}

int main()
{
	// Agregate Init
	Vector<int> A{ 1,3,1,2,5,6 };
	for (int i = 0; i < A.VectorSize(); i++)
	{
		std::cout << A[i] << " ";
	}
	std::cout << std::endl;

	// Iterator-based Init
	Vector<int> B(A.begin(), A.end());
	for (int i = 0; i < B.VectorSize(); i++)
	{
		std::cout << B[i] << " ";
	}
	std::cout << std::endl;

	// Copy Init
	Vector<int> C(B);
	for (int i = 0; i < C.VectorSize(); i++)
	{
		std::cout << C[i] << " ";
	}
	std::cout << std::endl;

	// Default Init
	Vector<int> D;

	// Move Init
	Vector<int> E = MoveConstructorFunc(E);

	std::cout << std::endl;

	// Comparasion Operator " == "
	/*
	Vector<int> B{ 1,3,1,2,5,6 };
	int res = A == B;
	std::cout << res;
	*/
	// At() Method
	//std::cout << "At Index: " << A.at(1);
	// Exepciton if out of available indexes
	//std::cout << A.at(10);

	// Capacity Method
	//std::cout << A.Capacity();

	// Back() Method
	//std::cout << A.back();

	// Front() Method
	// std::cout << A.front();

	// empty() Method Return Bool value
	//std::cout << A.empty();

	// pop_back() Method
	/*
	A.pop_back();
	for (int i = 0; i < A.VectorSize(); i++)
	{
		std::cout << A[i] << " ";
	}
	*/

	// Push_Back() Method
	/*
	A.push_back(2);
	for (int j = 0; j < A.VectorSize(); j++)
	{
		std::cout << A[j] << " ";
	}
	*/
	// Size() Method
	//std::cout << A.VectorSize();

	// Swap() Method
	/*
	Vector<int> B{ 1,2,3 };
	A.swap(B);
	for (int i = 0; i < B.VectorSize(); i++)
	{
		std::cout << B[i] << " ";
	}
	*/
}
