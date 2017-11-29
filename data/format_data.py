#!/usr/bin/python3
from itertools import islice
import shutil
import os

start = 0
end = 400
increment = 400
k = 5

for i in range(0, k):
    dir = 'fold%i' % (i + 1)
    shutil.rmtree(dir)
    os.makedirs(dir)

for i in range(0, k):
    with open('data3.txt', newline='') as data:
        train_file = open("fold%i/train.txt" % (i + 1), "w") 
        test_file = open("fold%i/test.txt" % (i + 1), "w") 
        for i, line in enumerate(data):
            if i >= start and i < end:
                test_file.write(line)
            if i < start or i >= end:
                train_file.write(line)
        test_file.close()
        train_file.close()
        start += increment
        end += increment
