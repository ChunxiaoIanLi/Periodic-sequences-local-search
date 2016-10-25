import math

def sum_of_square():
    n=100
    for i in range(1, n, 2):
        target = 4*i-2
        for a in range(1, int(math.sqrt(target))):
            b=math.sqrt(target-a*a)
            if b%1==0:
                #if b%2!=0:
                print("n is {0}; 4n-2 is {1}: ".format(i, target))
                print("{0} {1}".format(a,int(b)))
    return

sum_of_square();
                
                
                
                
