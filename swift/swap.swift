func swap<T> (_ a: inout T, _ b: inout T) {
  let temp: T = a
  a = b
  b = temp
}

infix operator <=>: AssignmentPrecedence
extension String {
  static func <=> (left: inout String, right: inout String) {
    swap(&left, &right)
  }
}

var (foo, bar) = ("World", "Hello")
foo <=> bar  // Swap
print("\(foo), \(bar)") // Hello, World
