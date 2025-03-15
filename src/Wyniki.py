import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("data.txt")

fig, axs = plt.subplots(2, 2, figsize=(10, 10))

axs[0, 0].hist(data[:, 0], bins=50, color='blue', edgecolor='black')
axs[0, 0].set_title("Rozklad Gaussa")

axs[0, 1].hist(data[:, 1], bins=50, color='green', edgecolor='black')
axs[0, 1].set_title("Rozklad Liniowy")

axs[1, 0].hist(data[:, 2], bins=50, color='red', edgecolor='black')
axs[1, 0].set_title("Rozklad Liniowy Odwrotny")

#axs[1, 1].hist(data[:, 3], bins=20, color='purple', edgecolor='black')
#axs[1, 1].set_title("Customowy Rozklad")

plt.tight_layout()
plt.show()