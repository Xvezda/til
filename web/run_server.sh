#!/usr/bin/env bash
docker run --rm --name httpd -p 80:80 \
    -v $PWD:/usr/local/apache2/htdocs httpd:latest
