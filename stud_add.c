#include <stdio.h>
#include <stdlib.h>
#include "student.h"

void stud_add(void) {
    Student *node = malloc(sizeof *node);
    if (!node) { puts("Memory allocation failed."); return; }
    read_name("Enter Student Name: ", node->name, sizeof node->name);
    node->percentage = read_percentage("Enter Percentage: ");
    node->roll = next_roll();
    node->next = NULL;
    if (!head) head = node;
    else {
        Student *p = head;
        while (p->next) p = p->next;
        p->next = node;
    }
    printf("Student added successfully! Roll Number: %d\n", node->roll);
}
