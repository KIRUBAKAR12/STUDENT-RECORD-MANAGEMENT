#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "student.h"

Student *head = NULL;

static void input_line(const char *prompt, char *buffer, int size) {
    int ch;
    printf("%s", prompt);
    if (!fgets(buffer, size, stdin)) { puts("Input ended."); exit(0); }
    if (!strchr(buffer, '\n')) {
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}

int read_int(const char *prompt) {
    char buffer[128], extra;
    int value;
    while (1) {
        input_line(prompt, buffer, sizeof buffer);
        if (sscanf(buffer, " %d %c", &value, &extra) == 1) return value;
        puts("Invalid number. Try again.");
    }
}

float read_percentage(const char *prompt) {
    char buffer[128], extra;
    float value;
    while (1) {
        input_line(prompt, buffer, sizeof buffer);
        if (sscanf(buffer, " %f %c", &value, &extra) == 1 && value >= 0 && value <= 100)
            return value;
        puts("Enter a percentage between 0 and 100.");
    }
}

void read_name(const char *prompt, char *dest, int size) {
    char buffer[256];
    while (1) {
        input_line(prompt, buffer, sizeof buffer);
        int nonspace = 0;
        for (int i = 0; buffer[i]; i++) if (!isspace((unsigned char)buffer[i])) nonspace = 1;
        if (nonspace && strlen(buffer) < (size_t)size) {
            strcpy(dest, buffer);
            return;
        }
        printf("Name must contain 1 to %d characters.\n", size - 1);
    }
}

Student *find_roll(int roll) {
    for (Student *p = head; p; p = p->next) if (p->roll == roll) return p;
    return NULL;
}

int next_roll(void) {
    int roll = 1;
    while (find_roll(roll)) roll++;
    return roll;
}

void clear_records(void) {
    while (head) {
        Student *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    int choice;
    stud_load();
    for (;;) {
        puts("\n========================================");
        puts("       STUDENT RECORD MANAGEMENT");
        puts("========================================");
        puts("1. Add New Record");
        puts("2. Delete a Record");
        puts("3. Show Student Records");
        puts("4. Modify a Record");
        puts("5. Save Records");
        puts("6. Sort Student Records");
        puts("7. Exit");
        puts("========================================");
        choice = read_int("Enter Your Choice: ");
        switch (choice) {
            case 1: stud_add(); break;
            case 2: stud_del(); break;
            case 3: stud_show(); break;
            case 4: stud_mod(); break;
            case 5: stud_save(); break;
            case 6: stud_sort(); break;
            case 7:
                if (stud_exit()) { clear_records(); return 0; }
                break;
            default: puts("Invalid choice. Select 1 to 7.");
        }
    }
}
