
all:
	@echo -n creating example program ... 
	@g++ -I../include -c ncrypter.cpp usage.cpp
	@g++ -o ../ncrypter ncrypter.o usage.o ../lib/xcrypter.a
	@echo done