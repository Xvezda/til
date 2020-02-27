
async function main() {
  const mongoose = require('mongoose');

  // Try connection until success
  for (let maxTry = 3; maxTry > 0; --maxTry) {
    try {
      await mongoose.connect('mongodb://localhost/test', {
        useNewUrlParser: true,
        useUnifiedTopology: true
      });
      break;
    } catch(e) {
      console.log('failed to connect mongodb');

      console.log('gracefully exit...');
      process.exit(0);
    }
  }

  const db = mongoose.connection;
  /*
  db.on('error', console.error.bind(console, 'connection error:'));
  db.once('open', function() {
    // we're connected!
  });
  */

}

main();

