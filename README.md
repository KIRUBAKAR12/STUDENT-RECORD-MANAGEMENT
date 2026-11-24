# Student Record Management System - C (Readable student.dat)

A multi-file C project using a singly linked list, dynamically allocated student records, numeric menus, and text-file persistence.

## Ubuntu commands

```bash
cd ~/kiruba/project1   # or go to the folder where you extracted the project
make
./student
```

If GCC/make is missing, install them using `sudo apt update && sudo apt install build-essential`.

## Convert existing binary student.dat safely

1. Copy the OLD `student.dat` from your existing project into the directory of the updated program. Do not open and resave the binary file in `vi`.
2. Back up the old file: `cp student.dat student.dat.bak`
3. Recompile with `make` and run `./student`.
4. The program will load the old binary records automatically (provided they use the format from the original version of this project).
5. Choose `3` to check your students, then choose `5` to save. `student.dat` will now contain a readable text table.
6. Check the file with `cat student.dat` or `vi student.dat`.
7. Exit and restart `./student` to confirm the text records load again.

## Build manually (alternative to make)

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c stud_add.c stud_del.c stud_show.c stud_mod.c stud_save.c stud_sort.c stud_exit.c -o student
./student
```

## What is in student.dat?

The saved file is *plain text*, for example:

```
---------------------------------------------------------------
Roll No  | Name                         | Percentage
---------------------------------------------------------------
1        | arun                         | 85.50%
2        | jai                          | 91.00%
3        | kiruba                       | 95.00%
---------------------------------------------------------------
```

The loader accepts this tabular format. Percentages are stored with two decimal places, matching the displayed table. A student name can include spaces. The original file's old binary format is supported for conversion to text.

## Files

- `main.c`: numeric menu, input helpers, and linked-list management
- `student.h`: shared struct and function declarations
- `stud_add.c`: add with lowest available positive roll number
- `stud_del.c`: delete by roll number or name
- `stud_show.c`: display table with `|` columns
- `stud_mod.c`: search by roll, name or percentage, then modify
- `stud_save.c`: read/write tabular student.dat and import old binary student.dat
- `stud_sort.c`: sort by name or descending percentage
- `stud_exit.c`: save and exit, exit without saving, return to menu
- `Makefile`: build the program

## Notes

- Run the program from the same folder as `student.dat`. Data is saved in the *current working directory*.
- Do not open the data file in `vi` while the program is saving it. You can safely inspect it after saving.
- Use option 5 to save changes, or option 7 then 1 to save and exit.
- Use option 7 then 2 to exit without saving changes made since the last save.
- Roll numbers use the smallest available positive integer and a deleted roll number can be reused.
- Do not run multiple instances against the same file simultaneously.

## author
KIRUBAKAR M , V26CE2K4
