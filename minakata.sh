#!/usr/local/bin/bash
set -u

trap 'echo err' ERR
platex minakata.tex
dvipdfmx minakata.dvi
open minakata.pdf


exit 0

