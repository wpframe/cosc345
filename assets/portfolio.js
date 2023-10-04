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

/**
 * 
 * Shows the users balance
 * @param {number} totalBalance 
 */
function initBalance(totalBalance) {
    var balanceContainer = document.getElementsByClassName("totalBalance")[0];
    var balanceParagraph = document.createElement("h");
    balanceParagraph.id = "balance-paragraph";
    balanceParagraph.textContent = "Total Balance: " + Number(totalBalance).toLocaleString("en-US", { style: "currency", currency: "USD" });
    balanceContainer.appendChild(balanceParagraph);
}

function updateBalance(newBalance) {
    var balanceContainer = document.getElementsByClassName("totalBalance")[0];

    // Remove the existing balance paragraph (if any)
    var existingParagraph = balanceContainer.querySelector("h");
    if (existingParagraph) {
        balanceContainer.removeChild(existingParagraph);
    }

    // Create a new paragraph with the updated balance
    var balanceParagraph = document.createElement("h");
    balanceParagraph.textContent = "Total Balance: " + Number(newBalance).toLocaleString("en-US", { style: "currency", currency: "USD" });
    balanceContainer.appendChild(balanceParagraph);
}


function addInvestmentSummary(amountBorrowed, totalInvestment, portfolioValue, totalProfit, totalProfitPercentage) {
    var tileContainer = document.getElementsByClassName("investment-summary")[0];

    // Create the main container div
    var summaryTile = document.createElement("div");
    summaryTile.className = "summary-tile";

    // Display "Amount Borrowed"
    var amountBorrowedLabel = document.createElement("p");
    amountBorrowedLabel.textContent = "Amount Borrowed: " + Number(amountBorrowed).toLocaleString("en-US", { style: "currency", currency: "USD" });
    summaryTile.appendChild(amountBorrowedLabel);

    // Display "Total Investment"
    var totalInvestmentLabel = document.createElement("p");
    totalInvestmentLabel.textContent = "Total Investment: " + Number(totalInvestment).toLocaleString("en-US", { style: "currency", currency: "USD" });;
    summaryTile.appendChild(totalInvestmentLabel);

    var portfolioValueParagraph = document.createElement("p");
    portfolioValueParagraph.textContent = "Current Portfolio Value: " + Number(portfolioValue).toLocaleString("en-US", { style: "currency", currency: "USD" });
    summaryTile.appendChild(portfolioValueParagraph);

    var totalProfitParagraph = document.createElement("p");
    var profitSpan = document.createElement("span");

    if (totalProfit < 0) {
        profitSpan.textContent = "-$" + Math.abs(totalProfit) + " (" + totalProfitPercentage + "%)";
    } else {
        profitSpan.textContent = "$" + totalProfit + " (" + totalProfitPercentage + "%)";
    }
    
    if (totalProfit > 0) {
        profitSpan.style.color = "green";
    } else if (totalProfit < 0) {
        profitSpan.style.color = "red";
    } else {
        profitSpan.style.color = "white";
    }

    totalProfitParagraph.textContent = "Total Profit/Loss: ";
    totalProfitParagraph.appendChild(profitSpan);

    summaryTile.appendChild(totalProfitParagraph);


    // Append the main container div to the tile container
    tileContainer.appendChild(summaryTile);
}

function updateInvestmentSummary(amountBorrowed, totalInvestment, portfolioValue, totalProfit, totalProfitPercentage) {
    var tileContainer = document.getElementsByClassName("investment-summary")[0]; // Assuming there's only one container

    // Remove the existing summary (if any)
    var existingSummaryTile = tileContainer.querySelector("div");
    if (existingSummaryTile) {
        tileContainer.removeChild(existingSummaryTile);
    }
    addInvestmentSummary(amountBorrowed, totalInvestment, portfolioValue, totalProfit, totalProfitPercentage);
}

/**
 * displays the current date
 * @param {string} newDate 
 */
function showDate(newDate) {
    var dateElement = document.getElementById("dateTime");
    dateElement.innerHTML = newDate;
}

