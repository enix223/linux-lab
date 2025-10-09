.PHONY: build-copy_sys_invoke run-copy_sys_invoke
ARG ?=

build-copy_sys_invoke:
	cmake --build --preset fileio

run-copy_sys_invoke: build-copy_sys_invoke
	./out/build/linux/src/fileio/copy_sys_invoke $(ARG)
