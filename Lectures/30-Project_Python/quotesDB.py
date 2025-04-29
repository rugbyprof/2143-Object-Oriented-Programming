from jsonDB import JsonDB
from rich import print


class QuotesDB(JsonDB):
    """
    QuotesDB is a subclass of JsonDB that provides additional functionality
    for managing a collection of quotes.
    """

    def __init__(self, filepath):
        """
        Initialize the QuotesDB with a path to the JSON file.
        """
        super().__init__(filepath)
        self.current = 0
        self._load_data()
        self._save_data()

    def read(self, **filters):
        author = filters.get("author", None)
        keyword = filters.get("keyword", None)

        records = []
        quotes = {}

        if author:
            # records = [record for record in self.data if record["author"] == author]

            i = 0
            for record in self.data:
                if record["Author"].lower() == author.lower():
                    records.append({"id": i, "record": record})
                i += 1
        elif keyword:
            # records = [record for record in self.data if keyword in record["text"]]
            i = 0
            for record in self.data:
                if keyword.lower() in record["Quote"].lower():
                    if record["Quote"] not in quotes:
                        quotes[record["Quote"]] = 1
                        records.append({"id": i, "record": record})
                i += 1

        return records


if __name__ == "__main__":
    db = QuotesDB("quotes_all.json")

    data = db.read(author="Pearl Buck")
    print(data)
