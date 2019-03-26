#!/usr/bin/python
import os, sys

dir_path = os.path.dirname(os.path.realpath(__file__))

dstpath = sys.argv[1]

templatepath = dir_path+"/templates/"
finalpath = dstpath+"/cfgs/"

lines = open(dstpath+"/globals.cfg", "r").read().split("\n")

myvars = []

for line in lines:
	if line:
		sline = line.split(" = ")
		myvars.append(sline)


for file in os.listdir(templatepath):
	print(file)
	content = open(templatepath+file, "r").read()
	for k, v in myvars:
		content = content.replace(k, v)
	open(finalpath+file, "w").write(content)

