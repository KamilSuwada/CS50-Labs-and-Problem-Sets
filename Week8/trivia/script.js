document.addEventListener("DOMContentLoaded", function() {
    const correctAnswers = document.getElementsByClassName('correct');
    const incorrectAnswers = document.getElementsByClassName('incorrect');

    function clear() {
        for (let i = 0; i < incorrectAnswers.length; i++) {
            incorrectAnswers[i].style.backgroundColor = '#d9edff';
        };

        for (let i = 0; i < correctAnswers.length; i++) {
            correctAnswers[i].style.backgroundColor = '#d9edff';
        };
        document.querySelector('#feedbackQ1').innerHTML = null;
    };

    for (let i = 0; i < correctAnswers.length; i++) {
        correctAnswers[i].addEventListener('click', function() {
            clear();
            correctAnswers[i].style.backgroundColor = 'green';
            document.querySelector('#feedbackQ1').innerHTML = 'Correct!';
        });
    };

    for (let i = 0; i < incorrectAnswers.length; i++) {
        incorrectAnswers[i].addEventListener('click', function() {
            clear();
            incorrectAnswers[i].style.backgroundColor = 'red';
            document.querySelector('#feedbackQ1').innerHTML = 'Incorrect.';
        });
    };

    const submitButton = document.querySelector('#checkAnswerButton');
    submitButton.addEventListener('click', function() {
        let input = document.querySelector('input');
        let n = Number(input.value);
        if (isNaN(n)) {
            document.querySelector('#feedbackQ2').innerHTML = 'This is not valid input, try again!';
            input.style.backgroundColor = 'red';
        } else {
            if (n <= 6) {
                document.querySelector('#feedbackQ2').innerHTML = 'Correct!';
                input.style.backgroundColor = 'green';
            } else {
                document.querySelector('#feedbackQ2').innerHTML = 'Incorrect.';
                input.style.backgroundColor = 'red';
            }
        }
    });
});


