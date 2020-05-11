from flask import Flask
from flask import Response, render_template, stream_with_context


app = Flask(__name__)

@app.route('/')
def root():
    # return 'hello'
    return render_template('sse.html')

@app.route('/sse')
def sse():
    import time
    def generate():
        while True:
            yield 'data: PING\r\n\r\n'
            time.sleep(3)
    return Response(stream_with_context(generate()),
                    mimetype='text/event-stream')


if __name__ == '__main__':
    app.run(port=7000, debug=True, threaded=True)
