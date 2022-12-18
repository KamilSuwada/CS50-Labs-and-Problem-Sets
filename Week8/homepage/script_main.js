// Script for the main page.


// Constants:
const pages = {
    "General" : "index.html",
    "Interests" : "interests.html",
    "Education" : "education.html",
    "About" : "about.html"
}


document.addEventListener("DOMContentLoaded", function() {

    // Title of the current page:
    let pageTitle = document.title;

    // Get all buttons:
    let buttons = document.getElementsByClassName('btn');

    for (let i = 0; i < buttons.length; i++) {
        let buttonID = buttons[i].textContent;
        let page = pages[buttonID];
        if (typeof page !== 'undefined') {
            if (buttonID === pageTitle) {
                buttons[i].style.color = 'gray';
            }
            buttons[i].addEventListener('click', function() {
                window.location.replace(page);
            })
        } else {
            alert("Something went wrong while loading the page. Please reload.")
        }
    }
});