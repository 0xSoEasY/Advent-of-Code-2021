#!/bin/bash

export session_id="YOUR_SESSION_ID_HERE"

if [ "$#" -ne 1 ]; then
    echo "Usage: ./new_day.sh <day_number>"
    exit 1

elif [ $session_id == "YOUR_SESSION_ID_HERE" ]; then
    echo "[-] Edit the script and modify your session_id"
    exit 2
fi

export challenge_name=$(curl -s https://adventofcode.com/2021/day/$1 | grep "\-\-\- Day" | sed 's/.*<h2>.*: //' | sed 's/ \-\-\-<\/h2>.*//' | sed 's/ /_/g')
export folder_name="$1_$challenge_name"

printf "[!] Creating folder './%s/'\n" $folder_name
mkdir $folder_name
cd $folder_name

echo "[!] Compying the template 'solve.c' script"
cp ../template.c solve.c

echo "[!] Fetching the 'input.txt' file"
curl -s "https://adventofcode.com/2021/day/$1/input" -H "cookie: session=$session_id" > input.txt

echo "[+] Done !"