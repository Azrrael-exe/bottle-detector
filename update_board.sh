#!/bin/sh

git remote -v update

UPSTREAM=${1:-'@{u}'}
LOCAL=$(git rev-parse @)
REMOTE=$(git rev-parse "$UPSTREAM")
BASE=$(git merge-base @ "$UPSTREAM")

if [ $LOCAL = $REMOTE ]; then
    echo "Reposity Up-to-date!"
elif [ $LOCAL = $BASE ]; then
    echo "Reposity Needs to be Updated... Wait!"
    git reset --hard origin/master
    platformio run --target upload --environment leonardo
fi
