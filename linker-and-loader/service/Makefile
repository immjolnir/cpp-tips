
target := dynamic

default: all

.PHONY: service.o
service.o: service.cpp
	g++ -std=c++14 -fPIC -c service.cpp -I ../dynamic-lib


.PHONY: all
all: service.o
	if [ x"$(target)" = x"static" ]; then \
		ar -cq libservice.a service.o; \
	else \
		g++ -shared service.o -o libservice.so; \
	fi

# ld: service.o: relocation R_X86_64_PC32 against undefined hidden symbol `__dso_handle' can not be used when making a shared object
# ld: final link failed: bad value
# ld -shared service.o -o libservice.so

.PHONY: test_service.o
test_service.o:
	g++ -std=c++14 -fPIC -I ../dynamic-lib -c test_service.cpp

.PHONY: test_service
test_service: dynamic test_service.o
	g++ test_service.cpp -o test_service \
		-I../dynamic-lib \
		-Wl,-rpath=. -L. -lservice \
		-Wl,-rpath=../dynamic-lib/v1 -L../dynamic-lib/v1 -lstudent && \
	./test_service

#$ readelf -d test_service
#
#Dynamic section at offset 0x2cd0 contains 32 entries:
#  Tag        Type                         Name/Value
# 0x0000000000000001 (NEEDED)             Shared library: [libservice.so]
# 0x0000000000000001 (NEEDED)             Shared library: [libstudent.so]
# 0x0000000000000001 (NEEDED)             Shared library: [libstdc++.so.6]
# 0x0000000000000001 (NEEDED)             Shared library: [libgcc_s.so.1]
# 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
# 0x000000000000001d (RUNPATH)            Library runpath: [../dynamic-lib/v1:.]
#

.PHONY: clean
clean:
	rm -rf test_service *.o *.a *.so
