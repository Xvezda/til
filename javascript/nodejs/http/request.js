const url = process.argv[2]
const http = url.startsWith('https') ?
  require('https') :
  require('http')

new Promise((resolve, reject) => {
  http
    .get(url, {timeout: 5000}, resolve)
    .on('timeout', function () {
      this.destroy()
      reject('request timeout')
    })
    .on('error', reject)
})
  .then((response) => {
    const fragments = []
    response.on('data', (d) => fragments.push(d))

    return new Promise((resolve, reject) => {
      response.on('end', () => resolve(fragments.join('')))
    })
  })
  .then((data) => {
    console.log(data)
  })
  .catch((err) => {
    console.error(err)
  })
