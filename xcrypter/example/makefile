
all:
	@echo -n creating example program ...
	@g++ -O2 -I../include -c ncrypter.cpp usage.cpp
	@g++ -O2 -o ../ncrypter ncrypter.o usage.o ../lib/xcrypter.a
	@rm -f *.o
	@echo done
