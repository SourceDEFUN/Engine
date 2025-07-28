#!/bin/sh

git submodule init && git submodule update

brew install sdl3

./waf.py configure -T debug --disable-warns $* &&
./waf.py build
