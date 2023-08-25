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

function addStockTile(symbol, purchasePrice, currentPrice, quantity, profitLoss, profitLossPercent, purchaseValue, currentPurchaseValue) {
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



    // Append the stock tile to the container
    tileContainer.appendChild(stockTile);
}

