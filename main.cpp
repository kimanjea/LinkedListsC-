//
// Test Program for templated version of Lab 1 - MultiMerge
// Author: Max Benson
// Date: 08/08/2021
//

#include <iostream>
#include <sstream>
#include <chrono>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::to_string;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

#include <assert.h>
#include <string.h>

#include "VariableArrayList.h"
#include "Merge.h"

enum OmitColumn {
    OMIT_NUMBER_OF_ELEMENTS,
    OMIT_NUMBER_OF_LISTS
};

void TestTwoWayMergeCorrectness();
void TestMultiMergeCorrectness(bool fRecursive);
void TestTwoWayMergePerformance();
void TestMultiMergePerformanceWithFixedNumberOfLists(size_t numberLists);
void TestMultiMergePerformanceWithFixedNumberOfElements(size_t numberElements);
void TestOneMultiMergeCase(size_t numberLists, size_t numberElements, OmitColumn omit);
void CreateListOfList(size_t numberLists, size_t averageNumberPerList, VariableArrayList<VariableArrayList<int>>& listOfLists, string& desiredResult);

int main(int argc, char* argv[]) {
    bool fPerf;

    if (argc > 1) {
        if (2 == argc && strcmp(argv[1], "-perf") == 0) {
            fPerf = true;
        }
        else {
            cout << "Usage: MultiMerge [-perf]" << endl;
            exit(1);
        }
    }
    else {
        fPerf = false;
    }

    // Correctness
    if (!fPerf) {
        cout << "Begin Correctness Testing" << endl;
        TestTwoWayMergeCorrectness();
        TestMultiMergeCorrectness(false);
        TestMultiMergeCorrectness(true);
        cout << "Correctness Testing Complete" << endl;
    }
    else {
        cout << "Begin Performance Testing" << endl;
        TestTwoWayMergePerformance();
        TestMultiMergePerformanceWithFixedNumberOfLists(512);
        TestMultiMergePerformanceWithFixedNumberOfElements(8192);
        cout << "Performance Testing Complete" << endl;
    }
    return 0;
}

void TestTwoWayMergeCorrectness() {
    VariableArrayList<int> listOfInt0;
    VariableArrayList<int> listOfInt1;
    VariableArrayList<int> listOfIntMerge;
    stringstream sstr;

    // Empty lists
    listOfInt0.Clear();
    listOfInt1.Clear();
    Merge(listOfInt0, listOfInt1, listOfIntMerge);
    sstr << listOfIntMerge;
    assert(sstr.str() == "[]");
    sstr.str("");

    // One of lists empty
    listOfInt0.Clear();
    listOfInt1.Clear();
    listOfInt0.Insert(0, 1);
    Merge(listOfInt0, listOfInt1, listOfIntMerge);
    sstr << listOfIntMerge;
    std::cout << listOfIntMerge << endl;
    assert(sstr.str() == "[1]");
    sstr.str("");

    // Simple test of Merge
    listOfInt0.Clear();
    listOfInt1.Clear();
    listOfInt0.Insert(0, 1);
    listOfInt0.Insert(1, 2);
    listOfInt0.Insert(2, 3);
    listOfInt0.Insert(3, 4);
    listOfInt0.Insert(4, 5);

    listOfInt1.Insert(0, 0);
    listOfInt1.Insert(1, 1);
    listOfInt1.Insert(2, 1);
    listOfInt1.Insert(3,2);
    listOfInt1.Insert(4,2);
    listOfInt1.Insert(5,5);
    listOfInt1.Insert(6,6);

    Merge(listOfInt0, listOfInt1, listOfIntMerge);
    sstr << listOfIntMerge;
    assert(sstr.str() == "[0, 1, 1, 1, 2, 2, 2, 3, 4, 5, 5, 6]");
    sstr.str("");

    // Random tests of merge
    srand(0);
    for (size_t itest = 0; itest < 50; itest ++) {
        string desiredResult;
        VariableArrayList<VariableArrayList<int>> listOfLists;

        CreateListOfList(2, 100, listOfLists, desiredResult);
        listOfLists.Get(0, listOfInt0);
        listOfLists.Get(1, listOfInt1);

        // Now merge them
        Merge(listOfInt0, listOfInt1, listOfIntMerge);

        // Verify merge
        sstr << listOfIntMerge;
        assert(sstr.str() == desiredResult);
        sstr.str("");
    }
    cout << "...Merge Test Correctness Succeeds" << endl;
}

