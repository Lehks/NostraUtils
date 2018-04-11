
#include<iostream>
int fak(int x)
{
	int i = 1, fak = 1;

	while (i <= x)
	{
		fak = i * fak;
		i++;
	}
	return fak;
}

int cos(int x)
{
	int result = 1;

	result = 1 - (pow(x, 2) / fak(2)) + (pow(x, 4) / fak(4)) - (pow(x, 6) / fak(6) + (pow(x, 8) / fak(8)));

	return result;
}

int sin(int x)
{

	return - 1;
}

int tan(int x)
{

	return -1;
}