import yfinance as yf

# Assuming you've already extracted the top 1000 tickers and saved them in the 'top_1000_by_market_cap_tickers.txt' file:
with open('tickers.txt', 'r') as file:
    tickers = [line.strip() for line in file.read().split(', ')]

start_date = "2013-08-08"
end_date = "2023-08-08"


def download_stock_data(ticker):
    # Download the data
    df = yf.download(ticker, start=start_date, end=end_date, interval='1wk')

    # Save to a CSV file
    output_filename = f"{ticker}.csv"
    df.to_csv(output_filename)
    print(f"Data for {ticker} saved to {output_filename}")


for ticker in tickers:
    try:
        download_stock_data(ticker)
    except Exception as e:
        print(f"Error downloading data for {ticker}: {e}")

print("Download complete.")
