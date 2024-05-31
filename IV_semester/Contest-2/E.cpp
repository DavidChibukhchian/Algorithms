#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>

//-------------------------------------------------------------------------------------------------

typedef std::complex<long double> complex;

//-------------------------------------------------------------------------------------------------

template <typename T>
class Polynom
{
	template <typename U>
	friend std::istream& operator>>(std::istream& input, Polynom<U>& polynom);
	template <typename U>
	friend std::ostream& operator<<(std::ostream& output, const Polynom<U>& polynom);

public:
	size_t pow = 0;
	std::vector<T> coeffs;

	void expand(size_t new_power);
	void delete_leading_zeroes();
};

//-------------------------------------------------------------------------------------------------

template <typename T>
std::istream& operator>>(std::istream& input, Polynom<T>& polynom);

template <typename T>
std::ostream& operator<<(std::ostream& output, const Polynom<T>& polynom);

//-------------------------------------------------------------------------------------------------

template <typename T>
Polynom<complex> to_complex(const Polynom<T>& polynom);

template <typename T>
void multiply(const Polynom<T>& polynom_a, const Polynom<T>& polynom_b, Polynom<T>& res);

template <typename T>
size_t get_min_power_of_two(const Polynom<T>& a, const Polynom<T>& b);

void fast_Fourier_transform(const Polynom<complex>& polynom, Polynom<complex>& out, bool is_inverse);

//-------------------------------------------------------------------------------------------------

int main()
{
	Polynom<int> a, b, res;
	std::cin >> a >> b;

	multiply(a, b, res);

	std::cout << res;

	return 0;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
std::istream& operator>>(std::istream& input, Polynom<T>& polynom)
{
	size_t power = 0;
	input >> power;

	polynom.expand(power);
	for (size_t i = 0; i < power + 1; i++)
	{
		T coeff = 0;
		input >> coeff;
		polynom.coeffs[i] = coeff;
	}

	std::reverse(polynom.coeffs.begin(), polynom.coeffs.end());

	return input;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
std::ostream& operator<<(std::ostream& output, const Polynom<T>& polynom)
{
	output << polynom.pow << ' ';
	for (size_t i = 0; i < polynom.pow + 1; i++)
	{
		output << polynom.coeffs[polynom.pow - i] << ' ';
	}
	output << '\n';

	return output;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
void Polynom<T>::expand(size_t new_power)
{
	coeffs.resize(new_power + 1);
	pow = new_power;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
void Polynom<T>::delete_leading_zeroes()
{
	size_t real_pow = coeffs.size() - 1;
	while (coeffs[real_pow] == 0)
	{
		real_pow--;
	}

	coeffs.resize(real_pow + 1);
	pow = real_pow;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
Polynom<complex> to_complex(const Polynom<T>& polynom)
{
	Polynom<complex> complex_polynom;
	complex_polynom.expand(polynom.pow);

	for (size_t i = 0; i < polynom.pow + 1; i++)
	{
		complex_polynom.coeffs[i] = complex(polynom.coeffs[i]);
	}

	return complex_polynom;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
void multiply(const Polynom<T>& polynom_a, const Polynom<T>& polynom_b, Polynom<T>& res)
{
	Polynom<complex> a = to_complex(polynom_a);
	Polynom<complex> b = to_complex(polynom_b);

	size_t min_power_of_two = get_min_power_of_two(polynom_a, polynom_b);
	a.expand(min_power_of_two - 1);
	b.expand(min_power_of_two - 1);

	Polynom<complex> transformed_a;
	Polynom<complex> transformed_b;
	fast_Fourier_transform(a, transformed_a, false);
	fast_Fourier_transform(b, transformed_b, false);

	for (size_t i = 0; i < min_power_of_two; i++)
	{
		transformed_a.coeffs[i] *= transformed_b.coeffs[i];
	}

	Polynom<complex> double_transformed_a;
	fast_Fourier_transform(transformed_a, double_transformed_a, true);

	res.expand(min_power_of_two - 1);
	for (size_t i = 0; i < min_power_of_two; i++)
	{
		res.coeffs[i] = std::lround(double_transformed_a.coeffs[i].real());
	}

	res.delete_leading_zeroes();
}

//-------------------------------------------------------------------------------------------------

template <typename T>
size_t get_min_power_of_two(const Polynom<T>& a, const Polynom<T>& b)
{
	size_t power_of_two = 1;
	while (power_of_two < std::max(a.pow + 1, b.pow + 1))
	{
		power_of_two <<= 1;
	}
	power_of_two <<= 1;

	return power_of_two;
}

//-------------------------------------------------------------------------------------------------

void fast_Fourier_transform(const Polynom<complex>& polynom, Polynom<complex>& out, bool is_inverse)
{
	if (polynom.coeffs.empty())
		return;

	out.expand(polynom.pow);
	if (polynom.pow == 0)
	{
		out.coeffs[0] = polynom.coeffs[0];
		return;
	}

	Polynom<complex> a, b;
	for (size_t i = 0; i < polynom.pow + 1; i++)
	{
		if (i % 2 == 0)
			a.coeffs.push_back(polynom.coeffs[i]);
		else
			b.coeffs.push_back(polynom.coeffs[i]);
	}
	a.pow = a.coeffs.size() - 1;
	b.pow = b.coeffs.size() - 1;

	Polynom<complex> transformed_a, transformed_b;
	fast_Fourier_transform(a, transformed_a, is_inverse);
	fast_Fourier_transform(b, transformed_b, is_inverse);

	complex x(1);
	complex delta = std::exp(complex(0., 2 * M_PI / (polynom.pow + 1)));
	if (is_inverse)
	{
		delta = complex(1., 0.) / delta;
	}

	for (size_t i = 0; i < (polynom.pow + 1) / 2; i++)
	{
		out.coeffs[i] = transformed_a.coeffs[i] + x * transformed_b.coeffs[i];
		out.coeffs[i + (polynom.pow + 1) / 2] = transformed_a.coeffs[i] - x * transformed_b.coeffs[i];
		if (is_inverse)
		{
			out.coeffs[i] /= 2.;
			out.coeffs[i + (polynom.pow + 1) / 2] /= 2.;
		}

		x *= delta;
	}
}

//-------------------------------------------------------------------------------------------------
