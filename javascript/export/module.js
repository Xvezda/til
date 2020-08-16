// Private
const SECRET = "Hey, this is secret! ;) shhhh...";

exports.create = function() {
  console.log('something created...');
  // Now public
  module.exports.secret = SECRET;
};
