# 🏨 Hostel Room Allocation System

A simple, console-based Hostel Room Allocation System built in C++ that digitally manages student records, room assignments, and occupancy tracking — replacing error-prone paper registers with a structured, reliable solution.

---

## 📋 Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Objectives](#objectives)
- [How It Works](#how-it-works)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Technologies Used](#technologies-used)

---

## About the Project

The **Hostel Room Allocation System** is a console-based application designed to simplify and streamline the process of assigning hostel rooms to students. Instead of relying on physical registers or scattered spreadsheets, this system stores all student and room details digitally in a clean, structured format.

It helps hostel administrators manage room availability, track occupancy in real time, search for students instantly, and maintain records safely across sessions through file storage.

---

## ✨ Features

### 🗂️ Digital Student Record Management
Stores each student's name, roll number, contact information, and branch in a structured format — eliminating the risk of misplaced or incomplete records.

### 🛏️ Automated Room Allocation
Automatically checks room availability before assigning a room, preventing double bookings and ensuring fair, error-free room distribution.

### 🔍 Simple Search & Quick Retrieval
Administrators can instantly search for any student using their roll number and view all associated details without manual effort.

### 📊 Real-Time Occupancy Tracking
Maintains an up-to-date status of every room — whether vacant or occupied — and displays which student is currently residing in each room.

### ✅ Smooth Check-in & Check-out
Built-in functions for allocating and deallocating rooms ensure that student movement in and out of the hostel is recorded accurately and without confusion.

### 💾 Safe File Storage & Data Retrieval
Saves all records to a file and reloads them on startup, so no data is ever lost when the program closes.

---

## 🎯 Objectives

1. **Interactive Environment** — Provide a smooth, menu-driven interface where users can navigate easily, enter details, and receive instant feedback.

2. **Logical Problem-Solving** — Encourage a step-by-step approach to managing room availability, handling student data, and processing check-in/check-out flows.

3. **Structured Data Management** — Keep all information — names, roll numbers, room numbers, contact details — in a neat and organised format.

4. **Quick Search & Retrieval** — Allow administrators to look up student details in seconds using their roll number.

5. **Accurate Occupancy Reporting** — Continuously track which rooms are occupied and which are vacant, giving administrators a clear picture at any moment.

6. **Persistent Data Storage** — Store all information in a file so records are preserved between sessions and can be reloaded when the program starts again.

---

## ⚙️ How It Works

The system uses **structs/classes** to represent students and rooms, and stores them using arrays or linked lists. The core workflow is:

1. **Load Data** — On startup, existing records are loaded from a file.
2. **Menu Navigation** — The user interacts through a numbered console menu.
3. **Allocate Room** — Enter student details; the system finds a vacant room and assigns it.
4. **Deallocate Room** — When a student checks out, their room is marked as vacant.
5. **Search Student** — Look up a student by roll number to view their details and room.
6. **View Occupancy** — Display a full list of rooms with their current status.
7. **Save & Exit** — All records are saved to a file before the program exits.

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler (e.g., GCC, MinGW, or MSVC)
- A terminal or IDE (e.g., VS Code, Code::Blocks, Dev-C++)

### Compilation

```bash
g++ hostel.cpp -o hostel
```

### Run

```bash
./hostel
```

On Windows:
```bash
hostel.exe
```

---

## 🖥️ Usage

Once the program starts, you will see a menu like:

```
===== Hostel Room Allocation System =====
1. Allocate Room
2. Deallocate Room
3. Search Student
4. View All Rooms
5. Display Occupancy Report
6. Save Records
7. Exit
=========================================
Enter your choice:
```

Follow the on-screen prompts to perform any operation.

---

## 📁 File Structure

```
hostel-room-allocation/
│
├── hostel.cpp          # Main source code
├── records.txt         # Auto-generated data file for storing records
└── README.md           # Project documentation
```

---

## 🛠️ Technologies Used

- **Language:** C
- **Concepts:** Structs / Classes, File I/O, Arrays / Linked Lists, Functions, Loops & Conditionals
- **Interface:** Console / Terminal (menu-driven)

---

## 👨‍💻 Author

Developed as an academic project to demonstrate the application of data structures and file handling in solving a real-world hostel management problem.

---

> *"Reducing manual errors and making hostel management faster, reliable, and digital."*
