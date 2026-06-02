#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HackEnrollment.h"

int FriendshipMeasure(Hacker hacker, Student student){

    int functionResult = FriendshipFunction1(hacker,student);

    if (functionResult == 20) //friends according to functoin 1
        return 1;

    int sum = functionResult;
    functionResult = FriendshipFunction2(hacker,student);

    if(functionResult >= 20) //friends according functoin 2
        return 1;
    sum *= functionResult;

    functionResult = FriendshipFunction3(hacker,student);
    if(functionResult >= 20) //friends according function 3
        return 1;

    sum *= functionResult;

    if (pow(functionResult,1/3) <= 0)
        return 2;

    return 0;


}


EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers){
    EnrollmentSystem enrollmentSystem;
    enrollmentSystem . students = students;
    enrollmentSystem . courses = courses;
    enrollmentSystem . hackers = hackers;

    return enrollmentSystem;
}