function addStockTile(type, symbol, purchasePrice, currentPrice, quantity,
    profitLoss, profitLossPercent, purchaseValue, currentPurchaseValue, headline, multiplier) {
    var tileContainer = document.getElementsByClassName("tiles-container")[0]; // Assuming there's only one container

    // Create the main container div
    var stockTile = document.createElement("div");
    stockTile.className = "stock-tile";

    var sellButton = document.createElement('button');
    sellButton.type = "button";
    sellButton.innerText = 'Sell';
    sellButton.className = 'sell-button';
    // Add data attributes to store stock information
    sellButton.setAttribute("data-type", type);
    sellButton.setAttribute("data-symbol", symbol);
    sellButton.setAttribute("data-purchasePrice", Number(purchasePrice).toFixed(2));
    sellButton.setAttribute("data-currentPrice", Number(currentPrice).toFixed(2));
    sellButton.setAttribute("data-quantity", Number(quantity));
    sellButton.setAttribute("data-profitLoss", Number(profitLoss).toFixed(2));
    sellButton.setAttribute("data-profitLossPercent", Number(profitLossPercent).toFixed(2));
    sellButton.setAttribute("data-purchaseValue", Number(purchaseValue).toFixed(2));
    sellButton.setAttribute("data-currentPurchaseValue", Number(currentPurchaseValue).toFixed(2));

    sellButton.addEventListener('click', function () {
        // Extract data attributes when the button is clicked
        var type = this.getAttribute("data-type");
        var symbol = this.getAttribute("data-symbol");
        var purchasePrice = this.getAttribute("data-purchasePrice");
        var currentPrice = this.getAttribute("data-currentPrice");
        var quantity = this.getAttribute("data-quantity");

        showSellTile(type, symbol, quantity, purchasePrice, currentPrice);

    });

    stockTile.appendChild(sellButton);
    // Create and add stock name 
    var typeParagraph = document.createElement("p");
    typeParagraph.textContent = "Holding: " + type; // Change this to the holding type (long or short)
    stockTile.appendChild(typeParagraph);

    var stockNameParagraph = document.createElement("p");
    stockNameParagraph.textContent = "Stock: " + symbol; // Change this to the actual stock name
    stockTile.appendChild(stockNameParagraph);

    var quantityParagraph = document.createElement("p");
    quantityParagraph.textContent = "Quantity: " + quantity; // Change this to the actual price
    stockTile.appendChild(quantityParagraph);

    // Create and add purchase price
    var purchasePriceParagraph = document.createElement("p");
    purchasePriceParagraph.textContent = "Purchase Price: " + Number(purchasePrice).toLocaleString("en-US", { style: "currency", currency: "USD" }); // Change this to the actual price
    stockTile.appendChild(purchasePriceParagraph);

    // Create and add current price
    var currentPriceParagraph = document.createElement("p");
    currentPriceParagraph.id = "current-price"
    currentPriceParagraph.textContent = "Current Price: " + Number(currentPrice).toLocaleString("en-US", { style: "currency", currency: "USD" }); // Change this to the actual price
    stockTile.appendChild(currentPriceParagraph);

    var purchaseValueLabel = type === "Short" ? "Amount Borrowed" : "Amount Invested";
    var purchaseValueParagraph = document.createElement("p");
    purchaseValueParagraph.textContent =
        purchaseValueLabel + ": " + Number(purchaseValue).toLocaleString("en-US", { style: "currency", currency: "USD" }); // Change this to the actual price
    stockTile.appendChild(purchaseValueParagraph);

    // // Create and add total amount invested
    // var purchaseValueParagraph = document.createElement("p");
    // purchaseValueParagraph.textContent = "Amount Invested: " + purchaseValue; // Change this to the actual price
    // stockTile.appendChild(purchaseValueParagraph);

    // Create and add how much the investment is now
    var currentPurchaseValueParagraph = document.createElement("p");
    currentPurchaseValueParagraph.textContent =
        "Investment Total Now: " + Number(currentPurchaseValue).toLocaleString("en-US", { style: "currency", currency: "USD" }); // Change this to the actual price
    stockTile.appendChild(currentPurchaseValueParagraph);

    var profitLossParagraph = document.createElement("p");
    var profitLossSpan = document.createElement("span");

    if (profitLoss < 0) {
        profitLossSpan.textContent = "-$" + Math.abs(profitLoss) + " (" + profitLossPercent + "%)";
    } else {
        profitLossSpan.textContent = "$" + profitLoss + " (" + profitLossPercent + "%)";
    }
    
    if (profitLoss > 0) {
        profitLossSpan.style.color = "green";
    } else if (profitLoss < 0) {
        profitLossSpan.style.color = "red";
    } else {
        profitLossSpan.style.color = "white";
    }

    profitLossParagraph.textContent = "Profit/Loss: ";
    profitLossParagraph.appendChild(profitLossSpan);

    stockTile.appendChild(profitLossParagraph);


    var headlineString = headline.toString();

    if (headlineString.length > 2) {
        var headlineParagrah = document.createElement("p");
        headlineParagrah.className = "headlineParagraph";
        headlineParagrah.textContent = "News this week: " + headline; // Change this to the actual price
        stockTile.appendChild(headlineParagrah);

        var multiplierParagraph = document.createElement("p");
        multiplierParagraph.className = "multiplier";
        multiplierParagraph.textContent = "changed total stock value by: " + multiplier; // Change this to the actual price
        stockTile.appendChild(multiplierParagraph);
    }

    // Append the stock tile to the container
    tileContainer.appendChild(stockTile);
}

