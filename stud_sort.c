#include <stdio.h>
#include <string.h>
#include "student.h"

void stud_sort(void) {
    if (!head || !head->next) { puts("Not enough records to sort."); return; }
    puts("\n1. Sort by Name (A-Z)\n2. Sort by Percentage (High-Low)");
    int choice = read_int("Enter Your Choice: ");
    if (choice != 1 && choice != 2) { puts("Invalid choice."); return; }
    /* Swap data, not list links, so roll numbers stay attached to students. */
    for (Student *a = head; a; a = a->next) {
        for (Student *b = a->next; b; b = b->next) {
            int swap = (choice == 1) ? strcmp(a->name, b->name) > 0 : a->percentage < b->percentage;
            if (swap) {
                int roll = a->roll; a->roll = b->roll; b->roll = roll;
                float pct = a->percentage; a->percentage = b->percentage; b->percentage = pct;
                char name[100]; strcpy(name, a->name); strcpy(a->name, b->name); strcpy(b->name, name);
            }
        }
    }
    puts("Records sorted successfully.");
    stud_show();
}
