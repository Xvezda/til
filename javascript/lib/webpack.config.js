var path = require('path');
var packageJson = require('./package.json');

module.exports = {
  mode: 'production',
  entry: path.join(__dirname, packageJson.main),
  output: {
    path: __dirname,
    filename: 'xvzd.js'
  },
  module: {
    rules: [
      {
        test: /\.ts$/,
        exclude: /node_modules/,
        use: [
          {
            loader: 'babel-loader'
          }
        ]
      }
    ]
  },
  optimization: {
    minimize: false
  }
};
