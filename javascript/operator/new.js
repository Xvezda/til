function mimicNew(ctorFunc) {
  const thisObj = {};
  thisObj.__proto__ = ctorFunc.prototype;
  const args = [];
  for (let i = 1; i < arguments.length; i++) {
    args.push(arguments[i]);
  }
  return ctorFunc.apply(thisObj, args) || thisObj;
}


function Cat(sound) {
  this.name = 'Garfield';
  this.sound = sound;
}

Cat.prototype.sayName = function sayName() {
  console.log("I'm " + this.name + ".");
};

Cat.prototype.makeSound = function makeSound() {
  console.log('*' + this.sound.toUpperCase() + '*');
};


const cat = mimicNew(Cat, 'Meow');
cat.sayName();
cat.makeSound();

const cat2 = new Cat('Meow');
cat2.sayName();
cat2.makeSound();

