#!/bin/sh
# Generates a git graph log of all branches since the last week
# Depends on:
#   git https://git-scm.com/
#   ansi2html https://github.com/pycontribs/ansi2html
git --no-pager log --since 1week --graph --date=human --all --color --decorate | ansi2html > log.html