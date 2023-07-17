# COSC345

## Group Members:
- Ben Knox
- Shamen Kumar
- Vincent Lee
- Will Frame

## Our idea:
A stock trading game in which you begin with a million US dollars. You must generate as much money over the 100 years of your life. High scores are stored in an online leaderboard. You can use stocks, crypto, property, and more to generate income. Stock data is predicted based on real world stock data, and world events and company happenings/announcements/financials are generated based on historical data. These are randomized for every playthrough. A "real-life" mode is also available which simply uses real stock data daily to update the performance of your portfolio - the leaderboard for this shows the highest growing portfolios over the past month.


### Things we need to decide on:
Game name (Millionaire Simulator, Greed Simulator, etc)

Features:
- Stocks (NASDAQ only?)
- Crypto
- Property (renting?)
- Online leaderboard
- Shorting stocks and crypto
- News headlines with impact on stocks
- Education and jobs
- Casino 

Maybes:
- Options trading?
- Real paper trading mode?
- Start your own business?

### Datasets:
- [NASDAQ history](https://www.nasdaq.com/market-activity/quotes/historical)
- [Stock news with senitment](https://www.kaggle.com/datasets/ankurzing/sentiment-analysis-for-financial-news)
- [Possibly majors with salaries data](https://www.kaggle.com/code/cdelany7/exploration-of-college-salaries-by-major)
- Housing data (not found yet)

### Functional requirements
- Must compile with most C++ compilers
- Fun
- Intuitive UI
- Less than 2 second load time for each year of data


### Non-functional requirements
- Data is generated efficiently
- Server uptime for the leaderboard
- C++ program
- QT for GUI
- Python for data processing, but we will use C++ to reprocess the data so every game is unique
Constraints:
- No multithreading
- GUI must be simple to prevent it taking up too much of our time
- Testing (GTest looks pretty good?)
- CI/CD (unsure)
- Documentation (Doxygen)

### Domain specific requirements
Our domain: Finance

