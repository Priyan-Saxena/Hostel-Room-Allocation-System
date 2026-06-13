#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#define MAX_ROOMS 50
#define MAX_NAME_LENGTH 100
#define MAX_CONTACT_LENGTH 15
#define MAX_BRANCH_LENGTH 50
#define DATA_FILE "hostel_data.txt"

typedef struct {
    char name[MAX_NAME_LENGTH];
    char rollNumber[20];
    char contact[MAX_CONTACT_LENGTH];
    char branch[MAX_BRANCH_LENGTH];
    int roomNumber;
    int isAllocated;
    int isActive;
} Student;

typedef struct {
    int roomNumber;
    int isOccupied;
    char occupantRollNumber[20];
} Room;

Student students[MAX_ROOMS];
Room rooms[MAX_ROOMS];
int studentCount = 0;

void initializeSystem() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isOccupied = 0;
        strcpy(rooms[i].occupantRollNumber, "");
        students[i].isActive = 0;
        students[i].isAllocated = 0;
        students[i].roomNumber = -1;
        strcpy(students[i].rollNumber, "");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void trim(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

int isValidContact(const char *contact) {
    if (strlen(contact) < 10) return 0;
    for (int i = 0; contact[i] != '\0'; i++) {
        if (!isdigit(contact[i])) return 0;
    }
    return 1;
}

int findStudentByRollNumber(const char *rollNumber) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (students[i].isActive && strcmp(students[i].rollNumber, rollNumber) == 0) {
            return i;
        }
    }
    return -1;
}

int findInactiveSlot() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (!students[i].isActive) {
            return i;
        }
    }
    return -1;
}

int getActiveStudentCount() {
    int count = 0;
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (students[i].isActive) {
            count++;
        }
    }
    return count;
}

void displayHeader() {
    printf("\n");
    printf("========================================================\n");
    printf("       HOSTEL ROOM ALLOCATION SYSTEM\n");
    printf("========================================================\n");
}

void displayMenu() {
    printf("\n");
    printf("-------------------- MAIN MENU -------------------------\n");
    printf("1. Add New Student\n");
    printf("2. Allocate Room to Student\n");
    printf("3. Search Student\n");
    printf("4. Display Occupancy Report\n");
    printf("5. Checkout Student (Deallocate Room)\n");
    printf("6. Display All Students\n");
    printf("7. Save Data to File\n");
    printf("8. Load Data from File\n");
    printf("9. Exit\n");
    printf("--------------------------------------------------------\n");
    printf("Enter your choice: ");
}

void addStudent() {
    int slotIndex = findInactiveSlot();
    
    if (slotIndex == -1) {
        printf("\nError: Maximum student capacity reached!\n");
        return;
    }

    Student newStudent;
    newStudent.isAllocated = 0;
    newStudent.roomNumber = -1;
    newStudent.isActive = 1;

    printf("\n--- Add New Student ---\n");
    
    printf("Enter Student Name: ");
    clearInputBuffer();
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    trim(newStudent.name);

    if (strlen(newStudent.name) == 0) {
        printf("Error: Name cannot be empty!\n");
        return;
    }

    printf("Enter Roll Number: ");
    fgets(newStudent.rollNumber, 20, stdin);
    newStudent.rollNumber[strcspn(newStudent.rollNumber, "\n")] = 0;
    trim(newStudent.rollNumber);

    if (strlen(newStudent.rollNumber) == 0) {
        printf("Error: Roll number cannot be empty!\n");
        return;
    }

    if (findStudentByRollNumber(newStudent.rollNumber) != -1) {
        printf("Error: Student with roll number %s already exists!\n", newStudent.rollNumber);
        return;
    }

    printf("Enter Contact Number: ");
    fgets(newStudent.contact, MAX_CONTACT_LENGTH, stdin);
    newStudent.contact[strcspn(newStudent.contact, "\n")] = 0;
    trim(newStudent.contact);

    if (!isValidContact(newStudent.contact)) {
        printf("Error: Invalid contact number! Must be at least 10 digits.\n");
        return;
    }

    printf("Enter Branch: ");
    fgets(newStudent.branch, MAX_BRANCH_LENGTH, stdin);
    newStudent.branch[strcspn(newStudent.branch, "\n")] = 0;
    trim(newStudent.branch);

    if (strlen(newStudent.branch) == 0) {
        printf("Error: Branch cannot be empty!\n");
        return;
    }

    students[slotIndex] = newStudent;
    if (slotIndex >= studentCount) {
        studentCount = slotIndex + 1;
    }

    printf("\nSuccess: Student added successfully!\n");
    printf("Name: %s | Roll No: %s | Contact: %s | Branch: %s\n", 
           newStudent.name, newStudent.rollNumber, newStudent.contact, newStudent.branch);
}

