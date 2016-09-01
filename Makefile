all: build doc

build:
	cd config && cmake -H. -Bbuild && cd build && make && cd ../..
	
doc:
	cd docs && cmake -H. -Bbuild && cd build && make && cd ../..

valgrind:
	valgrind -v --tool=memcheck --leak-check=full --show-leak-kinds=all config/build/bin/LincedInServer

clean:
	rm -rf config/build/ docs/build/

