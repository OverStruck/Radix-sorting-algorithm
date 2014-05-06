/*
	Radix sorting algorithm
	Implementation using 2 arrays
*/
#include<iostream>
#include<cmath>
#include<ctime>

using namespace std;

//determines the number of 'passes' based on the first number
//of the array(assuming all numbers have the same number of digits)
//12345 = 5 passes
int getNumbOfPasses(int n)
{
	int passes = 0;
	for (int i = 1; n > 0; i++)
	{
		passes = i;
		n /= 10;

		if (n > 0)
			passes++;
	}
	return passes;
}

//gets the 'correct' digit from a number based on the pass number
//12345 => on the first pass 5 would be returned; 4 on the second pass and so on...
int getDigit(int n, int pass)
{
	int x = static_cast<int>(pow(10, pass));
	return n % x / (x / 10);
}

//prints the array
void printArray(int a[], int numOfElems)
{
	for (int i = 0; i < numOfElems; i++)
		cout << a[i] << endl;
}

int main()
{
	int CAP = 50;
	int* a1 = new int[CAP];
	int* a2 = new int[CAP];
	int numOfElems = 20;
	//generate random array
	for (int i = 0; i < numOfElems; i++)
	{
		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0; i < numOfElems; ++i)
			a1[i] = 10000 + rand() % (numOfElems * 100000);
	}

	cout << "Printing Original Array: " << endl;
	printArray(a1, numOfElems);

	//setup ends

	int passes = getNumbOfPasses(a1[0]);
	int currentPass = 1;
	int loc = 0;//location
	while (currentPass <= passes)
	{
		//loop through nums 0 -> 9
		for (int lookingFor = 0; lookingFor <= 9; lookingFor++)
		{
			//loop through whole array
			for (int i = 0; i < numOfElems; i++)
			{
				//we toggle between arrays with each pass
				if (currentPass % 2 == 0)
				{
					//compare numb(0->9) with single digit from array
					if (getDigit(a2[i], currentPass) == lookingFor)
						a1[loc++] = a2[i];
				}
				else
				{
					if (getDigit(a1[i], currentPass) == lookingFor)
						a2[loc++] = a1[i];
				}
			}
		}	
		loc = 0;
		++currentPass;
	}

	cout << "\nPrinting Sorting Array :" << endl;
	if (currentPass % 2 == 0)
		printArray(a2, numOfElems);
	else
		printArray(a1, numOfElems);

	//delete dynamic data
	delete[] a1;
	delete[] a2;
	//we don't want dangling pointers
	a1 = 0;
	a2 = 0;

	cout << endl;
	system("pause");
	return 0;
}