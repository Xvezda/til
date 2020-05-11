# Protocols

## Gopher

I wrote quick example below, which converted HTTP request to gopher protocol.


```sh
cat <<EOD | xxd -p | tr -d '\n' |
sed -E \
 -e 's/([[:xdigit:]][[:xdigit:]])/%\1/g' \
 -e 's/%0a/%0d%0a/g' |
xargs -I{} curl gopher://$(dig +short www.google.com):80/_{}
GET / HTTP/1.1
Host: www.google.com
Connection: Close

EOD
```


## References

- https://en.wikipedia.org/wiki/Gopher_(protocol)
