import requests
from bs4 import BeautifulSoup
import shutil
import os
import time
import json
from rich import print
import sys


def validateJSON(jsonData):
    try:
        json.loads(jsonData)
    except ValueError as err:
        return False
    return True


def saveImgFlipHtml():
    r = requests.get("https://imgflip.com/memegenerator/")

    with open("imgflip.html", "w") as f:
        f.write(r.text)


def scrapeMemesMethod1():
    with open("imgflip.html") as f:
        html_doc = f.read()

    soup = BeautifulSoup(html_doc, "html.parser")

    imgs = soup.find("div", id="mm-select-popular")

    memeNames = imgs.find_all("div", class_="im")

    baseurl = "https://imgflip.com/s/meme/"

    for meme in memeNames:
        print(meme["alt"])
        altText = meme["alt"].replace(" ", "-")[:-5]
        saveImg("./memes", f"{baseurl}{altText}.jpg")
        time.sleep(0.5)


def scrapeMemesMethod2():
    with open("imgflip.html") as f:
        html_doc = f.read()

    soup = BeautifulSoup(html_doc, "html.parser")

    scripts = soup.find_all("script")
    jsonData = None

    for script in scripts:
        if "usermemeID=0;" in script.text:
            jsonData = script.text
            jsonData = jsonData.replace("\\", "")
            jsonData = jsonData.replace("\r", "").replace("\n", "")
            jsonData = jsonData.replace('"[', "[")
            jsonData = jsonData.replace(']"', "]")
            print(jsonData)
            sys.exit()

    if jsonData and validateJSON(jsonData):
        jsonData = json.loads(jsonData)
        print(jsonData.keys())


def saveMemesMethod3():
    with open("imageInfo.json") as f:
        jsonData = json.load(f)

    with open("imageInfo2.json", "w") as f:
        json.dump(jsonData, f, indent=4, sort_keys=True)

    with open("imageInfo2.json") as f:
        jsonData = json.load(f)

    print(jsonData.keys())


def saveImg(folder, url):
    """
    url = 'http://example.com/img.png'
    response = requests.get(url, stream=True)
    with open('img.png', 'wb') as out_file:
        shutil.copyfileobj(response.raw, out_file)
    del response
    """
    response = requests.get(url, stream=True)
    fileName = os.path.basename(url)
    savePath = os.path.join(folder, fileName)
    with open(savePath, "wb") as out_file:
        shutil.copyfileobj(response.raw, out_file)
    del response
    if os.path.exists(savePath):
        print("success")
    else:
        print("failed")


if __name__ == "__main__":
    # scrapeMemesMethod1()
    # scrapeMemesMethod2()
    saveMemesMethod3()
