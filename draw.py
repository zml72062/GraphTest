from ctypes.wintypes import FLOAT
import matplotlib.pyplot as plt

ax = plt.figure(figsize=(10, 10), dpi=100).add_subplot()
filename = ".\\test\\outInfo_1.txt"
file = open(filename, "r")
lines = file.readlines()
DATA = []
DIJKSTRA = []
FLOYD = []
JOHNSON = []
for line in lines:
    a = line.split()
    DATA.append(float(a[0]))
    DIJKSTRA.append(float(a[1]))
    FLOYD.append(float(a[2]))
    JOHNSON.append(float(a[3]))

ax.plot(DATA, DIJKSTRA, label='Dijkstra, power=1', c='green')
ax.plot(DATA, FLOYD, label='Floyd, power=1', c='red')
ax.plot(DATA, JOHNSON, label='Johnson, power=1', c='blue')
file.close()
filename = ".\\test\\outInfo_1.2.txt"
file = open(filename, "r")
lines = file.readlines()
DATA = []
DIJKSTRA = []
FLOYD = []
JOHNSON = []
for line in lines:
    a = line.split()
    DATA.append(float(a[0]))
    DIJKSTRA.append(float(a[1]))
    FLOYD.append(float(a[2]))
    JOHNSON.append(float(a[3]))

ax.plot(DATA, DIJKSTRA, label='Dijkstra, power=1.2', c='green')
ax.plot(DATA, FLOYD, label='Floyd, power=1.2', c='red')
ax.plot(DATA, JOHNSON, label='Johnson, power=1.2', c='blue')
file.close()

filename = ".\\test\\outInfo_1.5.txt"
file = open(filename, "r")
lines = file.readlines()
DATA = []
DIJKSTRA = []
FLOYD = []
JOHNSON = []
for line in lines:
    a = line.split()
    DATA.append(float(a[0]))
    DIJKSTRA.append(float(a[1]))
    FLOYD.append(float(a[2]))
    JOHNSON.append(float(a[3]))

ax.plot(DATA, DIJKSTRA, label='Dijkstra, power=1.5', c='green')
ax.plot(DATA, FLOYD, label='Floyd, power=1.5', c='red')
ax.plot(DATA, JOHNSON, label='Johnson, power=1.5', c='blue')
file.close()

filename = ".\\test\\outInfo_2.txt"
file = open(filename, "r")
lines = file.readlines()
DATA = []
DIJKSTRA = []
JOHNSON = []
for line in lines:
    a = line.split()
    DATA.append(float(a[0]))
    DIJKSTRA.append(float(a[1]))
    JOHNSON.append(float(a[3]))

ax.plot(DATA, DIJKSTRA, label='Dijkstra, power=2', c='green')
ax.plot(DATA, JOHNSON, label='Johnson, power=2', c='blue')
file.close()

filename = ".\\test\\outInfo.txt"
file = open(filename, "r")
lines = file.readlines()
DATA = []
FLOYD = []
for line in lines:
    a = line.split()
    DATA.append(float(a[0]))
    FLOYD.append(float(a[1]))
ax.plot(DATA, FLOYD, label='Floyd, power=2', c='red')
file.close()

plt.legend(loc='upper left')
plt.xlabel('Number of vertices $V$')
plt.ylabel('Runtime/sec')
plt.show()
