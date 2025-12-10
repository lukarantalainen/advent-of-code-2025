input = open("input.txt")

ans = 0
pointing = 50

def count_zeroes(dir, nums):
    global pointing
    global ans
    if dir == "R":
        if pointing+nums <= 99:
            pointing += nums
        else:
            pointing += nums
            while pointing > 99:
                pointing -= 100
                
    elif dir == "L":
        if 0 <= pointing-nums:
            pointing -= nums
        else:
            pointing -= nums
            while pointing < 0:
                pointing += 100

    if (pointing == 0):
        ans += 1

for line in input:
    count_zeroes(line[0], int(line[1:]))

print(ans)

# def test_answer():
#     count_zeroes("L", 68)
#     count_zeroes("L", 30)
#     count_zeroes("R", 48)
#     count_zeroes("L", 5)
#     count_zeroes("R", 50)
#     count_zeroes("L", 55)
#     count_zeroes("L", 1)
#     count_zeroes("L", 99)
#     count_zeroes("R", 14)
#     count_zeroes("L", 82)
# test_answer()
# print(ans)
