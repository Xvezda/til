var redux = require('redux');

function counter(state, action) {
  state = state || 0;
  switch (action.type) {
    case 'INC':
      return state + 1;
    case 'DEC':
      return state - 1;
    default:
      return state;
  }
}

var store = redux.createStore(counter);

store.subscribe(function () {
  console.log('subscribe:', store.getState());
});

store.dispatch({ type: 'INC' });
store.dispatch({ type: 'INC' });
store.dispatch({ type: 'DEC' });

