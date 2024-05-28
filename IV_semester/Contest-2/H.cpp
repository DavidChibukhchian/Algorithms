#include <iostream>
#include <cstdint>
#include <vector>

//-------------------------------------------------------------------------------------------------

const int64_t MOD = 1e9 + 9;

//-------------------------------------------------------------------------------------------------

struct Matrix
{
	int64_t a1;
	int64_t a2;
	int64_t a3;
	int64_t a4;
};

struct Airport
{
	int64_t x;
	int64_t y;
	int64_t number_of_flights;
};

//-------------------------------------------------------------------------------------------------

int64_t get_number_of_ways(const std::vector<Airport>& airports, int64_t number_of_airports, int64_t attraction);

int64_t get_Fib_number(int64_t ord);

Matrix power_matrix(Matrix matrix, int64_t power);

Matrix mul_matrix(Matrix matrix1, Matrix matrix2);

//-------------------------------------------------------------------------------------------------

int main()
{
	int64_t number_of_airports, number_of_attractions;
	std::cin >> number_of_airports >> number_of_attractions;

	std::vector<Airport> airports(number_of_airports);
	std::vector<int64_t> attractions(number_of_attractions);

	for (int64_t i = 0; i < number_of_airports; i++)
	{
		int64_t x_coord, y_coord, number_of_flights;
		std::cin >> x_coord >> y_coord >> number_of_flights;
		airports[i].x = x_coord;
		airports[i].y = y_coord;
		airports[i].number_of_flights = number_of_flights % MOD;
	}

	for (int64_t i = 0; i < number_of_attractions; i++)
	{
		int64_t coeff = 0;
		std::cin >> coeff;
		attractions[i] = coeff;
	}

	for (int64_t i = 0; i < number_of_attractions; i++)
	{
		int64_t number_of_ways = get_number_of_ways(airports, number_of_airports, attractions[i]);
		std::cout << number_of_ways << '\n';
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------

int64_t get_number_of_ways(const std::vector<Airport>& airports, int64_t number_of_airports, int64_t attraction)
{
	int64_t number_of_ways = 0;

	for (int64_t i = 0; i < number_of_airports; i++)
	{
		if ((airports[i].y - airports[i].x) >= attraction)
		{
			int64_t combinations = get_Fib_number(airports[i].y - airports[i].x - attraction + 1) % MOD;

			number_of_ways = (number_of_ways + (airports[i].number_of_flights * combinations) % MOD) % MOD;
		}
	}

	return number_of_ways;
}

//-------------------------------------------------------------------------------------------------

int64_t get_Fib_number(int64_t ord)
{
	Matrix matrix = {0, 1, 1, 1};

	Matrix powered_matrix = power_matrix(matrix, ord);

	return powered_matrix.a3;
}

//-------------------------------------------------------------------------------------------------

Matrix power_matrix(Matrix matrix, int64_t power)
{
	if (power == 0)
		return {1, 0, 0, 1};
	else if (power == 1)
		return matrix;

	Matrix half_powered = power_matrix(matrix, power / 2);

	if (power % 2 == 0)
		return mul_matrix(half_powered, half_powered);
	else
		return mul_matrix(half_powered, mul_matrix(half_powered, matrix));
}

//-------------------------------------------------------------------------------------------------

Matrix mul_matrix(Matrix matrix1, Matrix matrix2)
{
	Matrix res = {};

	res.a1 = ((matrix1.a1 % MOD) * (matrix2.a1 % MOD) % MOD + (matrix1.a2 % MOD) * (matrix2.a3 % MOD) % MOD) % MOD;
	res.a2 = ((matrix1.a1 % MOD) * (matrix2.a2 % MOD) % MOD + (matrix1.a2 % MOD) * (matrix2.a4 % MOD) % MOD) % MOD;
	res.a3 = ((matrix1.a3 % MOD) * (matrix2.a1 % MOD) % MOD + (matrix1.a4 % MOD) * (matrix2.a3 % MOD) % MOD) % MOD;
	res.a4 = ((matrix1.a3 % MOD) * (matrix2.a2 % MOD) % MOD + (matrix1.a4 % MOD) * (matrix2.a4 % MOD) % MOD) % MOD;

	return res;
}

//-------------------------------------------------------------------------------------------------
