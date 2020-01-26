#!/usr/bin/env bash


function echoerr() {
    1>&2 echo $@
}


OPTIONS="Ok Exit"
select opt in $OPTIONS; do
    case $opt in
        Ok)
            echo "OK :)"
            ;;
        Exit)
            echo "I'm exit!"
            exit 1
            ;;
        *)
            echoerr "selected option not exists"
            ;;
    esac
done
