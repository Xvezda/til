function logging() {
  var args = Array.from(arguments),
      output = window.output,
      rows = output.textContent.split('\n'),
      log = args.join(' ');

  rows.push(log);

  if (rows.length >= 10) {
    rows = rows.slice(-10);
  }
  output.textContent = rows.join('\n');
}

console.log = logging;

if (window.Worker) {
  console.log('worker supported');

  var worker = new Worker('worker.js'),
      userform = document.forms.userform,
      userinput = userform.userinput;

  userinput.onfocus = function(event) {
    console.log('focused');
    window.onkeypress = function(event) {
      // console.log(event);
      switch (event.key) {
        case 'Enter':
          // userform.submit();
          window.submit.click();
          break;
        default:
          break;
      }
      // console.log(userinput.value);
      // worker.postMessage({
      //   'message': userinput.value
      // })
    };
  };

  userform.onsubmit = function(event) {
    console.log('submitted');
    event.preventDefault();
    worker.postMessage({
      message: userinput.value.split('\n').slice(-1)
    });
  };

  worker.onmessage = function(event) {
    // console.log('message from worker: ' + event.data.message);
    // window.output.textContent = event.data.message;
    console.log(event.data.message);
  };

  window.terminate.onclick = function(event) {
    console.log('terminated');
    worker.terminate();
  };
}
