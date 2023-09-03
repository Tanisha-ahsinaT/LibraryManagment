# Library Management System

## Introduction

The Library Management System is a simple command-line program written in C that allows users to manage books and student book issuances within a library. This program provides basic functionalities such as adding books, listing available books, removing books, issuing books to students, and listing issued books.

The Library Management System uses the file system to store and manage information about books and book issuances.

## Features

- *Add Book*: Add new books to the library's collection, including book ID, name, author, and automatic date tracking.

- *List Books*: View a list of available books, including their details such as ID, name, author, and date of addition.

- *Remove Book*: Remove books from the library's collection based on their ID.

- *Issue Book*: Issue books to students by entering student details and book ID.

- *List Issued Books*: View a list of books issued to students, including student information, book name, and issue date.

## Getting Started

### Prerequisites

- You need a C compiler installed on your system, such as GCC.

### Installation

1. Clone the repository to your local machine:

   git clone https://github.com/yourusername/library-management-system.git

2. Compile the program using a C compiler:

   gcc library_management_system.c -o library_management_system

3. Run the program:

   ./library_management_system