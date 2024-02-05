#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstdint>

//----------------------------------------------------------------------------------------------------------------

class Puzzle_Solver
{
private:
	const size_t FIELD_SIZE = 3;
	const size_t       BASE = 10;
	const size_t FINISH_POS = 123456780;
	size_t start_pos;
	bool answer_is_restored;

	std::map<size_t, bool>   used;
	std::map<size_t, size_t> parent;
	std::map<size_t, char>   step;
	std::queue<size_t> unused;
	std::vector<char>  answer;

	void solve(size_t curr_pos);

	size_t get_null_idx(size_t pos);

	void change_pos(size_t* pos, size_t idx1, size_t idx2);

	size_t get_digit(size_t pos, size_t idx);

	void set_null(size_t* pos, size_t idx);

	void restore_answer();

public:
	bool puzzle_is_solved;

	Puzzle_Solver();

	void get_start_position();

	void solve_puzzle();

	void print_answer();
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	Puzzle_Solver puzzle_solver{};

	puzzle_solver.get_start_position();

	puzzle_solver.solve_puzzle();

	puzzle_solver.print_answer();

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

Puzzle_Solver::Puzzle_Solver()
{
	start_pos = 0;
	puzzle_is_solved   = false;
	answer_is_restored = false;
}

//----------------------------------------------------------------------------------------------------------------

void Puzzle_Solver::get_start_position()
{
	size_t powered_base = (size_t)std::pow(BASE, FIELD_SIZE * FIELD_SIZE - 1);

	for (size_t i = 0; i < FIELD_SIZE * FIELD_SIZE; i++)
	{
		size_t digit = 0;
		std::cin >> digit;

		start_pos += digit * powered_base;
		powered_base /= BASE;
	}
}

//----------------------------------------------------------------------------------------------------------------

void Puzzle_Solver::solve_puzzle()
{
	unused.push(start_pos);

	while (!unused.empty())
	{
		size_t curr_pos = unused.front();
		unused.pop();

		if (curr_pos == FINISH_POS)
		{
			puzzle_is_solved = true;
			return;
		}
		solve(curr_pos);
	}
}

//----------------------------------------------------------------------------------------------------------------

void Puzzle_Solver::print_answer()
{
	if (puzzle_is_solved)
	{
		if (!answer_is_restored)
		{
			restore_answer();
		}
		std::cout << answer.size() << "\n";
		for (size_t i = 0; i < answer.size(); i++)
		{
			std::cout << answer[i];
		}
	}
	else
	{
		std::cout << -1 << "\n";
	}
}

//----------------------------------------------------------------------------------------------------------------

void Puzzle_Solver::solve(size_t pos)
{
	if (used[pos]) return;

	size_t null_idx = get_null_idx(pos);
	if (null_idx == UINT16_MAX) return;

	if (null_idx % 3 != 2)
	{
		size_t next_pos = pos;

		change_pos(&next_pos, null_idx, null_idx + 1);
		if (!used[next_pos])
		{
			unused.push(next_pos);
			parent[next_pos] = pos;
			step[next_pos] = 'L';
		}
	}
	if (null_idx % 3 != 0)
	{
		size_t next_pos = pos;

		change_pos(&next_pos, null_idx, null_idx - 1);
		if (!used[next_pos])
		{
			unused.push(next_pos);
			parent[next_pos] = pos;
			step[next_pos] = 'R';
		}
	}
	if (null_idx < 6)
	{
		size_t next_pos = pos;

		change_pos(&next_pos, null_idx, null_idx + 3);
		if (!used[next_pos])
		{
			unused.push(next_pos);
			parent[next_pos] = pos;
			step[next_pos] = 'U';
		}
	}
	if (null_idx > 2)
	{
		size_t next_pos = pos;

		change_pos(&next_pos, null_idx, null_idx - 3);
		if (!used[next_pos])
		{
			unused.push(next_pos);
			parent[next_pos] = pos;
			step[next_pos] = 'D';
		}
	}
	
	used[pos] = true;
}

//----------------------------------------------------------------------------------------------------------------

size_t Puzzle_Solver::get_null_idx(size_t pos)
{
	size_t powered_base = 1;

	for (size_t i = 0; i < FIELD_SIZE * FIELD_SIZE; i++)
	{
		if ((pos / powered_base) % BASE == 0)
			return i;

		powered_base *= BASE;
	}

	// error
	return UINT16_MAX;
}

//----------------------------------------------------------------------------------------------------------------

void Puzzle_Solver::change_pos(size_t* pos, size_t idx1, size_t idx2)
{
	size_t digit1 = get_digit(*pos, idx1);
	size_t digit2 = get_digit(*pos, idx2);

	set_null(pos, idx1);
	set_null(pos, idx2);

	*pos += digit1 * ((size_t)std::pow(BASE, idx2));
	*pos += digit2 * ((size_t)std::pow(BASE, idx1));
}

//----------------------------------------------------------------------------------------------------------------

size_t Puzzle_Solver::get_digit(size_t pos, size_t idx)
{
	size_t powered_base = (size_t)std::pow(BASE, idx);

	return (pos / powered_base) % BASE;
}

//----------------------------------------------------------------------------------------------------------------

void Puzzle_Solver::set_null(size_t* pos, size_t idx)
{
	*pos -= get_digit(*pos, idx) * ((size_t)std::pow(BASE, idx));
}

//----------------------------------------------------------------------------------------------------------------

void Puzzle_Solver::restore_answer()
{
	size_t curr_pos = FINISH_POS;

	while (curr_pos != start_pos)
	{
		answer.push_back(step[curr_pos]);
		curr_pos = parent[curr_pos];
	}

	std::reverse(answer.begin(), answer.end());

	answer_is_restored = true;
}

//----------------------------------------------------------------------------------------------------------------