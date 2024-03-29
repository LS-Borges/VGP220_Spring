#include <iostream>
#include <assert.h>

//Name: Leon Borges e Silva
//StudentId: 2022595
//Grade: 92/100

int RecursiveMultiplication(int a, int b);
int NonRecursiveFibonacci(int n);
int PrintFibonacciLessThan15(int n);
int printRecursiveFactorialLessThan50(int n);
int DynamicProgrammingFunc(int n);

int main(int argc, char* argv[])
{
	//Tests:
	std::cout << RecursiveMultiplication(2, 10) << std::endl; // Expected result: 10

	std::cout << NonRecursiveFibonacci(8) << std::endl; //Expected result: 5

	PrintFibonacciLessThan15(14); //Expected result: 0 1 1 2 3 5 8 13

	std::cout << std::endl;// ->Adding an extra line

	printRecursiveFactorialLessThan50(49);//Expected result: 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1

	return 0;
}

//ERROR: -8. 2 main mistakes here. The first one, you are asking the user to use just 
//positive integers, which is wrong, because a multiplication accepts negative numbers 
//and zeros. The second one is that you didn't use Recursion. Look at the name of the function...

//A good answer for this question is: 
//int RecursiveMultiplication(int a, int b)
//{
//	if (b == 0) 
//	{
//		return 0;
//	}
//	if (b > 0) 
//	{
//		return a + RecursiveMultiplication(a, b - 1);
//	}
//	if (b < 0) 
//	{
//		return -RecursiveMultiplication(a, -b);
//	}
//}


int RecursiveMultiplication(int a, int b)
{
	int i;
	int result = 0;

	if (a < 0 || b < 0)
	{
		std::cout << "Use only positive integers" << std::endl;
		return 0;
	}

	else
	{
		for (i = 0; i < a; ++i)
		{
			result = result + b;
		}

		return result;
	}

//	TODO: Write a recursive function to multiply two positive integers
//	without using the operator *
//	You can use addition(+), subtraction(-) and bitShifting(<< or >>), but you
//	should minimize the number of those operations.

}

//COMMENT: It's working, so no deduction. But you could make it a little bit more optional.
//It's all good!
int NonRecursiveFibonacci(int n)
{
	int counter = 2;
	int n1 = 0;
	int n2 = 1;
	int temp;
	
	while ( counter < n)
	{
		temp = n2;
		n2 = n1 + n2;
		n1 = temp;
		++counter;
	}

	if(n == 0)
	{
		return 0;
	}

	else if (n == 1)
	{
		return 1;
	}

	else if (n < 0)
	{
		std::cout << "Only input 0 or positive integers!" << std::endl;
	}

	else
	{
		return n1 + n2;
	}


	//TODO: Convert the recursive fibonacci that we did in class
	//to a non recursive method, using a bottom-up approach.
}

//COMMENT: PERFECT!
int PrintFibonacciLessThan15(int n)
{
	assert(n < 15);

	for (int i = 0; i < n+1; ++i)
	{
		std::cout << NonRecursiveFibonacci(i) << " ";
	}

	//TODO: Create a method that will print all the fibonacci sequence
	//less than 15. The way that you should print is:
	//PrintFibonacciLessThan15(7) -> "0 1 1 2 3 5 8 13". You just need to print what is between "".
	//Don't forget that is less than 15, so use assert if the method is being used outside the
	//boundaries of the function.
	return 0;
}

//COMMENT: PERFECT!
int printRecursiveFactorialLessThan50(int n)
{
	assert(n < 50);

	for (int i = 0; i < n; ++i)
	{
		if (n - i == 1)
		{
			std::cout << n - i << std::endl;
			break;
		}

		std::cout << n - i << " * ";
	}


	//TODO: Create a method that will print recursive
	//the factorial multiplication format of a number that is less than 50.
	//ASSERT that this function will be used in a correct way.
	//As an example:
	//printRecursiveFactorialLessThan50(10) -> "10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1"
	//The function just prints what is between "".
	return 0;
}

//TODO: Show with dynamic programming, the results and calls for DynamicProgrammingFunc(10)
//Identify repeated calls. This question you can do in a piece of paper drawing the calls
//and results and saving an image on your git repo.
int DynamicProgrammingFunc(int n)
{
	if (n < 5)
	{
		return n - 2;
	}

	return DynamicProgrammingFunc(n - 3) - (DynamicProgrammingFunc(n - 1) * DynamicProgrammingFunc(n - 2));
}