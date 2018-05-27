#include <iostream>
#include <vector>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
#include <algorithm>

void Merge(std::vector<int>* data, std::vector<int>* tmpData, int left, int middle, int right)
{
	int size = right - left + 1;
	int iLeft = left;
	int iRight = middle + 1;
	for (int k = 0; k < size; ++k)
	{
		if (iLeft > middle + left)
		{
			(*tmpData)[k] = (*data)[iRight];
			++iRight;
		}
		else if (iRight > right)
		{
			(*tmpData)[k] = (*data)[iLeft];
			++iLeft;
		}
		else
		{
			if ((*data)[iLeft] < (*data)[iRight])
			{
				(*tmpData)[k] = (*data)[iLeft];
				++iLeft;
			}
			else
			{
				(*tmpData)[k] = (*data)[iRight];
				++iRight;
			}
		}
	}
	memcpy(data->data() + left, tmpData->data(), size * sizeof(int));
}

void MergeSort(std::vector<int>* data, std::vector<int>* tmpData, int left, int right)
{
	if (left < right)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int middle = left + (right - left) / 2;
		//sort left sub-array.
		MergeSort(data, tmpData, left, middle);
		//sort right sub-array
		MergeSort(data, tmpData, middle + 1, right);
		//Merge left and right
		Merge(data, tmpData, left, middle, right);
	}
}

void PrintArray(std::vector<int> data)
{
	for (int i = 0; i < data.size(); ++i)
	{
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}


int main(int argc, char** argv)
{
	std::cout << "Algorithm: merge sort\n";
	
	std::vector<int> data_set_1 = { 12, 11, 13, 5, 6, 7};	
	std::vector<int> tmp_data_set_1(data_set_1.size());

	std::cout << "Data set1:\n";
	PrintArray(data_set_1);	
	MergeSort(&data_set_1, &tmp_data_set_1, 0, data_set_1.size() - 1);
	PrintArray(data_set_1);

	std::vector<int> data_set_2 = { 4, 1, 2, 5, 9, 7, 8, 3, 6 };
	std::vector<int> tmp_data_set_2(data_set_2.size());
	std::cout << "Data set2:\n";
	PrintArray(data_set_2);
	auto t1 = Clock::now();
	MergeSort(&data_set_2, &tmp_data_set_2, 0, data_set_2.size() - 1);
	auto t2 = Clock::now();
	PrintArray(data_set_2);
	std::cout << "MergeSort tooks " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " ns" << std::endl;

	std::vector<int> data_set_3 = { 4, 1, 2, 5, 9, 7, 8, 3, 6 };

	auto ss1 = Clock::now();
	std::stable_sort(data_set_3.begin(), data_set_3.end());
	auto ss2 = Clock::now();

	std::cout << "std::stable_sort tooks " << std::chrono::duration_cast<std::chrono::nanoseconds>(ss2 - ss1).count() << " ns" << std::endl;

	return 0;
}