void allocateRoom() {
    char rollNumber[20];
    int roomNum;

    printf("\n--- Allocate Room ---\n");
    printf("Enter Student Roll Number: ");
    clearInputBuffer();
    fgets(rollNumber, 20, stdin);
    rollNumber[strcspn(rollNumber, "\n")] = 0;
    trim(rollNumber);

    int studentIndex = findStudentByRollNumber(rollNumber);
    if (studentIndex == -1) {
        printf("Error: Student with roll number %s not found!\n", rollNumber);
        return;
    }

    if (students[studentIndex].isAllocated) {
        printf("Error: Student already allocated to Room %d!\n", students[studentIndex].roomNumber);
        return;
    }

    printf("Enter Room Number (1-%d): ", MAX_ROOMS);
    if (scanf("%d", &roomNum) != 1) {
        printf("Error: Invalid input!\n");
        clearInputBuffer();
        return;
    }

    if (roomNum < 1 || roomNum > MAX_ROOMS) {
        printf("Error: Invalid room number! Must be between 1 and %d.\n", MAX_ROOMS);
        return;
    }

    if (rooms[roomNum - 1].isOccupied) {
        printf("Error: Room %d is already occupied!\n", roomNum);
        return;
    }

    students[studentIndex].roomNumber = roomNum;
    students[studentIndex].isAllocated = 1;
    rooms[roomNum - 1].isOccupied = 1;
    strcpy(rooms[roomNum - 1].occupantRollNumber, rollNumber);

    printf("\nSuccess: Room %d allocated to %s (Roll No: %s)\n", 
           roomNum, students[studentIndex].name, rollNumber);
}

void searchStudent() {
    int choice;
    printf("\n--- Search Student ---\n");
    printf("1. Search by Name\n");
    printf("2. Search by Roll Number\n");
    printf("3. Search by Room Number\n");
    printf("Enter choice: ");
    clearInputBuffer();
    
    if (scanf("%d", &choice) != 1) {
        printf("Error: Invalid input!\n");
        clearInputBuffer();
        return;
    }

    switch (choice) {
        case 1: {
            char name[MAX_NAME_LENGTH];
            printf("Enter Student Name: ");
            clearInputBuffer();
            fgets(name, MAX_NAME_LENGTH, stdin);
            name[strcspn(name, "\n")] = 0;
            trim(name);

            int found = 0;
            for (int i = 0; i < MAX_ROOMS; i++) {
                if (students[i].isActive && strcasecmp(students[i].name, name) == 0) {
                    printf("\n--- Student Details ---\n");
                    printf("Name: %s\n", students[i].name);
                    printf("Roll Number: %s\n", students[i].rollNumber);
                    printf("Contact: %s\n", students[i].contact);
                    printf("Branch: %s\n", students[i].branch);
                    if (students[i].isAllocated) {
                        printf("Room Number: %d\n", students[i].roomNumber);
                    } else {
                        printf("Room: Not Allocated\n");
                    }
                    found = 1;
                }
            }
            if (!found) {
                printf("No student found with name: %s\n", name);
            }
            break;
        }
        case 2: {
            char rollNumber[20];
            printf("Enter Roll Number: ");
            clearInputBuffer();
            fgets(rollNumber, 20, stdin);
            rollNumber[strcspn(rollNumber, "\n")] = 0;
            trim(rollNumber);

            int index = findStudentByRollNumber(rollNumber);
            if (index != -1) {
                printf("\n--- Student Details ---\n");
                printf("Name: %s\n", students[index].name);
                printf("Roll Number: %s\n", students[index].rollNumber);
                printf("Contact: %s\n", students[index].contact);
                printf("Branch: %s\n", students[index].branch);
                if (students[index].isAllocated) {
                    printf("Room Number: %d\n", students[index].roomNumber);
                } else {
                    printf("Room: Not Allocated\n");
                }
            } else {
                printf("No student found with roll number: %s\n", rollNumber);
            }
            break;
        }
        case 3: {
            int roomNum;
            printf("Enter Room Number: ");
            if (scanf("%d", &roomNum) != 1) {
                printf("Error: Invalid input!\n");
                clearInputBuffer();
                return;
            }

            if (roomNum < 1 || roomNum > MAX_ROOMS) {
                printf("Error: Invalid room number!\n");
                return;
            }

            if (rooms[roomNum - 1].isOccupied) {
                char *rollNum = rooms[roomNum - 1].occupantRollNumber;
                int index = findStudentByRollNumber(rollNum);
                if (index != -1) {
                    printf("\n--- Student Details ---\n");
                    printf("Room Number: %d\n", roomNum);
                    printf("Name: %s\n", students[index].name);
                    printf("Roll Number: %s\n", students[index].rollNumber);
                    printf("Contact: %s\n", students[index].contact);
                    printf("Branch: %s\n", students[index].branch);
                }
            } else {
                printf("Room %d is vacant.\n", roomNum);
            }
            break;
        }
        default:
            printf("Invalid choice!\n");
    }
}

