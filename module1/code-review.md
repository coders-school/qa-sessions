<!-- .slide: data-background="#111111" -->

# Przykłady z Code Review

___
<!-- .slide: style="font-size: 0.9em" -->

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
<!-- .element: class="fragment fade-in" -->

```cpp
bool doesPasswordsMatch(const std::string& password, const std::string& repeatedPassword) {
    return password == repeatedPassword;
}
```
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: 0.9em" -->

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

___

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

___

Example:

```cpp
if(doesPasswordsMatch(first_pass, second_pass)) {
    return checkPasswordRules(first_pass);
} else {
    return ErrorCode::PasswordsDoesNotMatch;
}
```

Better:
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
    PasswordNeedsAtLeastOneSpecialCharacters,  // trailing comma
}
```

> I do not know really, it's maybe my habit taken from python, to have commas also in the last element of enum/collection, because if I add new element in the future, i didn't have to worry about some errors in regards to missing comma :)

___
<!-- .slide: style="font-size: 0.75em" -->

> A: You can specify a size of vector in constructor :)

```cpp
std::vector<std::shared_ptr<int>> resultVector(count);
```

> B: Yes, but what about situation, when count is negative value? I do not think such value should be used in the vector constructor, that's why I do such check first.
<!-- .element: class="fragment fade-in" -->

```cpp
std::vector<std::shared_ptr<int>> resultVector{};
if (count < 0) {
    return resultVector;
}
resultVector.reserve(count);
```
<!-- .element: class="fragment fade-in" -->

> A: you are right :) , my fault :)
<!-- .element: class="fragment fade-in" -->

> B: No problem, thanks for review :)
<!-- .element: class="fragment fade-in" -->

https://github.com/coders-school/kurs_cpp_podstawowy/pull/254/files
<!-- .element: class="fragment fade-in" -->

___
<!-- .slide: style="font-size: 0.85em" -->

Max długość linii - 120. Jak formatować?

Zazwyczaj linie są długie gdy funkcja przyjmuje wiele parametrów:
<!-- .element: class="fragment fade-in" -->

```cpp
int superFunction(std::vector<std::shared_ptr<int>> vectorOfSharedPointers, std::map<std::string, int> miniMap, std::unordered_set<int> hashes, std::function<void(int, int)> compareFunction) {
    // do sth
}

// usage
auto result = superFunction(mySuperVector, myMiniMap, myGreatHashTable, [](const auto & lhs, const auto & rhs) { return lhs >= rhs;})
```
<!-- .element: class="fragment fade-in" -->

Better formatting:
<!-- .element: class="fragment fade-in" -->

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
<!-- .element: class="fragment fade-in" -->

___

Or for longer lambdas / too long first parameter which exceeds line limit:

```cpp
int superFunction(
        std::vector<std::shared_ptr<int>> vectorOfSharedPointers,
        std::map<std::string, int> miniMap,
        std::unordered_set<int> hashes,
        std::function<void(int, int)> compareFunction) {
        // two levels of indentation above to avoid confusion.
        // The function body below will be indented with one level
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
<!-- .element: class="fragment fade-in" -->

___

* <!-- .element: class="fragment fade-in" --> <a href="https://github.com/coders-school/kurs_cpp_podstawowy/pull/252/files">Nice usage of std::map instead of ifs' ladder</a>
* <!-- .element: class="fragment fade-in" --> Zwracajcie uwagę na znaki końca linii na końcu dokumentu.
* <!-- .element: class="fragment fade-in" --> <code>enum</code> lub <code>enum class</code> są pod spodem wartościami całkowitymi (jakiś rodzaj inta). Nie warto przekazywać ich przez const& w celu optymalizacji.
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
