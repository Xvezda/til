/** Original */

class Foo {}
class Qux extends Foo {}

/** Transpiled */

"use strict";

// Use typeof operator alternative with check type of symbol primitive support
function _typeof(obj) {
  "@babel/helpers - typeof";
  if (typeof Symbol === "function" && typeof Symbol.iterator === "symbol") {
    // _typeof is equivalent of typeof
    _typeof = function _typeof(obj) {
      return typeof obj;
    };
  } else {
    _typeof = function _typeof(obj) {
      return obj &&  // if obj is not falsy
        typeof Symbol === "function" &&  // check symbol exists
        obj.constructor === Symbol &&    // (probably a symbol polyfill)
        obj !== Symbol.prototype         // same here
        ? "symbol"     // then return symbol string
        : typeof obj;  // otherwise use typeof operator
    };
  }
  return _typeof(obj);
}

function _setPrototypeOf(o, p) {
  _setPrototypeOf =
    Object.setPrototypeOf ||
    function _setPrototypeOf(o, p) {
      // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object/proto
      o.__proto__ = p;  // __proto__ is lagacy feature
      return o;
    };
  return _setPrototypeOf(o, p);
}

function _inherits(subClass, superClass) {
  if (typeof superClass !== "function" && superClass !== null) {
    throw new TypeError("Super expression must either be null or a function");
  }
  // superClass could be function or null
  subClass.prototype = Object.create(superClass && superClass.prototype, {
    // class has constructor property as default
    constructor: { value: subClass, writable: true, configurable: true }
  });
  // subClass.__proto__ === superClass
  if (superClass) _setPrototypeOf(subClass, superClass);
}

function _isNativeReflectConstruct() {
  if (typeof Reflect === "undefined" || !Reflect.construct) return false;
  if (Reflect.construct.sham) return false;
  if (typeof Proxy === "function") return true;
  try {
    Boolean.prototype.valueOf.call(
      Reflect.construct(Boolean, [], function () {})
    );
    return true;
  } catch (e) {
    return false;
  }
}

function _createSuper(Derived) {
  var hasNativeReflectConstruct = _isNativeReflectConstruct();
  return function _createSuperInternal() {
    var Super = _getPrototypeOf(Derived),
      result;
    if (hasNativeReflectConstruct) {
      var NewTarget = _getPrototypeOf(this).constructor;
      result = Reflect.construct(Super, arguments, NewTarget);
    } else {
      result = Super.apply(this, arguments);
    }
    return _possibleConstructorReturn(this, result);
  };
}

function _possibleConstructorReturn(self, call) {
  if (call && (_typeof(call) === "object" || typeof call === "function")) {
    return call;
  } else if (call !== void 0) {
    throw new TypeError(
      "Derived constructors may only return object or undefined"
    );
  }
  return _assertThisInitialized(self);
}

function _assertThisInitialized(self) {
  if (self === void 0) {
    throw new ReferenceError(
      "this hasn't been initialised - super() hasn't been called"
    );
  }
  return self;
}

function _getPrototypeOf(o) {
  _getPrototypeOf = Object.setPrototypeOf
    ? Object.getPrototypeOf
    : function _getPrototypeOf(o) {
        return o.__proto__ || Object.getPrototypeOf(o);
      };
  return _getPrototypeOf(o);
}

function _classCallCheck(instance, Constructor) {
  if (!(instance instanceof Constructor)) {
    throw new TypeError("Cannot call a class as a function");
  }
}

var Foo = function Foo() {
  _classCallCheck(this, Foo);
};

var Qux = /*#__PURE__*/ (function (_Foo) {
  _inherits(Qux, _Foo);

  var _super = _createSuper(Qux);

  function Qux() {
    _classCallCheck(this, Qux);

    return _super.apply(this, arguments);
  }

  return Qux;
})(Foo);

