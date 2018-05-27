#include <iostream>
#include <vector>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;


template<typename T>
void PrintVector(std::vector<T> data)
{
	for (int i = 0; i < data.size(); ++i)
	{
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}

template<typename It>
size_t MergeAndCountInversions(It begin, It middle, It end)
{
	size_t size = (end - begin);
	std::vector<It::value_type> buffer(size);
	It left {begin};
	It right{ middle };
	size_t split_inversions = 0;
	for (int k = 0; k < size; ++k)
	{
		if (left >= middle && right <= end)
		{
			buffer[k] = *right;
			++right;
			split_inversions += (middle - left);
		}
		else if (right >= end && left < middle)
		{
			buffer[k] = *left;
			++left;
		}
		else
		{
			if (*left < *right)
			{
				buffer[k] = *left;
				++left;
			}
			else
			{
				buffer[k] = *right;
				++right;
				split_inversions += (middle - left);
			}
		}
	}
	std::copy(buffer.begin(), buffer.end(), begin);
	return split_inversions;
}

template<typename It>
size_t SortAndCountInversion(It begin, It end)
{
	size_t size = std::distance(begin, end);
	if (size <= 1)
		return 0;
	auto middle = std::next(begin, size / 2);
	size_t result_a = SortAndCountInversion(begin, middle);
	size_t result_b = SortAndCountInversion(middle, end);
	size_t result_c = MergeAndCountInversions(begin, middle, end);
	return result_a + result_b + result_c;
}

int main(int argc, char** argv)
{
	std::cout << "Counting inversions\n";

	std::vector<int> data = { 1, 3, 5, 2, 4, 6 };
	PrintVector(data);
	auto t1 = Clock::now();
	size_t inversions = SortAndCountInversion(data.begin(), data.end());
	auto t2 = Clock::now();
	PrintVector(data);
	std::cout << "Inversions: " << inversions << std::endl;
	std::cout << "SortAndCountInversion tooks " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " ns" << std::endl;

	return 0;
}