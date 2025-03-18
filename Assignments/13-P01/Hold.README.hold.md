## C++ Database Project Using JSON as a Backend

#### Due: 03-25-2025 (Tuesday)

Below is the **first document** in a series designed to guide students in creating an **OOP-based database** system in C++ with **JSON** serving as the “database” backend. This document provides a **high-level project outline** and **initial steps** to break the project into consumable stages. We will emphasize **design** (private/public/protected), **DRY** (Don’t Repeat Yourself), appropriate **class relationships**, and potentially **UML** for planning.

---

## Project Overview

### Goal

Create a small-scale database system in **C++** that:

1. Stores data in **JSON** files (instead of a traditional DB).
2. Allows basic operations: **CRUD** (Create, Read, Update, Delete).
3. Demonstrates **multiple classes** with well-thought-out responsibilities.

### Learning Objectives

1. **Apply OOP Principles** (classes, objects, encapsulation, DRY).
2. **Practice Good Design** (public/private/protected, minimized inheritance).
3. **Introduce UML** as a tool to plan class relationships and data flow.
4. **Handle JSON Data**: Understand how to parse and write JSON in C++.

---

## Suggested Major Components

1. **Data Model**

   - Classes representing entities (e.g., a `Record` or `User`, `Item`, etc.).
   - JSON reading/writing capabilities (parsing and serialization).

2. **Database / Storage Manager**

   - A class or set of classes handling loading and saving data to/from JSON.
   - Possibly a “driver” or “controller” that orchestrates CRUD.

3. **Application Logic**

   - Classes or methods providing user commands or programmatic interface for DB operations.

4. **Main Application**
   - Where everything ties together.
   - Possibly an interactive console or minimal user interface to demonstrate functionality.

---

## Consumable Steps (Blueprint)

### Step 1: Requirements & Sketching (Design Phase)

1. **Define the Scope**:
   - What data do we want to store?
   - Example: “A simple library or inventory system.”
2. **Determine JSON Structure**:
   - Example:
     ```json
     {
       "items": [
         { "id": 1, "name": "Sword", "quantity": 2 },
         { "id": 2, "name": "Potion", "quantity": 10 }
       ]
     }
     ```
3. **Outline Classes**:
   - Potentially a `Database` or `StorageManager` class for I/O with JSON.
   - One or more “model” classes (e.g., `Item`, `User`, `Record`).
   - Possibly a “Controller” class to coordinate interactions.
4. **DRY Emphasis**:
   - Don’t replicate logic across multiple constructors or classes unnecessarily.
   - Plan to centralize repeated code in helper functions.

### Step 2: UML and Initial Class Design

1. **Draft UML**:
   - Introduce simple UML diagrams for:
     - Class relationships: which classes hold references to others?
     - Minimal attributes & methods per class.
   - Example snippet:
     - `Item` class with private attributes (id, name, quantity).
     - `Database` class with a method `loadFromFile(string filename)`, `saveToFile(...)`, etc.
2. **Decide on Access Modifiers**:
   - **private** for internal data (e.g., `id`, `quantity`).
   - **public** for essential methods (e.g., `createItem(...)`, `deleteItem(...)`).
   - Possibly **protected** if inheritance is truly warranted—but caution that we don’t force inheritance where composition might suffice.

### Step 3: JSON Library Selection & Setup

