
import math

def  is_prime(n):
    if n < 2:
        return False

    if n == 2:
        return True

    if n%2 == 0:
        return False

    i= 3
    limit = int(math.sqrt(n))
    while i <= limit:
            if n%i == 0:
                 return False
            i += 2
    return True

def sPF(k):
    
    x, y = 0, 1
    while True:
        x, y = y, x + y   
        if x>k and is_prime(x):
             return x
        

k=17
print(sPF(k))