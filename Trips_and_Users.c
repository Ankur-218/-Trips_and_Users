#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_TRIPS 1000
#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int totalTrips;
} User;

typedef struct {
    int id;
    int userId;
    char destination[MAX_NAME_LENGTH];
    double distance;
    time_t date;
} Trip;

User users[MAX_USERS];
Trip trips[MAX_TRIPS];
int userCount = 0;
int tripCount = 0;

void addUser() {
    if (userCount >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }
    
    User newUser;
    newUser.id = userCount + 1;
    newUser.totalTrips = 0;
    
    printf("Enter user name: ");
    scanf("%s", newUser.name);
    
    users[userCount++] = newUser;
    printf("User added successfully. ID: %d\n", newUser.id);
}

void addTrip() {
    if (tripCount >= MAX_TRIPS) {
        printf("Maximum number of trips reached.\n");
        return;
    }
    
    Trip newTrip;
    newTrip.id = tripCount + 1;
    
    printf("Enter user ID: ");
    scanf("%d", &newTrip.userId);
    
    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == newTrip.userId) {
            userIndex = i;
            break;
        }
    }
    
    if (userIndex == -1) {
        printf("User not found.\n");
        return;
    }
    
    printf("Enter destination: ");
    scanf("%s", newTrip.destination);
    
    printf("Enter distance (km): ");
    scanf("%lf", &newTrip.distance);
    
    newTrip.date = time(NULL);
    
    trips[tripCount++] = newTrip;
    users[userIndex].totalTrips++;
    
    printf("Trip added successfully. ID: %d\n", newTrip.id);
}

void displayUserStats() {
    int userId;
    printf("Enter user ID: ");
    scanf("%d", &userId);
    
    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == userId) {
            userIndex = i;
            break;
        }
    }
    
    if (userIndex == -1) {
        printf("User not found.\n");
        return;
    }
    
    printf("User: %s\n", users[userIndex].name);
    printf("Total trips: %d\n", users[userIndex].totalTrips);
    
    double totalDistance = 0;
    for (int i = 0; i < tripCount; i++) {
        if (trips[i].userId == userId) {
            totalDistance += trips[i].distance;
        }
    }
    
    printf("Total distance traveled: %.2f km\n", totalDistance);
}

void displayAllTrips() {
    printf("All Trips:\n");
    printf("ID\tUser ID\tDestination\tDistance (km)\tDate\n");
    for (int i = 0; i < tripCount; i++) {
        char dateStr[20];
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", localtime(&trips[i].date));
        printf("%d\t%d\t%s\t\t%.2f\t\t%s\n", 
               trips[i].id, trips[i].userId, trips[i].destination, 
               trips[i].distance, dateStr);
    }
}

int main() {
    int choice;
    
    do {
        printf("\nTrips and Users Management System\n");
        printf("1. Add User\n");
        printf("2. Add Trip\n");
        printf("3. Display User Stats\n");
        printf("4. Display All Trips\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                addTrip();
                break;
            case 3:
                displayUserStats();
                break;
            case 4:
                displayAllTrips();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    
    return 0;
}