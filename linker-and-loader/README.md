# Linker and Loader

It's a feasibility study that a program depends on a library with different versions.

* `service`: depends on the `student` v1.
* `client`: depends on the `service` and `student` v2.

Based on the computer science knowledge, the dynamic linking is not work for this case.
But the static linking cannot work too.


## First try
```
$ make
...
g++ -std=c++14 client.cpp \
	-Idynamic-lib -Iservice \
	-Ldynamic-lib/v2 -lstudent \
	-Lservice -lservice \
	-o client
/usr/bin/ld: service/libservice.a(service.o): in function `Service::music()':
service.cpp:(.text+0x38): undefined reference to `Student::update(int, double)'
collect2: error: ld returned 1 exit status
make: *** [Makefile:15: client] Error 1
```

I was thought the `student` v1 static library was orchestrated into the `service` library.
```
$ ar -t service/libservice.a 
service.o
```
It's means that we should link the `student` v1 again. But we cannot.
```
g++ -std=c++14 client.cpp \
	-Idynamic-lib -Iservice \
	-Ldynamic-lib/v2 -lstudent \
	-Ldynamic-lib/v1 -lstudent \
	-Lservice -lservice \
	-o client
/usr/bin/ld: service/libservice.a(service.o): in function `Service::music()':
service.cpp:(.text+0x38): undefined reference to `Student::update(int, double)'
collect2: error: ld returned 1 exit status
make: *** [Makefile:15: client] Error 1
```
The order in the command is critical. In the above command, the `student` v1 will be ignored.


## multiple definition after static library orchestration
```
$ mkdir new-archive
$ cd new-archive
$ cp dynamic-lib/v1/libstudent.a .
$ cp service/libservice.a .
$ ar x libstudent.a
$ ar x libservice.a
$ ls 
libservice.a libstudent.a service.o student.o
$ ar -cq libservice.a *.o
$ mv libservice.a service/

$ make client     
g++ -std=c++14 client.cpp \
	-Idynamic-lib -Iservice \
	-Ldynamic-lib/v2 -lstudent \
	-Lservice -lservice \
	-o client
/usr/bin/ld: service/libservice.a(student.o): in function `Student::upgrade()':
student.cpp:(.text+0x2e): multiple definition of `Student::upgrade()'; dynamic-lib/v2/libstudent.a(student.o):student.cpp:(.text+0x4a): first defined here
/usr/bin/ld: service/libservice.a(student.o): in function `operator<<(std::ostream&, Student const&)':
student.cpp:(.text+0x61): multiple definition of `operator<<(std::ostream&, Student const&)'; dynamic-lib/v2/libstudent.a(student.o):student.cpp:(.text+0x7f): first defined here
collect2: error: ld returned 1 exit status
```

