#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_SUBJECTS 5
#define MAX_STUDENTS 100

typedef struct {
    char name[MAX_NAME];
    int marks[MAX_SUBJECTS];
    float gpa;
} Student;

void loadStudents(Student students[], int *count);
void calculateGPA(Student students[], int count);
void saveReport(Student students[], int count);
void displayStudents(Student students[], int count);

int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    while (1) {
        printf("\n=== Student Grading System ===\n");
        printf("1. Load Students from CSV\n");
        printf("2. Calculate GPA\n");
        printf("3. Display Students\n");
        printf("4. Generate Report CSV\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                loadStudents(students, &studentCount);
                break;
            case 2:
                calculateGPA(students, studentCount);
                printf("GPA calculated successfully.\n");
                break;
            case 3:
                displayStudents(students, studentCount);
                break;
            case 4:
                saveReport(students, studentCount);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void loadStudents(Student students[], int *count) {
    FILE *fp = fopen("students.csv", "r");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    *count = 0;

    while (fgets(line, sizeof(line), fp)) {
        char *token = strtok(line, ",");
        if (token == NULL) continue;

        strcpy(students[*count].name, token);

        for (int i = 0; i < MAX_SUBJECTS; i++) {
            token = strtok(NULL, ",");
            if (token != NULL)
                students[*count].marks[i] = atoi(token);
            else
                students[*count].marks[i] = 0;
        }
        students[*count].gpa = 0.0;
        (*count)++;
    }

    fclose(fp);
    printf("%d students loaded from CSV.\n", *count);
}

void calculateGPA(Student students[], int count) {
    for (int i = 0; i < count; i++) {
        int total = 0;
        for (int j = 0; j < MAX_SUBJECTS; j++) {
            total += students[i].marks[j];
        }
        students[i].gpa = total / (float)MAX_SUBJECTS / 20.0; // GPA out of 5
    }
}

void displayStudents(Student students[], int count) {
    printf("\nName\t\tMarks\t\tGPA\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-15s", students[i].name);
        for (int j = 0; j < MAX_SUBJECTS; j++)
            printf("%d ", students[i].marks[j]);
        printf("\t%.2f\n", students[i].gpa);
    }
}

void saveReport(Student students[], int count) {
    FILE *fp = fopen("report.csv", "w");
    if (!fp) {
        printf("Error creating report file!\n");
        return;
    }

    // Header
    fprintf(fp, "Name,Subject1,Subject2,Subject3,Subject4,Subject5,GPA\n");

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s", students[i].name);
        for (int j = 0; j < MAX_SUBJECTS; j++)
            fprintf(fp, ",%d", students[i].marks[j]);
        fprintf(fp, ",%.2f\n", students[i].gpa);
    }

    fclose(fp);
    printf("Report saved as report.csv\n");
}

