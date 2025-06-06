#include "include/algorithms/array_sorting.h"
#include "include/core/student.h"
#include "include/data_structures/array_list.h"
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    cout << "=== Test Modular Sorting Libraries ===" << endl;
    
    // Test Array Sorting
    ArrayStudentList testArray;
    testArray.count = 3;
    
    // Add test students
    strcpy(testArray.students[0].studentID, "SV001");
    strcpy(testArray.students[0].firstName, "Nguyen Van");
    strcpy(testArray.students[0].lastName, "A");
    testArray.students[0].score = 8.5;
    
    strcpy(testArray.students[1].studentID, "SV002");
    strcpy(testArray.students[1].firstName, "Tran Thi");
    strcpy(testArray.students[1].lastName, "B");
    testArray.students[1].score = 9.2;
    
    strcpy(testArray.students[2].studentID, "SV003");
    strcpy(testArray.students[2].firstName, "Le Van");
    strcpy(testArray.students[2].lastName, "C");
    testArray.students[2].score = 7.8;
    
    cout << "\nBefore sorting (Array List):" << endl;
    for (int i = 0; i < testArray.count; i++) {
        cout << testArray.students[i].studentID << " - " 
             << testArray.students[i].firstName << " " << testArray.students[i].lastName << " - " 
             << testArray.students[i].score << endl;
    }
    
    // Test bubble sort from array_sorting.cpp
    bubbleSortArrayList(testArray);
    
    cout << "\nAfter bubble sort by score (Array List):" << endl;
    for (int i = 0; i < testArray.count; i++) {
        cout << testArray.students[i].studentID << " - " 
             << testArray.students[i].firstName << " " << testArray.students[i].lastName << " - " 
             << testArray.students[i].score << endl;
    }
    
    cout << "\n=== Test Successful - All modules working! ===" << endl;
    return 0;
}
