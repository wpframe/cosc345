/**
 * Redirect to homepage
 */
function goToHome() {
    window.location.href = "secondHomepage.html";
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


// Add an event listener to the quantity input element
document.getElementById("quantity").addEventListener("input", updateTotalPrice);
document.getElementById("quantity").addEventListener("change", updateTotalPrice);
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

    if (!isNaN(totalPrice)) {
        document.getElementById("totalPrice").textContent = formattedNumber;
    } else {
        document.getElementById("totalPrice").textContent = "$0.00";
    }

    if (isNaN(quantity)) {
        document.getElementById("totalPrice").textContent = "$0.00";
    }

    if (parseFloat(totalPrice) > totalBalance) {
        document.getElementById("totalPrice").style.color = "#ff3343";
    } else {
        document.getElementById("totalPrice").style.color = "";
    }

}

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

/**
 * sends relative parameters to the c++ version of commitPurchase function 
 */
function commitPurchaseJS() {
    var symbol = document.getElementById('myInput').textContent;
    // var buyOrSell = document.getElementById('buySell').innerText;
    // var buyOrSell = document.querySelector('.selected-option');
    var selectElement = document.getElementById('actionDropdown');
    var selectedOption = selectElement.options[selectElement.selectedIndex];
    var buyOrSell = selectedOption.textContent;
    // var buyOrSell = document.getElementById('actionDropdown').textContent;

    var quantity = document.getElementById('quantity').value;

    if (symbol.length >= 1 && buyOrSell.length >= 1 && quantity >= 1) {
        commitPurchase(symbol, buyOrSell, quantity)
        // window.location.reload()
    } else {
        alert("Please enter a valid action and number of shares.");
    }
}

function commitPurchase() { }

/**
 * Clears the user input fields when a purchase is made.
 */
function clearInputs() {
    // Get the input element by its ID
    var searchBar = document.getElementById("myInput");
    searchBar.value = "";

    var quantityInput = document.getElementById("quantity");
    quantityInput.value = "";

    var currentPriceDiv = document.getElementById("currentPrice");
    currentPriceDiv.innerHTML = "";

    var totalPriceDiv = document.getElementById("totalPrice");
    totalPriceDiv.innerHTML = "";
}

/**
 * updates the users total balance when a purchase is made.
 * @param {string} newBalance 
 */
function updateBalance(newBalance) {
    var balanceContainer = document.getElementsByClassName("totalBalance")[0];

    // Remove the existing balance paragraph (if any)
    var existingParagraph = balanceContainer.querySelector("h");
    if (existingParagraph) {
        balanceContainer.removeChild(existingParagraph);
    }

    // Create a new paragraph with the updated balance
    var balanceParagraph = document.createElement("h");
    balanceParagraph.id = "balance-paragraph";
    balanceParagraph.textContent = "Total Balance: " + Number(newBalance).toLocaleString("en-US", { style: "currency", currency: "USD" });
    balanceContainer.appendChild(balanceParagraph);
}

/**
 * opens the popup indicating the end of the game.
 * @param {string} balance 
 */
function openEndPopup(balance) {
    const popup = document.getElementById('end-game-popup');
    const popupMessage = document.getElementById('popup-message');
    popupMessage.textContent = "Game over! You made " + Number(balance).toLocaleString("en-US", { style: "currency", currency: "USD" });
    popup.style.display = 'block';
}

/**
 * resets all game states. Sends the user back to homescreen
 */
function closeEndPopup() {
    const popup = document.getElementById('end-game-popup');
    window.location.href = "homepage.html";
    popup.style.display = 'none';
}

/**
 * Adds the graph to the div element "container". Currently super buggy if you look at one stock and then another. 
 * This is called in cppSelectStock() in MyApp.
 */

function getFilePath(ticker) {
    var filepath = "data/stocks/" + ticker + ".csv";
    document.getElementById('container').innerHTML = '';

    anychart.data.loadCsvFile(filepath, function (data) {
        anychart.theme('darkBlue');
        const lines = data.split('\n');
        let csvString = 'Date,Close\n';
        for (let i = 1; i < lines.length; i++) {

            const columns = lines[i].split(',');
            const date = columns[0];
            const close = columns[4];
            csvString += date + ',' + close + '\n';
        }
        var chart = anychart.line(csvString, { ignoreFirstRow: true });
        chart.title(ticker)
        chart.container('container');
        chart.bounds(0, 0, "100%", "89%");
        chart.draw();
    });
}

