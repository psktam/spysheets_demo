# Stuff to Not Forget
## February 24, 2023
Got the `EngineAction` class to work with serializing the provided commands and
encoding them using protobuf, and I was able to reconstruct the serialized data
in python. Exciting stuff. The next step is to get them communicating over a 
local TCP/IP socket, or some other means of IPC.

The ideal setup here is for the `EngineAction` to just send its serialized
contents to an abstract dispatcher that can be whatever we need it to be.

The usages of `std::string` have also been replaced with a generic container
called `CellValue` that can encapsulate integer, floating-point, or string 
types. Jury is out for me, however, as to whether or not my strategy of 
requiring all of the encapsulated data to already be allocated on the heap is a
wise idea or not. The idea here is that `CellValue` should own the lifetime of 
the data that it contains, so should it consume a reference, or should it just 
copy the provided data wholesale? Maybe it's okay to copy it, but then that 
means the class will need to carry extra empty fields for every new type that it
can wrap... I think.

Or maybe there's something that can be done here with templates that I just 
don't know enough about.

At this point, I've gotten a minimal demo `DirectInput` going. There are raw 
pointers all over the place which I imagine can be made a lot cleaner with 
usages of C++'s smart pointers.

## February 23, 2023
Finally figured out how to get protobuf to be a dependency here. Went the route
of installing `protobuf` as a system-level package using 
`sudo pacman -Sy protobuf`, which installs the compiler and the header files and
appropriate libraries. Feels way better than compiling from source and 
marshalling these to the right places manually, but maybe that's the way to go.

Just going to document here the _exact_ steps that I took to get the protobuf
that I sketched out to work with `main.cpp`.

1. From the top-level of this repo, run `protoc --cpp_out=. protocols/operations.proto`
1. This creates `operations.pb.h` and `operations.pb.cc` files.
1. The project can then be compiled by running `g++ -I./headers -I./ source/* protocols/operations.pb.cc -lprotobuf`
    1. This can probably be made more efficient by moving the generated code to the
        `headers` and `source` directories, rather than try to get the namespaces
        to work like this.
    2. As much as I hate to admit this, maybe I should look into learning how
       to actually use Bazel.