#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student {
    int roll;
    char name[100];
    float percentage;
    struct Student *next;
} Student;

extern Student *head;

int read_int(const char *prompt);
float read_percentage(const char *prompt);
void read_name(const char *prompt, char *dest, int size);
Student *find_roll(int roll);
int next_roll(void);
void clear_records(void);
void stud_add(void);
void stud_del(void);
void stud_show(void);
void stud_mod(void);
int stud_save(void);
void stud_load(void);
void stud_sort(void);
int stud_exit(void);
#endif
