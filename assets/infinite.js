
function goToHome() {
    // Change the button text
    document.getElementById("home").innerHTML;

    // Redirect to home
    window.location.href = "app.html";
}
// function filterFunction() {
//     var input, filter, ul, li, a, i;
//     input = document.getElementById("myInput");
//     filter = input.value.toUpperCase();
//     dropdownContent = document.getElementById("dropdownContent");
//     a = dropdownContent.getElementsByTagName("a");
//     for (i = 0; i < a.length; i++) {
//         if (a[i].innerHTML.toUpperCase().indexOf(filter) > -1) {
//             a[i].style.display = "";
//         } else {
//             a[i].style.display = "none";
//         }
//     }
// }
function filterDropdown() {
    var input = document.getElementById("myInput");
    var filter = input.value.toLowerCase();
    var dropdownContent = document.getElementById("dropdownContent");
    var dropdownOptions = dropdownContent.getElementsByTagName("a");

    for (var i = 0; i < dropdownOptions.length; i++) {
        var option = dropdownOptions[i];
        if (option.textContent.toLowerCase().indexOf(filter) > -1) {
            option.style.display = "";
        } else {
            option.style.display = "none";
        }
    }
}

// Function to toggle the dropdown visibility
// Function to toggle the visibility of the dropdown options
function toggleDropdown() {
    var dropdownContent = document.getElementById("dropdownContent");
    if (dropdownContent.style.display === "block") {
        dropdownContent.style.display = "none";
    } else {
        dropdownContent.style.display = "block";
    }
}

// Close the dropdown options if the user clicks outside of it
window.onclick = function (event) {
    var searchInput = document.getElementById("myInput");

    // Check if the clicked element is not the dropdown button or the search input
    if (!event.target.matches('.dropbtn') && event.target !== searchInput) {
        var dropdowns = document.getElementsByClassName("dropdown-content");
        var i;
        for (i = 0; i < dropdowns.length; i++) {
            var openDropdown = dropdowns[i];
            if (openDropdown.style.display === "block") {
                openDropdown.style.display = "none";
            }
        }
    }
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


function addStockDropdown(linkText, linkHref) {
    var dropdown = document.getElementById("dropdownContent");
    var newLink = document.createElement("a");
    newLink.href = linkHref;
    newLink.textContent = linkText;
    dropdown.appendChild(newLink);
}