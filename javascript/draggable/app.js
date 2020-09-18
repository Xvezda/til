
class App {
  constructor() {
    this.createBox = this.createBox.bind(this)
    this.parent = document.body
    this.parent.ondrag = event => event.preventDefault()

    this.boxes = []
    this.counter = 1
    this.dragged = null

    for (let i = 0; i < 5; ++i) {
      this.createBox()
    }
    console.log(this.boxes)
  }

  createBox() {
    const box = document.createElement('div')
    box.style.width = '100px'
    box.style.height = '100px'
    box.style.border = '1px solid gray'
    box.style.boxSizing = 'border-box'
    box.style.padding = '28px'

    box.style.fontSize = '32px'
    box.style.textAlign = 'center'

    box.setAttribute('draggable', 'true')

    box.addEventListener('dragstart', this.onDragStart.bind(this), false)
    box.addEventListener('dragenter', this.onDragEnter.bind(this), false)
    box.addEventListener('dragover', this.onDragOver.bind(this), false)
    box.addEventListener('dragend', this.onDragEnd.bind(this), false)

    box.dataset.num = this.counter
    box.textContent = this.counter

    ++this.counter
    this.boxes.push(box)
    this.parent.appendChild(box)
  }

  onDragStart(event) {
    console.log('dragstart:', event)
    event.dataTransfer.setData('text/plain', this.counter)
    event.dataTransfer.effectAllowed = 'move'

    this.dragged = event.target
  }

  onDragEnter(event) {
    console.log('dragenter:', event)

    let from = this.dragged
    let to = event.target

    if (from === to) return
    console.log('from:', from, 'to:', to)

    if (from.nextSibling === to) {
      to = to.nextSibling
    }
    to.parentNode.insertBefore(from, to)
  }

  onDragOver(event) {
    event.preventDefault()
  }

  onDragEnd(event) {
    console.log('dragend:', event)
  }
}

new App()
