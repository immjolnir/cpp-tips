
default: student.a

# The -c flag tells GCC to stop after the compilation process and not run the linker and 
# the -fPIC flag stands for position independent code which is required for shared libraries but 
# we will also use them for static linking to maintain uniformity.
.PHONY: student.o
student.o: student.cpp
	g++ -std=c++14 -fPIC -c student.cpp

.PHONY: static
static: student.o
	ar -cq libstudent.a student.o

.PHONY: dynamic
dynamic: student.o
	g++ -shared -o libstudent.so student.o

.PHONY: clean
clean:
	rm -rf *.o *.a *.so
