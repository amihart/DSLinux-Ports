#!/bin/sh
#copies files out of coreutils into /usr/bin/
# some of these are broken
for i in `ls /usr/bin/coreutils/`
do
  which "$i" >/dev/null && (
    echo "$i (skipped)"
  ) || (
    cp "/usr/bin/coreutils/$i" "/usr/bin/$i"
    echo "$i (copied)"
  )
done

