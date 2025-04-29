import json
from rich import print


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
        self.current = 0

    def _load_data(self):
        """
        Internal helper to load JSON data from the file into self.data.
        Handle exceptions and set self.data appropriately if file is missing/corrupted.
        """
        with open(self.filepath) as f:
            self.data = json.load(f)

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

    def atEnd(self):
        """
        Testing to see if we are at the end of the data.
        Return True if we are at the end, False otherwise.
        """
        return self.current == len(self.data) - 1

    def getNext(self):
        record = self.data[self.current]
        self.current += 1
        if self.current >= len(self.data):
            self.current = 0
        return record

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


if __name__ == "__main__":

    # dbptr = JsonDB("./quotes_all.json")
    db = JsonDB("../../Resources/06-Data/quotes/quotes_all.json")

    # print(db.data)

    # while not db.atEnd():
    #     record = db.getNext()
    #     print(record)
    #     print()

    records = db.read(author="Yogi Berra")
    print(records)

    records = db.read(keyword="life")
    print(records)
