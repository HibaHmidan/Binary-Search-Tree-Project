# Task Management System using Binary Search Tree (BST)

## Overview

This project is an enhanced **Task Management System** implemented in **C language**.  
It uses a **Binary Search Tree (BST)** as the core data structure to efficiently store, manage, and organize tasks.

Each task is inserted into the BST based on its **Task ID**, which allows fast searching, insertion, and deletion. The system is fully menu-driven and interacts with the user through the terminal.

This project was developed for the **COMP2421 – Data Structures (Spring 2024/2025)** course.

---

## Project Objective

The main goal of this project is to apply Binary Search Tree concepts in a practical application.  
The system reads tasks from a file and manages them efficiently while maintaining good time and space complexity.

The BST is used strictly as required — no alternative data structures are used to replace it.

---

## Features

The program provides the following menu options:

1. **Load Tasks from File**
   - Reads tasks from `tasks.txt`
   - Inserts them into the BST based on Task ID

2. **Add a New Task**
   - Inserts a new task into the tree

3. **Delete a Task**
   - Removes a task using its Task ID

4. **Search for a Task**
   - Searches for a task by its Task Name

5. **Perform a Task**
   - Marks a task as performed without deleting it

6. **View Unperformed Tasks**
   - Displays all unperformed tasks
   - Sorted by Task Name

7. **View Performed Tasks**
   - Displays all performed tasks
   - Sorted by Task ID

8. **Restructure the BST**
   - Rebuilds the tree based on:
     - Task Name
     - Task Date
     - Task Duration

9. **View BST Information**
   - Displays:
     - Tree Height
     - Tree Size
     - Number of Leaf Nodes
     - Number of Internal Nodes

10. **Exit**
   - Closes the program safely

---

## Input File Format

The program reads from a file named:
