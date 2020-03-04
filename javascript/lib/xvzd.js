/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = 0);
/******/ })
/************************************************************************/
/******/ ([
/* 0 */
/***/ (function(module, exports, __webpack_require__) {

var xvzd = __webpack_require__(1);

module.exports = {};


/***/ }),
/* 1 */
/***/ (function(module, exports, __webpack_require__) {

"use strict";

exports.__esModule = true;
function toPascalCase(_a) {
    var text = _a.text, separator = _a.separator;
    var prefixPattern = new RegExp("^([$_-]*)");
    var suffixPattern = new RegExp("([$_-]*)$");
    var string = text;
    var prefix = string.match(prefixPattern)[1];
    var suffix = string.match(suffixPattern)[1];
    string = string.replace(prefixPattern, '').replace(suffixPattern, '');
    var result = prefix;
    var chunks = string.split(separator).filter(function (x) { return x; });
    for (var i = 0; i < chunks.length; i++) {
        result += chunks[i][0].toUpperCase() + chunks[i].substring(1);
    }
    result += suffix;
    return result;
}
function fromSnakeToPascalCase(text) {
    return toPascalCase({ text: text, separator: '_' });
}
exports.fromSnakeToPascalCase = fromSnakeToPascalCase;
function fromKebabToPascalCase(text) {
    return toPascalCase({ text: text, separator: '-' });
}
exports.fromKebabToPascalCase = fromKebabToPascalCase;
function fromPascal(_a) {
    var text = _a.text, joiner = _a.joiner;
    var prefixPattern = new RegExp("^([$_-]*)");
    var suffixPattern = new RegExp("([$_-]*)$");
    var string = text;
    var prefix = string.match(prefixPattern)[1];
    var suffix = string.match(suffixPattern)[1];
    var result = prefix;
    string = string.replace(prefixPattern, '').replace(suffixPattern, '');
    do {
        var position = string.search(/[^A-Z$_-][A-Z]/);
        if (position === -1)
            break;
        ++position;
        string = string
            .substr(0, position)
            .concat(joiner)
            .concat(string.charAt(position).toLowerCase())
            .concat(string.substr(position + 1));
    } while (true);
    string = string.toLowerCase();
    result += string;
    result += suffix;
    return result;
}
function fromPascalToSnakeCase(text) {
    return fromPascal({ text: text, joiner: '_' });
}
exports.fromPascalToSnakeCase = fromPascalToSnakeCase;
function fromPascalToKebabCase(text) {
    return fromPascal({ text: text, joiner: '-' });
}
exports.fromPascalToKebabCase = fromPascalToKebabCase;


/***/ })
/******/ ]);