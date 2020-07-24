#!/bin/sh

if [ -d ./log ]; then
	rm -rf log
fi

if [ -e bin/app ]; then
	make clean -s
fi

if [ ! -d ./bin ]; then
	mkdir bin
fi

make -s

if [ -e bin/SwBlock ]; then
	cp bin/SwBlock bin/SwBlock1
	cp bin/SwBlock bin/SwBlock2
	cp bin/SwBlock bin/SwBlock3
	cp bin/SwBlock bin/SwBlock4
	cp bin/SwBlock bin/SwBlock5
fi
