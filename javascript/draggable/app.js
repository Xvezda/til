function pickAndPut(array, from, to) {
  console.assert(from >= 0 && to >= 0)
  const tmp = array[from]
  if (from > to) {
    for (let i = from; i > to; --i) {
      array[i] = array[i-1]
    }
  } else {
    for (let i = from; i < to; ++i) {
      array[i] = array[i+1]
    }
  }
  array[to] = tmp
}

class App {
  constructor() {
    this.resetStyle()

    this.container = document.createElement('div')
    this.container.classList.add('container')
    this.container.style.margin = '8px'
    document.body.appendChild(this.container)

    this.createBox = this.createBox.bind(this)
    this.parent = this.container
    this.parent.ondrag = event => event.preventDefault()

    this.boxes = []
    this.counter = 1
    this.dragged = null

    for (let i = 0; i < 5; ++i) {
      this.createBox()
    }
    console.log(this.boxes)
  }

  resetStyle() {
    const style = document.createElement('style')
    style.textContent = `
    html, body {
      margin: 0;
    }

    body {
      font-size: 1em;
    }
    `
    document.head.appendChild(style)
  }

  createBox() {
    const box = document.createElement('div')
    box.style.display = 'inline-block'
    box.style.width = '100px'
    box.style.height = '100px'
    box.style.border = '1px solid gray'
    box.style.backgroundColor = 'white'
    box.style.boxSizing = 'border-box'
    box.style.padding = '28px'
    box.style.margin = '5px'

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
    event.dataTransfer.setData('text/plain', event.target.dataset.num)
    event.dataTransfer.effectAllowed = 'move'

    this.dragged = event.target
  }

  onDragEnter(event) {
    console.log('dragenter:', event)

    let from = this.dragged
    let to = event.target

    console.log('from:', from, 'to:', to)
    console.log(from.dataset.num, to.dataset.num)

    const fromIdx = this.boxes.indexOf(from)
    const toIdx = this.boxes.indexOf(to)
    if (fromIdx === toIdx) return

    console.log(fromIdx, toIdx, this.boxes[fromIdx], this.boxes[toIdx])
    pickAndPut(this.boxes, fromIdx, toIdx)
    console.log(this.boxes.map(box => box.dataset.num))

    if (fromIdx > toIdx) {
      this.parent.insertBefore(from, to)
    } else {
      this.parent.insertBefore(from, to.nextSibling)
    }
  }

  onDragOver(event) {
    event.preventDefault()
  }

  onDragEnd(event) {
    console.log('dragend:', event)
  }
}

new App()
