import matplotlib.pyplot as plt
import sys

E_in = []
E_out = []
N = 1126
for i in range(N):
    tmp = input().strip().split()
    E_in.append(float(tmp[0]))
    E_out.append(float(tmp[1]))

plt.scatter(E_in, E_out)
plt.title("scatter chart of (E_in, E_out)")
# plt.show()
plt.savefig(sys.argv[1])
