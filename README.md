# Stuff to Not Forget
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