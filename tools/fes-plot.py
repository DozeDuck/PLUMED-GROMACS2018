import numpy as np
import matplotlib.pyplot as plt

# usage: python fes-plot.py
# Load data from fes.dat
# Assuming 'fes.dat' is formatted as in your example, with phi and psi as the first two columns and free energy as the third
data = np.loadtxt('fes.dat')

# Reshape data into a grid
phi_values = np.degrees(np.unique(data[:, 0]))
psi_values = np.degrees(np.unique(data[:, 1]))
phi_grid, psi_grid = np.meshgrid(phi_values, psi_values)
free_energy_grid = data[:, 2].reshape(len(psi_values), len(phi_values))

# Plot the FES
plt.contourf(phi_grid, psi_grid, free_energy_grid, levels=100)
plt.xlabel('phi / degrees')
plt.ylabel('psi / degrees')
plt.colorbar(label='Free energy / kJ mol^-1')
plt.show()

