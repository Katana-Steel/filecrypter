CXX=g++
AR=ar
CFLAGS=-O2 -c
YFLAGS=-f coff -DWIN32
OBJS=s-box.o \
    crypt.o \
    crypt_g2.o \
    crypt_g2.asm.o
#        tcp_socket.o \

all: xcrypter.a
	@echo xcrypter version 1.0.2a static lib is found in ./lib/
	@echo and the header files are in ./include/
	cd example && make

ncrypter:
	@cd example && make

xcrypter.a: $(OBJS)
	@echo "AR   xcrypter.a"
	@$(AR) -rcs xcrypter.a $(OBJS)
	@echo "INS  xcrypter.a"
	@./placefiles.sh

.cc.o:
	@echo "CC   $<"
	@$(CXX) $(CFLAGS) $<

crypt_g2.asm.o:
	@echo "ASM  crypt_g2.asm"
	@yasm $(YFLAGS) -o crypt_g2.asm.o crypt_g2.asm

cleanall: clean

clean:
	@echo -n "cleaning ... "
	@rm -f *.o xcrypter.a ncrypter
	@echo "done"
