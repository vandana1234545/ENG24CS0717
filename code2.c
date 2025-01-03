#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student information
struct Student {
    int id;
    char name[50];
    int age;
    float grade;
};

// Function prototypes
void addStudent();
void listStudents();
void searchStudent();
void deleteStudent();

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. List Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            listStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            printf("Exiting program...\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add a student
void addStudent() {
    FILE *file = fopen("students.dat", "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    struct Student student;
    printf("Enter Student ID: ");
    scanf("%d", &student.id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", student.name);  // Allows spaces in the name
    printf("Enter Age: ");
    scanf("%d", &student.age);
    printf("Enter Grade: ");
    scanf("%f", &student.grade);

    fwrite(&student, sizeof(struct Student), 1, file);
    printf("Student added successfully!\n");

    fclose(file);
}

// Function to list all students
void listStudents() {
    FILE *file = fopen("students.dat", "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    struct Student student;
    printf("\n--- List of Students ---\n");
    while (fread(&student, sizeof(struct Student), 1, file)) {
        printf("ID: %d, Name: %s, Age: %d, Grade: %.2f\n",
               student.id, student.name, student.age, student.grade);
    }

    fclose(file);
}

// Function to search for a student by ID
void searchStudent() {
    FILE *file = fopen("students.dat", "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    int id;
    struct Student student;
    int found = 0;

    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    while (fread(&student, sizeof(struct Student), 1, file)) {
        if (student.id == id) {
            printf("Student found!\n");
            printf("ID: %d, Name: %s, Age: %d, Grade: %.2f\n",
                   student.id, student.name, student.age, student.grade);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student")}}