// Snippet for convert tiobe hof table into xml
// https://www.tiobe.com/tiobe-index/
`<?xml version="1.0" encoding="UTF-8"?>
<!-- original source: www.tiobe.com -->
<hof>${
  Array.prototype.map
    .call(document.querySelector('table#PLHoF')
      .querySelectorAll('tr'),
      row => Array.from(row.querySelectorAll('th,td'))
        .map(cell => cell.textContent.trim()))
        .reduce((acc, v, i, orig) =>
          i === 0 ?
          '' :
          `${acc}\n\t<highest>\n${
            v.map((x, i) => (
              name=orig[0][i].toLowerCase(),
              `\t\t<${name}>${x}</${name}>`)).join('\n')}
          \t</highest>`,
        '')
}</hof>`
