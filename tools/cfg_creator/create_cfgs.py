#!/usr/bin/python
import os, sys

dstpath = sys.argv[1]

dir_path = os.path.dirname(os.path.realpath(__file__))

templatepath = dir_path+"/templates/"
finalpath = dstpath+"/cfgs/"

enc = "iso-8859-1"

with open(dstpath+"/globals.cfg", 'r', encoding=enc) as fd:
    if fd:
        lines = fd.read().split("\n")
        tmp = []
        for n in lines:
            if n:
                line = n.split(" = ")
                if line:
                    tmp.append(line)
        
        for f in os.listdir(templatepath):
            with open(templatepath+f, 'r', encoding=enc) as content:
                if content:
                    content = content.read()
                    for k, v in tmp:
                        content = content.replace(k, v)
                    with open(finalpath+f, 'w') as fd:
                        fd.write(content)
            print(f)
            