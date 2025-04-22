from pathlib import Path
import json
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse, RedirectResponse
from fastapi.templating import Jinja2Templates
from rich import print, print_json


DATA_FILE = Path(__file__).with_name("world_cities.json")
PAGE_SIZE = 25

CITIES = []
COUNTRIES = {}
# preload dataset once
with DATA_FILE.open() as f:
    data = json.load(f)  # list[dict]

i = 0
for country, list in data.items():
    COUNTRIES[country] = 0
    for item in list:
        item["id"] = i
        i += 1
        CITIES.append(item)

print(COUNTRIES.keys())


app = FastAPI()


# ───────────────────────────────
# helpers
# ───────────────────────────────
def slice_page(page: int, *, sort_key="city-name"):
    start = (page - 1) * PAGE_SIZE
    end = start + PAGE_SIZE
    return sorted(CITIES, key=lambda c: c[sort_key])[start:end]


# ───────────────────────────────
# routes
# ───────────────────────────────


# ─────────────────────────────────────────
# 1.  “/”  →  Swagger /docs
# ─────────────────────────────────────────
@app.get("/", include_in_schema=False)
def root():
    """
    Hitting http://localhost:8000 (no path) will *redirect*
    the browser to the automatically generated Swagger UI at /docs.
    """
    return RedirectResponse(url="/docs")


# ─────────────────────────────────────────
# 2.  “/index”  →  your normal home page
# ─────────────────────────────────────────
@app.get("/getAll")
def getAll(page: int = 1):
    """
    ## Description: Gets all the cities in the dataset.
    ## Returns: A list of dictionaries, each representing a city.
    ## Example: [{"city": "New York", "country": "USA"}, {"city": "Tokyo", "country": "Japan"}]
    """
    return slice_page(page, sort_key="id")


@app.get("/search")
def getAll(city: str = None):
    """
    ## Description: Gets all the cities in the dataset.
    ## Returns: A list of dictionaries, each representing a city.
    ## Example: [{"city": "New York", "country": "USA"}, {"city": "Tokyo", "country": "Japan"}]
    """
    for item in CITIES:
        if item["city-name"].lower() == city.lower():
            return item


@app.get("/countries}")
def countries():
    """
    ## Description: Gets all the countries in the dataset.
    ## Returns: A list of dictionaries, each representing a country.
    ## Example: [{"country": "USA", "cities": 100}, {"country": "Japan", "cities": 50}]
    """
    codes = []
    for k, v in COUNTRIES.items():
        codes.append(k)
    return codes


@app.post("/city")
def city(city: str, country: str):
    """
    ## Description: Gets a specific city from the dataset.
    ## Returns: A dictionary representing the city.
    ## Example: {"city": "New York", "country": "USA"}
    """
    CITIES.append(
        {"city": city, "country": country, "id": len(CITIES), "lat": 0.0, "lon": 0.0}
    )


# @app.get("/city/{city}", response_class=HTMLResponse)
# def city(request: Request, city: str):
#     # find the city in the dataset
#     for item in CITIES:
#         if item["city"] == city:
#             break
#     else:
#         return templates.TemplateResponse(
#             "404.html", {"request": request, "city": city}
#         )

#     return templates.TemplateResponse("city.html", {"request": request, "city": item})


if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="127.0.0.1", port=8080)
