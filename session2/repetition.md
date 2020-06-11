# Powtórka #2

## Przykłady z Code Review

---

Example:

```cpp
bool doesPasswordsMatch(const std::string& password, const std::string& repeatedPassword) {
    if (password == repeatedPassword) {
        return true;
    }
    return false;
}
```

Better:

```cpp
bool doesPasswordsMatch(const std::string& password, const std::string& repeatedPassword) {
    return password == repeatedPassword;
}
```

---

Example:

```cpp
std::string getErrorMessage(ErrorCode Error) {
    switch (Error) {
        case ErrorCode::Ok:
            return "OK";
            break;
        case ErrorCode::PasswordNeedsAtLeastNineCharacters:
            return "Password Needs At Least Nine Characters";
            break;
        case ErrorCode::PasswordNeedsAtLeastOneNumber:
            return "Password Needs At Least One Number";
            break;
        case ErrorCode::PasswordNeedsAtLeastOneSpecialCharacter:
            return "Password Needs At Least One Special Character";
            break;
        case ErrorCode::PasswordNeedsAtLeastOneUppercaseLetter:
            return "Password Needs A Least One Uppercase Letter";
            break;
        case ErrorCode::PasswordsDoesNotMatch:
            return "Passwords Does Not Match";
            break;
        default:
            return "UNDEFINED ERROR";
    }
 }
 // What do you think about removing case ErrorCode::Ok: and putting it in default?
 // Braces are not needed even for multiline cases. It's only matter of convention if you should apply them or not. They don't provide additional safety.
 // We usually don't indent case and code inside namespace
```

Better?:

```cpp
std::string getErrorMessage(ErrorCode error) {
    switch (error) {
    case ErrorCode::PasswordNeedsAtLeastNineCharacters:
        return "Password Needs At Least Nine Characters";
    case ErrorCode::PasswordNeedsAtLeastOneNumber:
        return "Password Needs At Least One Number";
    case ErrorCode::PasswordNeedsAtLeastOneSpecialCharacter:
        return "Password Needs At Least One Special Character";
    case ErrorCode::PasswordNeedsAtLeastOneUppercaseLetter:
        return "Password Needs A Least One Uppercase Letter";
    case ErrorCode::PasswordsDoesNotMatch:
        return "Passwords Does Not Match";
    default:
        return "OK";
    }
 }
```

---

Example:

```cpp
if(doesPasswordsMatch(first_pass, second_pass)) {
    return checkPasswordRules(first_pass);
} else {
    return ErrorCode::PasswordsDoesNotMatch;
}
```

Better:

```cpp
if(doesPasswordsMatch(first_pass, second_pass)) {
    return checkPasswordRules(first_pass);
}
return ErrorCode::PasswordsDoesNotMatch;
```


---

```cpp
enum class ErrorCode {
    PasswordNeedsAtLeastNineCharacters,
    PasswordNeedsAtLeastOneUppercaseLetter,
    PasswordNeedsAtLeastOneSpecialCharacters,  // trailing comma
}
```

> I do not know really, it's maybe my habit taken from python, to have commas also in the last element of enum/collection, because if I add new element in the future, i didn't have to worry about some errors in regards to missing comma :)

---

> A: You can specify a size of vector in constructor :)

```cpp
std::vector<std::shared_ptr<int>> resultVector(count);
```

> B: Yes, but what about situation, when count is negative value? I do not think such value should be used in the vector constructor, that's why I do such check first.

```cpp
std::vector<std::shared_ptr<int>> resultVector{};
if (count < 0) {
    return resultVector;
}
resultVector.reserve(count);
```

> A: you are right :) , my fault :)

> B: No problem, thanks for review :)

https://github.com/coders-school/kurs_cpp_podstawowy/pull/254/files

---

Max długość linii - 120. Jak formatować?

Zazwyczaj linie są długie gdy funkcja przyjmuje wiele parametrów:

```cpp
int superFunction(std::vector<std::shared_ptr<int>> vectorOfSharedPointers, std::map<std::string, int> miniMap, std::unordered_set<int> hashes, std::function<void(int, int)> compareFunction) {
    // do sth
}

// usage
auto result = superFunction(mySuperVector, myMiniMap, myGreatHashTable, [](const auto & lhs, const auto & rhs) { return lhs >= rhs;})
```

