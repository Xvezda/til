#!/usr/bin/env bash
# Copyright (c) 2019 Xvezda <https://xvezda.com/>
#
# Use of this source code is governed by an MIT-style
# license that can be found in the LICENSE file or at
# https://opensource.org/licenses/MIT.


# Requested by @BooDeer

echo -n "Would you like to add or to remove files? (a)dd/(r)emove: "
read cmd
case $cmd in
    a|add)
        cmd='add'
        ;;
    r|remove)
        cmd='remove'
        ;;
    *)
        echo "'$cmd' is invalid command! try again"
        exit 1
        ;;
esac

list=(*)
for (( i=-1; ; ))
do
    echo -n "Which files would you like to $cmd: "
    # Empty IFS to read tab(\t) chracter
    IFS= read -r -n1 chr
    # Check input's ascii code
    # '9' is tab character
    if [ "$(printf "%d" "'$chr")" -eq 9 ]
    then
        echo
        if [ $i -eq -1 ] || [ $i -eq ${#list[@]} ]
        then
            # Print current file list
            echo ${list[@]}
        else
            echo ${list[$i]}
        fi
    # Enter pressed
    elif [ "$(printf "%d" "'$chr")" -eq 0 ]
    then
        if [ $i -eq -1 ] || [ $i -eq 0 ]
        then
            # Print error
            >&2 echo "Error: Please select file by pressing tab" \
                "or type file name"
            continue
        else
            target="${list[$i-1]}"
            break
        fi
    else
        # Read remaining inputs
        read -r remain
        # Concat chr and remain chracters
        target="${chr}${remain}"

        if [ ! -e "$target" ]
        then
            >&2 echo "Error: Filename '$target' does not exists! try again."
            continue
        fi
        break
    fi
    # Increase index 'i' \w Keep i in range size of a list
    (( i = (i + 1) % (${#list[@]} + 1) ))
done


echo -n "Insert your commit: "
read commit

git $cmd $target && git commit -m "$commit" && git push
