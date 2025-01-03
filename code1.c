#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50
#define NAME_LENGTH 50

// Structure to store student information
typedef struct {
    int id;
    char name[NAME_LENGTH];
    float marks;
} Student;

// Function prototypes
void addStudent(Student students[], int *count);
void displayStudents(Student students[], int count);
void searchStudent(Student students[], int count, int id);
void saveToFile(Student students[], int count);
void loadFromFile(Student students[], int *count);

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice, id;

    loadFromFile(students, &count);

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                printf("Enter Student ID to search: ");
                scanf("%d", &id);
                searchStudent(students, count, id);
                break;
            case 4:
                saveToFile(students, count);
                printf("Data saved successfully. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Error: Cannot add more students. Database is full.\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &students[*count].id);
    printf("Enter Student Name: ");
    getchar(); // To clear the newline character from input buffer
    fgets(students[*count].name, NAME_LENGTH, stdin);
    students[*count].name[strcspn(students[*count].name, "\n")] = '\0'; // Remove newline
    printf("Enter Marks: ");
    scanf("%f", &students[*count].marks);

    (*count)++;
    printf("Student added successfully.\n");
}

void displayStudents(Student students[], int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nList of Students:\n");
    printf("ID\tName\t\tMarks\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t\t%.2f\n", students[i].id, students[i].name, students[i].marks);
    }
}

void searchStudent(Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Student Found:\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Marks: %.2f\n", students[i].marks);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

void saveToFile(Student students[], int count) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%.2f\n", students[i].id, students[i].name, students[i].marks);
    }

    fclose(file);
}

void loadFromFile(Student students[], int *count) {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%d,%49[^,],%f\n", &students[*count].id, students[*count].name, &students[*count].marks) != EOF) {
        (*count)++;
    }

    fclose(file);
    printf("Data loaded successfully. %d students found.\n", *count);
}