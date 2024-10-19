import matplotlib.pyplot as plt
import sys

E_in = []
E_out = []
color = []
N = 80
K = 16
for i in range(N):
    for j in range(K):
        tmp = input().strip().split()
        E_in.append(float(tmp[0]))
        E_out.append(float(tmp[1]))
        color.append(i + 20)

plt.scatter(E_in, E_out, c = color, cmap = "Blues_r")
plt.title("scatter chart of (E_in, E_out)")
plt.colorbar()
# plt.show()
plt.savefig(sys.argv[1])
