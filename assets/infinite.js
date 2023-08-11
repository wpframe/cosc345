
function goToHome() {
    // Change the button text
    document.getElementById("home").innerHTML;

    // Redirect to home
    window.location.href = "app.html";
}

function showStockInfo(currentPrice, stocksAvailable) {
    document.getElementById("currentPrice").textContent = currentPrice;
    document.getElementById("stocksAvailable").textContent = stocksAvailable;
}

function switchBuySell() {
    var button = document.getElementById("buySell");
    if (button.innerHTML === "Buy") {
        // Change the content to "Sell" if it's currently "Buy"
        button.innerHTML = "Sell";
    } else {
        // Change the content to "Buy" if it's currently "Sell" or any other text
        button.innerHTML = "Buy";
    }
}
function updateTotalPrice() {
    var currentPrice = parseFloat(document.getElementById("currentPrice").textContent.slice(1));
    var quantity = parseInt(document.getElementById("quantity").value);

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

    if (event.target !== dropdown && event.target !== searchInput && event.target !== dropdownButton) {
        dropdown.style.display = "none";
        dropdownButton.style.display = "block";
    }
});

function filterFunction() {
    var input, filter, a, i;
    input = document.getElementById("myInput");
    filter = input.value.toUpperCase();
    div = document.getElementById("myDropdown");
    a = div.getElementsByTagName("a");
    for (i = 0; i < a.length; i++) {
        txtValue = a[i].textContent || a[i].innerText;
        if (txtValue.toUpperCase().indexOf(filter) > -1) {
            a[i].style.display = "";
        } else {
            a[i].style.display = "none";
        }
    }
}




// Toggle dropdown display
function toggleDropdown() {
    var dropdown = document.getElementById("myDropdown");
    var dropbtn = document.getElementById("dropbtn");
    dropdown.style.display = (dropdown.style.display === "block") ? "none" : "block";
    dropbtn.style.display = (dropdown.style.display === "block") ? "block" : "none";

}


function addStockDropdown(ticker) {
    var dropdown = document.getElementById("myDropdown");
    var newButton = document.createElement("button");
    newButton.type = "button";
    newButton.onclick = "selectStock('" + ticker + "')";
    newButton.textContent = ticker;
    dropdown.appendChild(newButton);
}