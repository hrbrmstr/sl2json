CC=g++

.PHONY: clean test

sl2json:
	$(CC) sl2-main.cpp -o x86_app -target x86_64-apple-macos10.12 && \
	$(CC) sl2-main.cpp -o arm_app -target arm64-apple-macos11 && \
	lipo -create -output sl2json x86_app arm_app && rm x86_app arm_app

clean:
	rm sl2json

test:
	./sl2json testdata/chart.sl2

codesign:
	codesign --force --verify --verbose --sign "${APPLE_DEV_ID}" sl2json
