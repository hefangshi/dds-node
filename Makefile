all: build/Release/dds.node

build/Release/dds.node: dds.cc binding.gyp
	CC=gcc CXX=g++ node-gyp -v configure build

.PHONY: clean

clean:
	node-gyp clean
