CC=g++

.PHONY: clean test

sl2json:
	$(CC) sl2-main.cpp -o sl2json

clean:
	rm sl2json

test:
	./sl2json testdata/chart.sl2