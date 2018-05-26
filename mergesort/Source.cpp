#include <iostream>
#include <vector>

void Merge(std::vector<int>* data, int left, int middle, int right)
{
	int size = right - left + 1;
	std::vector<int> tmpArray(size);	
	int iLeft = left;
	int iRight = middle + 1;
	for (int k = 0; k < size; ++k)
	{
		if (iLeft > middle + left)
		{
			tmpArray[k] = (*data)[iRight];
			++iRight;
		}
		else if (iRight > right)
		{
			tmpArray[k] = (*data)[iLeft];
			++iLeft;
		}
		else
		{
			if ((*data)[iLeft] < (*data)[iRight])
			{
				tmpArray[k] = (*data)[iLeft];
				++iLeft;
			}
			else
			{
				tmpArray[k] = (*data)[iRight];
				++iRight;
			}
		}
	}
	memcpy(data->data() + left, tmpArray.data(), size * sizeof(int));
}

void MergeSort(std::vector<int>* data, int left, int right)
{
	if (left < right)
	{
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int middle = left + (right - left) / 2;
		//sort left sub-array.
		MergeSort(data, left, middle);
		//sort right sub-array
		MergeSort(data, middle + 1, right);
		//Merge left and right
		Merge(data, left, middle, right);
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
	

	std::cout << "Data set1:\n";
	PrintArray(data_set_1);
	MergeSort(&data_set_1, 0, data_set_1.size() - 1);
	PrintArray(data_set_1);

	std::vector<int> data_set_2 = { 4, 1, 2, 5, 9, 7, 8, 3, 6 };
	std::cout << "Data set2:\n";
	PrintArray(data_set_2);
	MergeSort(&data_set_2, 0, data_set_2.size() - 1);
	PrintArray(data_set_2);

	return 0;
}