#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

void stud_del(void) {
    if (!head) { puts("No records to delete."); return; }
    puts("\n1. Delete using Roll Number\n2. Delete using Name");
    int choice = read_int("Enter Your Choice: ");
    int roll;
    if (choice == 1) roll = read_int("Enter Roll Number: ");
    else if (choice == 2) {
        char name[100];
        int matches = 0;
        read_name("Enter Student Name: ", name, sizeof name);
        for (Student *p = head; p; p = p->next) {
            if (strcmp(p->name, name) == 0) {
                printf("Roll: %d | Name: %s | Percentage: %.2f%%\n", p->roll, p->name, p->percentage);
                matches++;
            }
        }
        if (!matches) { puts("No matching students."); return; }
        roll = read_int("Enter Roll Number to Delete: ");
        Student *target = find_roll(roll);
        if (!target || strcmp(target->name, name) != 0) {
            puts("Roll number does not match the selected name."); return;
        }
    } else { puts("Invalid choice."); return; }
    Student *p = head, *prev = NULL;
    while (p && p->roll != roll) { prev = p; p = p->next; }
    if (!p) { puts("Roll number not found."); return; }
    if (prev) prev->next = p->next;
    else head = p->next;
    free(p);
    puts("Student record deleted successfully.");
}
