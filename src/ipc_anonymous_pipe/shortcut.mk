.PHONY: build-ipc_anonymous_pipe run-ipc_anonymous_pipe

build-ipc_anonymous_pipe:
	cmake --build --preset ipc_anonymous_pipe

run-ipc_anonymous_pipe:
	./out/build/linux/src/ipc_anonymous_pipe/ipc_anonymous_pipe
