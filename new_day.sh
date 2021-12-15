#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: ./new_day.sh <day_number>"
    exit 1
fi

export session_id="YOUR_SESSION_ID_HERE"
export challenge_name=$(curl -s https://adventofcode.com/2021/day/$1 | grep "\-\-\- Day" | sed 's/.*<h2>.*: //' | sed 's/ \-\-\-<\/h2>.*//' | sed 's/ /_/')
export folder_name="$1_$challenge_name"

printf "[+] Creating folder '%s'\n" $folder_name
mkdir $folder_name
cd $folder_name

cp ../template.c solve.c

curl -s "https://adventofcode.com/2021/day/$1/input" -H "cookie: session=$session_id" > input.txt