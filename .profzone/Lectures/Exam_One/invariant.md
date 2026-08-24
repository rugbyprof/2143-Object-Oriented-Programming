An algorithm is a repeatable process. If it is repeatable, it has to have attributes that do not change with repetition. These are your invariants. The invariants are combined with and/or operate on the (potentially) varying data that will be fed into your algorithm.

Thus the whole point of programming is to identify what does not vary--that is essentially your program.

In object-oriented program, there is a notion that each object should do a single thing well. This essentially means that (for class-based OOP) a class defines the invariants for a single algorithm, along with place-holders (variables) for any variant data that its objects might need. Ideally in OO, you would isolate what varies as much as possible, so that each object is mostly invariant.e