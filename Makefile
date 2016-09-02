all: build doc

build:
	cd config && cmake -H. -Bbuild && cd build && make && cd ../..

test:
	config/build/bin/RunUnitTests
	
doc:
	cd docs && cmake -H. -Bbuild && cd build && make && cd ../..

valgrind:
	valgrind -v --tool=memcheck --leak-check=full --show-leak-kinds=all config/build/bin/LincedInAppServer

clean:
	rm -rf config/build/ docs/build/ *.log

