function blink() {

    let blinkers = document.querySelector('#bli');

    if (blinkers.style.visibility === 'hidden')
    {
        blinkers.style.visibility = 'visible';
    }
    else
    {
        blinkers.style.visibility = 'hidden';
    }
}
 window.setInterval(blink, 500);