Better formatting:

```cpp
int superFunction(std::vector<std::shared_ptr<int>> vectorOfSharedPointers,
                  std::map<std::string, int> miniMap,
                  std::unordered_set<int> hashes,
                  std::function<void(int, int)> compareFunction) {
    // do sth
}

// usage
auto result = superFunction(mySuperVector,
                            myMiniMap,
                            myGreatHashTable,
                            [](const auto & lhs, const auto & rhs) { return lhs >= rhs;});
```

Or for longer lambdas / too long first parameter which exceeds line limit:

```cpp
int superFunction(
        std::vector<std::shared_ptr<int>> vectorOfSharedPointers,
        std::map<std::string, int> miniMap,
        std::unordered_set<int> hashes,
        std::function<void(int, int)> compareFunction) {
        // two levels of indentation above to avoid confusion. The function body below will be indented with one level
    // do sth
}

// usage
auto result = superFunction(mySuperVector,
                            myMiniMap,
                            myGreatHashTable,
                            [](const auto & lhs, const auto & rhs) {
                                return lhs >= rhs;
                            });
```

---

* [Nice usage of std::map instead of ifs' ladder](https://github.com/coders-school/kurs_cpp_podstawowy/pull/252/files)
* Zwracajcie uwagę na znaki końca linii na końcu dokumentu.
* `enum` lub `enum class` są pod spodem wartościami całkowitymi (jakiś rodzaj inta). Nie warto przekazywać ich przez const& w celu optymalizacji.
* Max 2 puste linie. Zazwyczaj wystarcza jedna. 2 puste linie nie mogą wystąpić wewnątrz żadnych bloków (zakresów), jak funkcje, klasy, enumy.
* Dobra praktyka - alokowanie pojemności wektora, gdy jest z góry znana.
* Kiedy stosujemy konwencje?
  * Współpraca grupowa - obowiązkowo. Nie ma nic gorszego niż niejednolite formatowanie w projekcie. Narzucamy wam styl zmodyfikowany styl Chromium, aby nie było przepychanek. Możecie go egzekwować do woli, w szczególności w Internal Code Review (czyli wewnątrz grupy, zanim zgłosicie nam Pull Request do sprawdzenia)
  * Praca indywidualna - można stosować własne upodobania, ważne żeby było jednolicie.
  * Nie bądźcie "code style nazi" i nie wymuszajcie na innych osobach waszego stylu formatowania, jeśli komentujecie indywidualne PR. Oczywiście fajnie gdyby wszystko było tak samo wszędzie, ale tak naprawdę co firma/projekt to spotkacie się z innym formatowaniem. Warto przywyknąć, że nie zawsze wam pasuje to co sprawdzacie. Głównie odnosi się to do nowych linii i nawiasów {}.
* `#include` - ja (Łukasz) nie jestem zbyt nazistowski z komentowaniem wam że:
  * jest nieposortowane
  * nie ma nowej linii
  * żeby to przenosić do cpp zamiast trzymać w hpp
  * usunąć, bo nieużywane.
  
  Tylko jak mi się rzuci w oczy to daję taki komentarz. Ale wiedzcie, że to są dobre praktyki i warto je stosować.

* Też nie bądźcie nazistami i nie róbcie całego code review tylko po to, żeby komuś wytknąć nieposortowane headery lub brakujące {} w jednym miejscu. Podczas projektów grupowych takie rzeczy sobie nawytykacie wewnątrz grup i tak się najszybciej nauczycie :) Na zewnątrz do sprawdzenia ma wychodzić kod przejrzany przez pozostałe osoby z grupy. Nie ma zwalania winy, że to pisał X i on nie dopilnował. Cała grupa obrywa równo ;)

---

## Współpraca grupowa - Scrum

[Spotkania Scrumowe](ScrumFramework.pdf)

[Ściąga ze Scruma](sciaga_scrum.pdf)

---

## Scrum - dobre praktyki

