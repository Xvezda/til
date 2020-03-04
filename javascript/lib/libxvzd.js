"use strict";
exports.__esModule = true;
function toPascalCase(_a) {
    var text = _a.text, separator = _a.separator;
    var prefixPattern = new RegExp("^([$_-]*)");
    var suffixPattern = new RegExp("([$_-]*)$");
    var string_ = text;
    var prefix = string_.match(prefixPattern)[1];
    var suffix = string_.match(suffixPattern)[1];
    string_ = string_.replace(prefixPattern, '').replace(suffixPattern, '');
    var result = prefix;
    var chunks = string_.split(separator).filter(function (x) { return x; });
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
    var string_ = text;
    var prefix = string_.match(prefixPattern)[1];
    var suffix = string_.match(suffixPattern)[1];
    var result = prefix;
    string_ = string_.replace(prefixPattern, '').replace(suffixPattern, '');
    do {
        var position = string_.search(/[^A-Z$_-][A-Z]/);
        if (position === -1)
            break;
        ++position;
        string_ = string_
            .substr(0, position)
            .concat(joiner)
            .concat(string_.charAt(position).toLowerCase())
            .concat(string_.substr(position + 1));
    } while (true);
    string_ = string_.toLowerCase();
    result += string_;
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
