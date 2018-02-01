from sys import stdin

for line in stdin:
    v = list(map(int,line.split()))
    if len(v) <= 0:
        continue
    del v[-1]
    n = len(v)
    zeros = [0]*(n+1)
    answer = v[0]
    for i in range(n):
        if v[i] == 0:
            answer = 0
            zeros[i] += 1
            v[i] = 1
    if(n >= 1):
        for i in range(1,n):
            v[i] *= v[i-1]
            zeros[i] += zeros[i-1]
    for i in range(n):
        for j in range(i,n):
            prod = v[j]
            if i > 0:
                prod //= v[i-1]
            zero = zeros[j]
            if i > 0:
                zero -= zeros[i-1]
            if zero > 0:
                prod = 0
            if answer < prod:
                answer = prod
    print(int(answer))

