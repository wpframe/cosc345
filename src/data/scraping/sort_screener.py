import csv
import os

# Read the CSV data
data = []
with open('nasdaq_screener_1694923226318.csv', 'r') as csv_file:
    reader = csv.reader(csv_file)
    header = next(reader)  # get the header
    for row in reader:
        data.append(row)

# Sort by market cap (column index 5, converted to float)
sorted_data = sorted(data, key=lambda x: float(x[5]) if x[5] else 0, reverse=True)

# Check for stock files and filter out those with less than 5 lines
filtered_data = []
for row in sorted_data:
    ticker = row[0]
    stock_file_path = f"../stocks/{ticker}.csv"
    if os.path.exists(stock_file_path):
        with open(stock_file_path, 'r') as stock_file:
            lines = stock_file.readlines()
            if len(lines) < 5:
                os.remove(stock_file_path)
                continue
    filtered_data.append(row)

# Write the filtered and sorted data back to a new CSV file
with open('sorted_by_market_cap.csv', 'w', newline='') as csv_file:
    writer = csv.writer(csv_file)
    writer.writerow(header)
    writer.writerows(filtered_data)

print("Operation complete!")
