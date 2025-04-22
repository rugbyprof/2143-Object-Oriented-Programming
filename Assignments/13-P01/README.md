# Database Project - Using Json

### Due: TBD

Below is a **conceptual outline** of how one might structure a base JSON-DB class followed by some specialized child class examples tailored toward some of the data files [HERE](../../Resources/06-Data/)

The initial goal is to:

1. Implement a **generic** DB class (**Baseclass**) with CRUD operations that uses Json.
2. Extend the DB class (**Subclass**) to handle unique data shapes and behaviors.

---

## 1. Base Class: `JsonDB`

### Purpose

- Manage reading/writing JSON from a file.
- Provide generic Create, Read, Update, and Delete (CRUD) methods.
- Store data in-memory (e.g., in a list or dictionary) after loading.

<details>
<summary>Possible Class Stub</summary>

```python
class JsonDB:
    """
    Base class for a simple JSON "database."

    Attributes:
        filepath (str): Path to the JSON file on disk.
        data (any): The loaded JSON data (e.g., list, dict).
    """
    def __init__(self, filepath):
        """
        Initialize the DB with a path to the JSON file.
        """
        self.filepath = filepath
        self.data = None
        self._load_data()

    def _load_data(self):
        """
        Internal helper to load JSON data from the file into self.data.
        Handle exceptions and set self.data appropriately if file is missing/corrupted.
        """
        pass

    def _save_data(self):
        """
        Internal helper to save self.data back to the JSON file.
        """
        pass

    def create(self, record):
        """
        Insert a new record into self.data.
        'record' could be a dict or some structure that matches the data layout.
        Return the inserted record or some identifier.
        """
        pass

    def read(self, **filters):
        """
        Read/search the database.
        E.g., read(name="Teresa", city="Los Angeles") might filter by matching fields.
        Return a list of matching records or a single record.
        """
        pass

    def update(self, record_id, updated_data):
        """
        Update an existing record by some identifier.
        Return the updated record, or raise an error if not found.
        """
        pass

    def delete(self, record_id):
        """
        Remove a record by its identifier.
        Return the deleted record, or raise an error if not found.
        """
        pass
```

</details>

### Key Points to Discuss

- **Generic Handling of `self.data`:** It might be a list, dict, or nested structure.
- **Identifying Records:**
  - If the data is a list, you might use an index or a unique key in each record.
  - If it’s a dict of records keyed by IDs, you can directly use the keys.
- **Filtering** in `read()`: A simplistic approach is to loop over each record and check if it matches the filters.
- **Persistence**: `_save_data()` updates the JSON file each time you do a CRUD operation—or maybe only upon explicit “save.”

---

## 2. Subclass Example: `PeopleDB`

### Purpose

- Handle “user” objects (like in your Example 1).
- Provide convenience methods specific to “people” data: e.g., searching by name, city, or generating emails.

<details>
<summary>Possible Class Stub</summary>

```python
class PeopleDB(JsonDB):
    """
    Specialized DB class for handling 'user' records in JSON format.
    """
    def __init__(self, filepath):
        super().__init__(filepath)

    def find_by_name(self, first_name=None, last_name=None):
        """
        Convenience method to query people by first/last name.
        """
        # Possibly call self.read() or do custom logic here.
        pass

    def create_person(self, person_data):
        """
        A more domain-specific create method.
        Might validate the user structure, e.g., checking phone, SSN formats, etc.
        Then call self.create(...) from the base class.
        """
        pass

    # Optionally override or extend the base CRUD methods if needed
    # e.g., custom validation, special indexing, etc.
```

</details>

### Why Inheritance?

- **Domain-Specific Methods**: `find_by_name()`, `create_person()`, etc.
- **Validation**: If the “user” record has fields like SSN, phone, etc., you can validate them here before saving. This is specialized logic that wouldn’t make sense in the generic base class.

---

## 3. Subclass Example: `MeteoriteDB`

### Purpose

- Store meteorite data like `name`, `id`, `mass`, `location`, etc.
- Could have special queries like `find_heaviest_meteorites()` or `find_by_year_range()`.

<details>
<summary>Possible Class Stub</summary>

```python
class MeteoriteDB(JsonDB):
    """
    Specialized DB class for handling meteorite JSON records.
    """
    def __init__(self, filepath):
        super().__init__(filepath)

    def find_by_year_range(self, start_year, end_year):
        """
        Return meteorites that fall within [start_year, end_year].
        """
        pass

    def find_by_location(self, lat, lng, radius):
        """
        Potentially search for meteorites near a certain coordinate.
        """
        pass

    # Additional domain-specific logic (mass-based queries, etc.)
```

</details>

---

## 4. Subclass Example: `EarthquakeDB`

### Purpose

- Manage earthquake data from USGS or similar feeds.
- Could have methods like `filter_by_magnitude()`, `filter_by_place()`, or parse nested geometry.

<details>
<summary>Possible Class Stub</summary>

```python
class EarthquakeDB(JsonDB):
    """
    Specialized DB class for earthquake-related data.
    """
    def __init__(self, filepath):
        super().__init__(filepath)

    def filter_by_magnitude(self, min_mag, max_mag):
        """
        Return earthquakes with magnitude in [min_mag, max_mag].
        """
        pass

    def get_coordinates(self, quake_id):
        """
        Extract the 'geometry' -> 'coordinates' array for a given quake.
        """
        pass
```

</details>

---

## 5. Discussion Points and Ideas

1. **Why Subclass the DB?**

   - The generic `JsonDB` may suffice for basic CRUD. But each domain can have specialized queries, validation, or data transformations that belong in a subclass.

2. **Potential Overriding**

   - You might override `create()`, `update()`, or `read()` in the child if you want more robust logic (e.g., ensuring a meteorite record always has a valid year, etc.).

3. **Error Handling**

   - You can practice raising custom exceptions if a record is invalid or if an ID doesn’t exist.

4. **Extensibility**

   - Another student might build `InventoryDB` or `CustomerDB` from the same base class.

5. **Advanced**:
   - Keep track of “dirty” states to avoid rewriting the file on every small operation.
   - Use a context manager pattern: `with PeopleDB(...) as db:` that automatically saves on exit.
   - Potential concurrency or file-locking issues if multiple processes read/write simultaneously (beyond the scope of most sophomore courses, but still good to mention).

---

## 6. Sample Usage Flow

```python
def main():
    # Base usage:
    db = JsonDB("path/to/generic.json")
    all_data = db.read()
    new_record_id = db.create({"some": "record"})
    db.update(new_record_id, {"some": "updated_value"})
    db.delete(new_record_id)

    # Specialized usage:
    people_db = PeopleDB("path/to/people.json")
    found = people_db.find_by_name(first_name="Teresa")
    if found:
        print("Found person:", found)

    meteor_db = MeteoriteDB("path/to/meteorites.json")
    heavy_rocks = meteor_db.find_by_year_range(1900, 1956)
    # etc.

if __name__ == "__main__":
    main()
```

This final snippet shows how you might incorporate the base and child classes in an actual script.

---

### Final Thoughts

By **forcing** a difference between the **generic** JSON DB (handles universal CRUD) and the **specialized** child class (handles domain-specific queries/validation), we create a **practical** reason for inheritance, even if the example is a little contrived. This is am exercise to compare a “simple” approach (**a single** flexible DB class) vs. an OOP approach (**base class w/ sub class**) where domain logic is extended in child classes.
