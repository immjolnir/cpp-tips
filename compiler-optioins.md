# g++

## Options for Debugging Your Program
To tell GCC to emit extra information for use by a debugger, in almost all cases you need only to add -g to your other options.
GCC allows you to use -g with -O. 
If you are not using some other optimization option, consider using -Og with -g.  With no -O option at all,
       some compiler passes that collect information useful for debugging do not run at all, so that -Og may result
       in a better debugging experience.


```
       -g  Produce debugging information in the operating system's native format (stabs, COFF, XCOFF, or DWARF).
           GDB can work with this debugging information.

       -ggdb
           Produce debugging information for use by GDB.  This means to use the most expressive format available
           (DWARF, stabs, or the native format if neither of those are supported), including GDB extensions if at
           all possible.

       -glevel
       -ggdblevel
       -gstabslevel
       -gxcofflevel
       -gvmslevel
           Request debugging information and also use level to specify how much information.  The default level is
           2.

           Level 0 produces no debug information at all.  Thus, -g0 negates -g.

           Level 1 produces minimal information, enough for making backtraces in parts of the program that you
           don't plan to debug.  This includes descriptions of functions and external variables, and line number
           tables, but no information about local variables.

           Level 3 includes extra information, such as all the macro definitions present in the program.  Some
           debuggers support macro expansion when you use -g3.

           If you use multiple -g options, with or without level numbers, the last such option is the one that is
           effective.

           -gdwarf does not accept a concatenated debug level, to avoid confusion with -gdwarf-level.  Instead use
           an additional -glevel option to change the debug level for DWARF.
```