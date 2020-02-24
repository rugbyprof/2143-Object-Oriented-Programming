#!/usr/bin/python3

import requests
from bs4 import BeautifulSoup
import os,sys
import subprocess
import pypandoc


links = [("/uml-diagrams.html" , "What are UML Diagrams"),
("/uml-notation-symbol.html" , "UML Notation Tutorial"),
("/uml-relationships-with-example.html" , "UML Relationships"),
("/association-aggregation-composition-difference.html" , "UML Association vs Aggregation vs Composition"),
("/uml-class-diagram.html" , "UML Class Diagram"),
("/uml-object-diagram.html" , "What is UML Object Diagram?"),
("/use-case-diagrams-example.html" , "UML Use Case Diagram"),
("/state-machine-transition-diagram.html" , "State Machine Diagram UML"),
("/uml-activity-diagram.html" , "UML Activity Diagram"),
("/interaction-collaboration-sequence-diagrams-examples.html" , "Interaction, Collaboration, Sequence Diagrams"),
("/component-diagram-uml-example.html" , "Component Diagram UML"),
("/deployment-diagram-uml-example.html" , "Deployment Diagram UML"),
("/best-uml-tools.html" , "BEST UML Tools"),
("/uml-tutorial-pdf.html" , "UML Tutorial PDF")]

domain = "https://www.guru99.com"

for link,title in links:

    url = domain+link

    title = title.replace(' ','_')
    
    print(url)
    
    page = requests.get(url)

    soup = BeautifulSoup(page.content, 'html.parser')

    article = soup.find('div', class_='item-page')

    
    if len(article) > 0:
        f = open("buff.html","w")
        article = str(article)

        article = article.replace('src="','src="https://www.guru99.com')
        
        f.write(article)

        f.close()

        outfile = "./pages/"+title+".md"

        image="./images"
        
        pandoc = [
            "pandoc",
            "--log=log.log" ,
            "buff.html", 
            "-t", "gfm",
            "--extract-media="+image ,
            "-o", outfile
        ]

        subprocess.run(pandoc)

    
    

    