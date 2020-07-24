import Chat from './chat.js'


class App {
  constructor() {
    this.worker = new SharedWorker('worker.js')
    this.chat = new Chat(this.worker.port)
  }
}

new App()
