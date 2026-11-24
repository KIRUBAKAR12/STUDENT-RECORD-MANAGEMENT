#include <stdio.h>
#include <string.h>
#include "student.h"

void stud_mod(void) {
    if (!head) { puts("No records to modify."); return; }
    puts("\nSearch Record By:\n1. Roll Number\n2. Name\n3. Percentage");
    int choice = read_int("Enter Your Choice: ");
    int roll;
    if (choice == 1) roll = read_int("Enter Roll Number: ");
    else if (choice == 2) {
        char name[100]; int matches = 0;
        read_name("Enter Name: ", name, sizeof name);
        for (Student *p = head; p; p = p->next)
            if (!strcmp(p->name, name)) {
                printf("Roll: %d | %s | %.2f%%\n", p->roll, p->name, p->percentage);
                matches++;
            }
        if (!matches) { puts("No matches found."); return; }
        roll = read_int("Enter Roll Number to Modify: ");
        Student *p = find_roll(roll);
        if (!p || strcmp(p->name, name)) { puts("Selected roll does not match search."); return; }
    } else if (choice == 3) {
        float percentage = read_percentage("Enter Percentage: ");
        int matches = 0;
        for (Student *p = head; p; p = p->next)
            if (p->percentage > percentage - 0.005f && p->percentage < percentage + 0.005f) {
                printf("Roll: %d | %s | %.2f%%\n", p->roll, p->name, p->percentage);
                matches++;
            }
        if (!matches) { puts("No matches found."); return; }
        roll = read_int("Enter Roll Number to Modify: ");
        Student *p = find_roll(roll);
        if (!p || !(p->percentage > percentage - 0.005f && p->percentage < percentage + 0.005f)) {
            puts("Selected roll does not match search."); return;
        }
    } else { puts("Invalid choice."); return; }
    Student *p = find_roll(roll);
    if (!p) { puts("Student not found."); return; }
    puts("\n1. Modify Name\n2. Modify Percentage");
    choice = read_int("Enter Your Choice: ");
    if (choice == 1) read_name("Enter New Name: ", p->name, sizeof p->name);
    else if (choice == 2) p->percentage = read_percentage("Enter New Percentage: ");
    else { puts("Invalid choice."); return; }
    puts("Student record modified successfully.");
}
