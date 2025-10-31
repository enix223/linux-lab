.PHONY: build-fileio run-copy_sys_invoke run-copy_with_stdlib run-file_link run-dup_file
ARG ?=

build-fileio:
	cmake --build --preset fileio

run-copy_sys_invoke: build-fileio
	./out/build/linux/src/fileio/copy_sys_invoke $(ARG)

run-copy_with_stdlib: build-fileio
	./out/build/linux/src/fileio/copy_with_stdlib $(ARG)

run-file_link: build-fileio
	./out/build/linux/src/fileio/file_link $(ARG)

run-dup_file: build-fileio
	./out/build/linux/src/fileio/dup_file $(ARG)
