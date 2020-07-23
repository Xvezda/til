self.onmessage = function(event) {
  if (!event.data) return;

  self.postMessage(event.data);  // echo message
};
