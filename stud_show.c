#include <stdio.h>
#include "student.h"

void stud_show(void) {
    if (!head) {
        puts("No student records found.");
        return;
    }
    puts("\n---------------------------------------------------------------");
    printf("%-8s | %-28s | %s\n", "Roll No", "Name", "Percentage");
    puts("---------------------------------------------------------------");
    for (Student *p = head; p; p = p->next)
        printf("%-8d | %-28s | %.2f%%\n", p->roll, p->name, p->percentage);
    puts("---------------------------------------------------------------");
}
