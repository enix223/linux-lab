.PHONY: build-copy_sys_invoke run-copy_sys_invoke run-copy_with_stdlib
ARG ?=

build-fileio:
	cmake --build --preset fileio

run-copy_sys_invoke: build-fileio
	./out/build/linux/src/fileio/copy_sys_invoke $(ARG)

run-copy_with_stdlib: build-fileio
	./out/build/linux/src/fileio/copy_with_stdlib $(ARG)
