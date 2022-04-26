
```
// Type your code here, or load an example.
struct S {    
    char a;     // 1 byte  
   int b;      // 4 bytes  
   short c;    // 2 bytes  
   char d;     // 1 byte   
}__attribute__ ((aligned (8)));
// __attribute__ ((aligned));

 //__attribute__ ((aligned (8)));
int squareS(S s, S s2) {
    return s.a * s2.a + s.b + s2.c  +sizeof(S);
}

struct T {     
   char a;     // 1 byte  
   int b;      // 4 bytes  
   short c;    // 2 bytes  
   char d;     // 1 byte    
};

int squareT(T s,T s2) {
    return s.a * s2.a + s.b + s2.c +sizeof(T);
}
```