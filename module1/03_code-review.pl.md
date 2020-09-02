<!-- .slide: data-background="#111111" -->

# Przykłady z Code Review

___
<!-- .slide: style="font-size: 0.9em" -->

Przykład:

```cpp
bool doesPasswordsMatch(const std::string& password, const std::string& repeatedPassword) {
    if (password == repeatedPassword) {
        return true;
    }
    return false;
}
```

Lepiej:
<!-- .element: class="fragment fade-in" -->

```cpp
bool doesPasswordsMatch(const std::string& password, const std::string& repeatedPassword) {
    return password == repeatedPassword;
}
```
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: 0.9em" -->

Przykład:

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
 //
 //
 //
 // Co myślisz o usunięciu przypadku ErrorCode::Ok: i ustawieniu go jako domyślnego?
 // Nawiasy klamrowe nie są potrzebne nawet w przypadkach wielowierszowych. To tylko kwestia konwencji, czy powinieneś je stosować, czy nie. Nie zapewniają dodatkowego bezpieczeństwa.
 // Zazwyczaj nie dokonujemy wcięć przy caseach i kodzie w namespaceach
```

___

Lepiej?:

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

___

Przykład:

```cpp
if(doesPasswordsMatch(first_pass, second_pass)) {
    return checkPasswordRules(first_pass);
} else {
    return ErrorCode::PasswordsDoesNotMatch;
}
```

Lepiej:
<!-- .element: class="fragment fade-in" -->

```cpp
if(doesPasswordsMatch(first_pass, second_pass)) {
    return checkPasswordRules(first_pass);
}
return ErrorCode::PasswordsDoesNotMatch;
```
<!-- .element: class="fragment fade-in" -->

___

```cpp
enum class ErrorCode {
    PasswordNeedsAtLeastNineCharacters,
    PasswordNeedsAtLeastOneUppercaseLetter,
    PasswordNeedsAtLeastOneSpecialCharacters,  // końcowy przecinek
}
```

> Naprawdę nie wiem, może to mój nawyk zaczerpnięty z Pythona, aby mieć przecinki również po ostatnim elemencie wyliczenia/kolekcji, bo jeśli w przyszłości dodam nowy element, nie będę się musiał martwić o błędy w odniesieniu do brakującego przecinka :)

___
<!-- .slide: style="font-size: 0.75em" -->

> A: Możesz określić rozmiar wektora w konstruktorze :)

```cpp
std::vector<std::shared_ptr<int>> resultVector(count);
```

> B: Tak, ale co z sytuacją, gdy licznik ma wartość ujemną? Nie sądzę, aby taka wartość była używana w konstruktorze wektora, dlatego najpierw wykonuję takie sprawdzenie.
<!-- .element: class="fragment fade-in" -->

```cpp
std::vector<std::shared_ptr<int>> resultVector{};
if (count < 0) {
    return resultVector;
}
resultVector.reserve(count);
```
<!-- .element: class="fragment fade-in" -->

> A: masz racje :) , mój błąd :)
<!-- .element: class="fragment fade-in" -->

> B: Nie ma problemu, dziękuję za recenzję :)
<!-- .element: class="fragment fade-in" -->

https://github.com/coders-school/kurs_cpp_podstawowy/pull/254/files
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: 0.85em" -->

Max line length - 120. How to format?

Typically lines are long when the function takes multiple parameters:
<!-- .element: class="fragment fade-in" -->

```cpp
int superFunction(std::vector<std::shared_ptr<int>> vectorOfSharedPointers, std::map<std::string, int> miniMap, std::unordered_set<int> hashes, std::function<void(int, int)> compareFunction) {
    // rób coś
}

// użycie
auto result = superFunction(mySuperVector, myMiniMap, myGreatHashTable, [](const auto & lhs, const auto & rhs) { return lhs >= rhs;})
```
<!-- .element: class="fragment fade-in" -->

Lepsze formatowanie:
<!-- .element: class="fragment fade-in" -->

```cpp
int superFunction(std::vector<std::shared_ptr<int>> vectorOfSharedPointers,
                  std::map<std::string, int> miniMap,
                  std::unordered_set<int> hashes,
                  std::function<void(int, int)> compareFunction) {
    // rób coś
}