void TestMultiMergeCorrectness(bool fRecursive) {
    const size_t NUMBER_LISTS = 16;
    const size_t AVERAGE_NUMBER_ELEMENTS_PER_LIST = 50;

    VariableArrayList<int> listOfInt0;
    VariableArrayList<int> listOfInt1;
    VariableArrayList<int> listOfInt2;
    VariableArrayList<int> listOfInt3;
    VariableArrayList<int> listOfInt4;
    VariableArrayList<VariableArrayList<int>> listOfLists;
    VariableArrayList<int> multiMerge;
    stringstream sstr;

    // Test no lists
    if (fRecursive) {
        RecursiveMultiMerge(listOfLists, 0, listOfLists.Size(), multiMerge);
    }
    else {
        IterativeMultiMerge(listOfLists, multiMerge);
    }
    // Verify merge
    sstr << multiMerge;
    assert(sstr.str() == "[]");
    sstr.str("");

    // Test one list
    listOfInt0.Insert(0, 1);
    listOfInt0.Insert(1, 2);
    listOfInt0.Insert(2, 3);
    listOfInt0.Insert(3, 4);
    listOfInt0.Insert(4, 5);
    listOfLists.Insert(0, listOfInt0);

    if (fRecursive) {
        RecursiveMultiMerge(listOfLists, 0, listOfLists.Size(), multiMerge);
    }
    else {
        IterativeMultiMerge(listOfLists, multiMerge);
    }

    // Verify merge
    sstr << multiMerge;
    assert(sstr.str() == "[1, 2, 3, 4, 5]");
    sstr.str("");

    // Test two lists
    listOfInt1.Insert(0, 0);
    listOfInt1.Insert(1, 1);
    listOfInt1.Insert(2, 1);
    listOfInt1.Insert(3, 2);
    listOfInt1.Insert(4, 2);
    listOfInt1.Insert(5,5);
    listOfInt1.Insert(6, 6);
    listOfLists.Insert(1, listOfInt1);

    if (fRecursive) {
        RecursiveMultiMerge(listOfLists, 0, listOfLists.Size(), multiMerge);
    }
    else {
        IterativeMultiMerge(listOfLists, multiMerge);
    }

    // Verify merge
    sstr << multiMerge;
    assert(sstr.str() == "[0, 1, 1, 1, 2, 2, 2, 3, 4, 5, 5, 6]");
    sstr.str("");

    // Test three lists
    listOfInt2.Insert(0, 1);
    listOfInt2.Insert(1, 3);
    listOfInt2.Insert(2, 4);
    listOfInt2.Insert(3, 6);
    listOfInt2.Insert(4, 7);
    listOfLists.Insert(2, listOfInt2);

    if (fRecursive) {
        RecursiveMultiMerge(listOfLists, 0, listOfLists.Size(), multiMerge);
    }
    else {
        IterativeMultiMerge(listOfLists, multiMerge);
    }

    // Verify merge
    sstr << multiMerge;
    assert(sstr.str() == "[0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7]");
    sstr.str("");

    // Test four lists
    listOfInt3.Insert(0, 0);
    listOfInt3.Insert(1, 1);
    listOfInt3.Insert(2, 2);
    listOfInt3.Insert(3, 3);
    listOfInt3.Insert(4, 8);
    listOfLists.Insert(3, listOfInt3);

    if (fRecursive) {
        RecursiveMultiMerge(listOfLists, 0, listOfLists.Size(), multiMerge);
    }
    else {
        IterativeMultiMerge(listOfLists, multiMerge);
    }

    // Verify merge
    sstr << multiMerge;
    assert(sstr.str() == "[0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8]");
    sstr.str("");

    // Test five lists
    listOfInt4.Insert(0, 1);
    listOfInt4.Insert(1,2);
    listOfInt4.Insert(2,3);
    listOfInt4.Insert(3,3);
    listOfInt4.Insert(4,5);

    listOfLists.Insert(4, listOfInt4);

    if (fRecursive) {
        RecursiveMultiMerge(listOfLists, 0, listOfLists.Size(), multiMerge);
    }
    else {
        IterativeMultiMerge(listOfLists, multiMerge);
    }

    // Verify merge
    sstr << multiMerge;
    assert(sstr.str() == "[0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5, 5, 5, 6, 6, 7, 8]");
    sstr.str("");

    // Random tests of merge
    srand(0);
    for (size_t itest = 0; itest < 50; itest ++) {
        // Determine number of lists this test
        size_t numberLists = rand() % NUMBER_LISTS + 1;

        // Create the lists
        string desiredResult;
        VariableArrayList<VariableArrayList<int>> listOfLists;

        CreateListOfList(numberLists, AVERAGE_NUMBER_ELEMENTS_PER_LIST, listOfLists, desiredResult);

        // Do the multi merge
        if (fRecursive) {
            RecursiveMultiMerge(listOfLists, 0, listOfLists.Size(), multiMerge);
        }
        else {
            IterativeMultiMerge(listOfLists, multiMerge);
        }

        // Verify merge
        sstr << multiMerge;
        assert(sstr.str() == desiredResult);
        sstr.str("");
    }

    if (fRecursive) {
        cout << "...Recursive Merge Test Correctness Succeeds" << endl;
    }
    else {
        cout << "...Iterative Merge Test Correctness Succeeds" << endl;
    }
}

