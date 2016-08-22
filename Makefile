all: build doc
build:
	cd config && cmake -H. -Bbuild && cd build && make && cd ../..
doc:
	cd docs && cmake -H. -Bbuild && cd build && make && cd ../..
clean:
	rm -rf config/build/ docs/build/
