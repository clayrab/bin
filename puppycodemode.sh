#!/bin/bash

# File to read
filename="puppycodemode.sh"
# Ensure filename is provided
if [ ! -f "$filename" ]; then
    echo "File not found!"
    exit 1
fi

# Disable Ctrl-C
trap '' SIGINT

# Current byte position
position=0
# Size of the file
filesize=$(stat -c %s "$filename")

# Loop until we reach the end of the file
while [ $position -lt $filesize ]; do
    # Read a single character from the file at the current position
    IFS= read -r -d '' -n 1 char < <(dd bs=1 skip=$position count=1 if="$filename" 2>/dev/null)

    # Output the character
    echo -n "$char"

    # Wait for any key press
    read -r -s -n1 -t 0.01

    # Increment the position
    position=$((position + 1))
done

# Re-enable Ctrl-C before exiting
trap - SIGINT