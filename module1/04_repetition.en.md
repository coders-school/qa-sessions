<!-- .slide: data-background="#111111" -->

# Questions from #powtórka channel
<!-- Pytanie czy tłumaczyć nazwę kanału, czy uznać ją za nazwę własną? -->
___

@edmundoPL
> Question from me to for the recap. What is the point of ensuring a long enough life for the variable which the pointer or reference points to?
> It happened a couple of times now, and I still don't feel it. I kind of understand but not quite. Maybe an interesting example will be found by Thursday?

___
<!-- .slide: style="font-size: 0.65em" -->

Let's trace the stack in this piece of code

```cpp
#include <iostream>

int doNothing() {
/* G */ int b = 50;
        int c = 100;
/* H */ return b;
}

int* getObject() {
/* C */ int a = 10;
        int* ptr = &a;
/* D */ return ptr;
}

int main() {
/* A */ int number = 5;
/* B */ int* pointer = getObject();
/* E */ *pointer = 20;
/* F */ number = doNothing();
/* I */ std::cout << *pointer << '\n';
}
```

Stack graphically. Right -> next lines of code

<div style="font-size: 0.7em">

| FRAME | A               | B              | C           | D            | E                    | F            | G               | H            | I               |
| :---: | :-------------- | :------------- | :---------- | :----------- | :------------------- | :----------- | :-------------- | :----------- | :-------------- |
|   1   |                 |                | **ptr = ?** | **ptr = &a** |                      |              | **c = ?**       | **c = 100**  |                 |
|   1   |                 |                | **a = ?**   | **a = 10**   |                      | **??? = 20** | **b = ? (20?)** | **b = 50**   |                 |
|   0   | **pointer = ?** | pointer = ?    | pointer = ? | pointer = ?  | **pointer = &a** !!! | pointer = &a | pointer = &a    | pointer = &a | pointer = &a    |
|   0   | **number = ?**  | **number = 5** | number = 5  | number = 5   | number = 5           | number = 5   | number = 5      | number = 5   | **number = 50** |

</div>

___

@Jakub J
> Generic lambdas, what's the point of using regular lambdas (in which we pass a specific type)?

Limited. Only when we want lambda to work for a certain type and e.g. not compile for another.
I normally recommend using generics. You can come across such and such in the code. Generics are in C++14, and are yet to become well-established. But I strongly encourage you to use them.
___
<!-- .slide: style="font-size: 0.9em" -->

@lisie_sprawy
> Repasting it from other channel, so it will not lost itself :) why in some tasks about deleting vowels you can see "constexpr int" instead "const int"?

`constexpr` in the context of a variable is a stronger const. In addition to the fact that it is a constant and we will not change its value, the compiler can further optimize all calculations made with its use and simply calculate the result during compilation and put it in the appropriate places as program constants. We will learn how to do it in modern C ++, where more fascinating will be topic of `constexpr` functions, not a variables (constants).

Anyway, this is an optimization and you should have the habit to write `constexpr` right away. If the compiler protests somewhere, it means you can't use it there and should leave just `const`. From C++20, `constexpr` will become even more common, because many of the limitations of `constexpr` will be lifted.

To remember for now: try to use `constexpr` by default when defining constants instead of `const`.
