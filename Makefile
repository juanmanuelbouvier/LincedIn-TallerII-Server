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
	-./config/build/bin/RunUnitTests
	@rm -rf .temp-test/ *.log
	
clean-test:
	@rm -rf .temp-test/ *.log

doc:
	@cd docs && cmake -H. -Bbuild && cd build && make && cd ../..

valgrind:
	valgrind -v --tool=memcheck --leak-check=full --show-leak-kinds=all config/build/bin/LincedInAppServer

valgrind-test:
	@mkdir -p .temp-test/
	-valgrind -v --tool=memcheck --leak-check=full --show-leak-kinds=all config/build/bin/RunUnitTests
	@rm -rf .temp-test/ *.log

coverage-test:
	@mkdir -p config/build/src && mkdir -p config/build/.temp-test/logs && mkdir -p config/build/.temp-test/settings && cp settings/setting.json config/build/.temp-test/settings/setting.json
	@cd config && cd build && make run_coverage && cd ../..
	@rm -rf config/build/.temp-test config/build/*.log config/build/db
	
coverage-run:
	@mkdir -p config/build/db mkdir -p config/build/logs && mkdir -p config/build/settings && cp settings/setting.json config/build/settings/setting.json
	@cd config && cd build && make run_coverage_server && cd ../..
	@rm -rf config/build/db config/build/logs config/build/db

clean:
	@echo -n "Limpiando.."
	@rm -rf config/build/ docs/build/
	@rm -rf .temp-test/ *.log
	@echo "OK"

.SILENT:
