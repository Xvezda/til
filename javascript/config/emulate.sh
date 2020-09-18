#!/usr/bin/env bash

NAME=config-test
KEY=foobar

npm run print

npm config set $NAME:$KEY 'config changed!'
npm run print
npm config delete $NAME:$KEY