function showSellTile(type, symbol, quantity, purchasePrice, currentPrice) {
    // Show the custom modal with instructions
    var sellTileModal = document.getElementById("sellTileModal");
    sellTileModal.style.display = "block";

    // Populate the modal with stock information
    var modalContent = sellTileModal.querySelector(".modal-content");
    modalContent.innerHTML = ""; // Clear existing content
    var closeButton = document.createElement("button");
    closeButton.type = "button";
    closeButton.className = "close"
    closeButton.innerText = 'Close';
    closeButton.addEventListener('click', function () {
        document.getElementById("sellTileModal").style.display = "none";
    });
    // Create and add stock information to the modal
    var typeParagraph = document.createElement("p");
    typeParagraph.textContent = "Holding Type: " + type;
    modalContent.appendChild(typeParagraph);

    var stockInfoParagraph = document.createElement("p");
    stockInfoParagraph.textContent = "Stock: " + symbol;
    modalContent.appendChild(stockInfoParagraph);

    var purchasePriceParagraph = document.createElement("p");
    purchasePriceParagraph.textContent = "Purchase Price: " + Number(purchasePrice).toLocaleString("en-US", { style: "currency", currency: "USD" });
    modalContent.appendChild(purchasePriceParagraph);

    var currentPriceParagraph = document.createElement("p");
    currentPriceParagraph.textContent = "Current Price: " + Number(currentPrice).toLocaleString("en-US", { style: "currency", currency: "USD" });
    modalContent.appendChild(currentPriceParagraph);

    var quantityParagraph = document.createElement("p");
    quantityParagraph.textContent = "Amount Owned: " + quantity;
    modalContent.appendChild(quantityParagraph);

    var sellAmountInput = document.createElement("input");
    sellAmountInput.type = "number";
    sellAmountInput.placeholder = "Enter Amount to Sell";
    modalContent.appendChild(sellAmountInput);

    var amountToReceive = document.createElement("p");
    amountToReceive.textContent = "Amount to recieve: " + quantity * parseFloat(sellAmountInput.value);
    modalContent.appendChild(amountToReceive);
    // Create a "Sell" button
    var sellButton = document.createElement("button");
    sellButton.type = "button";
    sellButton.innerText = 'Sell';

    // Add data attributes to store stock information
    sellButton.setAttribute("data-type", type);
    sellButton.setAttribute("data-symbol", symbol);
    sellButton.setAttribute("data-currentPrice", currentPrice);
    sellButton.setAttribute("data-quantity", quantity);
    sellButton.setAttribute("data-amountToSell", sellAmountInput);
    sellButton.setAttribute("data-amountToSell", sellAmountInput);

    sellButton.addEventListener('click', function () {
        // Extract data attributes when the button is clicked
        var type = this.getAttribute("data-type");
        var symbol = this.getAttribute("data-symbol");
        var amountToSell = parseFloat(sellAmountInput.value);
        var currentPrice = this.getAttribute("data-currentPrice");
        var quantity = this.getAttribute("data-quantity");

        if (amountToSell > 0) {

            commitSaleJS(type, symbol, amountToSell, quantity, currentPrice);
        }

        sellTileModal.style.display = "none";
        window.location.reload()

    });

    modalContent.appendChild(sellButton);
    modalContent.appendChild(closeButton);
}

function closeSellTile() {
    // Close the custom modal
    document.getElementById("sellTileModal").style.display = "none";
}

function commitSaleJS(symbol, amountToSell, stockQuantity, stockCurrentPrice) {
    commitSale(symbol, amountToSell, stockQuantity, stockCurrentPrice);

}

function commitSale() { }

/**
 * Toggles the dropdown display
 */
function toggleDropdown() {
    var dropdown = document.getElementById("myDropdown");
    // var dropbtn = document.getElementById("dropbtn");
    dropdown.style.display = (dropdown.style.display === "block") ? "none" : "block";
    // dropbtn.style.display = (dropdown.style.display === "none") ? "none" : "block";
}

// /**
//  * Filters a list of items based on a search input.
//  */
// function filterFunction() {
//     var input, filter, div, i;
//     input = document.getElementById("myInput");
//     filter = input.value.toUpperCase();
//     div = document.getElementById("myDropdown");
//     button = div.getElementsByTagName("button");
//     for (i = 0; i < button.length; i++) {
//         txtValue = button[i].innerText;
//         // txtValue = button[i].textContent || button[i].innerText;
//         if (txtValue.toUpperCase().indexOf(filter) > -1) {
//             button[i].style.display = "";
//         } else {
//             button[i].style.display = "none";
//         }
//     }
// }

