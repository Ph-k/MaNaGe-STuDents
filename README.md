
# MaNaGe-STuDents

A student information management program in C

*This program was written as part of the Operating System course at DIT – UoA. Credits to the professor of the course at the time, [Alex Delis](https://www.alexdelis.eu/).*

## About this project:

The program is named mngstd *(**m**a**n**a**g**e **st**u**d**ents)*, and it uses data structures to export information and statistics for the secretary office of a university. All the information is stored in a data structure which has an access cost of O(1), therefore a hash table. Furthermore, because the program has to answer queries for certain groups of students in reasonable time *(ie the entries of the hash tables cannot be iterated for every query)*, an inverted index data structure is used in combination of the hash table.

More specifically. Information about the students is inserted into the hash table based on their unique StudentID (key). This information can be inserted or removed any time and consists of the following students information: his/her full name, home address, postal code, year of entry and GPA.

The inverted index groups the above student information based on the year of entry of each student, by having a list of pointers to the according hash table entries. This way we can fast & easily get a list of students based on their entry year without wasting memory *(ie creating a whole new data structure)* and computational resources *(ie iterating the hash table entries one by one)*.

All the data structures memory is dynamically allocated, allowing for theoretical infinite (as infinite as your systems memory) number of student records.

## Project compilation/makefile usage:

The makefile can effortless compile the entirety of the program by simply typing `make` on a tty (in the Source directory). The only requirement is a linux/unix machine running a stable version of the gcc compiler. *Personally the program worked fine on Debian based distros.*

## mngstd usage:

The program can be executed from a cli as `./mngstd -i inputfile -c configfile` where:
-	mngstd: is the executable of the project
-	inputfile: is a file containing the information of various students *(see `Example_Inputs-Configs` for examples)*
-	configfile: is an optional configuration file which can be used to change the default settings of: the hash table size and the size of the string input buffer *(see `Example_Inputs-Configs` for examples)*. The program works fine without a custom configuration file, with the default values, but according to your input you might or might not want to change them in order to achieve better performance.

## Program interface usage:

The program provides a tui to the user allowing him to interact with the information of the students. The tui instructions are the following:

1. i(nsert) studentid lastname firstname zip year gpa: Provided a students information, it inserts him/her to the hash table/inverted index data structure (succeeds only if the studentid *(key)* does not already exist).
2. l(ook-up) studentid: Searched for a student given his studentid. Print error message if not found.
3. d(elete) studentid: Deletes a student from the data structure, *only if he exists*.
4. n(umber) year: for the given year, find the number of students still in the university.
5. t(op) num year: For the given academic year, prints the num top (better) students based on the GPA. 
6. a(verage) year: Print the GPA of the given academic year.
7. m(inimum) year: For the given academic year, prints the students with the smallest GPA.
8. c(ount): For every academic year, find the number of students saved in the data structure.
9. p(ostal code) rank: Finds the town (from the postal code) which is the nth/rankth most popular as home address among the students.
10. exit: Terminates the program. Of course all the dynamically allocated memory is gracefully freed. 

*You can see how the commands are defined in `Command_format.txt`.*

## Source code files overview:

- `main.c`: This file contains the main() function and provides the tui of the program. The utility of the tui is achieved by calling the according functions from the `Controller.c` module.
- `fileReader.c`/`fileReader.h`: Provides functions from which the main() can initialize the programs data structures (and set configurations) from data of input files (and configuration files).
- `Student.c`/`Student.h`: Defines a structure (C struct) which can hold all the information of a student. Also, there are functions which enable the creation/deletion/printing of student structs.
- `HashTable.c`/`HashTable.h`: The hash table implementation. Provides functions for the creation destruction and manipulation of the data structure.
- `LinkedList.c`/`LinkedList.h`: Implements a custom linked list. The customization of the structure make it the inverted list of the project, and also allows it to be used in the answering of queries. 
- `Controller.c`/`Controller.h`: Every command of the project is basically implemented in a C function which does all the necessary data structure manipulation and searching. All these functions can be found here, providing a level of abstraction between the programs utilities called from the main and the actual data structure manipulation.

