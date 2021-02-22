class Foo {
  constructor() {
    console.log(this)
  }
}


class Bar extends Foo {
  constructor() {
    const s = super()
    console.log(s)
    console.log(this)
    console.log(Object.getPrototypeOf(this))
  }
}

new Bar()
