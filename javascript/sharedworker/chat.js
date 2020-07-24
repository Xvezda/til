export class Chat {
  constructor(port) {
    this.port = port
    this.port.onmessage = this.onMessage.bind(this)

    this.root = document.createElement('div')
    this.header = document.createElement('h1')
    this.header.textContent = 'fake chat'
    this.root.appendChild(this.header)

    const chatView = document.createElement('div')
    chatView.style.display = 'inline-block'

    this.view = document.createElement('textarea')

    this.userName = document.createElement('input')
    this.userName.setAttribute('required', '')

    this.userInput = document.createElement('input')
    this.userInput.style.width = '100%'

    this.sendButton = document.createElement('button')
    this.sendButton.setAttribute('type', 'submit')

    this.userInput.setAttribute('type', 'text')

    this.sendButton.textContent = 'send'
    this.sendButton.onclick = this.onSubmit.bind(this)

    this.view.setAttribute('cols', 80)
    this.view.setAttribute('rows', 25)
    this.view.setAttribute('readonly', '')

    const group = document.createElement('div')
    chatView.appendChild(group.cloneNode(true).appendChild(this.view))

    this.form = document.createElement('form')
    this.form.onsubmit = this.onSubmit.bind(this)

    const inputGroup = group.cloneNode(true)
    inputGroup.appendChild(this.userName)
    inputGroup.appendChild(this.userInput)
    inputGroup.appendChild(this.sendButton)
    inputGroup.style.display = 'flex'

    this.form.appendChild(inputGroup)
    chatView.appendChild(group.cloneNode(true).appendChild(this.form))

    this.root.appendChild(chatView)

    document.body.appendChild(this.root)

    this.userName.focus()
  }

  onSubmit(event) {
    event.preventDefault()
    if (!this.userName.checkValidity()) {
      this.form.reportValidity()
      return
    }
    const message = `${this.userName.value}: ${this.userInput.value}`
    console.log(`send clicked: @${message}`)
    this.port.postMessage(message)

    this.userInput.value = ''
  }

  onMessage(event) {
    if (!event.data) return

    console.log(`message from worker: ${event.data}`)
    this.view.textContent += event.data + '\n'
  }
}

export default Chat
