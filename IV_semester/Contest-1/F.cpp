#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	size_t len = 0;
	size_t number_of_colors = 0;
	std::cin >> len >> number_of_colors;

	std::vector<size_t> arr(len, 0);
	for (size_t i = 0; i < len; i++)
	{
		size_t temp = 0;
		std::cin >> temp;
		arr[i] = temp;
	}

	std::vector<int> d2(len, 0);
	int l = 0;
	int r = -1;
	for (int i = 0; i < len; i++)
	{
		int k = i > r ? 0 : std::min(d2[l + r - i + 1], r - i + 1);
		while (i + k < len && i - k - 1 >= 0 && arr[i + k] == arr[i - k - 1])  ++k;
		d2[i] = k;
		if (i + k - 1 > r)
		{
			l = i - k;
			r = i + k - 1;
		}
	}

	std::vector<int> answer;

	for (size_t i = 0; i <= (len / 2); i++)
	{
		if (d2[i] >= i)
		{
			answer.push_back(len - i);
		}
	}

	std::reverse(answer.begin(), answer.end());
	for (size_t i = 0; i < answer.size(); i++)
	{
		std::cout << answer[i] << ' ';
	}

	return 0;
}
