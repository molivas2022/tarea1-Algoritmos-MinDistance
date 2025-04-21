import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load CSV file (adjust filename as needed)
df = pd.read_csv('../result.csv', sep=';')

# Create the plot
plt.figure(figsize=(10, 6))

# Filter to only specific NAMEs
filtered_df = df[df['NAME'].isin(['divide_and_conquer', 'better_divide_and_conquer'])]

# Group and plot only those
for name, group in filtered_df.groupby('NAME'):
    match name:
        case "brute_force": label = "Fuerza bruta"
        case "divide_and_conquer": label = "Dividir para vencer"
        case "better_brute_force": label = "Fuerza bruta potenciado"
        case "better_divide_and_conquer": label = "Dividir para vencer potenciado"
    group_sorted = group.sort_values('SIZE')
    plt.plot(group_sorted['SIZE'], group_sorted['TIME'], marker='o', label=label)

# Customize x-axis: replace ticks with 2^EXPONENT
# Find unique SIZE/EXPONENT pairs
# Filter ticks: EXPONENT is an integer and >= 10
tick_data = df[
    (df['EXPONENT'] == df['EXPONENT'].astype(int)) &
    (df['EXPONENT'] >= 10)
].drop_duplicates(subset='SIZE')

tick_positions = tick_data['SIZE']
tick_labels = [f'$2^{{{int(exp)}}}$' for exp in tick_data['EXPONENT']]

plt.xticks(ticks=tick_positions, labels=tick_labels)

# Labels and formatting
plt.xlabel('cantidad de puntos')
plt.ylabel('tiempo de ejecución [ns]')
plt.title('Comparativa dividir para vencer')
plt.legend()
plt.grid(True)
plt.tight_layout()

# Show or save
plt.savefig('plot_only_dac.png')  # or plt.show() if interactive