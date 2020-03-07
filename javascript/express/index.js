var express = require('express');

var app = express();

app.get('/', function(req, res, next) {
  console.log('app:', app);
  console.log('req.app:', req.app);
  console.log('res.app:', res.app);
  console.log('app === req.app:', app === req.app);
  console.log('app === res.app:', app === req.app);

  console.dir(app.mountpath);

  console.log(res.headersSent);
  res.end();
  console.log(res.headersSent);
});

app.get('/user/:id', function (req, res, next) {
  // if the user ID is 0, skip to the next route
  if (req.params.id == 0) next('route');
  // otherwise pass the control to the next middleware function in this stack
  else next(); //
}, function (req, res, next) {
  // render a regular page
  res.send('regular');
  // res.render('regular');
});

// handler for the /user/:id path, which renders a special page
app.get('/user/:id', function (req, res, next) {
  res.send('special')
  // res.render('special');
});

app.listen(3333);
