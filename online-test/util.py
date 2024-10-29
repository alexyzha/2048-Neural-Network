import math

def log2char(x):
    x = int(x) if x else 0
    return int(math.log2(x) if x > 0 else 0)