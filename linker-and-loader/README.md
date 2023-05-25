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


## ar

We are using the `-c` (create) option to create the library file, the `-r `(add with replace) option to add the files to the library file, and the `-s` (index) option to create an index of the files inside the library file.

```
ar -crs libcipher.a cipher_encode.o cipher_decode.o
```

We can add the new object file to the libcipher.a library with the following command. The -v (verbose) option makes the usually silent ar tell us what it has done.
```
$ ar -rsv libcipher.a cipher_version.o
a - cipher_version.o
```

We can use the `-t` (table) option to see what modules are inside the library file.
```
ar -t libcipher.a
```

* Deleting Modules from a Library

we’ll use the -d (delete) option. We’ll also use the -v (verbose) option, so that ar tells us what it has done. We’ll also include the -s (index) option to update the index in the library file.
```
ar -dsv libcipher.a cipher_version.o
```

## `nm` and `readelf`
If this contains C++ code you should use the -C option to demangle the symbol names:
```
# nm -C libschnoeck.a | less
```
or use `readelf -a` to display the contents of all the object files in a static library.
```
# readelf -a mystaticlib.a
```

## Creating relocatable Linux executables by setting `RPATH` with `$ORIGIN`

In computing, `rpath` designates the run-time search path hard-coded in an executable file or library. Dynamic linking loaders use the `rpath` to find required libraries.

* What is RPATH and `$ORIGIN`

`RPATH` stands for run-time search path. According to Wikipedia, “rpath designates the run-time search path hard-coded in an executable file or library. Dynamic linking loaders use the rpath to find required libraries.” Dynamic linking is a sort of “lazy” linking of required shared libraries not during the stage of compiling but the later stage of running one executable. A path to the shared libraries will be encoded into the header of the executable if rpath is set, overriding or supplementing the system default shared library searching paths, similar as one extends the chain of PATH system variable.

`$ORIGIN` is a special variable that indicate actual executable filename. It is resolved to where the executable is at run-time, and can be quite useful when setting RPATH.

How to check the value of RPATH/RUNPATH
There are various ways of checking the RPATH value for an executable or library. objdump, readelf and chrpath are 3 of the frequently used utilities.
```
$ objdump -x path/to/executable | grep RPATH
```
or
```
$ readelf -d path/to/executable | head -20
```

or
```
$ chrpath -l path/to/executable
```

RUNPATH, introduced after RPATH to make it easier to testing libraries (without needing to rebuild them every time), is gaining wider adoptions these days and making the latter obsolete. There’s another post covering more details on this topic. So don’t be surprised if an executable has RUNPATH instead of RPATH set.

Below screenshot provides an example of readelf output with `RUNPATH` and `$ORIGIN`:

* Why and How to set RPATH

The aim of RPATH setting is to change the library search path so that one executable or library is able to link the desired dependent libraries during run-time.

There are 2 different stages RPATH could be set:

During compilation time
```
$ ./configure LDFLAGS=-Wl,-rpath=$ORIGIN/path/to/library
```
will tell the linker to build and run the executable under the specified library path, usually used to override the default library paths.

After compilation before execution
```
$ chrpath -r “\$\ORIGIN/path/to/library” <executable>
```
Above command could fail if no rpath was set previously for the executable.

Try below command with patchelf utility, which won’t complain about an unset rpath, and will get RUNPATH set to achieve similar target.
```
$ patchelf — set-rpath ‘$ORIGIN/path/to/library’ <executable>
```

* Conclusion

After setting RPATH/RUNPATH to the directory where dependent libraries locate, with the help of $ORIGIN, an Linux executable could be run successfully either in place, or be moved around to different directories or even hosts, achieving the desired properties of relocatability and flexibility.


## [I don't understand -Wl,-rpath -Wl,](https://stackoverflow.com/questions/6562403/i-dont-understand-wl-rpath-wl)

man gcc:
```
-Wl,option

    Pass option as an option to the linker. If option contains commas, it is split into multiple options at the commas. You can use this syntax to pass an argument to the option. For example, -Wl,-Map,output.map passes -Map output.map to the linker. When using the GNU linker, you can also get the same effect with `-Wl,-Map=output.map'.
```
man ld:
```
-rpath=dir

    Add a directory to the runtime library search path. This is used when linking an ELF executable with shared objects. All -rpath arguments are concatenated and passed to the runtime linker, which uses them to locate shared objects at runtime. The -rpath option is also used when locating shared objects which are needed by shared objects explicitly included in the link;
```

The `-Wl,xxx` option for gcc passes a comma-separated list of tokens as a space-separated list of arguments to the linker. So
```
gcc -Wl,aaa,bbb,ccc
```
eventually becomes a linker call
```
ld aaa bbb ccc
```
In your case, you want to say "ld -rpath .", so you pass this to gcc as `-Wl,-rpath,.` Alternatively, you can specify repeat instances of `-Wl`:
```
gcc -Wl,aaa -Wl,bbb -Wl,ccc
```
Note that there is no comma between aaa and the second `-Wl`.

* https://stackoverflow.com/questions/496664/c-dynamic-shared-library-on-linux

```
main: libshared.so main.o
    $(CXX) -o main  main.o -L. -lshared

libshared.so: shared.cpp
    $(CXX) -fPIC -c shared.cpp -o shared.o
    $(CXX) -shared  -Wl,-soname,libshared.so -o libshared.so shared.o

clean:
    $rm *.o *.so
```

What's the meaning of `-Wl,-soname,libshared.so`?

`export LD_LIBRARY_PATH=.`


* [Intermediate C++ : Static and Dynamic linking](https://ayandas.me/blog-tut/2019/01/05/linking-in-c++.html)


