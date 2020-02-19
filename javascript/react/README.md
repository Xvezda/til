# React

## Component

Function component
```javascript
function MyComponent(props) {
    return <h1>Hello</h1>
}
```

Class component - ES6
```javascript
class MyComponent extends React.Component {
    render() {
        return <h1>Hello</h1>
    }
}
```

## Props & State

- Props: Immutable, Read-Only
- State: Mutable, Encapsulated, Local


## Setting States


What Reacts state different from `Vue.js` is, state can't be update directly by assignment.
(It will not effect rendering)

```javascript
// no
this.state.foo = 'bar';

// yes
this.setState({ foo: 'bar' });
```

Async state update

```javascript
this.setState((state, props) => { foo: 'bar' });
```

## Inputs

`<input>`, `<textarea>` and `<select>` use `value` attribute to initialize.


## Special `props.children`

Works similar to `Vue.js` default slot.
But, it can store more than just component because it's part of props.
