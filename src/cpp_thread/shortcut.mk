.PHONY: build-cpp_thread run-cpp_thread_join run-cpp_thread_detach

build-cpp_thread:
	cmake --build --preset cpp_thread

run-cpp_thread_join: build-cpp_thread
	./out/build/linux/src/cpp_thread/cpp_thread_join

run-cpp_thread_detach: build-cpp_thread
	./out/build/linux/src/cpp_thread/cpp_thread_detach
