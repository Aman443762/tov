import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 1. Load the unmodified dataset
try:
    df = pd.read_csv('mr_curve.csv')
except FileNotFoundError:
    print("Error: mr_curve.csv not found. Ensure  tov_solver ran successfully inside this folder!")
    exit()

df = df.sort_values(by='P_central').reset_index(drop=True)

# Calculate the numerical derivative dM/dPc
dM_dPc = np.gradient(df['Mass_Msun'], df['P_central'])

fig, axes = plt.subplots(1, 3, figsize=(18, 5.5))
plt.subplots_adjust(wspace=0.3)

max_idx = df['Mass_Msun'].idxmax()
max_M = df['Mass_Msun'].max()
max_R = df['Radius_km'].iloc[max_idx]

stable_df = df.iloc[:max_idx+1]
unstable_df = df.iloc[max_idx+1:]

print(f"Target TOV Core Boundary coordinates: {max_M:.2f} M_sun at {max_R:.2f} km.")

# PANEL 1: Mass-Radius Relation

axes[0].plot(stable_df['Radius_km'], stable_df['Mass_Msun'], color='#1b3a4b', linewidth=3, label='Stable Branch')
axes[0].plot(unstable_df['Radius_km'], unstable_df['Mass_Msun'], color='#e63946', linewidth=2, linestyle='--', label='Unstable Branch')
axes[0].scatter(max_R, max_M, color='#d90429', s=80, zorder=5, label=f'TOV Limit ({max_M:.2f} $M_\odot$)')

axes[0].set_title('Mass-Radius Relation', fontsize=12, fontweight='bold')
axes[0].set_xlabel('Radius ($R$ in km)', fontsize=11)
axes[0].set_ylabel('Total Mass ($M$ in $M_\odot$)', fontsize=11)
axes[0].grid(True, linestyle=':', alpha=0.6)
axes[0].legend(fontsize=9)

# PANEL 2: Stability Derivative

axes[1].plot(df['P_central'], dM_dPc, color='#457b9d', linewidth=2.5, label='$dM/dP_c$')
axes[1].axhline(0, color='black', linestyle='-', linewidth=1, alpha=0.5)
axes[1].axvline(df['P_central'].iloc[max_idx], color='#e63946', linestyle=':', label='Transition Point')

axes[1].set_title('Stellar Stability Derivative', fontsize=12, fontweight='bold')
axes[1].set_xlabel('Central Pressure ($P_c$ in geo units)', fontsize=11)
axes[1].set_ylabel('Derivative Scale ($dM/dP_c$)', fontsize=11)
axes[1].set_xscale('log')
axes[1].grid(True, linestyle=':', alpha=0.6)
axes[1].legend(fontsize=9)

# PANEL 3: Mass & Radius Response to Core Pressure

color = '#1b3a4b'
axes[2].set_title('Stellar Response to Compression', fontsize=12, fontweight='bold')
axes[2].set_xlabel('Central Pressure ($P_c$ in geo units)', fontsize=11)
axes[2].set_xscale('log')

axes[2].plot(df['P_central'], df['Mass_Msun'], color=color, linewidth=2.5)
axes[2].set_ylabel('Mass ($M_\odot$)', color=color, fontsize=11)
axes[2].tick_params(axis='y', labelcolor=color)
axes[2].axvline(df['P_central'].iloc[max_idx], color='#e63946', linestyle=':', alpha=0.7)

ax2 = axes[2].twinx()
color2 = '#2a9d8f'
ax2.plot(df['P_central'], df['Radius_km'], color=color2, linewidth=2.5, linestyle='-.')
ax2.set_ylabel('Radius (km)', color=color2, fontsize=11)
ax2.tick_params(axis='y', labelcolor=color2)
axes[2].grid(True, linestyle=':', alpha=0.6)

plt.savefig('tov_plots.png', dpi=300, bbox_inches='tight')
plt.close()

print(f"HPC Diagnostic Plot successfully compiled and saved as 'tov_plots.png'")