#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Math.h>


struct Student {
    char* studentID;
    int totalCredits;
    int GPA;
    char* name;
    char* surname;
    char* city;
    char* department;
};
struct Hacker {
    Student* studentDetails;
    int* courseNumbers;
    char** Friends;
    char** Rivals;
};


struct EnrollmentSystem {
    File* students;
    File* courses;
    File* hackers;
};


/* Thee friendship functions as mentioned in the assignment.
 * FriendshipFunction1: Gets a Student in the Queue and the Hacker's details.
 *                      Checks if the student is in the hacker's friends/rivals list.
 * FriendshipFunction2: returns the absolute value of the difference of their names in
 *                      ASCII code.
 * FriendshipFunction3: returns the absolute value of the difference in their ID numbers.
 * */
int FriendshipFunction1(Hacker hacker, Student student) {
    char* studentID = student -> studentID;
    char** temp = hacker.Friends;
    while (temp != NULL) {
        if (strcmp(*temp, studentID) == 0)
            return 20;
        temp++;
    }

    char** temp = hacker.Rivals;
    while (temp != NULL) {
        if (strcmp(*temp, studentID) == 0)
            return -20;
        temp++;
    }

    return 0;
}

int FriendshipFunction2(Hacker hacker, Student student) {
    char* Name1F = hacker->studentDetails->name;
    char* Name2F = student->name;
    char* Name1L = hacker->studentDetails->surname;
    char* Name2L = student->surname;
    int sum = 0

        while (Name1F != NULL || Name2F != NULL) {
            if (Name1F != NULL && Name2F != NULL) {
                sum += abs(*Name1F - Name2F);
            }
            else if (Name1F != NULL) {
                if (*Name1F >= 'A') {
                    *Name1F = *Name1F - 'A' + 'a';
                }
                sum += abs(*Name1F - '0');
            }
            else {
                if (*Name2F >= 'A') {
                    *Name2F = *Name2F - 'A' + 'a';
                }
                sum += abs(*Name2F - '0');
            }
            Name1F++;
            Name2F++;
        }

    while (Name1L != NULL || Name2L != NULL) {
        if (Name1L != NULL && Name2L != NULL) {
            sum += abs(*Name1L - Name2L);
        }
        else if (Name1L != NULL) {
            if (*Name1L >= 'A') {
                *Name1L = *Name1L - 'A' + 'a';
            }
            sum += abs(*Name1L - '0');
        }
        else {
            if (*Name2L >= 'A') {
                *Name2L = *Name2L - 'A' + 'a';
            }
            sum += abs(*Name2L - '0');
        }

        Name1L++;
        Name2L++;
    }

    return sum;
}

int FriendshipFunction3(Hacker hacker, Student student){
    int n1 = atoi(hacker -> studentDetails -> studentID);
    int n2 = atoi(student -> studentID);

    return abs(n1 - n2);
}

/*
 * This function recieves a Student and a Hacker, checks if they are rivals
 * or friends through the friendship functions above. and returns:
 * 1- if friends.
 * 2- if rivals.
 * 0- if neutral.
 */
int FriendshipMeasure(Hacker hacker, Student student);








EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers);