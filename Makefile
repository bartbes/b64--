CXX=g++
CXXFLAGS=-Wall -pedantic -O2 -fPIC
LDFLAGS=
AR=ar rcs
RM=rm -rIf

.PHONY: all clean

.INTERMEDIATE: b64.o

all: libb64.so libb64.a

clean:
	-$(RM) *.o *.so *.a

b64.o: b64.cpp b64.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<

libb64.so: b64.o
	$(CXX) -shared $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

libb64.a: b64.o
	$(AR) $@ $^
