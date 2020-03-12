#!/usr/local/opt/python@3.8/bin/python3
import json
import os
import random
import pprint

os.chdir(os.path.dirname(__file__))

print(os.getcwd())

def filter_types():
    attack_types = []

    f = open("pokemon_att_effect.json","r")
    data = f.read()
    jdata = json.loads(data)

    for j in jdata:
        if not j['attack'] in attack_types:
            attack_types.append(j['attack'])

    random.shuffle(attack_types)
    return attack_types[:5]

def attack_matrix():
    matrix = {}
    attack_types = []

    f = open("pokemon_att_effect.json","r")
    data = f.read()
    jdata = json.loads(data)
    f.close()

    for j in jdata:
        if not j["attack"] in matrix:
            attack_types.append(j["attack"])
            matrix[j["attack"]] = {}
    
    for k in matrix: 
        for att in attack_types:
            if k != att:
                matrix[k][att] = 0

    for j in jdata:
        matrix[j["attack"]][j["defend"]] = j["effectiveness"]


    attack_types = sorted(attack_types)

    f = open("attack_effect_filtered.csv","w")

    head = ","
    f.write(head)
    for k in attack_types:
        head += k + ","
    f.write(head[:-1]+"\n")
    for i in attack_types:
        line = i+","
        for j in attack_types:
            line += str(matrix[i][j]) + ","
        f.write(line[:-1]+"\n")
    f.close()


def filter_pokedex(attack_types):

    # hard coded attack types so they will be consistent
    attack_types = ['fighting', 'dragon', 'poison', 'ground', 'normal']
    pokedex = []

    f = open("pokedex.json","r")
    data = f.read()
    jdata = json.loads(data)\

    for j in jdata:
        for t in j['type']:
            if t.lower() in attack_types:
                n = j["name"]["english"]
                i = j["id"]
                b = j["base"]
                t = j["type"]
                p = {"id":i,"name":n,"base":b,"type":t}
                pokedex.append(p)
    f = open("pokedex_filtered.json","w")
    f.write(json.dumps(pokedex,indent=4))
    f.close()
    return pokedex

if __name__=='__main__':
    #attack_types = filter_types()
    #pokedex = filter_pokedex(attack_types)
    attack_matrix()
    