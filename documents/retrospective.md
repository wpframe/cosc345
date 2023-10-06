Initially in our project, we set out functional goals and requirements:

- Stock Market Trading
As the primary functional requirement of our program, this was our primary focus and we therefore spent the most time to get it working. Buying and selling stocks works smoothly and the system is very intuitive.
- Real Estate Trading
We didn't end up implementing real estate trading as there were too many variables to account for. Considering the amount of time required to get stock market trading working smoothly we decided this would not be the best use of our time. If we were continuing with this project, we would implement this.
- Job and Education Simulation
Even though originally this was a lower priority than implementing real estate, we ended up implementing this effectively. Players can select a college to work for, and using a salary dataset based on different colleges, their pay in their future job is changed. Originally we were going to allow selection of different majors, and use average salaries from those majors to determine pay, however we decided to change this as players would likely just select the highest paying job. The higher ranked colleges require a higher net worth to get into, and our idea behind this reasoning was that the player is applying for a financial course and therefore their portfolio would back their knowledge and previous education.
- Updating Leaderboard
We couldn't figure out the logistics of a leaderboard - the leaderboard would have to be centralised and hosted on a server, which we are able to do, however with an open-source game we decided not to do this as we have no way of easily identifying the authenticity of a score being uploaded to the leaderboard.
- Economic Simulation with news headlines
We did get the news headlines figured out - you can see headlines occasionally show up for your chosen stocks in your portfolio. These have an impact on the stock price going forwards.
- Portfolio Management
Portfolio management is clean and simple. You can see your total profits (as well as a percentage) and other statistics (including per stock statistics) in the portfolio page.
- Real time data updating
Early on we decided this would not be worth the time - it's a lot of effort downloading new stock data for specifically missing days from APIs, so we instead simply cut off stock history at the beginning of 2023.

Our non-function goals and requirements were:

- Fun
Based on our user testing, many people found our game to be enjoyable which resulted in all of our criticism specifically regarding the UI.
- Intuitive UI
Our UI is quite simple, and during user testing, we received suggestions to improve it, which I'll cover later.
- Lest than 2 second load time for each year of data
Data loads within one second for even a decade of data.
- C++ program
Our program is C++ and uses a C++ library called Ultralight to allow HTML/CSS/JS for front-end.
- Must compile with most C++ compilers
We compiled using G++ and also one of us used Visual Studio to build the program and everything worked fine.
- Server uptime for the leaderboard
As mentioned previously, we didn't add the leaderboard so we didn't need to implement this non-functional requirement.
- Ultralight for GUI
As mentioned previously, we did use Ultralight for GUI and created a professional and sleek looking application using it.

We followed all of our constraints as per the assignment;
- No multitthreading
- GUI must be simple to prevent it taking up too much of our time
- Testing (we wrote our own tests)
- CI/CD (we integrated automated CMake build and testing, and automated Doxygen documentation generation)

We also met the requirement of using two datasets, one being the stock data from the NASDAQ, and the other being the college salaries dataset.

From user testing, we received and implemented the following suggestions:
1. Highlight profit green and highlight losses red
2. Change the layout of the navigation bar as it's not intuitive causing the user to accidentally go to the menu regularly
3. Add a functioning updating graph
4. Round numbers to 2 decimal places
5. Add shortcuts for buying numbers of stocks (e.g. 10, 100, 1000)

We implemented these suggestions for our final product and found the critcism and suggestions from user testing to be very valuable, especially the highlighting and shortcut ideas as we had not thought of those before.

Some suggestions we didn't implement were:
1. Display most popular/trending stocks of the week
We thought this would be a cool feature if everyone's portfolios were linked to a server so we could see what our users purchased the most, but we didn't have enough time to implement this.
2. More user documentation about how the stock market works in general
We didn't implement this as there are curated resources written by professionals online, however it could be helpful to link the user to some of these resources in the help menu.
3. Remove 100 years mode
We didn't want to remove the 100 years mode as progressively around 200 years in the stock prediction can become quite erratic.

In all we found that the weekly standup sessions helped a lot to keep in touch and up to date with what we were doing. Using Discord also helped a lot to be able to easily message teammates for extra information. The GitHub webhook on Discord was also helpful to see the commit history with CI/CD status/notifications.

Since most of our feedback was in regard to UI we found it easy to implement all changes requested as they were all deemed beneficial to our app.

We are happy with how our development went - everything was smooth and organized. There are some features we didn't add that we wanted to add, but we are satisfied with what we completed and believe it is a polished final product.
