# mkver

This little utility generates a C/C++ version header 
file and increments the build number at each invocation.

The *major*, *minor* and *patch* components of the
version are changed manually when appropriate.

Example of generated file:

``` c
// mkver generated file.
#ifndef __VERSION__
#define __VERSION_MAJOR__ 1
#define __VERSION_MINOR__ 2
#define __VERSION_PATCH__ 25
#define __VERSION_BUILD__ 344
#define __VERSION__ "1.2.25.344"
#endif
```
