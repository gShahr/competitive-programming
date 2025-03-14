#!/bin/bash

# Use relative paths based on the script's location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# Template directory name
TEMPLATE_DIR="contest-template"

# Find the highest numbered contest directory
highest_contest=0
for dir in "$SCRIPT_DIR"/contest-*; do
    if [ -d "$dir" ]; then
        dir_name=$(basename "$dir")
        if [[ $dir_name =~ ^contest-([0-9]+)$ ]]; then
            contest_num=${BASH_REMATCH[1]}
            if (( contest_num > highest_contest )); then
                highest_contest=$contest_num
            fi
        fi
    fi
done

# Calculate the next contest number
next_contest=$((highest_contest + 1))
new_dir="$SCRIPT_DIR/contest-$next_contest"

echo "Creating new contest directory: contest-$next_contest"

# Check if template directory exists
if [ ! -d "$SCRIPT_DIR/$TEMPLATE_DIR" ]; then
    echo "Error: Template directory $TEMPLATE_DIR not found!"
    exit 1
fi

# Copy template directory to new contest directory
cp -r "$SCRIPT_DIR/$TEMPLATE_DIR" "$new_dir"

# Navigate to the script directory
cd "$SCRIPT_DIR" || exit 1

# Add the new directory to git
git add "contest-$next_contest"

# Commit the changes
git commit -m "Initialize p1-p4 for contest-$next_contest"

echo "Successfully created and committed contest-$next_contest"