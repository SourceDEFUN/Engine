#!/bin/sh

git submodule init && git submodule update
sudo apt-get update
sudo apt-get install -f -y libopenal-dev g++-multilib gcc-multilib libpng-dev libjpeg-dev libfreetype6-dev libfontconfig1-dev libcurl4-gnutls-dev libsdl3-dev zlib1g-dev libbz2-dev libedit-dev

python3 ./waf.py configure -T debug --disable-warns $* &&
python3 ./waf.py build
