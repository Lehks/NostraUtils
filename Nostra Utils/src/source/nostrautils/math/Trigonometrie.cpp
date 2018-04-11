
#include<iostream>

double const pi = 3.1415;
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

double cos(double x)
{
	double x_rad = (x*pi) / 180;
	double ans = 1;
	double temp = 1;
	int acc = 1;
	for (int i = 1; i <= 2; i += 2)
	{
		temp = temp * (-1) * x_rad * x_rad / (i * (i + 1));
		ans = ans + temp;
	}

	return ans;
}

double sin(double x)
{
	double temp = 1 - cos(x) * cos(x);
	double ans = sqrt(temp);
	return ans;
}

double tan(double x)
{
	
	return (cos(x)/sin(x));
}