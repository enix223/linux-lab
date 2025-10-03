.PHONY: build-clock run-clock

build-clock:
	cmake --build --preset clock

run-clock: build-clock
	./out/build/linux/src/clock/clock
