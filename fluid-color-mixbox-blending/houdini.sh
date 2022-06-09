#!/bin/bash

export "PATH=/opt/hfs19.0/bin:${PATH}"
export "PYTHONPATH=./python3.7libs:${PYTHONPATH}"

houdini \
    -foreground \
    -n \
    "$@"

