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
    addInvestmentSummary(totalInvestment, portfolioValue, totalProfit, totalProfitPercentage);

}


function addStockTile(symbol, purchasePrice, currentPrice, quantity, profitLoss, profitLossPercent, purchaseValue, currentPurchaseValue, currentBalance) {
    var tileContainer = document.getElementsByClassName("tiles-container")[0]; // Assuming there's only one container

    // Create the main container div
    var stockTile = document.createElement("div");
    stockTile.className = "stock-tile";

    var sellButton = document.createElement('button');
    sellButton.type = "button";
    sellButton.innerText = 'Sell';

    // Add data attributes to store stock information
    sellButton.setAttribute("data-symbol", symbol);
    sellButton.setAttribute("data-purchasePrice", purchasePrice);
    sellButton.setAttribute("data-currentPrice", currentPrice);
    sellButton.setAttribute("data-quantity", quantity);
    sellButton.setAttribute("data-profitLoss", profitLoss);
    sellButton.setAttribute("data-profitLossPercent", profitLossPercent);
    sellButton.setAttribute("data-purchaseValue", purchaseValue);
    sellButton.setAttribute("data-currentPurchaseValue", currentPurchaseValue);

    sellButton.addEventListener('click', function () {
        // Extract data attributes when the button is clicked
        var symbol = this.getAttribute("data-symbol");
        var purchasePrice = this.getAttribute("data-purchasePrice");
        var currentPrice = this.getAttribute("data-currentPrice");
        var quantity = this.getAttribute("data-quantity");

        showSellTile(symbol, quantity, purchasePrice, currentPrice);

    });

    stockTile.appendChild(sellButton);
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



    // Append the stock tile to the container
    tileContainer.appendChild(stockTile);
}

function showSellTile(symbol, quantity, purchasePrice, currentPrice) {
    // Show the custom modal with instructions
    var sellTileModal = document.getElementById("sellTileModal");
    sellTileModal.style.display = "block";

    // Populate the modal with stock information
    var modalContent = sellTileModal.querySelector(".modal-content");
    modalContent.innerHTML = ""; // Clear existing content

    // Create and add stock information to the modal
    var stockInfoParagraph = document.createElement("p");
    stockInfoParagraph.textContent = "Stock: " + symbol;
    modalContent.appendChild(stockInfoParagraph);

    var purchasePriceParagraph = document.createElement("p");
    purchasePriceParagraph.textContent = "Purchase Price: " + purchasePrice;
    modalContent.appendChild(purchasePriceParagraph);

    var currentPriceParagraph = document.createElement("p");
    currentPriceParagraph.textContent = "Current Price: " + currentPrice;
    modalContent.appendChild(currentPriceParagraph);

    var quantityParagraph = document.createElement("p");
    quantityParagraph.textContent = "Amount Owned: " + quantity;
    modalContent.appendChild(quantityParagraph);

    var sellAmountInput = document.createElement("input");
    sellAmountInput.type = "number";
    sellAmountInput.placeholder = "Enter Amount to Sell";
    modalContent.appendChild(sellAmountInput);

    // Create a "Sell" button
    var sellButton = document.createElement("button");
    sellButton.type = "button";
    sellButton.innerText = 'Sell';

    // Add data attributes to store stock information
    sellButton.setAttribute("data-symbol", symbol);
    sellButton.setAttribute("data-currentPrice", currentPrice);
    sellButton.setAttribute("data-quantity", quantity);
    sellButton.setAttribute("data-amountToSell", sellAmountInput);

    sellButton.addEventListener('click', function () {
        // Extract data attributes when the button is clicked
        var symbol = this.getAttribute("data-symbol");
        var amountToSell = parseFloat(sellAmountInput.value);
        var currentPrice = this.getAttribute("data-currentPrice");
        var quantity = this.getAttribute("data-quantity");

        // showSellTile(symbol, quantity, purchasePrice, currentPrice);
        commitSaleJS(symbol, amountToSell, quantity, currentPrice);

        // Close the modal
        sellTileModal.style.display = "none";

    });

    modalContent.appendChild(sellButton);
}




function closeSellTile() {
    // Close the custom modal
    document.getElementById("sellTileModal").style.display = "none";
}

function commitSaleJS(symbol, amountToSell, stockQuantity, stockCurrentPrice) {


    commitSale(symbol, amountToSell, stockQuantity, stockCurrentPrice);

}

function commitSale() { }

