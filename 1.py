a = int(input())
cnt = 1
num = 1

while(num % a != 0):
    cnt+=1
    num = num * 10 + 1

print(num//a, cnt)