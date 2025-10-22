.PHONY: build-recursive_dir_read run-recursive_dir_read
ARG ?=

build-recursive_dir_read:
	cmake --build --preset recursive_dir_read

run-recursive_dir_read: build-recursive_dir_read
	./out/build/linux/src/recursive_dir_read/recursive_dir_read $(ARG)
