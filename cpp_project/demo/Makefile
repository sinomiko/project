.PHONY: format format-check

ALL_SRCS=$(shell find . -name "*.h" -o -name "*.cc" -o -name "*.c" -o -name "*.cpp")
SHELL=/bin/bash

format:
	@clang-format-8 -i -style=file ${ALL_SRCS}

format-check:
	@ if ! diff -u <(cat ${ALL_SRCS}) <(clang-format-8 -style=file ${ALL_SRCS}); then \
		echo "Code format check failed. Please run 'make format' to fix it."; \
		exit 1; \
	fi