/**
 * Adds a college to the dropdown menu
 * @param {string} name - The name of the college.
 * @param {string} rank - The rank of the college.
 */
function addCollegeDropdown(name, rank) {
    var dropdown = document.getElementById("myDropdown");
    var newButton = document.createElement("button");
    newButton.type = "button";
    newButton.setAttribute = ("id", name);

    // Create a <span> for the name and rank
    var nameSpan = document.createElement("span");
    nameSpan.textContent = name;

    var rankSpan = document.createElement("span");
    rankSpan.textContent = "Rank: " + rank;

    // Add the name and rank <span> elements to the button
    newButton.appendChild(nameSpan);
    newButton.appendChild(document.createElement("br")); // Add a line break if needed
    newButton.appendChild(rankSpan);

    newButton.onclick = function () {
        cppSelectCollege(name);
        selectCollege(name);
    };

    // Add the button to the dropdown
    dropdown.appendChild(newButton);
}

const popup_success = document.getElementById("popup-success");
const popup_unsuccess = document.getElementById("popup-unsuccess");
/**
 * Sets the content of the button to the stock symbol
 * @param {string} name
 */
function selectCollege(name) {
    var dropbtn = document.getElementById("dropbtn");
    dropbtn.textContent = name;

    var result = document.getElementById("result");
    if (result.textContent == "success") {
        popup_success.style.display = "block";
    } else {
        popup_unsuccess.style.display = "block";
    }
}

/**
 * Event listener triggers function when the window is clicked outside of the dropdown
 */
window.addEventListener("click", function (event) {
    var dropdown = document.getElementById("myDropdown");
    var searchInput = document.getElementById("myInput");
    var dropdownButton = document.querySelector(".dropbtn");

    if (
        event.target !== dropdown && event.target !== searchInput && event.target !== dropdownButton) {
        dropdown.style.display = "none";
        dropdownButton.style.display = "block";
    }
});

/**
 * Closes success popup
 */
const closeSuccessPopupButton = document.getElementById("closeSuccessPopup");
closeSuccessPopupButton.addEventListener("click", (event) => {
    popup_success.style.display = "none";
});

/**
 * Closes unsuccessful popup
 */
const closeUnsuccessPopupButton = document.getElementById("closeUnsuccessPopup");
closeUnsuccessPopupButton.addEventListener("click", (event) => {
    popup_unsuccess.style.display = "none";
});

// Close the pop-up if the user clicks outside of it
window.addEventListener("click", (event) => {
    if (event.target === popup_success) {
        popup_success.style.display = "none";
    }
    else if (event.target === popup_unsuccess) {
        popup_unsuccess.style.display = "none";
    }
});

function acceptOfferJS() {
    var dropbtn = document.getElementById("dropbtn");
    var name = dropbtn.textContent;

    var pop_success = document.getElementById("popup-success");
    pop_success.style.display = "none";

    var education_selection_container = document.querySelector(".education-selection-container");
    if (education_selection_container) {
        education_selection_container.style.display = "none";
    }

    var education_container = document.querySelector(".education-container");
    if (education_container) {
        education_container.style.display = "block";
    }
    acceptOffer(name);
    window.location.reload();
}


function declineOfferJS() {
    popup_success.style.display = "none";
    var dropbtn = document.getElementById("dropbtn");
    var name = dropbtn.textContent;

    var declinedCollege = document.getElementById(name);
    declinedCollege.style.display = "none";
    declinedCollege.remove();
    declineOffer(name);
}


function showCareerStage(stage) {
    var education_selection_container = document.querySelector(".education-selection-container");
    var education_container = document.querySelector(".education-container");
    var job_container = document.querySelector(".job-container");
    if (stage == 0) {
        education_selection_container.style.display = "block";
        education_container.style.display = "none";
        job_container.style.display = "none";
    } else if (stage == 1) {
        education_selection_container.style.display = "none";
        education_container.style.display = "block";
        job_container.style.display = "none";
    } else {
        education_selection_container.style.display = "none";
        education_container.style.display = "none";
        job_container.style.display = "block";
    }
}

function showTuitionDetails(collegeName, remainingTimeParam, tuitionParam) {
    var remainingTime = document.getElementById("remainingTime");
    remainingTime.textContent = "Time remaining at " + collegeName + ": " + remainingTimeParam;

    var tuition = document.getElementById("tuition");
    tuition.textContent = "Tuition costs per year: " + tuitionParam;
}

function showJobDetails(collegeName, salary) {
    var graduatedFrom = document.getElementById("grad");
    graduatedFrom.textContent = "Graduated from: " + collegeName;

    var currentSalary = document.getElementById("income");
    currentSalary.textContent = "Current salary: $" + salary;
}

function raiseRequestedJS() {
    var rasieRes = document.getElementById('raiseResult');
    raiseRequested();
}
