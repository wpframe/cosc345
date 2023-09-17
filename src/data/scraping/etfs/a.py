import csv

# Name of your input CSV file
input_file = 'input.csv'

# Name of your output file
output_file = 'stock_tickers.txt'


def extract_tickers(input_file, output_file):
    with open(input_file, 'r') as csv_file:
        reader = csv.DictReader(csv_file)
        tickers = [row['SYMBOL'] for row in reader]

    with open(output_file, 'w') as txt_file:
        for ticker in tickers:
            txt_file.write(f"{ticker}\n")


if __name__ == "__main__":
    extract_tickers(input_file, output_file)
    print(f"All stock tickers have been saved to {output_file}.")
