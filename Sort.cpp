#include <iostream>
#include <vector>

using namespace std;
/**
 * @author Nima Adibpour
 * @brief Tests whether the first parameter given is greater than the second parameter
 * @param a The first number
 * @param b The second number
 * @return True if a &gt b, false otherwise
 */
bool isGreaterThan(int a, int b);
/**
 * @author Nima Adibpour
 * @brief Tests whether the first parameter given is smaller than the second parameter
 * @param a The first number
 * @param b The second number
 * @return True if a &lt b, false otherwise
 */
bool isLessThan(int a, int b);
/**
 * @author Nima Adibpour
 * @brief Function pointer to a compare function that compares two integers and returns
 * the result of comparison as <strong>true</strong> or <strong>false</strong>.
 */
typedef bool (*compFunction)(int, int);
/**
 * @brief Bubble sort meant for use with an array (vector) that uses
 * a function pointer, whose function is called on comparison of two
 * values to decide whether the sort has to be ascending or descending
 * @param p         Reference to the first element of the array to be sorted
 * @param length    The length of the array to be sorter
 * @param compare   Pointer to function to be called on each comparison on
 *                  two elements of the array
 */
void(sortWithPointers(int* p, int length, compFunction compare));

int main() {
	int arraySize = 10;
	vector<int> myArray1(arraySize);
	vector<int> myArray2(arraySize);

	for (int i = 0; i < arraySize; i++) {
		myArray2[i] = myArray1[i] = rand() % arraySize + 1;
        cout << myArray1[i] << " ";
	}
    cout << endl;
	sortWithPointers(&myArray1[0], arraySize, isGreaterThan);
    for (int j = 0; j < arraySize; ++j) {
        cout << myArray1[j] << " ";
    }
	return 0;
}

void sortWithPointers(int* p, int length, compFunction compare) {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - 1 - i; j++) {
            if (compare(*(p + j),*(p + j + 1))) {
                int temp = *(p + j);
                *(p + j) = *(p + j + 1);
                *(p + j + 1) = temp;
            }
		}
	}
}

bool isLessThan(int a, int b) {
    return a < b;
}

bool isGreaterThan(int a, int b) {
    return a > b;
}