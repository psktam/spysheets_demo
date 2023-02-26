# Stuff to Not Forget
## February 25, 2023
Went down a deep rabbit warren learning about C++'s smart pointers, copy 
construction, and started touching a bit on move semantics. My head hurts, but I
think this was worth the time that I spent learning all of the mechanics that I
could about the myriad tricks that have been cooked up to make C++'s memory
management and SAFETY more tractable. Needless to say I am rather shocked at the
number of ways you can shoot yourself in the foot with this stuff.

Ultimately, I focused my efforts on learning how C++ deals with the fact that 
the container classes all allocate their entries on the heap, but that it can be
done WITHOUT needing to manually call `new` for every new key and such. Because
of that, I don't have to worry about freeing the `coord` tuples I create as keys
for the internal dictionary that the `Table` class encapsulates.

Along a similar vein, I began working on making sure that the `CellValue` class
was fully copy-constructible. That led me to learning about the "Big 3" about
C++ programming for classes; to override the constructor, destructor, and 
copy-assignment operators. 

I had originally implemented the copy-constructor and the destructor, but I 
hadn't implemented the copy-assignment operator because in my head, that's just
something I never have to think about when working with Python. That was leading
to strange bugs where whenever I assigned `CellValue` to another `CellValue` 
instance, the data would somehow get lost. But once the `=` operator was 
implemented, it worked the way that it needed to again.

Next step: adding the socket for the engine. All in all, this was painful, but
I'm glad I went through this exercise _now_.

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