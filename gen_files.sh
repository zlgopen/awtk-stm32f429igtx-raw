#!/bin/bash

echo "# 文件清单"
echo '```'

grep PathWithFileName USER/awtk.uvoptx | sed -e 's/<PathWithFileName>..\\//' -e 's/<\/PathWithFileName>//' | grep awtk | sed -e 's/\\/\//g' | sort

echo '```'
