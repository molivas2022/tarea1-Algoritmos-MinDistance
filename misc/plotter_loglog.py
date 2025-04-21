import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load CSV (one directory above)
df = pd.read_csv('../result.csv', sep=';')

# Add a column for log2(TIME)
df['LOG2_TIME'] = np.log2(df['TIME'])

# Create the plot
plt.figure(figsize=(10, 6))

# Plot each curve by NAME
for name, group in df.groupby('NAME'):
    match name:
        case "brute_force": label = "Fuerza bruta"
        case "divide_and_conquer": label = "Dividir para vencer"
        case "better_brute_force": label = "Fuerza bruta potenciado"
        case "better_divide_and_conquer": label = "Dividir para vencer potenciado"
    group_sorted = group.sort_values('EXPONENT')
    plt.plot(group_sorted['EXPONENT'], group_sorted['LOG2_TIME'], marker='o', label=label)

# Labels and formatting
plt.xlabel('log₂ de la cantidad de puntos')
plt.ylabel('log₂ del tiempo de ejecución [ns]')
plt.title('Gráfico log-log')
plt.legend()
plt.grid(True)
plt.tight_layout()

# Show or save
plt.savefig('plot_loglog.png')  # or plt.show() if interactive
