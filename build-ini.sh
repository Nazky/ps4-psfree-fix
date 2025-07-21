#!/bin/bash
set -e
if [ -e files/plugins.ini ]
then
    base64 -w 0 files/plugins.ini > files/plugins.b64
    echo 'static const unsigned char INIStr[] = "'$(cat files/plugins.b64)'";' > include/INI.h
    rm -f files/plugins.b64
fi
