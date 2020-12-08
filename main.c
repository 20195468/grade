#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[20];
    double chinese;
    double math;
    double english;
    struct Student *next;
} Student;

//???????????????
Student *iniList();

//???????????
void insertStudent(Student *students, char name[20], int chinese, int math, int english);

//??????????
Student *creatStudent(char name[20], int chinese, int math, int english);

//?????????
void print(Student *student);

//?????????
double *getAverage(Student *student);

//?????????
void MaxOrMin(Student *student, int choose);

int main() {
    Student *students = iniList();
    insertStudent(students, "??", 90, 98, 70);
    insertStudent(students, "????", 100, 95, 88);
    insertStudent(students, "?????", 60, 100, 60);
    print(students);
    double *average = getAverage(students);
    printf("?????????????%.2f\n", average[0]);
    printf("????????????%.2f\n", average[1]);
    printf("????????????%.2f\n", average[2]);
    MaxOrMin(students, 1);//???????????
    MaxOrMin(students, 0);//????????§³???
}

//?????????
Student *iniList() {
    Student *students = (Student *) malloc(sizeof(Student));
    if (students == NULL) exit(1);
    students->next = NULL;
    return students;
}

//??????????
Student *creatStudent(char name[20], int chinese, int math, int english) {
    Student *student = (Student *) malloc(sizeof(Student));
    if (student == NULL) {
        printf("??????????");
        exit(1);
    }
    strcpy(student->name, name);
    student->chinese = chinese;
    student->english = english;
    student->math = math;
    return student;
}

//?????????????¾Þ
void insertStudent(Student *students, char name[20], int chinese, int math, int english) {
    if (students == NULL) {
        printf("????????\n");
        exit(1);
    }
    Student *temp = creatStudent(name, chinese, math, english);
    temp->next = students->next;
    students->next = temp;
}

//?????????
void print(Student *student) {
    if (student == NULL) {
        printf("????¦Ê???????\n");
        exit(1);
    }
    Student *temp = student->next;
    while (temp != NULL) {
        printf("?????????%.2f ?????????%.2f  ????????%.2f\n", temp->chinese, temp->math, temp->english);
        temp = temp->next;
    }
}

//?????????
double *getAverage(Student *student) {
    if (student == NULL) {
        printf("????¦Ê???????\n");
        exit(1);
    }
    static double average[3] = {0, 0, 0};
    Student *temp = student->next;
    int num = 0;
    while (temp != NULL) {
        average[0] = average[0] + temp->chinese;
        average[1] = average[1] + temp->math;
        average[2] = average[2] + temp->english;
        num++;
        temp = temp->next;
    }
    for (int i = 0; i < 3; ++i) {
        average[i] = average[i] / num;
    }
    return average;
}

//??????
void MaxOrMin(Student *student, int choose) {
    if (student == NULL) {
        printf("????¦Ê???????\n");
        exit(1);
    }

    static double average[3];
    if (choose == 1) {
        for (int i = 0; i < 3; ++i) {
            average[i] = 0;
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            average[i] = 101;
        }
    }

    char name[3][20];

    Student *temp = student->next;
    while (temp != NULL) {
        if (choose == 1) {
            if (average[0] < temp->chinese) {
                average[0] = temp->chinese;
                strcpy(name[0], temp->name);
            }
            if (average[1] < temp->math) {
                average[1] = temp->math;
                strcpy(name[1], temp->name);
            }
            if (average[2] < temp->english) {
                average[2] = temp->english;
                strcpy(name[2], temp->name);
            }
        } else {
            if (average[0] > temp->chinese) {
                average[0] = temp->chinese;
                strcpy(name[0], temp->name);
            }
            if (average[1] > temp->math) {
                average[1] = temp->math;
                strcpy(name[1], temp->name);
            }
            if (average[2] > temp->english) {
                average[2] = temp->english;
                strcpy(name[2], temp->name);
            }
        }
        temp = temp->next;
    }
    if (choose == 1) {
        printf("????????????%.2f??????????%s\n", average[0], name[0]);
        printf("???????????%.2f??????????%s\n", average[1], name[1]);
        printf("???????????%.2f??????????%s\n", average[2], name[2]);
    } else {
        printf("????????????%.2f??????????%s\n", average[0], name[0]);
        printf("???????????%.2f??????????%s\n", average[1], name[1]);
        printf("???????????%.2f??????????%s\n", average[2], name[2]);
    }
}