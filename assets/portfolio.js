function goToHome() {
    window.location.href = "homepage.html";
}

function goTo100Years() {
    window.location.href = "100years.html";
}


function addStock() {
    var result = document.getElementById("result");
    result.innerText = "success";
    addStockTile("extra", "100.42", "1000000");
}

function initBalance(totalBalance) {
    var balanceContainer = document.getElementsByClassName("totalBalance")[0];

    var balanceParagraph = document.createElement("p");
    balanceParagraph.textContent = "Total Balance: " + totalBalance; // Change this to the actual stock name
    balanceContainer.appendChild(balanceParagraph);
}

function updateBalance(newBalance) {
    var balanceContainer = document.getElementsByClassName("totalBalance")[0];

    // Remove the existing balance paragraph (if any)
    var existingParagraph = balanceContainer.querySelector("p");
    if (existingParagraph) {
        balanceContainer.removeChild(existingParagraph);
    }

    // Create a new paragraph with the updated balance
    var balanceParagraph = document.createElement("p");
    balanceParagraph.textContent = "Total Balance: " + newBalance;
    balanceContainer.appendChild(balanceParagraph);
}

function addStockTile(symbol, purchasePrice, currentPrice, quantity, profitLoss, profitLossPercent, purchaseValue, currentPurchaseValue, currentBalance) {
    var tileContainer = document.getElementsByClassName("tiles-container")[0]; // Assuming there's only one container

    // Create the main container div
    var stockTile = document.createElement("div");
    stockTile.className = "stock-tile";

    // Create and add stock name 
    var stockNameParagraph = document.createElement("p");
    stockNameParagraph.textContent = "Stock: " + symbol; // Change this to the actual stock name
    stockTile.appendChild(stockNameParagraph);

    var quantityParagraph = document.createElement("p");
    quantityParagraph.textContent = "Quantity: " + quantity; // Change this to the actual price
    stockTile.appendChild(quantityParagraph);

    // Create and add purchase price
    var purchasePriceParagraph = document.createElement("p");
    purchasePriceParagraph.textContent = "Purchase Price: " + purchasePrice; // Change this to the actual price
    stockTile.appendChild(purchasePriceParagraph);

    // Create and add current price
    var currentPriceParagraph = document.createElement("p");
    currentPriceParagraph.textContent = "Current Price: " + currentPrice; // Change this to the actual price
    stockTile.appendChild(currentPriceParagraph);

    // Create and add total amount invested
    var purchaseValueParagraph = document.createElement("p");
    purchaseValueParagraph.textContent = "Amount Invested: " + purchaseValue; // Change this to the actual price
    stockTile.appendChild(purchaseValueParagraph);

    // Create and add how much the investment is now
    var currentPurchaseValueParagraph = document.createElement("p");
    currentPurchaseValueParagraph.textContent = "Investment Total Now: " + currentPurchaseValue; // Change this to the actual price
    stockTile.appendChild(currentPurchaseValueParagraph);

    var profitLossParagraph = document.createElement("p");
    profitLossParagraph.textContent = "Profit/Loss: $" + profitLoss; // Change this to the actual price
    stockTile.appendChild(profitLossParagraph);

    var profitLossPercentParagraph = document.createElement("p");
    profitLossPercentParagraph.textContent = "Profit/Loss Percentage: " + profitLossPercent + "%"; // Change this to the actual price
    stockTile.appendChild(profitLossPercentParagraph);

    // var currentBalanceParagraph = document.createElement("p");
    // currentBalanceParagraph.textContent = "Current Balance: " + currentBalance; // Change this to the actual price
    // stockTile.appendChild(currentBalanceParagraph);
    // Append the stock tile to the container
    tileContainer.appendChild(stockTile);
}

function addInvestmentSummary(totalInvestment, portfolioValue, totalProfit, totalProfitPercentage) {
    var tileContainer = document.getElementsByClassName("investment-summary")[0]; // Assuming there's only one container

    // Create the main container div
    var summaryTile = document.createElement("div");
    summaryTile.className = "summary-tile";

    var totalInvestmentParagraph = document.createElement("p");
    totalInvestmentParagraph.textContent = "Total Investment: " + totalInvestment;
    summaryTile.appendChild(totalInvestmentParagraph);

    var portfolioValueParagraph = document.createElement("p");
    portfolioValueParagraph.textContent = "Current Portfolio Value: " + portfolioValue;
    summaryTile.appendChild(portfolioValueParagraph);

    var totalProfitParagraph = document.createElement("p");
    totalProfitParagraph.textContent = "Total Profit/Loss: " + totalProfit;
    summaryTile.appendChild(totalProfitParagraph);

    var totalProfitPercentageParagraph = document.createElement("p");
    totalProfitPercentageParagraph.textContent = "Total Profit/Loss Percentage: " + totalProfitPercentage + "%";
    summaryTile.appendChild(totalProfitPercentageParagraph);

    // Append the main container div to the tile container
    tileContainer.appendChild(summaryTile);
}

function updateInvestmentSummary(totalInvestment, portfolioValue, totalProfit, totalProfitPercentage) {
    var tileContainer = document.getElementsByClassName("investment-summary")[0]; // Assuming there's only one container

    // Remove the existing summary (if any)
    var existingSummaryTile = tileContainer.querySelector("div");
    if (existingSummaryTile) {
        tileContainer.removeChild(existingSummaryTile);
    }

    // Create the main container div for the new summary
    var summaryTile = document.createElement("div");
    summaryTile.className = "summary-tile";

    var totalInvestmentParagraph = document.createElement("p");
    totalInvestmentParagraph.textContent = "Total Investment: " + totalInvestment;
    summaryTile.appendChild(totalInvestmentParagraph);

    var portfolioValueParagraph = document.createElement("p");
    portfolioValueParagraph.textContent = "Current Portfolio Value: " + portfolioValue;
    summaryTile.appendChild(portfolioValueParagraph);

    var totalProfitParagraph = document.createElement("p");
    totalProfitParagraph.textContent = "Total Profit/Loss: " + totalProfit;
    summaryTile.appendChild(totalProfitParagraph);

    var totalProfitPercentageParagraph = document.createElement("p");
    totalProfitPercentageParagraph.textContent = "Total Profit/Loss Percentage: " + totalProfitPercentage + "%";
    summaryTile.appendChild(totalProfitPercentageParagraph);

    // Append the new summary to the tile container
    tileContainer.appendChild(summaryTile);
}

