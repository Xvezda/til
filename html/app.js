class App {
  constructor() {
    this.sandbox = document.createElement('iframe')
    this.sandbox.setAttribute('sandbox', 'allow-scripts')
    this.sandbox.setAttribute('referrerpolicy', 'no-referrer')
    // this.sandbox.style.border = 'none'
    const csp = `
      <meta http-equiv="Content-Security-Policy"
            content="default-src 'self' 'unsafe-inline'">
    `
    const head = `
      ${csp}
    `
    const body = `
      <h1>foo</h1>
      <script>document.write('bar')</script>
    `
    const html = `
      <html>
        <head>
          ${head}
        </head>
        <body>
          ${body}
        </body>
      </html>
    `
    this.sandbox.srcdoc = html
    document.body.appendChild(this.sandbox)
  }
}

new App()
