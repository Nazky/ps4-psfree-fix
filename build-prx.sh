#!/bin/bash
set -e
if [ -e files/aio_fix_505.prx ]
then
    base64 -w 0 files/aio_fix_505.prx > files/aio_fix_505.b64
    echo 'static const unsigned char PRXStr[] = "'$(cat files/aio_fix_505.b64)'";' > include/PRX.h
    rm -f files/aio_fix_505.b64
fi
