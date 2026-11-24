#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "student.h"

/* Old student.dat files used this binary layout. */
typedef struct {
    int roll;
    char name[100];
    float percentage;
} DiskStudent;

/* Remove leading and trailing spaces (used when reading formatted rows). */
static char *trim(char *text) {
    while (isspace((unsigned char)*text)) text++;
    char *end = text + strlen(text);
    while (end > text && isspace((unsigned char)end[-1])) --end;
    *end = '\0';
    return text;
}

/* Read lines such as: 1        | arun                         | 85.50% */
static int parse_text_row(char *line, DiskStudent *record) {
    char *first = strchr(line, '|');
    char *last = strrchr(line, '|');
    if (!first || !last || first == last) return 0;

    *first = '\0';
    *last = '\0';
    char *roll_text = trim(line);
    char *name_text = trim(first + 1);
    char *percent_text = trim(last + 1);
    char *end;

    errno = 0;
    long roll = strtol(roll_text, &end, 10);
    if (errno || *end != '\0' || roll <= 0 || roll > INT_MAX) return 0;

    size_t name_length = strlen(name_text);
    if (name_length == 0 || name_length >= sizeof record->name) return 0;

    errno = 0;
    float percent = strtof(percent_text, &end);
    if (errno || end == percent_text || *end != '%' ||
        *trim(end + 1) != '\0' || !(percent >= 0 && percent <= 100))
        return 0;

    record->roll = (int)roll;
    strcpy(record->name, name_text);
    record->percentage = percent;
    return 1;
}

static int add_loaded_record(const DiskStudent *record, Student **tail) {
    if (record->roll <= 0 ||
        !memchr(record->name, '\0', sizeof record->name) ||
        record->name[0] == '\0' ||
        !(record->percentage >= 0 && record->percentage <= 100) ||
        find_roll(record->roll)) {
        puts("Warning: invalid or duplicate student skipped.");
        return 0;
    }

    Student *node = malloc(sizeof *node);
    if (!node) {
        puts("Not enough memory to load more students.");
        return -1;
    }
    node->roll = record->roll;
    strcpy(node->name, record->name);
    node->percentage = record->percentage;
    node->next = NULL;

    if (!head) head = node;
    else (*tail)->next = node;
    *tail = node;
    return 1;
}

int stud_save(void) {
    FILE *file = fopen("student.dat.tmp", "w");
    if (!file) {
        perror("Cannot open temporary data file");
        return 0;
    }

    int ok = 1;
    if (fprintf(file,
        "---------------------------------------------------------------\n"
        "%-8s | %-28s | %s\n"
        "---------------------------------------------------------------\n",
        "Roll No", "Name", "Percentage") < 0) ok = 0;

    for (Student *p = head; ok && p; p = p->next) {
        if (fprintf(file, "%-8d | %-28s | %.2f%%\n",
                    p->roll, p->name, p->percentage) < 0)
            ok = 0;
    }

    if (ok && fprintf(file,
        "---------------------------------------------------------------\n") < 0) ok = 0;
    if (fclose(file) != 0) ok = 0;

    if (!ok) {
        remove("student.dat.tmp");
        puts("Failed to save student records.");
        return 0;
    }
    if (rename("student.dat.tmp", "student.dat") != 0) {
        perror("Cannot replace student.dat");
        remove("student.dat.tmp");
        return 0;
    }
    puts("Student records saved as a readable table in student.dat.");
    return 1;
}

void stud_load(void) {
    FILE *file = fopen("student.dat", "rb");
    if (!file) {
        puts("No saved data found. Starting with an empty list.");
        return;
    }

    unsigned char header[3];
    size_t bytes = fread(header, 1, sizeof header, file);
    if (bytes == 0) {
        fclose(file);
        puts("student.dat is empty.");
        return;
    }
    rewind(file);

    Student *tail = head;
    while (tail && tail->next) tail = tail->next;
    int count = 0;
    DiskStudent record;

    if (bytes == sizeof header && memcmp(header, "---", sizeof header) == 0) {
        /* New readable table format. */
        char line[512];
        while (fgets(line, sizeof line, file)) {
            char *start = trim(line);
            if (*start == '-' || *start == '\0' ||
                strncmp(start, "Roll No", 7) == 0) continue;
            if (!parse_text_row(start, &record)) {
                puts("Warning: invalid student data row skipped.");
                continue;
            }
            int result = add_loaded_record(&record, &tail);
            if (result < 0) break;
            count += result;
        }
    } else {
        /* Compatibility with the original binary student.dat. */
        while (fread(&record, sizeof record, 1, file) == 1) {
            int result = add_loaded_record(&record, &tail);
            if (result < 0) break;
            count += result;
        }
    }

    if (ferror(file)) puts("Warning: error while reading student.dat.");
    fclose(file);
    printf("Loaded %d student record(s).\n", count);
}
