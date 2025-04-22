from pathlib import Path
import json
from fastapi import FastAPI, Request
from fastapi.responses import HTMLResponse, RedirectResponse
from fastapi.templating import Jinja2Templates
from rich import print, print_json


DATA_FILE = Path(__file__).with_name("world_cities.json")
PAGE_SIZE = 25

CITIES = []
# preload dataset once
with DATA_FILE.open() as f:
    data = json.load(f)  # list[dict]

for country, list in data.items():
    for item in list:
        CITIES.append(item)


app = FastAPI()
templates = Jinja2Templates(directory="templates")


# ───────────────────────────────
# helpers
# ───────────────────────────────
def slice_page(page: int, *, sort_key="city-name"):
    start = (page - 1) * PAGE_SIZE
    end = start + PAGE_SIZE
    return sorted(CITIES, key=lambda c: c[sort_key])[start:end]


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


# ───────────────────────────────
# routes
# ───────────────────────────────


# ─────────────────────────────────────────
# 2.  “/index”  →  your normal home page
# ─────────────────────────────────────────
@app.get("/index", response_class=HTMLResponse)
def index(request: Request):
    """
    Render whatever you consider your ‘home’ template.
    """
    page1 = slice_page(1)
    return templates.TemplateResponse(
        "index.html", {"request": request, "cities": page1, "page": 1}
    )


# @app.get("/", response_class=HTMLResponse)
# def index(request: Request):
#     page1 = slice_page(1)
#     return templates.TemplateResponse(
#         "index.html", {"request": request, "cities": page1, "page": 1}
#     )


# @app.get("/page/{page}", response_class=HTMLResponse)
# def page(request: Request, page: int):
#     rows = slice_page(page)
#     return templates.TemplateResponse(  # return ONLY the tbody fragment
#         "_rows.html", {"request": request, "cities": rows}
#     )


@app.get("/page/{page}", response_class=HTMLResponse)
def page(request: Request, page: int):
    rows = slice_page(page)
    return templates.TemplateResponse(
        "_rows.html", {"request": request, "cities": rows, "page": page}
    )


@app.get("/city/{city}", response_class=HTMLResponse)
def city(request: Request, city: str):
    # find the city in the dataset
    for item in CITIES:
        if item["city"] == city:
            break
    else:
        return templates.TemplateResponse(
            "404.html", {"request": request, "city": city}
        )

    return templates.TemplateResponse("city.html", {"request": request, "city": item})


if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="127.0.0.1", port=8000)
