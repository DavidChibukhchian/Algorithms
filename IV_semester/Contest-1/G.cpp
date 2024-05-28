#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

//-------------------------------------------------------------------------------------------------

size_t get_number_of_occurences(const std::string& pattern, const std::string& text);

//-------------------------------------------------------------------------------------------------

class Hash
{
private:
	static const int  mod = (int)(1000000123);
	static const int base = (int)(1000000007);

	static std::vector<int>      pow_base_mod;
	static std::vector<uint64_t> pow_base_uint64;

	std::vector<int>      pref_hash_mod;
	std::vector<uint64_t> pref_hash_uint64;

public:
	Hash(const std::string& str);

	std::pair<int, uint64_t> get_substr_hash(size_t pos, size_t len, size_t max_pow = 0);
};

//-------------------------------------------------------------------------------------------------

std::vector<int>      Hash::pow_base_mod{1};
std::vector<uint64_t> Hash::pow_base_uint64{1};

//-------------------------------------------------------------------------------------------------

int main()
{
	std::string pattern, text;
	std::cin >> pattern >> text;

	size_t number_of_occurences = get_number_of_occurences(pattern, text);

	std::cout << number_of_occurences;

	return 0;
}

//-------------------------------------------------------------------------------------------------

size_t get_number_of_occurences(const std::string& pattern, const std::string& text)
{
	size_t text_len = text.size();
	size_t pattern_len = pattern.size();
	size_t max_pow = std::max(text_len, 2 * pattern_len);

	Hash hash_text(text);
	Hash hash_pattern(pattern + pattern);

	std::vector<std::pair<int, uint64_t>> substr_hashes;
	for (size_t i = 0; i  < pattern_len; i++)
	{
		substr_hashes.push_back(hash_pattern.get_substr_hash(i, pattern_len, max_pow));
	}
	std::sort(substr_hashes.begin(), substr_hashes.end());

	size_t number_of_occurences = 0;
	for (size_t i = 0; i + pattern_len <= text_len; i++)
	{
		number_of_occurences += (size_t)std::binary_search(substr_hashes.begin(), substr_hashes.end(),
		                                                   hash_text.get_substr_hash(i, pattern_len, max_pow));
	}

	return number_of_occurences;
}

//-------------------------------------------------------------------------------------------------

Hash::Hash(const std::string &str)
{
	pref_hash_mod.assign(str.size() + 1, 0);
	pref_hash_uint64.assign(str.size() + 1, 0);

	while (pow_base_mod.size() <= str.size())
	{
		pow_base_mod.push_back(1LL * pow_base_mod.back() * base % mod);
		pow_base_uint64.push_back(pow_base_uint64.back() * base);
	}

	for (size_t i = 0; i < str.size(); i++)
	{
		pref_hash_mod[i + 1] = (pref_hash_mod[i] + 1LL * str[i] * pow_base_mod[i]) % mod;
		pref_hash_uint64[i + 1] = pref_hash_uint64[i] + str[i] * pow_base_uint64[i];
	}
}

//-------------------------------------------------------------------------------------------------

std::pair<int, uint64_t> Hash::get_substr_hash(size_t pos, size_t len, size_t max_pow)
{
	int         hash_mod =    pref_hash_mod[pos + len] -    pref_hash_mod[pos];
	uint64_t hash_uint64 = pref_hash_uint64[pos + len] - pref_hash_uint64[pos];

	if (hash_mod < 0)
	{
		hash_mod += mod;
	}

	if (max_pow != 0)
	{
		hash_mod = 1LL * hash_mod * pow_base_mod[max_pow - (pos + len - 1)] % mod;
		hash_uint64 *= pow_base_uint64[max_pow - (pos + len - 1)];
	}

	return std::make_pair(hash_mod, hash_uint64);
}

//-------------------------------------------------------------------------------------------------