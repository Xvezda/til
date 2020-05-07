'use strict';

function setElementStyle(elm, style) {
  Object.entries(style).forEach(function (css) {
    css[1]
    elm.style[css[0]] = css[1];
  });
}

document.onmousedown = function (e) {
  console.log('mouse down');

  var box;
  var direction;
  var init = {};

  function removeSelection() {
    try {
      // Remove box
      for (var selection of document.querySelectorAll('#selection')) {
        selection.parentElement.removeChild(selection);
      }
      box = undefined;
    } catch (e) {}
  }
  removeSelection();

  document.onmousemove = function (e) {

    if (!box) {
      // Initial position
      init.x = e.x;
      init.y = e.y;

      box = document.createElement('div');
      box.id = 'selection'

      setElementStyle(box, {
        boxSizing: 'border-box',
        border: '1px solid #aaa',
        backgroundColor: '#eee',
        opacity: '.85',
        position: 'absolute',
        top: e.y + 'px',
        left: e.x + 'px',
      });
      document.body.appendChild(box);
    }

    // Update box style
    switch ((init.y < e.y ? 's' : 'n') + (init.x < e.x ? 'e' : 'w')) {
      // Clockwise
      case 'ne':  // 0 - 3
        setElementStyle(box, {
          top: e.y + 'px',
          left: init.x + 'px',
          width: e.x - init.x + 'px',
          height: init.y - e.y + 'px'
        });
        break;
      case 'se':  // 3 - 6
        setElementStyle(box, {
          top: init.y + 'px',
          left: init.x + 'px',
          width: e.x - init.x + 'px',
          height: e.y - init.y + 'px'
        });
        break;
      case 'sw':  // 6 - 9
        setElementStyle(box, {
          top: init.y + 'px',
          left: e.x + 'px',
          width: init.x - e.x + 'px',
          height: e.y - init.y + 'px'
        });
        break;
      case 'nw':  // 9 - 0
        setElementStyle(box, {
          top: e.y + 'px',
          left: e.x + 'px',
          width: init.x - e.x + 'px',
          height: init.y - e.y + 'px'
        });
        break;
      default:
        console.error('something is wrong!');
        break;
    }
  }

  function resetHandler(event) {
    document.onmousemove = new Function;
    removeSelection();
  }

  document.onmouseup = resetHandler;
  document.oncontextmenu = resetHandler;
};
