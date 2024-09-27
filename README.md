# OOP (CUT)
Object Oriented Programming macros for C

Quick overview:
===============
Object-oriented programming (OOP) in C is not natively supported, but it can simplify a lot of issues
especially when dealing with complex sequences of memory allocations and freeing.

This library has the aim of providing an easy-to-use, but even more importantly reliable, framework
for OOP in C. The idea is that all objects initialized using the macros defined in this header can be
predictable in their format, so that the utility functions defined in it can manipulate them in a safe 
way, hopefully freeing the programmer of memory-leak concerns.

Additionnaly:
-------------
- it can provide some nice naming collision prevention through automated prefixes
- it can provide more advanced OOP features like virtual adressing and inheritance
- it provides very minimal reflectivity

Usage:
======
This library is heavily inspired by how OOP works in C++, this is why to demonstrate its usage, we will 
compare the examples in C with C++ equivalents.

Definition:
-----------
The macros provided aim to make the definition of objects as simple as possible:

####C++
```C++
class Object : Base {
  type member1;
  type member2;

  Object(params...) : Base(params[x:y])
  {
    ...
  }
  
  ~Object()
  {
    ...
  }
};
```

####C
```C
#define TYPENAME Object
OBJECT(params...) INHERIT (Base)
  type member1;
  type member2;
END_OBJECT;

Object_cons(params...)
{
  Base_cons(BASE(0), params[x:y]);
}

Object_free()
{
  Base_free(BASE(0));
}
```

**Note: the BASE(N) macro gets the Nth level inheritance pointer**

Obviously, it's a little less sleek, but the information provided is essentially the same. The main
difference is that there is no automated base construction/destruction, and the base object must 
explicitely be constructed/destroyed in the inheriting object's constructor/destructor.

Calling constructiors and destructiors:
---------------------------------------
The methods 'cons' and 'free' work by building an object from an existing memory location, for
instance:

####C++
```C++
{
  Object object = Object(params...);
}
```

####C
```C
{
  Object object;
  Object_cons(&object, params...);

  Object_free(&object);
}
```

The important thing to notice here is that there is no automated compiler destructor being called in C,
and so the programmer has the responsability to call it themselves.

For memory allocation the usage is even closer in syntax:

####C++
```C++
{
  Object *object = new Object(params...);

  delete object;
}
```

####C
```C
{
  Object *object = NEW (Object) (params...)

  DELETE (object);
}
```