void displayOccupancyReport() {
    int occupiedCount = 0;
    int vacantCount = 0;

    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i].isOccupied) {
            occupiedCount++;
        } else {
            vacantCount++;
        }
    }

    float vacancyPercentage = ((float)vacantCount / MAX_ROOMS) * 100;

    printf("\n========== OCCUPANCY REPORT ==========\n");
    printf("Total Rooms: %d\n", MAX_ROOMS);
    printf("Occupied Rooms: %d\n", occupiedCount);
    printf("Vacant Rooms: %d\n", vacantCount);
    printf("Vacancy Percentage: %.2f%%\n", vacancyPercentage);
    printf("======================================\n");

    printf("\n--- Room Status ---\n");
    printf("%-10s %-10s %-20s\n", "Room No", "Status", "Occupant");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i].isOccupied) {
            int studentIndex = findStudentByRollNumber(rooms[i].occupantRollNumber);
            if (studentIndex != -1) {
                printf("%-10d %-10s %-20s\n", rooms[i].roomNumber, "Occupied", students[studentIndex].name);
            }
        } else {
            printf("%-10d %-10s %-20s\n", rooms[i].roomNumber, "Vacant", "-");
        }
    }
}

void checkoutStudent() {
    char rollNumber[20];

    printf("\n--- Checkout Student ---\n");
    printf("Enter Student Roll Number: ");
    clearInputBuffer();
    fgets(rollNumber, 20, stdin);
    rollNumber[strcspn(rollNumber, "\n")] = 0;
    trim(rollNumber);

    int studentIndex = findStudentByRollNumber(rollNumber);
    if (studentIndex == -1) {
        printf("Error: Student with roll number %s not found!\n", rollNumber);
        return;
    }

    if (!students[studentIndex].isAllocated) {
        printf("Error: Student is not allocated any room!\n");
        return;
    }

    int roomNum = students[studentIndex].roomNumber;
    rooms[roomNum - 1].isOccupied = 0;
    strcpy(rooms[roomNum - 1].occupantRollNumber, "");
    students[studentIndex].isAllocated = 0;
    students[studentIndex].roomNumber = -1;
    students[studentIndex].isActive = 0;

    printf("\nSuccess: Student %s checked out from Room %d and removed from the system!\n", 
           students[studentIndex].name, roomNum);
}

void displayAllStudents() {
    int activeCount = getActiveStudentCount();
    
    if (activeCount == 0) {
        printf("\nNo students registered yet!\n");
        return;
    }

    printf("\n========== ALL STUDENTS ==========\n");
    printf("%-20s %-15s %-15s %-20s %-10s\n", 
           "Name", "Roll Number", "Contact", "Branch", "Room");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < MAX_ROOMS; i++) {
        if (students[i].isActive) {
            char roomInfo[10];
            if (students[i].isAllocated) {
                sprintf(roomInfo, "%d", students[i].roomNumber);
            } else {
                strcpy(roomInfo, "N/A");
            }
            printf("%-20s %-15s %-15s %-20s %-10s\n",
                   students[i].name, students[i].rollNumber, 
                   students[i].contact, students[i].branch, roomInfo);
        }
    }
    printf("==================================\n");
    printf("Total Active Students: %d\n", activeCount);
}

void saveDataToFile() {
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL) {
        printf("Error: Unable to open file for writing!\n");
        return;
    }

    fprintf(file, "%d\n", studentCount);

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s|%s|%s|%s|%d|%d|%d\n",
                students[i].name, students[i].rollNumber,
                students[i].contact, students[i].branch,
                students[i].roomNumber, students[i].isAllocated, students[i].isActive);
    }

    for (int i = 0; i < MAX_ROOMS; i++) {
        fprintf(file, "%d|%d|%s\n",
                rooms[i].roomNumber, rooms[i].isOccupied,
                rooms[i].occupantRollNumber);
    }

    fclose(file);
    printf("\nSuccess: Data saved to file successfully!\n");
}

void loadDataFromFile() {
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("Info: No existing data file found. Starting fresh.\n");
        return;
    }

    initializeSystem();

    fscanf(file, "%d\n", &studentCount);

    for (int i = 0; i < studentCount; i++) {
        fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d\n",
               students[i].name, students[i].rollNumber,
               students[i].contact, students[i].branch,
               &students[i].roomNumber, &students[i].isAllocated, &students[i].isActive);
    }

    for (int i = 0; i < MAX_ROOMS; i++) {
        fscanf(file, "%d|%d|%[^\n]\n",
               &rooms[i].roomNumber, &rooms[i].isOccupied,
               rooms[i].occupantRollNumber);
    }

    fclose(file);
    printf("\nSuccess: Data loaded from file successfully!\n");
    printf("Loaded %d students.\n", studentCount);
}

int main() {
    int choice;
    
    initializeSystem();
    
    displayHeader();
    printf("Welcome to the Hostel Room Allocation System!\n");
    printf("Loading existing data...\n");
    loadDataFromFile();

    while (1) {
        displayMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                allocateRoom();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                displayOccupancyReport();
                break;
            case 5:
                checkoutStudent();
                break;
            case 6:
                displayAllStudents();
                break;
            case 7:
                saveDataToFile();
                break;
            case 8:
                loadDataFromFile();
                break;
            case 9:
                printf("\nSaving data before exit...\n");
                saveDataToFile();
                printf("Thank you for using the Hostel Room Allocation System!\n");
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
