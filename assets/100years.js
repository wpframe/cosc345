/**
 * Redirect to homepage
 */
function goToHome() {
    window.location.href = "homepage.html";
}

/**
 * Redirect to portfolio
 */
function goToPortfolio() {
    window.location.href = "portfolio.html";
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

/**
 * Displays current price of selected stock
 * @param {number} currentPrice 
 * @param {*} stocksAvailable 
 */
function showStockInfo(currentPrice) {
    document.getElementById("currentPrice").textContent = "$" + Number(currentPrice).toFixed(2);
    // document.getElementById("stocksAvailable").textContent = stocksAvailable;
}

/**
 * Switches the text shown next to the long/short slider
 */
function switchBuySell() {
    var selectedOption = document.querySelector('.select.option');
    if (selectedOption.textContent === "Short") {
        // Change the selected option to "Short" if it's currently "Long"
        selectedOption.textContent = "Short";
        // Send this information to C++
    } else {
        // Change the selected option to "Long" if it's currently "Short" or any other text
        selectedOption.textContent = "Long";
        // Send this information to C++
    }
}


/**
 * Calculates the total price of the number of shares selected
 * @returns break out of function
 */
function updateTotalPrice() {
    var totalBalanceText = document.getElementById("balance-paragraph").textContent;
    var totalBalance = totalBalanceText.replace("Total Balance: $", "");
    totalBalance = parseFloat(totalBalance.replace(",", ""));
    var currentPriceText = document.getElementById("currentPrice").textContent;
    var currentPrice = parseFloat(currentPriceText.replace("$", ""));
    var quantity = parseInt(document.getElementById("quantity").value, 10);

    var totalPrice = (currentPrice * quantity).toFixed(2);
    var formattedNumber = Number(totalPrice).toLocaleString("en-US", { style: "currency", currency: "USD" });

    if (isNaN(quantity)) {
        document.getElementById("totalPrice").textContent = "$0.00";
    }

    document.getElementById("totalPrice").textContent = formattedNumber;

    if (parseFloat(totalPrice) > totalBalance) {
        document.getElementById("totalPrice").style.color = "#ff3343";
    } else {
        document.getElementById("totalPrice").style.color = "";
    }

}
// Add an event listener to the quantity input element
document.getElementById("quantity").addEventListener("input", updateTotalPrice);
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
 * Filters a list of items based on a search input.
 */
function filterFunction() {
    var input, filter, div, i;
    input = document.getElementById("myInput");
    filter = input.value.toUpperCase();
    div = document.getElementById("myDropdown");
    button = div.getElementsByTagName("button");
    for (i = 0; i < button.length; i++) {
        txtValue = button[i].innerText;
        // txtValue = button[i].textContent || button[i].innerText;
        if (txtValue.toUpperCase().indexOf(filter) > -1) {
            button[i].style.display = "";
        } else {
            button[i].style.display = "none";
        }
    }
}


/**
 * Toggles the dropdown display
 */
function toggleDropdown() {
    var dropdown = document.getElementById("myDropdown");
    // var dropbtn = document.getElementById("dropbtn");
    dropdown.style.display = (dropdown.style.display === "block") ? "none" : "block";
    // dropbtn.style.display = (dropdown.style.display === "none") ? "none" : "block";
}

/**
 * Adds a stock to the dropdown menu
 * @param {string} ticker 
 */
function addStockDropdown(ticker, name) {
    var dropdown = document.getElementById("myDropdown");
    var newButton = document.createElement("button");
    newButton.type = "button";


    newButton.onclick = function () {
        selectStock(ticker);
        cppSelectStock(ticker);
        var inputElement = document.getElementById("myInput");

        inputElement.value = ticker;
    };
    let combinedString = (ticker + " (" + name + ")");
    let first40Chars = combinedString.length > 35 ? combinedString.substring(0, 35) + "..." : combinedString;

    newButton.textContent = first40Chars;

    dropdown.appendChild(newButton);
}

/**
 * Sets the content of the button to the stock symbol
 * @param {string} ticker
 */
function selectStock(ticker) {
    var dropbtn = document.getElementById("myInput");
    dropbtn.textContent = ticker;
}

/**
 * displays the current date
 * @param {string} newDate 
 */
function showDate(newDate) {
    var dateElement = document.getElementById("dateTime");
    dateElement.innerHTML = newDate;
}


function commitPurchaseJS() {
    var symbol = document.getElementById('myInput').textContent;
    var selectElement = document.getElementById('actionDropdown');
    var selectedOption = selectElement.options[selectElement.selectedIndex];
    var buyOrSell = selectedOption.textContent;
    var quantity = document.getElementById('quantity').value;

    // Check if any of the required fields is null or empty
    if (!symbol || !buyOrSell || !quantity) {
        alert('Please fill out all required fields before committing the purchase.');
        return; // Prevent the purchase from being committed
    }

    commitPurchase(symbol, buyOrSell, quantity);
    window.location.reload();
}

function commitPurchase() { }