1. **Choose a JSON Parsing Library**:
   - Examples: [nlohmann/json](https://github.com/nlohmann/json) or [RapidJSON](https://github.com/Tencent/rapidjson).
2. **Test JSON I/O**:
   - Simple test to read a small JSON file and print data to confirm library usage.

### Step 4: Implement the Data Model (e.g., `Item` or `User` Class)

1. **Write Minimal Constructors**:
   - Possibly an empty constructor plus one that initializes from parameters.
   - Emphasize DRY if multiple constructors share logic—use a private `init(...)` function.
2. **Add JSON Conversion**:
   - A method `toJson()` returning a JSON object.
   - A method `fromJson(...)` that updates the object’s attributes.

### Step 5: Implement the Storage Manager / Database Class

1. **Loading from JSON**:
   - Method `loadFromFile(std::string filePath)` that reads JSON, populates an internal list/vector of items.
2. **Saving to JSON**:
   - Method `saveToFile(...)` that writes the current data model to disk.
3. **CRUD Methods**:
   - `createItem(...)`, `getItem(id)`, `updateItem(...)`, `deleteItem(id)`.

### Step 6: Testing & Demonstration

1. **Console-based UI**:
   - Simple main program that loads from a JSON file, lets user add/update/delete an item, then saves.
2. **Verify Data**:
   - Print list of items before and after an operation.

### Step 7: Reflection & Feedback

1. **Discuss**:
   - Did the design remain consistent with DRY and the chosen UML?
   - Could inheritance be replaced by composition in any place?
   - Are public/private divisions logical?

---

## Project Deliverables (for Students)

1. **Design Document** (First Milestone)

   - UML sketches for classes.
   - Written justification for each class and method.

2. **Implementation** (Second Milestone)

   - C++ source code with multiple classes (e.g., `Item`, `Database`).
   - Minimal usage of inheritance unless truly necessary.

3. **Demo / Test** (Final Milestone)
   - Simple console program showing you can load, create, update, delete, and save data to JSON.
   - Reflection paragraph on how design changed or improved during development.

---

## Additional Suggestions on Approach

1. **Modularize**:
   - Keep each class in its own `.hpp`/`.cpp` pair.
2. **Avoid Over-Engineering**:
   - Let’s not get stuck adding unnecessary inheritance. For instance, if `Item` and `User` share no logic, no need for a `BaseEntity`.
3. **Focus on DRY**:
   - Repeated constructor code? Use a private `init()` method.
   - Repeated JSON code? Possibly a helper function or a separate “JsonHelper” if it’s repeated across classes.
4. **Incremental Development**:
   - Start with reading JSON and building a minimal list of items.
   - Add writing to JSON once reading is stable.
   - Introduce CRUD operations step by step.

---

## Next Steps

- **Document** your proposed classes in a short UML or textual design doc.
- **Implement** a minimal data model and test reading/writing JSON.
- **Iterate** by adding CRUD logic, UI, and final polishing.

_(We can later generate more specific tasks, code skeletons, or additional clarifications as your students progress in each milestone.)_

# Mapping the Consumable Steps to Suggested Major Components

Below is a short guide explaining how each **consumable step** (from the project blueprint) relates to the **major components** of the C++ + JSON database project.

---

## Major Components (Recap)

1. **Data Model**

   - Classes representing entities (e.g., `Item`, `Record`, or `User`).
   - JSON-conversion methods (e.g., `toJson()`, `fromJson(...)`).

2. **Database / Storage Manager**

   - Handles I/O with JSON files (load/save).
   - Provides CRUD methods (create, read, update, delete).

3. **Application Logic**

   - Could be a “controller” that orchestrates user commands or programmatic calls to the database/storage manager.
   - Possibly includes some business logic or validation.

4. **Main Application**
   - Ties everything together (e.g., main function).
   - May include a console-based interface or minimal UI for demonstrations.

---

## Consumable Steps (Blueprint)

Here’s how each suggested step aligns with one or more major components.

1. **Requirements & Sketching (Design Phase)**

   - **Covers All Components**
   - You decide **what** classes you need (data model, manager, logic), plus the overall structure.
   - Brainstorming for data model (entities), high-level database class, and what the main app does.

2. **UML and Initial Class Design**

   - **Covers All Components**
   - UML diagrams show **relationships** between data classes, the storage manager, and the application logic.
   - This step ensures clarity on responsibilities (SRP, DRY) before coding.

3. **JSON Library Selection & Setup**

   - **Mostly Database/Storage Manager**
   - Affects how you’ll **load/save** the data.
   - Minimal effect on the data model or main app, but it’s critical for the database manager portion.

4. **Implement the Data Model**

   - **Data Model Component**
   - Build classes that represent the domain (e.g., `Item`, `User`, `Record`).
   - Add JSON-conversion methods in these classes or in small helper utilities, so they can be easily serialized/deserialized.

5. **Implement the Storage Manager / Database Class**

   - **Database / Storage Manager Component**
   - Actually read/write JSON to disk.
   - Provide `loadFromFile`, `saveToFile`, plus CRUD operations referencing the data model.

6. **Testing & Demonstration**

   - **Main Application & Possibly Application Logic**
   - The console-based program (or minimal UI) that shows how you can load data, create objects, update them, and save back to JSON.
   - Testing the synergy of all components.

7. **Reflection & Feedback**
   - **Covers All Components**
   - Evaluate whether the data model was well-structured.
   - Assess if the storage manager’s approach was correct.
   - Check if the main application or logic code is organized and adheres to DRY.

---

## Summary

- **Steps 1 & 2**: High-level design, applying to every component in terms of **planning**.
- **Step 3**: Primarily about **choosing JSON approach** for the storage manager.
- **Step 4**: Solely about the **Data Model** (entities, classes).
- **Step 5**: Specifically implements the **Database / Storage** logic.
- **Step 6**: Involves hooking up everything in the **Main Application** (plus any extra logic).
- **Step 7**: Reflection on design, code structure, and the synergy across **all components**.

By mapping each consumable step to the relevant components, students can develop the system incrementally while keeping track of the big picture.
