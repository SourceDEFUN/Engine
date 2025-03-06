#!/bin/sh

git submodule init && git submodule update

brew install sdl3

python3 ./waf.py configure -T debug --disable-warns $* &&
python3 ./waf.py build
