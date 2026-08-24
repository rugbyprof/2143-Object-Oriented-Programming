---
title: "C++ JSON CRUD Tutorial using nlohmann::json"
description: "A small tutorial on performing basic CRUD operations on a JSON file using nlohmann::json, with examples based on a candy store dataset."
---

Below is a compact tutorial that demonstrates how to use the popular nlohmann::json library for C++ to perform basic CRUD operations on a JSON file. In our examples, we use a simplified version of the candy store JSON data.

> Note: For this tutorial, we assume you have the nlohmann::json library installed (either via single header inclusion or using your package manager).

## 1. Setup

Include the header file in your C++ source:

```cpp
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <vector>

// For convenience
using json = nlohmann::json;
using namespace std;
```

## 2. Reading JSON Data

Assume your JSON file (e.g., candy_store.json) contains multiple candy items. In a real-world scenario, you might have the data in an array. For example, here’s a simplified JSON array:

```json
[
  {
    "id": 1,
    "price": "$19.49",
    "category": "individually-wrapped",
    "title": "Gourmet Salt Water Taffy - 5lb",
    "imagetype": "jpg"
  },
  {
    "id": 2,
    "price": "$15.99",
    "category": "individually-wrapped",
    "title": "Key Lime Pie Hard Candy - 5lb",
    "imagetype": "jpg"
  }
  // ... additional items ...
]
```

Read the JSON file into a json object:

```cpp
json readJsonFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        exit(1);
    }
    json j;
    file >> j;
    return j;
}
```

## 3. CRUD Operations

### a. Create (Add a New Candy Item)

```cpp
void createItem(json& j, const json& newItem) {
    // Assuming the JSON file is an array of objects
    j.push_back(newItem);
}
```

**Usage:**

```cpp
json newCandy = {
    {"id", 999},
    {"price", "$12.99"},
    {"category", "gummy"},
    {"title", "New Gummy Candy - 5lb"},
    {"imagetype", "jpg"}
};

json candyStore = readJsonFromFile("candy_store.json");
createItem(candyStore, newCandy);
```

### b. Read (Query an Item by ID)

```cpp
json readItemById(const json& j, int id) {
    for (const auto& item : j) {
        if (item["id"] == id)
            return item;
    }
    return nullptr; // or throw an exception
}
```

**Usage:**

```cpp
json candyItem = readItemById(candyStore, 2);
if (!candyItem.is_null()) {
    cout << "Found item: " << candyItem.dump(4) << endl;
} else {
    cout << "Item not found." << endl;
}
```

### c. Update (Modify an Existing Item)

```cpp
bool updateItemById(json& j, int id, const json& updatedFields) {
    for (auto& item : j) {
        if (item["id"] == id) {
            // Merge updated fields
            for (json::const_iterator it = updatedFields.begin(); it != updatedFields.end(); ++it) {
                item[it.key()] = it.value();
            }
            return true;
        }
    }
    return false;
}
```

**Usage:**

```cpp
json updateData = {
    {"price", "$17.99"},
    {"title", "Key Lime Pie Hard Candy - Updated Price"}
};

if (updateItemById(candyStore, 2, updateData)) {
    cout << "Item updated successfully." << endl;
} else {
    cout << "Item not found." << endl;
}
```

### d. Delete (Remove an Item by ID)

```cpp
bool deleteItemById(json& j, int id) {
    for (auto it = j.begin(); it != j.end(); ++it) {
        if ((*it)["id"] == id) {
            j.erase(it);
            return true;
        }
    }
    return false;
}
```

**Usage:**

```cpp
if (deleteItemById(candyStore, 1)) {
    cout << "Item deleted successfully." << endl;
} else {
    cout << "Item not found." << endl;
}
```

## 4. Writing Back to the File

After making your CRUD modifications, you may want to save the JSON back to the file:

```cpp
void writeJsonToFile(const json& j, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        exit(1);
    }
    file << j.dump(4); // Pretty print with an indent of 4 spaces
}
```

**Usage:**

```cpp
writeJsonToFile(candyStore, "candy_store.json");
```

## 5. Putting It All Together

Here’s a small main function that demonstrates reading, performing a CRUD operation, and writing back the JSON:

```cpp
int main() {
    // Read JSON file
    json candyStore = readJsonFromFile("candy_store.json");

    // Create: Add a new candy item
    json newCandy = {
        {"id", 999},
        {"price", "$12.99"},
        {"category", "gummy"},
        {"title", "New Gummy Candy - 5lb"},
        {"imagetype", "jpg"}
    };
    createItem(candyStore, newCandy);

    // Read: Get a candy by id
    json candyItem = readItemById(candyStore, 2);
    if (!candyItem.is_null()) {
        cout << "Item with id 2:" << endl;
        cout << candyItem.dump(4) << endl;
    }

    // Update: Change the price of the candy with id 2
    json updateData = {
        {"price", "$17.99"},
        {"title", "Key Lime Pie Hard Candy - Updated Price"}
    };
    if (updateItemById(candyStore, 2, updateData)) {
        cout << "Item updated successfully." << endl;
    } else {
        cout << "Item not found." << endl;
    }

    // Delete: Remove candy item with id 1
    if (deleteItemById(candyStore, 1)) {
        cout << "Item deleted successfully." << endl;
    } else {
        cout << "Item not found." << endl;
    }

    // Write changes back to file
    writeJsonToFile(candyStore, "candy_store.json");

    return 0;
}
```

This tutorial covers the basics of reading a JSON file, performing CRUD operations, and writing back the updated data using nlohmann’s JSON library. You can extend this example as needed for our project.
