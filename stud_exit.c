
    
  
#include <stdio.h>
#include "student.h"

int stud_exit(void) {
    puts("\n1. Save and Exit\n2. Exit Without Saving\n3. Return to Main Menu");
    int choice = read_int("Enter Your Choice: ");
    if (choice == 1) {
        if (stud_save()) { puts("Goodbye!"); return 1; }
        puts("Save failed. Returning to main menu to prevent data loss.");
    } else if (choice == 2) { puts("Exiting without saving. Goodbye!"); return 1; }
    else if (choice != 3) puts("Invalid choice.");
    return 0;
}


