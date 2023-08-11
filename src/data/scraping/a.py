import csv

# Name of your input CSV file
input_file = 'screener.csv'

# Name of your output file
output_file = 'tickers.txt'

def extract_tickers(input_file, output_file):
    with open(input_file, 'r') as csv_file:
        reader = csv.DictReader(csv_file)
        
        # Extract data and convert Market Cap to float (assuming Market Cap is in format like 1,000,000.50)
        data = [{'Symbol': row['Symbol'], 'Market Cap': float(row['Market Cap'].replace(',', '')) if row['Market Cap'] else 0} for row in reader]

        # Sort by Market Cap in descending order
        sorted_data = sorted(data, key=lambda x: x['Market Cap'], reverse=True)
        
        # Extract top 1000 tickers
        top_1000_tickers = [item['Symbol'] for item in sorted_data]

    with open(output_file, 'w') as txt_file:
        # Join tickers with a comma and a space and write to file
        txt_file.write(', '.join(top_1000_tickers))

if __name__ == "__main__":
    extract_tickers(input_file, output_file)
    print(f"Top 1000 stock tickers by market cap have been saved to {output_file}.")