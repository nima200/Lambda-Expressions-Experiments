#include <iostream>
#include <vector>
#include <iomanip>
#include <functional>

using namespace std;

 /**
  * Base class for the rest of the comparers to inherit from.
  */
class IComparer {
public:
    virtual bool isBefore(int a, int b) {}
};
/**
 * Class for less than comparison
 */
class LessThanComparer : public IComparer {
public:
    /**
     * Checks if the first number is smaller than the second number
     * @param a The first number
     * @param b The second number
     * @return True if a &lt b, false otherwise.
     */
    bool isBefore(int a, int b) {
        return a < b;
    }
};
/**
 * Class for greater than comparison
 */
class GreaterThanComparer : public IComparer {
public:
    /**
     * Checks if the first number is greater than the second number
     * @param a The first number
     * @param b The second number
     * @return True if a &gt b, false otherwise.
     */
    bool isBefore(int a, int b) {
        return a > b;
    }
};
/**
 * Class for distance comparison between the two numbers provided against
 * a center stored privately in the class
 */
class IsClosestToComparer : public IComparer {
private:
    int center;
public:
    IsClosestToComparer(int center) : center(center) {}
    /**
     * Checks which of the two provided numbers are closer to the center.
     * @param a The first number
     * @param b The second number
     * @return <strong>True</strong> if a is closer to the center than b, <strong>false otherwise</strong>.
     */
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
/**
 * Test function that demonstrates the features of sorting using function pointers.
 */
void testSortPointers() {
    cout << "Testing sort with Function Pointers" << endl << endl;
    unsigned long arraySize = 10;
    // Creating two arrays as we will be testing two ways of sorting here.
    vector<int> myArray1(arraySize);
    vector<int> myArray2(arraySize);
    cout << "Unsorted array: " << setw(20) << "\t";
    // Printing the array before being sorted by any function.
    for (int i = 0; i < arraySize; i++) {
        myArray2[i] = myArray1[i] = rand() % arraySize + 1;
        cout << myArray1[i] << " ";
    }
    cout << endl;
    cout << "Sorted array: " << endl;
    cout << "With isLessThan: " << endl << setw(35) << "\t";
    // Calling onto the respective sort function for this test, with pointer to "isLessThan" function passed.
    sortWithFunctionPointers(&myArray1[0], arraySize, isLessThan);
    // Printing out the result of the sorted array
    for (int i = 0; i < arraySize; ++i) {
        cout << myArray1[i] << " ";
    }
    cout << endl;
    cout << "With isGreaterThan: " << endl << setw(35) << "\t";
    // Calling onto the respective sort function for this test, with pointer to "isGreaterThan" function passed.
    sortWithFunctionPointers(&myArray2[0], arraySize, isGreaterThan);
    // Printing out the result of the sorted array.
    for (int i = 0; i < arraySize; ++i) {
        cout << myArray2[i] << " ";
    }
    cout << endl << endl;
}
/**
 * Test function that demonstrates the features of sorting using inheritance from an interface.
 */
void testSortWithInterfaces() {
    cout << "Testing sort with interfaces" << endl << endl;
    cout << "LessThanComparer: " << endl;
    unsigned long arraySize = 10;
    vector<int> myArray1(arraySize);
    // Printing out the unsorted array.
    cout << "Unsorted array: " << setw(20) << "\t";
    for (int i = 0; i < arraySize; i++) {
        myArray1[i] = rand() % arraySize + 1;
        cout << myArray1[i] << " ";
    }
    cout << endl;
    cout << "Sorted array: " << setw(20) << "\t";
    // Calling to the respective sort function of this test with a new instance of the "LessThanComparer" as
    // The interface that we pass for sorting.
    sortWithInterfaces(&myArray1[0], arraySize, new LessThanComparer());
    // Printing out the sorted array as a result of our sort function call.
    for (int j = 0; j < arraySize; ++j) {
        cout << myArray1[j] << " ";
    }
    cout << endl << endl << "GreaterThanComparer: " << endl;
    vector<int> myArray2(arraySize);
    // Printing the unsorted array.
    cout << "Unsorted array: " << setw(20) << "\t";
    for (int i = 0; i < arraySize; i++) {
        myArray2[i] = rand() % arraySize + 1;
        cout << myArray2[i] << " ";
    }
    cout << endl;
    cout << "Sorted array: " << setw(20) << "\t";
    // Calling to the respective sort function of this test with a new instance of the "GreaterThanComparer" as
    // The interface that we pass for sorting.
    sortWithInterfaces(&myArray2[0], arraySize, new GreaterThanComparer());
    // Printing the sorted array as a result of our sort function call.
    for (int j = 0; j < arraySize; ++j) {
        cout << myArray2[j] << " ";
    }
    cout << endl << endl << "IsClosestToComparer with center 3: " << endl;
    vector<int> myArray3(arraySize);
    // Printing the unsorted array.
    cout << "Unsorted array:" << setw(20) << "\t";
    for (int i = 0; i < arraySize; i++) {
        myArray3[i] = rand() % arraySize + 1;
        cout << myArray3[i] << " ";
    }
    cout << endl;
    cout << "Sorted array:" << setw(20) << "\t";
    // Calling to the respective sort function of this test with a new instance of the "IsClosestToComparer" as
    // The interface that we pass for sorting, with a center value of 3.
    sortWithInterfaces(&myArray3[0], arraySize, new IsClosestToComparer(3));
    // Printing the sorted array as a result of our sort function call.
    for (int j = 0; j < arraySize; ++j) {
        cout << myArray3[j] << " ";
    }
    cout << endl << endl;
}
/**
 * Test function that demonstrates the features of sorting with lambda expressions
 */
void testSortWithLambdas() {
    cout << "Testing sort with Lambda Expressions" << endl << endl;
    unsigned long arraySize = 10;
    // Two arrays for testing two different lambda expressions, very similar to each other however.
    vector<int> myArray1(arraySize);
    vector<int> myArray2(arraySize);
    // Printing out the unsorted array.
    cout << "Unsorted array: " << setw(20) << "\t";
    for (int i = 0; i < arraySize; i++) {
        myArray2[i] = myArray1[i] = rand() % arraySize + 1;
        cout << myArray1[i] << " ";
    }
    cout << endl << "Sorted array: " << endl;
    cout << "Center value 3: " << endl << setw(35) << "\t";
    // Calling the respective sort function for this demonstration, passing 3 as center value to the
    // Lambda expression that we have generated in the function "generateNearestTo(center)".
    sortWithStandardFunction(&myArray1[0], arraySize, generateNearestTo(3));
    // Printing out the result of
    for (int i = 0; i < arraySize; ++i) {
        cout << myArray1[i] << " ";
    }
    cout << endl << "Center value 10: " << endl << setw(35) << "\t";
    // Calling the respective sort function for this demonstration, passing 10 as center value to the
    // Lambda expression that we have generated in the function "generateNearestTo(center)".
    sortWithStandardFunction(&myArray2[0], arraySize, generateNearestTo(10));
    for (int i = 0; i < arraySize; ++i) {
        cout << myArray2[i] << " ";
    }
    cout << endl;
}

/**
 * Function that checks if the first number is smaller than the second number or not
 * @param a The first number
 * @param b The second number
 * @return <strong>True</strong> if a &lt b, <strong>false</strong> otherwise.
 */
bool isLessThan(int a, int b) {
    return a < b;
}

/**
 * Function that checks if the first number is greater than the second number or not
 * @param a The first number
 * @param b The second number
 * @return <strong>True</strong> if a &gt b, <strong>False</strong> otherwise.
 */
bool isGreaterThan(int a, int b) {
    return a > b;
}
/**
 * Bubble sort with function pointers.
 * @param p Pointer to the first element of the array
 * @param length Length of the array
 * @param compare Function to call on two elements for comparison
 */
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
/**
 * Bubble sort with interfaces
 * @param p Pointer to the first element of the array
 * @param length Length of the array
 * @param compare Pointer to the interface class that contains the compare method we use on two elements of the array
 */
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
/**
 * Lambda expression generator
 * @param center The center value to check the other values against
 * @return A lambda expression that takes in two numbers and checks if the first number is closer to the center than
 * the second
 */
function<bool(int, int)> generateNearestTo(int center) {
    auto compare = [center](int a, int b) {
        return abs(a - center) < abs(b - center);
    };
    return compare;
}
/**
 * Bubble sort with lambda expressions
 * @param p Pointer to the first element of the array
 * @param length The length of the array
 * @param compare The lambda expression expected in order to perform a comparison on two values of the array with.
 */
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





