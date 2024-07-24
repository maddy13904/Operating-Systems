#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.dat"
#define NAME_LENGTH 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float salary;
} Employee;

void addEmployee() {
    Employee emp;
    FILE *file = fopen(FILENAME, "ab");
    
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf("%s", emp.name);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(Employee), 1, file);
    fclose(file);

    printf("Employee added successfully.\n");
}

void viewEmployee(int id) {
    Employee emp;
    FILE *file = fopen(FILENAME, "rb");
    
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            printf("Employee ID: %d\n", emp.id);
            printf("Employee Name: %s\n", emp.name);
            printf("Employee Salary: %.2f\n", emp.salary);
            fclose(file);
            return;
        }
    }

    printf("Employee with ID %d not found.\n", id);
    fclose(file);
}

void updateEmployee(int id) {
    Employee emp;
    FILE *file = fopen(FILENAME, "rb+");
    
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            printf("Enter new Employee Name: ");
            scanf("%s", emp.name);
            printf("Enter new Employee Salary: ");
            scanf("%f", &emp.salary);

            fseek(file, -sizeof(Employee), SEEK_CUR);
            fwrite(&emp, sizeof(Employee), 1, file);
            fclose(file);

            printf("Employee updated successfully.\n");
            return;
        }
    }

    printf("Employee with ID %d not found.\n", id);
    fclose(file);
}

void deleteEmployee(int id) {
    Employee emp;
    FILE *file = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    
    if (file == NULL || temp == NULL) {
        perror("Error opening file");
        return;
    }

    int found = 0;

    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            found = 1;
        } else {
            fwrite(&emp, sizeof(Employee), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found) {
        printf("Employee with ID %d deleted successfully.\n", id);
    } else {
        printf("Employee with ID %d not found.\n", id);
    }
}

int main() {
    int choice, id;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Employee\n");
        printf("2. View Employee\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                printf("Enter Employee ID to view: ");
                scanf("%d", &id);
                viewEmployee(id);
                break;
            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &id);
                updateEmployee(id);
                break;
            case 4:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &id);
                deleteEmployee(id);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

