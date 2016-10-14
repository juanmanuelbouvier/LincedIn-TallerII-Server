all: build doc

build:
	@cd config && cmake -H. -Bbuild && cd build && make && cd ../..

run:
	@#Default log dir
	@mkdir -p logs
	@mkdir -p resources
	./config/build/bin/LincedInAppServer

test:
	@mkdir -p .temp-test/
	./config/build/bin/RunUnitTests
	@rm -rf .temp-test/ *.log

doc:
	@cd docs && cmake -H. -Bbuild && cd build && make && cd ../..

valgrind:
	valgrind -v --tool=memcheck --leak-check=full --show-leak-kinds=all config/build/bin/LincedInAppServer

valgrind-test:
	@mkdir -p .temp-test/
	valgrind -v --tool=memcheck --leak-check=full --show-leak-kinds=all config/build/bin/RunUnitTests
	@rm -rf .temp-test/ *.log

coverage-test:
	@mkdir -p config/build/src && mkdir -p config/build/.temp-test/logs && mkdir -p config/build/.temp-test/settings && cp settings/setting.json config/build/.temp-test/settings/setting.json
	@cd config && cd build && make run_coverage && cd ../..

clean:
	@echo -n "Limpiando.."
	@rm -rf config/build/ docs/build/
	@echo "OK"

.SILENT:
