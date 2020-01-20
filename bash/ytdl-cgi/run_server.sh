#!/usr/bin/env bash

docker run --rm --name httpd -p 80:80 \
    -v $PWD/conf/httpd.conf:/usr/local/apache2/conf/httpd.conf \
    -v $PWD/ytdl.cgi:/usr/local/apache2/cgi-bin/ytdl.cgi \
    httpd:latest