void TestTwoWayMergePerformance() {
    const size_t NUMBER_TESTS = 1000;

    cout << "Two Way Merge Performance" << endl;
    cout << "Elements\tTime" << endl;
    for (size_t numberElements = 100; numberElements < 5000; numberElements += 100) {
        long long totalTime = 0;
        for (size_t test = 0; test < NUMBER_TESTS; test ++) {
            string desiredResult;
            VariableArrayList<VariableArrayList<int>> listOfLists;
            VariableArrayList<int> listOfInt0;
            VariableArrayList<int> listOfInt1;
            VariableArrayList<int> listOfIntMerge;

            CreateListOfList(2, numberElements/2, listOfLists, desiredResult);
            listOfLists.Get(0, listOfInt0);
            listOfLists.Get(1, listOfInt1);

            steady_clock::time_point begin = steady_clock::now();
            Merge(listOfInt0, listOfInt1, listOfIntMerge);
            steady_clock::time_point end = steady_clock::now();

            totalTime += duration_cast<nanoseconds>(end-begin).count();
        }
        cout << numberElements << "\t" << totalTime/NUMBER_TESTS << endl;
    }
}

void TestMultiMergePerformanceWithFixedNumberOfLists(size_t numberLists) {
    cout << "MultiMerge Performance With " << numberLists << " Lists" << endl;
    cout << "Elements\tIterative\tRecursive" << endl;
    for (size_t numberElements = numberLists; numberElements < 8192; numberElements += numberLists) {
        TestOneMultiMergeCase(numberLists, numberElements, OMIT_NUMBER_OF_LISTS);
    }
}

void TestMultiMergePerformanceWithFixedNumberOfElements(size_t numberElements) {
    cout << "MultiMerge Performance With " << numberElements << " Elements" << endl;
    cout << "Lists\tIterative\tRecursive" << endl;
    for (size_t numberLists = 1; numberLists < 4096; numberLists *= 2) {
        TestOneMultiMergeCase(numberLists, numberElements, OMIT_NUMBER_OF_ELEMENTS);
    }
}

void TestOneMultiMergeCase(size_t numberLists, size_t numberElements, OmitColumn omit) {
    const size_t NUMBER_TESTS = 100;

    VariableArrayList<VariableArrayList<int>> listOfLists;
    long long totalTimeIterative = 0;
    long long totalTimeRecursive = 0;
    for (size_t test = 0; test < NUMBER_TESTS; test++) {
        string desiredResult;
        VariableArrayList<int> mergedList;
        steady_clock::time_point begin;
        steady_clock::time_point end;

        CreateListOfList(numberLists, numberElements/numberLists, listOfLists, desiredResult);

        // Time Iterative Multimerge
        mergedList.Clear();
        begin = steady_clock::now();
        IterativeMultiMerge(listOfLists, mergedList);
        end = steady_clock::now();
        totalTimeIterative += duration_cast<nanoseconds>(end - begin).count();

        // Time Recursive Multimerge
        mergedList.Clear();
        begin = steady_clock::now();
        RecursiveMultiMerge(listOfLists,0, numberLists, mergedList);
        end = steady_clock::now();
        totalTimeRecursive += duration_cast<nanoseconds>(end - begin).count();
    }
    if (OMIT_NUMBER_OF_LISTS == omit) {
        cout << numberElements << "\t " << totalTimeIterative / NUMBER_TESTS << "\t "
             << totalTimeRecursive / NUMBER_TESTS << endl;
    }
    else {
        cout << numberLists << "\t " << totalTimeIterative / NUMBER_TESTS << "\t "
             << totalTimeRecursive / NUMBER_TESTS << endl;
    }
}

void CreateListOfList(size_t numberLists, size_t averageNumberPerList, VariableArrayList<VariableArrayList<int>>& listOfLists, string& desiredResult) {
    size_t numberElements = numberLists*averageNumberPerList;
    int* arrAll;
    int* arrList;
    size_t* numberInList;

    // Allocate array to store elements for staging
    arrAll = new int[numberElements];
    arrList = new int[numberLists*numberElements];
    numberInList = new size_t[numberLists];

    // Fill sorted array and format result string
    desiredResult ="[";
    arrAll[0] = rand() % 4;
    desiredResult.append(to_string(arrAll[0]));
    for (size_t i = 1; i < numberElements; i ++) {
        arrAll[i] = arrAll[i-1] + rand() % 3;
        desiredResult.append(", ");
        desiredResult.append(to_string(arrAll[i]));
    }
    desiredResult.append("]");

    // Zero out counts in each list
    for (size_t i = 0; i < numberLists; i ++) {
        numberInList[i] = 0;
    }

    // Now distribute numbers into 2d array
    for (size_t i = 0; i < numberElements; i ++) {
        size_t listIndex = rand() % numberLists;

        arrList[listIndex*numberElements+numberInList[listIndex]] = arrAll[i];
        numberInList[listIndex] ++;
    }

    // Now put them into their lists
    listOfLists.Clear();
    for (size_t i = 0; i < numberLists; i ++) {
        VariableArrayList<int> list;

        for (size_t j = 0; j < numberInList[i]; j++) {
            list.Insert(list.Size(), arrList[i*numberElements+j] );
        }
        listOfLists.Insert(i, list);
    }

    delete[] arrAll;
    delete[] arrList;
    delete[] numberInList;
}

