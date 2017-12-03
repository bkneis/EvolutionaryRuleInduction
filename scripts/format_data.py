#!/usr/bin/python3
import shutil
import os


def create_dir(i):
    """Create fold directory for train and test files"""
    dir = 'fold%i' % (i)
    if os.path.isdir(dir):
        shutil.rmtree(dir)
    os.makedirs(dir)


def split_data(data, k, start, end):
    """Split the 2000 data entries into 80 / 20 train test for fold k"""
    train_file = open("fold%i/train.txt" % k, "w")
    test_file = open("fold%i/test.txt" % k, "w")
    for i, line in enumerate(data):
        if i >= start and i < end:
            test_file.write(line)
        if i < start or i >= end:
            train_file.write(line)
    test_file.close()
    train_file.close()


def main():
    """Split data k number of times so each (100% / k) test set is available and present the rest as training data"""
    start = 0
    end = 400
    increment = 400
    k = 5
    for i in range(0, k):
        create_dir(i + 1)
        with open('data3.txt', newline='') as data:
            split_data(data, i + 1, start, end)
            start += increment
            end += increment

if __name__ == '__main__':
    main()
