#!/bin/bash

# Http Response Header
#echo "Content-type: text/html"
#echo

# Http Body Start
ytdlurls=$(echo $QUERY_STRING | sed -E 's/ytdlurls=([^&]*?).*/\1/')
ytid=${ytdlurls##*v\%3D}

# If ID not exists
if [ -z $ytid ]; then
	echo "Content-Type: text/html"
	echo
	echo $(whoami)
	exit 1
fi


# Download start
youtube-dl "https://www.youtube.com/watch?v=$ytid" > /dev/null 2>&1
# Rename downloaded file
filename="${ytid}.mp4"
mv *"$filename" $filename

echo "Content-Type: video/mp4"
echo "Content-Disposition: attachment; filename=\"$filename\""
echo

cat $filename

rm *.mp4


exit

