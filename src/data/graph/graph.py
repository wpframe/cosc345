import csv
import matplotlib.pyplot as plt

# Read data from CSV
dates = []
close_values = []

def is_valid_format(row):
    # Check if the date is in the format YYYY-MM-DD and the close value is a float
    try:
        year, month, day = map(int, row[0].split('-'))
        float(row[1])
        return True
    except:
        return False

with open('data.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)  # Skip the header row
    for index, row in enumerate(reader):
        if not is_valid_format(row):
            print(f"Invalid format on line {index + 2}: {','.join(row)}")
            continue
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
