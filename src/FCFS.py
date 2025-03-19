import numpy as np
import matplotlib.pyplot as plt

with open('FCFS.txt', 'r') as file:
    lines = file.readlines()
    
avg_stats = np.array([int(x) for x in lines[0].strip().split()]) 

proces_stats = np.loadtxt(lines[1:])

fig, axes = plt.subplots(10, 2, figsize=(10, 8))

axes[0,0].hist()

# Rozklad priorytetu