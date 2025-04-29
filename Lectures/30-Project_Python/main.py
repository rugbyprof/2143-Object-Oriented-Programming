from quotesDB import QuotesDB
from rich import print

if __name__ == "__main__":
    db = QuotesDB("quotes_all.json")

    data = db.read(author="Pearl Buck")
    print(data)
