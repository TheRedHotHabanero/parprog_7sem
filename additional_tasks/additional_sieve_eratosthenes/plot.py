import matplotlib.pyplot as plt

with open('results.txt', 'r') as f:
    #fig = plt.figure()
    xs  = []
    y1s = []
    y1fast = []
    line = f.readline()
    line = f.readline()
    line = f.readline()
    while True:
        line = f.readline()
        if line == '':
            break
        line = line.split(',')
        xs.append(float(line[0]))
        y1s.append(float(line[1]))
        y1fast.append(float(line[2][:-1]))

    plt.title("Sieve")
    plt.xlabel("N")
    plt.ylabel("time, mls")
    plt.scatter(xs, y1s, label="Sequential")
    plt.scatter(xs, y1fast, label="Parallel")
    plt.legend()
    plt.show()

    line = f.readline()
    line = f.readline()

    xs  = []
    y1s = []
    y2fast = []