// użycie
auto result = superFunction(mySuperVector,
                            myMiniMap,
                            myGreatHashTable,
                            [](const auto & lhs, const auto & rhs) { return lhs >= rhs;});
```
<!-- .element: class="fragment fade-in" -->

___

Albo dla dłuższych lambd / zbyt długich parametrów, które przekraczają limit linii:

```cpp
int superFunction(
        std::vector<std::shared_ptr<int>> vectorOfSharedPointers,
        std::map<std::string, int> miniMap,
        std::unordered_set<int> hashes,
        std::function<void(int, int)> compareFunction) {
        // dwa poziomy wcięcia powyżej, aby uniknąć nieporozumień.
        // Ciało funkcji poniżej będzie wcięte o jeden poziom
    // rób coś
}

// użycie
auto result = superFunction(mySuperVector,
                            myMiniMap,
                            myGreatHashTable,
                            [](const auto & lhs, const auto & rhs) {
                                return lhs >= rhs;
                            });
```
<!-- .element: class="fragment fade-in" -->

___

* <!-- .element: class="fragment fade-in" --> <a href="https://github.com/coders-school/kurs_cpp_podstawowy/pull/252/files">Dobre użycie <code>std::map</code> zamiast drabiny ifów</a>
* <!-- .element: class="fragment fade-in" --> Zwracajcie uwagę na znaki końca linii na końcu dokumentu.
* <!-- .element: class="fragment fade-in" --> <code>enum</code> lub <code>enum class</code> są pod spodem wartościami całkowitymi (jakiś rodzaj inta). Nie warto przekazywać ich przez <code>const&</code> w celu optymalizacji.
* <!-- .element: class="fragment fade-in" -->  Max 2 puste linie. Zazwyczaj wystarcza jedna. 2 puste linie nie mogą wystąpić wewnątrz żadnych bloków (zakresów), jak funkcje, klasy, enumy.
* <!-- .element: class="fragment fade-in" -->  Dobra praktyka - alokowanie pojemności wektora, gdy jest z góry znana.
* <!-- .element: class="fragment fade-in" -->  Kiedy stosujemy konwencje?
  * <!-- .element: class="fragment fade-in" -->  Współpraca grupowa - obowiązkowo. Nie ma nic gorszego niż niejednolite formatowanie w projekcie. Narzucamy wam styl zmodyfikowany styl Chromium, aby nie było przepychanek. Możecie go egzekwować do woli, w szczególności w Internal Code Review (czyli wewnątrz grupy, zanim zgłosicie nam Pull Request do sprawdzenia)
  * <!-- .element: class="fragment fade-in" -->  Praca indywidualna - można stosować własne upodobania, ważne żeby było jednolicie.
  * <!-- .element: class="fragment fade-in" -->  Nie bądźcie "code style nazi" i nie wymuszajcie na innych osobach waszego stylu formatowania, jeśli komentujecie indywidualne PR. Oczywiście fajnie gdyby wszystko było tak samo wszędzie, ale tak naprawdę co firma/projekt to spotkacie się z innym formatowaniem. Warto przywyknąć, że nie zawsze wam pasuje to co sprawdzacie. Głównie odnosi się to do nowych linii i nawiasów {}.

___

* <!-- .element: class="fragment fade-in" --> <code>#include</code> - ja (Łukasz) nie jestem zbyt nazistowski z komentowaniem wam że:
  * <!-- .element: class="fragment fade-in" --> jest nieposortowane
  * <!-- .element: class="fragment fade-in" --> nie ma nowej linii
  * <!-- .element: class="fragment fade-in" --> żeby to przenosić do cpp zamiast trzymać w hpp
  * <!-- .element: class="fragment fade-in" --> usunąć, bo nieużywane.
  
  Tylko jak mi się rzuci w oczy to daję taki komentarz. Ale wiedzcie, że to są dobre praktyki i warto je stosować.
  <!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Też nie bądźcie nazistami i nie róbcie całego code review tylko po to, żeby komuś wytknąć nieposortowane headery lub brakujące {} w jednym miejscu. Podczas projektów grupowych takie rzeczy sobie nawytykacie wewnątrz grup i tak się najszybciej nauczycie :) Na zewnątrz do sprawdzenia ma wychodzić kod przejrzany przez pozostałe osoby z grupy. Nie ma zwalania winy, że to pisał X i on nie dopilnował. Cała grupa obrywa równo ;)
