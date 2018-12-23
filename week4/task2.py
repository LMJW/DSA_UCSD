# python3

from collections import defaultdict

n = int(input())

arr = list(map(int, input().split(" ")))

class Solution(object):
    def __init__(self):
        self.found = False
        self.d = defaultdict(int)
    def major(self, arr):
        l = len(arr)
        if l>1:
            self.major(arr[0:l//2])
            self.major(arr[l//2:])
        elif l == 1:
            self.d[arr[0]]+=1
            if self.d[arr[0]]>n/2:
                self.found = True

    def wrapper(self, arr):
        self.major(arr)
        if self.found:
            print(1)
        else:
            print(0)

Solution().wrapper(arr)