* **Daily meetings** - codzienne spotkania w celu zsynchronizowania się, zobaczenia jak idzie robota i w szczególności, komu trzeba pomóc, bo utknął.
* **Podejście iteracyjne** - dostarczamy małe kawałki funkcjonalności. Ważne żeby jak najszybciej dostarczyć cokolwiek, co powoduje, że choćby tylko jeden test przechodzi. Potem każdy może nad tym nadbudowywać kolejne funkcjonalności.
* **Retrospektywy** - wg mnie najważniejsze spotkanie. Odbywa się po zakończonej iteracji (sprincie) i zespół klepie się po pleckach jak to było wspaniale, jak dużo się udało zrobić i jak to można jeszcze polepszyć. Poza tym zespół wrzuca sobie najgorsze epitety odnośnie nieumiejętności współpracy, wyrobienia się na czas i poprawnego zaplanowania swojej pracy. Po tym spotkaniu muszą być sformułowane wnioski co można poprawić, aby lepiej się współpracowało oraz akcje do zrobienia dla każdej osoby.

---

## Pytania z kanału #powtórka

@edmundoPL
> Pytanie ode mnie na powtórkę. O co chodzi z tym zapewnianiem odpowiednio długiego życia zmiennej, na która wskazuje pointer lub referencja? 
> Pojawiło się to już kilka razy, a ja nadal jakoś tego nie czuje. Niby trochę rozumiem ale nie do końca. Może jakiś ciekawy przykład się znajdzie do czwartku?

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

Stos graficznie. Prawo -> kolejne linie kodu

| FRAME | A               | B              | C           | D            | E                    | F            | G               | H            | I               |
| :---: | :-------------- | :------------- | :---------- | :----------- | :------------------- | :----------- | :-------------- | :----------- | :-------------- |
|   1   |                 |                | **ptr = ?** | **ptr = &a** |                      |              | **c = ?**       | **c = 100**  |                 |
|   1   |                 |                | **a = ?**   | **a = 10**   |                      | **??? = 20** | **b = ? (20?)** | **b = 50**   |                 |
|   0   | **pointer = ?** | pointer = ?    | pointer = ? | pointer = ?  | **pointer = &a** !!! | pointer = &a | pointer = &a    | pointer = &a | pointer = &a    |
|   0   | **number = ?**  | **number = 5** | number = 5  | number = 5   | number = 5           | number = 5   | number = 5      | number = 5   | **number = 50** |

---

@Jakub J
> Generyczne lambdy, jaki jest w takim razie sens stosowania zwykłych lambd(w których przekazujemy konkretny typ)?

Ograniczony. Tylko gdy chcemy aby lambda zadziałała dla określonego typu i np nie skompilowała się dla innego.
Normalnie zalecam stosowanie generycznych. W kodzie można się natknąć na takie i takie. Generyczne weszły w C++14 jeszcze się dobrze nie upowszechniły. Ale mocno do nich zachęcam.

---

@lisie_sprawy
> Przeklejam z innego kanału, żeby nie uciekło :) czemu w niektórych zadaniach związanych z wywaleniem samogłosek pojawia się np. "constexpr int", zamiast "const int"?

`constexpr` w kontekście zmiennej to taki silniejszy const. Oprócz tego, że jest to stała i nie zmienimy jej wartości to kompilator może dodatkowo optymalizować wszelkie obliczenia wykonywane z jej użyciem i po prostu już podczas kompilacji obliczyć wynik i wstawić go w odpowiednie miejsca jako stałe programu. Jak to robić to się nauczymy na nowoczesnym C++, gdzie bardziej fascynujący będzie temat funkcji `constexpr`, a nie zmiennych (stałych).

W każdym bądź razie jest to optymalizacja i warto mieć odruch pisania constexpr od razu. Jeśli gdzieś kompilator zaprotestuje, to znaczy że się nie da i zostawiamy sam const. Od C++20 `constexpr` wejdzie w użycie jeszcze powszechniej, bo dużo ograniczeń funkcji `constexpr` zostanie zniesionych.

Do zapamiętania na teraz: staraj się domyślnie używać `constexpr` przy definiowaniu stałych zamiast const.

---

## Wnioski po konkursie

* Formułowanie zadań / wymagań to sztuka. Jakby dokładnie tego nie zrobić to zawsze będzie wiele osób, które będzie potrafiło inaczej zinterpretować wymagania niż zakładał autor. [Polecam motzno to wideo](https://www.youtube.com/watch?v=Ct-lOOUqmyY)
* Ilu trenerów tyle opinii na temat wymagań
* Ilu trenerów tyle opinii na temat styli kodowania
