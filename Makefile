build:
	cd fist && make
	mkdir -p bin
	mv fist/fist bin/fist

clean:
	rm -f bin/fist
