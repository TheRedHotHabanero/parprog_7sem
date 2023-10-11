import matplotlib.pyplot as plt

with open('resultss.txt', 'r') as f:
    #fig = plt.figure()
    xs  = []
    y1s = []
    y2s = []
    line = f.readline()
    line = f.readline()
    line = f.readline()
    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        xs.append(float(line[0]))
        y1s.append(float(line[1]))
        y2s.append(float(line[2][:-1]))

    plt.title("2 vs 1 Variant. treshold = 100")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1s, label="Slow")
    plt.scatter(xs, y2s, label="Fast")
    plt.legend()
    plt.show()

    line = f.readline()
    line = f.readline()

    xs  = []
    y1s = []
    y2s = []

    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        xs.append(float(line[0]))
        y1s.append(float(line[1]))
        y2s.append(float(line[2][:-1]))

    plt.title("2 vs 1 Variant. treshold = 200")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.scatter(xs, y1s, label="Slow")
    plt.scatter(xs, y2s, label="Fast")
    plt.legend()
    plt.show()

    line = f.readline()
    line = f.readline()

    xs  = []
    y1s = []
    y2s = []

    while True:
        line = f.readline()
        if line[0] == '-':
            break
        line = line.split(',')
        xs.append(float(line[0]))
        y1s.append(float(line[1]))
        y2s.append(float(line[2][:-1]))

    plt.title("2 vs 1 Variant. treshold = 50")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.legend()
    plt.scatter(xs, y1s, label="Slow")
    plt.scatter(xs, y2s, label="Fast")
    plt.show()

    line = f.readline()
    line = f.readline()

    xs  = []
    y1s = []
    y2s = []

    while True:
        line = f.readline()
        if line == '':
            break
        line = line.split(',')
        xs.append(float(line[0]))
        y1s.append(float(line[1]))
        y2s.append(float(line[2][:-1]))

    plt.title("2 vs 1 Variant. treshold = 300")
    plt.xlabel("matrix size")
    plt.ylabel("time, msecs")
    plt.legend()
    plt.scatter(xs, y1s, label="Slow")
    plt.scatter(xs, y2s, label="Fast")
    plt.show()