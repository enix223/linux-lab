.PHONY: build-ipc_named_pipe run-ipc_named_pipe-sender run-ipc_named_pipe-receiver

build-ipc_named_pipe:
	cmake --build --preset ipc_named_pipe

run-ipc_named_pipe-sender:
	./out/build/linux/src/ipc_named_pipe/ipc_named_pipe_sender

run-ipc_named_pipe-receiver:
	./out/build/linux/src/ipc_named_pipe/ipc_named_pipe_receiver
