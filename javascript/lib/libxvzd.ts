function toPascalCase({ text, separator }: { text: string, separator: string }) {
  const prefixPattern: RegExp = new RegExp(`^([$_-]*)`);
  const suffixPattern: RegExp = new RegExp(`([$_-]*)$`);

  let string_: string = text;

  let prefix: string = (string_.match(prefixPattern) || [''])[1];
  let suffix: string = (string_.match(suffixPattern) || [''])[1];

  string_ = string_.replace(prefixPattern, '').replace(suffixPattern, '');

  let result = prefix;
  let chunks = string_.split(separator).filter(x => x);
  for (let i = 0; i < chunks.length; i++) {
    result += chunks[i][0].toUpperCase() + chunks[i].substring(1);
  }
  result += suffix;

  return result;
}

export function fromSnakeToPascalCase(text: string) {
  return toPascalCase({ text: text, separator: '_' });
}

export function fromKebabToPascalCase(text: string) {
  return toPascalCase({ text: text, separator: '-' });
}

function fromPascal({ text, joiner }: { text: string, joiner: string }) {
  const prefixPattern = new RegExp(`^([$_-]*)`);
  const suffixPattern = new RegExp(`([$_-]*)$`);

  let string_ = text;
  let prefix = (string_.match(prefixPattern) || [''])[1];
  let suffix = (string_.match(suffixPattern) || [''])[1];
  let result = prefix;

  string_ = string_.replace(prefixPattern, '').replace(suffixPattern, '');

  do {
    let position = string_.search(/[^A-Z$_-][A-Z]/);
    if (position === -1) break;
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

export function fromPascalToSnakeCase(text: string) {
  return fromPascal({ text: text, joiner: '_' });
}

export function fromPascalToKebabCase(text: string) {
  return fromPascal({ text: text, joiner: '-' });
}


