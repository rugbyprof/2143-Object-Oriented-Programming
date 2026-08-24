---
title: "Data Sets Collection"
description: "A curated and growing collection of real-world datasets in various formats for practice, experimentation, and project inspiration."
category: "resource"
tags: ["data", "csv", "json", "geojson", "ascii", "datasets"]
slug: "datasets"
order: 3
visibility: "public"
---

# Data Sets Collection

This folder contains a **growing archive** of real-world datasets used across assignments, projects, and spontaneous experiments. The data here is _never pruned_ — because sometimes creativity is sparked by stumbling across the perfect data. Students are encouraged to browse, explore, and even build projects around anything they find here.

## 🧠 Why So Much Data?

Because you can’t write interesting programs using ten integers and a dream.

Working with actual data — messy, inconsistent, and voluminous — is how you build real-world skills. It also helps you think about:

- Error handling
- Input/output formatting
- Scalability
- File structure and naming conventions
- How data is _stored_ vs how it's _used_

## 🔍 What Formats Will You Find?

You'll encounter a variety of ASCII-friendly formats, each with their own quirks and strengths:

### 1. **CSV (Comma-Separated Values)**

- Format: `name,age,score`
- Use: Widely supported by spreadsheets and scripts.
- Notes: Watch for commas **inside** values — quotes may be used to wrap such fields.

### 2. **TSV (Tab-Separated Values)**

- Format: `name<TAB>age<TAB>score`
- Use: More robust than CSV when commas appear in the data.
- Notes: Can be opened in Excel, but often used in command-line tools like `awk` or `cut`.

### 3. **JSON (JavaScript Object Notation)**

- Format: Structured data as key-value pairs.
- Use: Great for nested data, used in most modern APIs.
- Notes: Not ideal for line-by-line streaming or super-large files without preprocessing.

### 4. **GeoJSON**

- Format: JSON-based format for geospatial data (points, lines, polygons).
- Use: Mapping, GIS tools, browser-based visualizations.
- Notes: Requires understanding of geographic coordinates and shape structures.

### 5. **Plaintext Files & Logs**

- Files like `quotes_all.json` or `random_people.10000.json` are large enough to feel realistic.
- Other files (like `.cpp`, `.py`) are included when used to generate or process data.

## 📁 Organization

The datasets are loosely organized by topic or format:

- `earthquakes/` – time-series seismic data
- `quotes/` – JSON collections of quotations
- `world_people/` – same data in `.csv`, `.json`, and a small C++ parser
- `meteorites_export.json`, `ufo_*.geojson` – interesting, publicly available datasets
- `dictionary_20mb.json` – big enough to stress-test loading and parsing logic

## 💡 For Students

- Use these datasets in your own experiments or side projects.
- Compare formats: Load the same data from `.csv` and `.json`, and observe parsing differences.
- If you write something cool using this data — **share it**!

> Real-world programs don’t start with toy input. They start with a file that’s too big, too weird, and too interesting to ignore.

---

_Last updated automatically when Terry finds another irresistible dataset._
