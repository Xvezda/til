/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const { Color } = require('./common.js')

const argv = require('yargs')
  .usage('Usage: $0 [options...] [file]')
  .option('scope', {
    alias: 's',
    description: 'Print information about scopes',
    type: 'boolean'
  })
  .default('scope', false)
  .option('stack', {
    alias: 'S',
    description: 'Print information about callstack',
    type: 'boolean'
  })
  .default('stack', false)
  .option('file', {
    alias: 'f',
    description: 'Pascal source code file to execute',
    type: 'string'
  })
  .help()
  .alias('help', 'h')
  .argv

global.argv = argv


global.isDev = process.env.NODE_ENV === 'development'

// Overwrite console loggers
if (typeof console !== 'undefined') {
  global.console.info = console.info.bind(null, Color.blue`INFO:`)
  if (isDev) {
    global.console.debug = console.debug.bind(null, Color.red`DEBUG:`)
  } else {
    global.console.debug = new Function
  }
}


