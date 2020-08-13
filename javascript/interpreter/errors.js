/* Copyright (C) 2020 Xvezda <xvezda@naver.com> */

const UNEXPECTED_TOKEN = 'Unexpected token'
const ID_NOT_FOUND     = 'Identifier not found'
const DUPLICATE_ID     = 'Duplicate id found'

const ErrorCode = {
  UNEXPECTED_TOKEN,
  ID_NOT_FOUND,
  DUPLICATE_ID
}


class BaseError extends Error {
  constructor(...args) {
    super(...args)
  }
}

class LexerError extends BaseError {
  constructor(...args) {
    super(...args)
  }
}


class ParserError extends BaseError {
  constructor(...args) {
    super(...args)
  }
}


class SemanticError extends BaseError {
  constructor(...args) {
    super(...args)
  }
}


module.exports = {
  ErrorCode,
  LexerError,
  ParserError,
  SemanticError
}
