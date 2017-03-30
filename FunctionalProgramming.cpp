#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>

using namespace std;
class IComparer {
public:
    virtual bool isBefore(int a, int b) {}
};
class LessThanComparer : public IComparer {
public:
    bool isBefore(int a, int b) {
        return a < b;
    }
};
class GreaterThanComparer : public IComparer {
public:
    bool isBefore(int a, int b) {
        return a > b;
    }
};
class IsClosestToComparer : public IComparer {
private:
    int center;
public:
    IsClosestToComparer(int center) : center(center) {}
    bool isBefore(int a, int b) {
        return abs(a - center) < abs(b - center);
    }
};

/*************************
 * FUNCTION DECLARATIONS *
 *************************/
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
void(sortWithFunctionPointers(int *p, int length, compFunction compare));
void sortWithInterfaces(int *p, int length, IComparer* compare);
void sortWithStandardFunction(int *p, int length, function<bool (int, int)> compare);
function<bool (int, int)> generateNearestTo(int center);
void testSortPointers();
void testSortWithInterfaces() ;
void testSortWithLambdas();

int main() {
    cout << endl;
    cout << "*********************************************************" << endl;
    cout << "*   COMP 322 Assignment 3 - NIMA ADIBPOUR - 260606511   *" << endl;
    cout << "*********************************************************" << endl;
    testSortPointers();
    testSortWithInterfaces();
    testSortWithLambdas();
    return 0;
}
void testSortPointers() {
    cout << "Testing sort with Function Pointers" << endl << endl;
    unsigned long arraySize = 10;
    vector<int> myArray1(arraySize);
    vector<int> myArray2(arraySize);
    cout << "Unsorted array: " << setw(20) << "\t";
    for (int i = 0; i < arraySize; i++) {
        myArray2[i] = myArray1[i] = rand() % arraySize + 1;
        cout << myArray1[i] << " ";
    }
    cout << endl;
    cout << "Sorted array: " << endl;
    cout << "With isLessThan: " << endl << setw(35) << "\t";
    sortWithFunctionPointers(&myArray1[0], arraySize, isLessThan);
    for (int i = 0; i < arraySize; ++i) {
        cout << myArray1[i] << " ";
    }
    cout << endl;
    cout << "With isGreaterThan: " << endl << setw(35) << "\t";
    sortWithFunctionPointers(&myArray2[0], arraySize, isGreaterThan);
    for (int i = 0; i < arraySize; ++i) {
        cout << myArray2[i] << " ";
    }
    cout << endl << endl;
}
void testSortWithInterfaces() {
    cout << "Testing sort with interfaces" << endl << endl;
    cout << "LessThanComparer: " << endl;
    unsigned long arraySize = 10;
    vector<int> myArray1(arraySize);
    cout << "Unsorted array: " << setw(20) << "\t";
    for (int i = 0; i < arraySize; i++) {
        myArray1[i] = rand() % arraySize + 1;
        cout << myArray1[i] << " ";
    }
    cout << endl;
    cout << "Sorted array: " << setw(20) << "\t";
    sortWithInterfaces(&myArray1[0], arraySize, new LessThanComparer());
    for (int j = 0; j < arraySize; ++j) {
        cout << myArray1[j] << " ";
    }
    cout << endl << endl << "GreaterThanComparer: " << endl;
    vector<int> myArray2(arraySize);
    cout << "Unsorted array: " << setw(20) << "\t";
    for (int i = 0; i < arraySize; i++) {
        myArray2[i] = rand() % arraySize + 1;
        cout << myArray2[i] << " ";
    }
    cout << endl;
    cout << "Sorted array: " << setw(20) << "\t";
    sortWithInterfaces(&myArray2[0], arraySize, new GreaterThanComparer());
    for (int j = 0; j < arraySize; ++j) {
        cout << myArray2[j] << " ";
    }

    cout << endl << endl << "IsClosestToComparer with center 3: " << endl;
    vector<int> myArray3(arraySize);
    cout << "Unsorted array:" << setw(20) << "\t";
    for (int i = 0; i < arraySize; i++) {
        myArray3[i] = rand() % arraySize + 1;
        cout << myArray3[i] << " ";
    }
    cout << endl;
    cout << "Sorted array:" << setw(20) << "\t";
         sortWithInterfaces(&myArray3[0], arraySize, new IsClosestToComparer(3));
    for (int j = 0; j < arraySize; ++j) {
        cout << myArray3[j] << " ";
    }
    cout << endl << endl;
}
void testSortWithLambdas() {
    cout << "Testing sort with Lambda Expressions" << endl << endl;
    unsigned long arraySize = 10;
    vector<int> myArray1(arraySize);
    vector<int> myArray2(arraySize);
    cout << "Unsorted array: " << setw(20) << "\t";
    for (int i = 0; i < arraySize; i++) {
        myArray2[i] = myArray1[i] = rand() % arraySize + 1;
        cout << myArray1[i] << " ";
    }
    cout << endl << "Sorted array: " << endl;
    cout << "Center value 3: " << endl << setw(35) << "\t";
    sortWithStandardFunction(&myArray1[0], arraySize, generateNearestTo(3));
    for (int i = 0; i < arraySize; ++i) {
        cout << myArray1[i] << " ";
    }
    cout << endl << "Center value 10: " << endl << setw(35) << "\t";
    sortWithStandardFunction(&myArray2[0], arraySize, generateNearestTo(10));
    for (int i = 0; i < arraySize; ++i) {
        cout << myArray2[i] << " ";
    }
    cout << endl;
}

bool isLessThan(int a, int b) {
    return a < b;
}

bool isGreaterThan(int a, int b) {
    return a > b;
}

void sortWithFunctionPointers(int *p, int length, compFunction compare) {
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

void sortWithInterfaces(int *p, int length, IComparer *compare) {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length - 1 - i; ++j) {
            if(compare->isBefore(*(p + j),*(p + j + 1))){
                int temp = *(p + j);
                *(p + j) = *(p + j + 1);
                *(p + j + 1) = temp;
            }
        }
    }
}

function<bool(int, int)> generateNearestTo(int center) {
    auto compare = [center](int a, int b) {
        return abs(a - center) < abs(b - center);
    };
    return compare;
}

void sortWithStandardFunction(int *p, int length, function<bool(int, int)> compare) {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length - 1 - i; ++j) {
            if(compare(*(p + j), *(p + j  + 1))) {
                int temp = *(p + j);
                *(p + j) = *(p + j  + 1);
                *(p + j + 1) = temp;
            }
        }
    }
}





