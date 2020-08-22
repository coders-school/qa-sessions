<!-- .slide: data-background="#111111" -->

# Pytania z kanału #powtórka

___

@edmundoPL
> Pytanie ode mnie na powtórkę. O co chodzi z tym zapewnianiem odpowiednio długiego życia zmiennej, na która wskazuje pointer lub referencja? 
> Pojawiło się to już kilka razy, a ja nadal jakoś tego nie czuje. Niby trochę rozumiem ale nie do końca. Może jakiś ciekawy przykład się znajdzie do czwartku?

___

Prześledźmy stos w tym kawałku kodu

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

___
<!-- .slide: style="font-size: 0.7em" -->

Stos graficznie. Prawo -> kolejne linie kodu

| FRAME | A               | B              | C           | D            | E                    | F            | G               | H            | I               |
| :---: | :-------------- | :------------- | :---------- | :----------- | :------------------- | :----------- | :-------------- | :----------- | :-------------- |
|   1   |                 |                | **ptr = ?** | **ptr = &a** |                      |              | **c = ?**       | **c = 100**  |                 |
|   1   |                 |                | **a = ?**   | **a = 10**   |                      | **??? = 20** | **b = ? (20?)** | **b = 50**   |                 |
|   0   | **pointer = ?** | pointer = ?    | pointer = ? | pointer = ?  | **pointer = &a** !!! | pointer = &a | pointer = &a    | pointer = &a | pointer = &a    |
|   0   | **number = ?**  | **number = 5** | number = 5  | number = 5   | number = 5           | number = 5   | number = 5      | number = 5   | **number = 50** |

___

@Jakub J
> Generyczne lambdy, jaki jest w takim razie sens stosowania zwykłych lambd(w których przekazujemy konkretny typ)?

Ograniczony. Tylko gdy chcemy, aby lambda zadziałała dla określonego typu i np. nie skompilowała się dla innego.
Normalnie zalecam stosowanie generycznych. W kodzie można się natknąć na takie i takie. Generyczne weszły w C++14 i jeszcze się dobrze nie upowszechniły. Ale mocno do nich zachęcam.

___
<!-- .slide: style="font-size: 0.9em" -->

@lisie_sprawy
> Przeklejam z innego kanału, żeby nie uciekło :) czemu w niektórych zadaniach związanych z wywaleniem samogłosek pojawia się np. "constexpr int", zamiast "const int"?

`constexpr` w kontekście zmiennej to taki silniejszy const. Oprócz tego, że jest to stała i nie zmienimy jej wartości to kompilator może dodatkowo optymalizować wszelkie obliczenia wykonywane z jej użyciem i po prostu już podczas kompilacji obliczyć wynik i wstawić go w odpowiednie miejsca jako stałe programu. Jak to robić to się nauczymy na nowoczesnym C++, gdzie bardziej fascynujący będzie temat funkcji `constexpr`, a nie zmiennych (stałych).

W każdym bądź razie jest to optymalizacja i warto mieć odruch pisania constexpr od razu. Jeśli gdzieś kompilator zaprotestuje, to znaczy że się nie da i zostawiamy sam const. Od C++20 `constexpr` wejdzie w użycie jeszcze powszechniej, bo dużo ograniczeń funkcji `constexpr` zostanie zniesionych.

Do zapamiętania na teraz: staraj się domyślnie używać `constexpr` przy definiowaniu stałych zamiast const.
