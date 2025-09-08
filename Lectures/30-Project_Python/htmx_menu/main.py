from fastapi import FastAPI, Request, Form
from fastapi.responses import HTMLResponse, RedirectResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
import json, os
from uuid import uuid4

app = FastAPI()
templates = Jinja2Templates(directory="templates")
DATA_PATH = "data/db.json"

app.mount("/static", StaticFiles(directory="static"), name="static")


def load_db():
    if not os.path.exists(DATA_PATH):
        return []
    with open(DATA_PATH, "r") as f:
        return json.load(f)


def save_db(data):
    with open(DATA_PATH, "w") as f:
        json.dump(data, f, indent=2)


@app.get("/", response_class=HTMLResponse)
async def home(request: Request):
    return templates.TemplateResponse(
        "index.html", {"request": request, "items": load_db()}
    )


@app.post("/create", response_class=HTMLResponse)
async def create(request: Request, name: str = Form(...), value: str = Form(...)):
    db = load_db()
    db.append({"id": str(uuid4()), "name": name, "value": value})
    save_db(db)
    return templates.TemplateResponse(
        "partials/item_list.html", {"request": request, "items": db}
    )


if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="127.0.0.1", port=8080)
