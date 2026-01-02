# 🎓 University Management System (UMS) 💖

Welcome to the **University Management System (UMS)** – a small C++ console application I built for my fiancée’s **first semester project** 😄.

This project is **educational, fun, and a little heart-filled**, showing how a university manages students, courses, attendance, and grades – all in **pure C++** without fancy databases.

---

## 🗝️ Credentials & Access

The system uses **Role-Based Access Control (RBAC)**. What you see depends on who logs in:

| Access Level | Username / ID | Password     | Capabilities                                      |
| ------------ | ------------- | ------------ | ------------------------------------------------- |
| System Admin | `admin`       | `admin123`   | Full CRUD on all data                             |
| Student      | Roll Number   | User-defined | View-only personal marks, courses, and attendance |

> 💡 Pro tip: The student login is perfect to let your loved one check her marks and attendance without worrying about breaking anything 😏.

---

## 🗄️ Data Architecture

No SQL, no complicated setup – everything lives in **global struct arrays**:

* **Structs**: Group related data, e.g., student’s name, roll number, and status.
* **Arrays**: Hold multiple records like `students[100]` and `marksRecords[500]`.
* **Relationships**: Students are linked to courses by `rollNumber`, so data stays consistent and clean.

---

## 🔧 Functional Modules

### 1️⃣ Utility Engine (The Brain)

* `findStudentIndex(int roll)`: Finds a student in the array.
* `isStudentEnrolled(roll, code)`: Checks if a student is actually enrolled in a course.

### 2️⃣ Student & Teacher Management

* **Add**: Prevents duplicate entries.
* **Delete**: Soft delete (`isActive = false`) to keep historical data safe.

### 3️⃣ Course & Enrollment Logic

* **Add Course**: Creates a subject entity (e.g., CS101).
* **Assign Course**: Links a student to a course using enrollments.

### 4️⃣ Attendance Tracking

* Marks presence and calculates **attendance percentage** in real-time.
* Formula: `(classesPresent / totalClasses) * 100`.

### 5️⃣ Marks & Grading

* Admin enters **obtainedMarks** and **totalMarks**.
* `calculateResult()` converts marks to grades:

| Marks  | Grade          |
| ------ | -------------- |
| 90–100 | A+ (Excellent) |
| 80–89  | A              |
| 70–79  | B              |
| 60–69  | C              |
| 50–59  | D (Passing)    |
| <50    | F (Fail)       |

---

## 🚀 How to Use (Beginner Friendly)

1. Run the program – it comes with **sample student Ali Khan (Roll 1001)** and **CS101** course.
2. **Admin Login**:

   ```
   Username: admin
   Password: admin123
   ```
3. **Assign Course**: Go to Course Management → Assign Roll 1001 to CS101.
4. **Enter Marks**: Go to Marks Management → Enter 85 marks for Roll 1001.
5. **Calculate Result**: View the generated report card (‘A’ grade!).
6. **Student Login**: Logout → choose Student Login → ID 1001, password `ali123`. View personal marks.

> 💖 Fun part: Now your fiancée can log in and see her marks without you hovering over her shoulder 😉

---

## 🎨 UI/UX Design Logic

* `setw(n)`: Keeps columns neat and aligned.
* `cin.ignore()`: Prevents skipped input fields.
* `clearScreen()`: Cleans the console for every new menu.

⚠️ **Important**: This app is **non-persistent**. Closing the console erases all added students, teachers, and marks because no file handling is implemented.

---

## 💖 Why I Built This

* To help my fiancée with her **first semester project** ❤️
* To **practice C++ structs and arrays**
* To create something **practical, cute, and meaningful**

---

## 📌 Next Steps (Optional Fun Upgrades)

* Add **file storage** for persistence
* Add **teacher login** and grading privileges
* More **beautiful report generation**

---

### 💻 Have fun exploring UMS!

This project shows the **power of arrays and structs in C++** – and a little love sprinkled in for motivation 😉

---
