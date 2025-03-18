# DB Manager - Using Nlohmann's json lib in C++

#### Due: Multiple Dates

## Overview

In this assignment, you will design and implement a small **database manager** using JSON files as the underlying storage mechanism. You will create a simple class structure (based on your own UML design) to perform CRUD (Create, Read, Update, Delete) operations on the data. By the end of this assignment, you should have:

1. A **UML Class Diagram** showing your proposed design.
2. A **C++ implementation** that uses the [nlohmann/json](https://github.com/nlohmann/json) library to manage a JSON “database.”

Although the specific domain of the data is up to you, **candies** or similar straightforward data (e.g., items in a store) are good references since they’re easy to conceptualize.

---

## Objectives

1. **Practice UML Design**

   - Identify classes, their relationships, and major responsibilities.

2. **Use JSON for Data Persistence**

   - Store data in a JSON file.
   - Implement reading, writing, and modifying the JSON file.

3. **Demonstrate OOP Principles**

   - Encapsulation: Keep class responsibilities separate (e.g., a database manager class vs. a model class).
   - Abstraction: Provide methods to interact with the data without exposing internal details.
   - Potential use of **inheritance** and/or **composition** if it makes sense in your design.

4. **Perform CRUD Operations**
   - **Create**: Add new items to your “database” file.
   - **Read**: Retrieve and display specific items (or list them all).
   - **Update**: Modify existing items.
   - **Delete**: Remove items from the file.

---

## Part 1: UML Class Diagram

Before writing any code, design your class structure in UML. Your diagram should include:

- **Classes**
  - Example: `Candy`, `CandyManager`, `JSONDBManager`, etc.
- **Relationships**
  - Indicate if classes have a _composition_ or _aggregation_ relationship.
  - Show which classes might inherit from a base class, if applicable.
- **Attributes**
  - For instance, a `Candy` class might have `id`, `price`, `category`, `title`, etc.
- **Methods**
  - For a JSON database manager, you’ll likely have methods like `load()`, `save()`, `addItem()`, `getItem()`, `updateItem()`, and `deleteItem()`.

Here’s a **text-based UML** snippet as an example (feel free to adapt or create your own style):

### Example Text-Based UML

```txt
+—————–+
|     Candy       |
+—————–+
| - id: int       |
| - price: string |
| - category: … |
| - title: …    |
| - imagetype:… |
+—————–+
| + setters/getters
| + constructor(…)
| + toJSON(): json
+—————–+

+———————–+
|     JSONDBManager     |
+———————–+
| - filename: string    |
| - data: json          |
+———————–+
| + load(): void        |
| + save(): void        |
| + addItem(…): bool  |
| + getItem(…): Candy |
| + updateItem(…):bool|
| + deleteItem(…):bool|
+———————–+

+––––––––––+
|    CandyManager    |
+––––––––––+
| - dbManager: JSONDBManager
+––––––––––+
| + createCandy(…): bool
| + readCandy(id): Candy
| + updateCandy(id,…): bool
| + deleteCandy(id): bool
| + listAllCandies(): void
+––––––––––+
```

You can create your UML in a diagramming tool or simply draw it on paper and scan it. The key is to clarify **what** classes exist, **how** they interact, and **why**.

---

## Part 2: Implementation Details

### 2.1 Project Setup

1. **Add nlohmann/json**

   - Include `json.hpp` in your project.
   - Make sure your compiler can find the header (e.g., in the same directory or via CMake).

2. **Create Your Classes**

   - Each class in the UML corresponds to a `.hpp/.cpp` pair (unless you’re doing header-only).

3. **Candy Class (Model Layer)**

   - Represents a candy object with attributes like `id`, `price`, `category`, `title`, and `imagetype`.
   - Implement convenient constructors, getters/setters, and possibly a `toJSON()` or `fromJSON()` method for easier serialization/deserialization.

4. **JSONDBManager Class**

   - Responsible for loading and saving JSON from/to a file.
   - Maintains a `json data` structure in memory.
   - Provides **CRUD** helper methods that operate directly on the JSON data.

5. **CandyManager (Higher-Level Interface)**
   - Uses `JSONDBManager` to manipulate Candy objects.
   - Handles any domain-specific logic (e.g., ensuring no duplicate IDs).
   - Exposes methods like `createCandy()`, `readCandy()`, `updateCandy()`, `deleteCandy()`, and `listAllCandies()`.

### 2.2 Example Flow

1. **Initialization**

   - `CandyManager` instantiates a `JSONDBManager`, specifying the filename of the JSON file.
   - `JSONDBManager` tries to load the file into memory.

2. **Create**

   - `CandyManager::createCandy(...)` constructs a `Candy` object, then calls `JSONDBManager::addItem(...)` with the candy’s JSON data.

3. **Read**

   - `CandyManager::readCandy(id)` calls `JSONDBManager::getItem(id)`, converts the resulting JSON back into a `Candy` object.

4. **Update**

   - `CandyManager::updateCandy(id, ...)` modifies a candy’s data by calling `JSONDBManager::updateItem(...)`.

5. **Delete**

   - `CandyManager::deleteCandy(id)` calls `JSONDBManager::deleteItem(id)`.

6. **Listing**
   - `CandyManager::listAllCandies()` might fetch all items from `JSONDBManager` and iterate through them, printing out details.

### 2.3 Sample Code Structure

```cpp
// Candy.hpp
#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Candy {
private:
    int id;
    std::string price;
    std::string category;
    std::string title;
    std::string imagetype;

public:
    // Constructors, getters, setters...
    nlohmann::json toJSON() const {
        return nlohmann::json{
            {"id", id},
            {"price", price},
            {"category", category},
            {"title", title},
            {"imagetype", imagetype}
        };
    }

    // static fromJSON(...) method is optional if you prefer constructing from JSON
};

// JSONDBManager.hpp
#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class JSONDBManager {
private:
    std::string filename;
    nlohmann::json data;

public:
    JSONDBManager(const std::string& file);
    void load();
    void save() const;

    bool addItem(const nlohmann::json& itemJSON);
    nlohmann::json getItem(int id) const;
    bool updateItem(int id, const nlohmann::json& updatedFields);
    bool deleteItem(int id);
    std::vector<nlohmann::json> getAllItems() const;
};
```

## Part 3: Your Task

1. Create a Detailed UML:
   - Identify the classes and methods you’ll need based on the snippet above (or your own design).
2. Implement Your Classes in C++:
   - Candy (or a different model if you prefer).
   - JSONDBManager.
   - CandyManager (or your manager class of choice).
3. Demonstrate CRUD Operations in main():
   - Load the JSON file.
   - Create a new candy item.
   - Read a candy item (by ID) and print it.
   - Update an existing candy’s price/title.
   - Delete a candy item.
   - Print a list of all candies.
4. Write a Short Report:
   - Summarize your UML design decisions.
   - Show sample inputs/outputs.
   - Discuss any edge cases (e.g., non-existent IDs, empty JSON, etc.).

## Tips & Suggestions

- Error Handling:
- Decide what to do if a file fails to open or an ID doesn’t exist.
- Multiple Models:
- If you want to expand, consider classes like Customer, Order, etc.
- Testing:
- Test each CRUD method thoroughly before moving on.

## Submission

- Create a folder called P01 in your assignments folder.
- Includer the following documents in your project upload:
  1. UML Diagram (PDF or image file).
  2. Source Code (header/source files and main.cpp).
  3. Short Report documenting your approach, testing, and any notable design decisions (README file).
