file1 = open('pic.ppm', 'r')
for line in file1:
    print(len(line.split(' ')))
