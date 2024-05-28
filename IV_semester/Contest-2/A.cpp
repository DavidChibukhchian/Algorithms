#include <iostream>

//--------------------------------------------------------------------------------------------------------------

const long long MOD = 1e9 + 7;

//--------------------------------------------------------------------------------------------------------------

long long get_inverse(long long number, long long mod);
long long get_pow_mod(long long number, long long pow, long long mod);

//--------------------------------------------------------------------------------------------------------------

int main()
{
	long long a, b, c, d;
	std::cin >> a >> b >> c >> d;

	long long res = (((a * get_inverse(b, MOD)) % MOD + (c * get_inverse(d, MOD)) % MOD) % MOD + MOD) % MOD;

	std::cout << res << std::endl;

	return 0;
}

//--------------------------------------------------------------------------------------------------------------

long long get_inverse(long long number, long long mod)
{
	return get_pow_mod(number, mod - 2, mod);
}

//--------------------------------------------------------------------------------------------------------------

long long get_pow_mod(long long number, long long pow, long long mod)
{
	if (pow == 0)
		return 1;

	if (pow % 2 == 1)
		return (number * get_pow_mod(number, pow - 1, mod)) % mod;

	long long half = get_pow_mod(number, pow / 2, mod);

	return (half * half) % mod;
}

//--------------------------------------------------------------------------------------------------------------
