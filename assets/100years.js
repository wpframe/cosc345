function goToHome() {
    window.location.href = "homepage.html";
}

function goToPortfolio() {
    window.location.href = "portfolio.html";
}

function showStockInfo(currentPrice, stocksAvailable) {
    document.getElementById("currentPrice").textContent = currentPrice;
    // document.getElementById("stocksAvailable").textContent = stocksAvailable;
}

function switchBuySell() {
    var button = document.getElementById("buySell");
    if (button.innerHTML === "Long") {
        // Change the content to "Sell" if it's currently "Buy"
        button.innerHTML = "Short";
        // send this information to c++ 
    } else {
        // Change the content to "Buy" if it's currently "Sell" or any other text
        button.innerHTML = "Long";
        // send this information to c++ 
    }
}

function updateTotalPrice() {
    var currentPrice = parseFloat(document.getElementById("currentPrice").textContent.slice(18));
    var quantity = parseInt(document.getElementById("quantity").value, 10);

    var totalPrice = currentPrice * quantity;

    if (isNaN(quantity)) {
        document.getElementById("totalPrice").textContent = "Total Price: $0.00";
        return;
    }

    document.getElementById("totalPrice").textContent = "Total Price: $" + totalPrice.toFixed(2);
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
    var input, filter, a, i;
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

function initBalance(totalBalance) {
    var balanceContainer = document.getElementsByClassName("totalBalance")[0];
    var balanceParagraph = document.createElement("h");
    balanceParagraph.textContent = "Total Balance: " + totalBalance;
    balanceContainer.appendChild(balanceParagraph);
}

// Toggle dropdown display
function toggleDropdown() {
    var dropdown = document.getElementById("myDropdown");
    var dropbtn = document.getElementById("dropbtn");
    dropdown.style.display = (dropdown.style.display === "block") ? "none" : "block";
    dropbtn.style.display = (dropdown.style.display === "none") ? "none" : "block";
}

function addStockDropdown(ticker) {
    var dropdown = document.getElementById("myDropdown");
    var newButton = document.createElement("button");
    newButton.type = "button";
    newButton.onclick = function () {
        selectStock(ticker);
        cppSelectStock(ticker);
    };
    newButton.textContent = ticker;
    dropdown.appendChild(newButton);
}

function selectStock(ticker) {
    var dropbtn = document.getElementById("dropbtn");
    dropbtn.textContent = ticker;
}

function showDate(newDate) {
    var dateElement = document.getElementById("dateTime");
    dateElement.innerHTML = newDate;
}


var playPauseButton = document.getElementById("playPauseButton");
var iconElement = playPauseButton.querySelector("i");
var isPlaying = false;

playPauseButton.addEventListener("click", function switchPlayPause() {
    if (isPlaying) {
        // Change to play icon
        iconElement.className = "fas fa-play";
        isPlaying = false;
        console.log("timer should be stopped");
        stopTimer();
    } else {
        // Change to pause icon
        iconElement.className = "fas fa-pause";
        isPlaying = true;
        startTimer();
    }
});

function swapPlayAndPause() {
    if (iconElement.className == "fas fa-play") {
        iconElement.className = "fas fa-pause";
    } else {
        iconElement.className = "fas fa-play";
    }
}


function commitPurchaseJS() {
    var symbol = document.getElementById('dropbtn').textContent;
    var buyOrSell = document.getElementById('buySell').innerText;
    var quantity = document.getElementById('quantity').value;

    commitPurchase(symbol, buyOrSell, quantity)
    window.location.reload()
}

function commitPurchase() { }