import csv
import matplotlib.pyplot as plt

# Read data from CSV
dates = []
close_values = []

with open('data.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)  # Skip the header row
    for index, row in enumerate(reader):
        if index % 52 == 0:  # Only take every 52nd entry
            dates.append(row[0])
            close_values.append(float(row[1]))

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(dates, close_values, marker='o', linestyle='-', color='b')
plt.xticks(rotation=45)
plt.xlabel('Date')
plt.ylabel('Close Value')
plt.title('Close Value over Time')
plt.tight_layout()
plt.grid(True)
plt.show()
