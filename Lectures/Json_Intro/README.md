---
title: "Introduction to JSON and Using nlohmann::json in C++"
description: "An introductory document on JSON and how to use the nlohmann::json library in C++ for common CRUD operations, using candy store data as an example."
---

## Introduction to JSON

JSON (JavaScript Object Notation) is a lightweight data-interchange format that is easy for humans to read and write and easy for machines to parse and generate. It is language-independent but uses conventions familiar to programmers of the C-family of languages, making it a popular choice for data storage, configuration files, and web APIs.

### JSON Basics

A JSON object is a collection of key/value pairs. Here’s an example using candy store data:

```json
{
  "id": 18,
  "price": "$19.99",
  "category": "individually-wrapped",
  "title": "Peppermint Twists Mints",
  "imagetype": "jpg"
}
```

This snippet shows:
- **Keys**: "id", "price", "category", "title", "imagetype"
- **Values**: A mix of numbers and strings.

Multiple objects can be stored in a JSON array:

```json
[
  {
    "id": 18,
    "price": "$19.99",
    "category": "individually-wrapped",
    "title": "Peppermint Twists Mints",
    "imagetype": "jpg"
  },
  {
    "id": 19,
    "price": "$15.99",
    "category": "individually-wrapped",
    "title": "Spearmint Starlight Mints",
    "imagetype": "jpg"
  }
]

### Why Use JSON?

Using JSON offers several advantages:
- **Readability**: The format is clean and human-readable.
- **Flexibility**: It can easily represent complex nested data.
- **Language Agnostic**: Nearly every modern programming language includes libraries for working with JSON.
- **Interoperability**: JSON is widely used for configuration files, web services, and data interchange.

In C++, dealing with JSON manually (parsing, formatting, etc.) can be tedious. That’s where libraries like nlohmann::json shine by providing a simple, intuitive interface to work with JSON.

### Using nlohmann::json in C++

The nlohmann::json library is a single-header JSON parser and generator for C++ that makes it very easy to work with JSON data. Let’s see how to use it in a few common scenarios, including basic CRUD operations, using our candy store example.

- Setup
1.	Installation:
- Download the single header file json.hpp from the nlohmann/json GitHub repository and include it in your project.
2.	Including the Library:

```cpp
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;
using namespace std;
```

### CRUD Operations with JSON

Assume we have a JSON file named candy_store.json containing an array of candy items similar to the snippet below:

```json
[
  {
    "id": 18,
    "price": "$19.99",
    "category": "individually-wrapped",
    "title": "Peppermint Twists Mints",
    "imagetype": "jpg"
  },
  {
    "id": 19,
    "price": "$15.99",
    "category": "individually-wrapped",
    "title": "Spearmint Starlight Mints",
    "imagetype": "jpg"
  }
]
```

Below are examples of basic CRUD operations.

### 1. Reading JSON Data

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
### 2. Creating (Adding) an Item

Add a new candy item to the JSON array:

```cpp
void createItem(json& j, const json& newItem) {
    // Assuming the JSON file is an array of objects
    j.push_back(newItem);
}

// Usage:
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

### 3. Reading (Querying) an Item

Query for an item by its id:

```cpp
json readItemById(const json& j, int id) {
    for (const auto& item : j) {
        if (item["id"] == id)
            return item;
    }
    return nullptr; // Item not found
}

// Usage:
json candyItem = readItemById(candyStore, 18);
if (!candyItem.is_null()) {
    cout << "Found item:\n" << candyItem.dump(4) << endl;
} else {
    cout << "Item not found." << endl;
}
```

### 4. Updating an Item

Modify an existing item by merging updated fields:

bool updateItemById(json& j, int id, const json& updatedFields) {
    for (auto& item : j) {
        if (item["id"] == id) {
            // Update each field present in updatedFields
            for (json::const_iterator it = updatedFields.begin(); it != updatedFields.end(); ++it) {
                item[it.key()] = it.value();
            }
            return true;
        }
    }
    return false;
}

// Usage:
json updateData = {
    {"price", "$17.99"},
    {"title", "Peppermint Twists Mints - Updated"}
};

if (updateItemById(candyStore, 18, updateData)) {
    cout << "Item updated successfully." << endl;
} else {
    cout << "Item not found." << endl;
}

5. Deleting an Item

Remove an item by its id:

bool deleteItemById(json& j, int id) {
    for (auto it = j.begin(); it != j.end(); ++it) {
        if ((*it)["id"] == id) {
            j.erase(it);
            return true;
        }
    }
    return false;
}

// Usage:
if (deleteItemById(candyStore, 19)) {
    cout << "Item deleted successfully." << endl;
} else {
    cout << "Item not found." << endl;
}

6. Writing JSON Data Back to a File

After performing CRUD operations, save your changes back to the file:

void writeJsonToFile(const json& j, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        exit(1);
    }
    file << j.dump(4); // Pretty print with an indent of 4 spaces
}

// Usage:
writeJsonToFile(candyStore, "candy_store.json");

Summary

Using JSON with C++ becomes very convenient with libraries like nlohmann::json. This tutorial covered:
- Introduction to JSON: Its syntax and common use cases.
- CRUD Operations: How to create, read, update, and delete JSON objects.
- File Operations: Reading from and writing to a JSON file.

These examples demonstrate the simplicity and power of nlohmann’s library to manage JSON data—making it easier to work with complex data structures and eliminate many of the typical programming hassles related to manual parsing.

Feel free to experiment with the examples and extend them to suit your projects. Let me know if you have any questions or need further clarification!