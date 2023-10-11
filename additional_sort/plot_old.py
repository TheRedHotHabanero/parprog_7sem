import matplotlib.pyplot as plt

with open('resultss.txt', 'r') as f:
    #fig = plt.figure()
    xs  = []
    y1s = []
    line = f.readline()
    line = f.readline()
    line = f.readline()
    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        xs.append(float(line[0]))
        y1s.append(float(line[1][:-1]))

    line = f.readline()
    line = f.readline()

    y2s = []

    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        y2s.append(float(line[1][:-1]))

    line = f.readline()
    line = f.readline()

    y3s = []

    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        y3s.append(float(line[1][:-1]))

    line = f.readline()
    line = f.readline()

    y4s = []

    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        y4s.append(float(line[1][:-1]))

    line = f.readline()
    line = f.readline()

    y5s = []

    while True:
        line = f.readline()
        if line == "":
            break
        line = line.split(',')
        y5s.append(float(line[1][:-1]))

    line = f.readline()
    line = f.readline()

    plt.title("1 variant.")
    plt.xlabel("array")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1s, label="Treshold = 100")
    plt.scatter(xs, y2s, label="Treshold = 150")
    plt.scatter(xs, y3s, label="Treshold = 60")
    plt.scatter(xs, y4s, label="Treshold = 250")
    plt.legend()
    plt.show()
