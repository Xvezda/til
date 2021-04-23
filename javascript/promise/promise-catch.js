
// General catch routine
new Promise((resolve, reject) => {
  reject()
}).catch((err) => {
  console.log('catch chain')
})

// Not gonna work
try {
  new Promise((resolve, reject) => {
    reject()
  })
} catch (e) {
  console.log('catch statement')
}
