all: build doc
build:
	cd config && cmake CMakeLists.txt && make && cd ..
doc:
	cd docs && cmake CMakeLists.txt && make && cd ..
