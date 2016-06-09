CXX=g++
AR=ar

all: lib example

lib: .FORCE
	@echo -n compiling s-box.cc ...
	@$(CXX) -c s-box.cc
	@echo done
	@echo -n compiling crypt.cc ...
	@$(CXX) -c crypt.cc
	@echo done
	@echo -n creating xcrypter.a ...
	@$(AR) -rcs xcrypter.a s-box.o crypt.o
	@./placefiles.sh
	@echo done
	@echo xcrypter version 1.0 static lib is found in ./lib/
	@echo and the header files are in ./include/

example: .FORCE
	cd example && make

.FORCE: