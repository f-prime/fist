build:
	cd spear && make
	mkdir -p bin
	mv spear/spear bin/spear
