import random


def gacha(n):
    cd = 0
    posters = []
    while len(set(posters)) < n:
        posters.append(random.randint(1, n))
        cd += 1
    return cd


trial = 100
cd = 0
N = 44
for _ in range(trial):
    cd += gacha(N)
print(cd / trial)
