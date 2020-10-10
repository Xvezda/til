# Gulp

`Gulp`는 워크플로우의 자동화 및 개선을 돕는 도구이다.

## Task

각 태스크는 전부 비동기로 이루어져야 한다.
[Error-first callback](https://nodejs.org/api/errors.html#errors_error_first_callbacks) 함수를 호출하거나, Stream, Promise, Event Emitter, Child Process 혹은 Observable을 반환한다.
일반적인 자바스크립트 문법을 그대로 따르기 때문에 ES2017의 async-await 문법을 통해 가독성 향상을 꾀해볼 수 있다.

### Exporting

- Public tasks: CJS의 exports를 이용해서 export된 태스크. `gulp` 명령어를 통해 실행이 가능해진다.
- Private tasks: 내부적으로 사용되는 태스크들. 대부분 `series()`, `parallel()`의 일부로 사용된다.

### Compose
```javascript
const { series, parallel } = require('gulp');
```

- `series()`: 순차적으로 실행할 태스크를 인자로 받는다.
- `parallel()`: 최대의 동시성으로 실행 할 태스크를 인자로 받는다.

두 매서드는 서로 중첩되어 사용할 수 있다.

### Completion

실행중 에러가 감지되면 `series()`는 에러 발생 시점 이후 태스크들은 실행이 되지 않을것이고, `parallel()`의 나머지 태스크들은 실행이 보장되지 않는다. (완료되거나 완료되지 못할 것이다.)

## Files

`src()`와 `dest()` 매서드는 `gulp`가 컴퓨터의 파일들을 다룰 때 주로 사용된다.
`src()`는 glob 패턴을 받아 [Node stream](https://nodejs.org/api/stream.html)으로 변환한다.


## Epilogue

감상: 다른 프레임워크에 비해 굉장히 직관적인것 같다. `Node.js`의 철학이 녹아있는듯한 툴킷.