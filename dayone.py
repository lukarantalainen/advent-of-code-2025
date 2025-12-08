input = open("input.txt")

ans = 0
pointing = 50
for line in input:
    nums = int(line[1:])
    if pointing == 0:
        ans+=1

    if line[0] == "R":
        if pointing+nums <= 99:
            pointing += nums
        else:
            pointing += nums
            while pointing > 99:
                pointing -= 100
                ans+=1
                
    elif line[0] == "L":
        if 0 <= pointing-nums:
            pointing -= nums
        else:
            pointing -= nums
            while pointing < 0:
                pointing += 100
                ans+=1

    if (pointing == 0):
        ans += 1

print(ans)
