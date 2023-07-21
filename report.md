# COSC345 Assignment 1

## Group Members:

### Ben Knox
Ben has studied finance and computer science at Otago. Meaning the knowledge attained from his finance degree will help in the implementation of trading stocks. He is most comfortable coding in Python and Java but has some knowledge of C and C++. His experience in coding leans towards backend development however he is open to learning different concepts in the creation of UI as needed. He will provide help in generating backend functionality to parts of the game.

### Shamen Kumar

### Vincent Lee

### Will Frame
I'm Will, a third year Computer Science student minoring in Information Science. I've been interested in stocks for a few years now as some of my family work in the field, and I've played a few investment simulator games in the past. I also did COSC360 (the game design paper) which I think will be very useful for this project/idea. I think my main contributions to the project will be for programming, game design, data processing, and GUI design.

## Our idea

Our idea is a stock market simulator game. The objective of the game is to generate as much money as you can over the 100 years of your life. Everyone starts with a million US dollars and must use stocks, property, ETFs, precious metals, cryptocurrency, and more to generate income. Players can even get an education and a job in the game to earn extra income. High scores are stored in an online leaderboard.

There are two modes that will be supported for our game; a real-world trading game which uses current stock market data in real time, and a simulated trading game in which historical data is accurate but future data is generated based on the historical data (stock prices and financial news). The future data is generated with a degree of randomness for every playthrough, and years can be skipped to keep the game fast and arcade-y. We will also add a casino, which will have blackjack, slots, and roulette. We will have to limit the amount a player can make from the casino to prevent the leaderboards just being filled with people who gambled all their money repeatedly.

Some other features we would like to add are options trading and starting your own business, however these ideas would almost definitely take up too much time to implement. If we have leftover time at the end we will give these a go.

## Datasets

Our main dataset is NASDAQ's and the NYSE's historical stock data. The NASDAQ website (https://www.nasdaq.com/market-activity/quotes/historical) and the NYSE website (https://www.nyse.com/market-data/historical) both historical data for almost all of the stocks listed under the NASDAQ and NYSE.

Another dataset we will use is a US housing data (https://www.kaggle.com/datasets/paultimothymooney/zillow-house-price-data). This will be used to give the players an alternative investment to typical stocks. This dataset has rental pricing as well as housing pricing by number of rooms. Investment properties in the game will also generate rent once someone moves in.

Another dataset we will use is a stock news with sentiment dataset (https://www.kaggle.com/datasets/ankurzing/sentiment-analysis-for-financial-news). This will be used to assist in generating news headlines for companies as well as their impact on company stocks.

We may also use a majors with salaries dataset (https://www.kaggle.com/code/cdelany7/exploration-of-college-salaries-by-major) to calculate how much players earn depending on their chosen education and job.

## Similar products and evidence of customer interest

The most popular three similar products are "MarketWatch Virtual Stock Exchange", "The Stock Market Game", and "Investopedia Simulator". "MarketWatch Virtual Stock Exchange" and "The Stock Market Game" have lengthy signup processes that collect a large amount of data. "Investopedia Simulator" is the product the closest to what we hope to achieve, with a simple UI for the features we plan to implement, as well as a very simple starting process. The downfall of "Investopedia Simulator" is that alike the other similar products, there is no simulated economy, so the pacing of the game is extremely slow.

There are a lot of business simulators and stock market simulator games, in which share the same objective as ours - make as much money as possible. We also believe the educational value of our stock market simulator could be useful to a larger customer base, teaching people to recognize how stock prices interact with financial news regarding companies.


## Functional requirements
- Must compile with most C++ compilers
- Fun
- Intuitive UI
- Less than 2 second load time for each year of data


## Non-functional requirements
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
