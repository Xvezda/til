function toPascalCase({ text, separator }) {
  const prefixPattern = new RegExp(`^([$_-]*)`);
  const suffixPattern = new RegExp(`([$_-]*)$`);

  let string = text;

  let prefix = string.match(prefixPattern)[1];
  let suffix = string.match(suffixPattern)[1];

  string = string.replace(prefixPattern, '').replace(suffixPattern, '');

  let result = prefix;
  let chunks = string.split(separator).filter(x => x);
  for (let i = 0; i < chunks.length; i++) {
    result += chunks[i][0].toUpperCase() + chunks[i].substring(1);
  }
  result += suffix;

  return result;
}

export function fromSnakeToPascalCase(text) {
  return toPascalCase({ text: text, separator: '_' });
}

export function fromKebabToPascalCase(text) {
  return toPascalCase({ text: text, separator: '-' });
}

function fromPascal({ text, joiner }) {
  const prefixPattern = new RegExp(`^([$_-]*)`);
  const suffixPattern = new RegExp(`([$_-]*)$`);

  let string = text;
  let prefix = string.match(prefixPattern)[1];
  let suffix = string.match(suffixPattern)[1];
  let result = prefix;

  string = string.replace(prefixPattern, '').replace(suffixPattern, '');

  do {
    let position = string.search(/[^A-Z$_-][A-Z]/);
    if (position === -1) break;
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

export function fromPascalToSnakeCase(text) {
  return fromPascal({ text: text, joiner: '_' });
}

export function fromPascalToKebabCase(text) {
  return fromPascal({ text: text, joiner: '-' });
}


