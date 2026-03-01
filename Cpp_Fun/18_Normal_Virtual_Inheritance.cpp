//normal inheritance
//Class D inherits two copies of A — one via B and one via C.
class A {};
class B : public A {};
class C : public A {};
class D : public B, public C {};

//virtual inheritance
//only one instance exists even with multiple inheritance paths.
class A1 {};
class B1 : virtual public A1 {};
class c1 : virtual public A1 {};
class D1 : public B1, public c1 {};



//single       -> one base, one derived
//multilevel   -> derived fron derived
//multiple     -> derived from many bases
//Hierarchical -> many derived from one base
//Hybrid       -> combination of above
