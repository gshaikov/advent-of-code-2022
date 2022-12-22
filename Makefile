bin/%: %/main.cpp
	mkdir -p bin
	clang++ -std=gnu++17 -o $@ $<
