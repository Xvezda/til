// https://ko.wikipedia.org/wiki/%ED%94%84%EB%A1%9C%ED%86%A0%ED%83%80%EC%9E%85_%EA%B8%B0%EB%B0%98_%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D
// Example of true prototypal inheritance style
// in JavaScript.

// "ex nihilo" object creation employing the literal
// object notation {}.
var foo = {one: 1, two: 2};

// Another "ex nihilo" object.
var bar = {three: 3};

// Gecko and Webkit JavaScript engines can directly
// manipulate the internal prototype link.
// For the sake of simplicity, let's just pretend
// that the following line works regardless of the
// engine used:
bar.__proto__ = foo; // foo is now the parent of bar.

// If we try to access foo's properties from bar
// from now on, we'll succeed.
console.log(bar.one); // Resolves to 1.

// The child object's properties are also accessible.
console.log(bar.three); // Resolves to 3.
