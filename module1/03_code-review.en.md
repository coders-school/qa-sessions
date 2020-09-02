<!-- .slide: data-background="#111111" -->

# Examples from Code Review

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

Max line length - 120. How to format?

Typically lines are long when the function takes multiple parameters:
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

* <!-- .element: class="fragment fade-in" --> <a href="https://github.com/coders-school/kurs_cpp_podstawowy/pull/252/files">Nice usage of <code>std::map</code> instead of ifs' ladder</a>
* <!-- .element: class="fragment fade-in" --> Pay attention to the line breaks at the end of the document.
* <!-- .element: class="fragment fade-in" --> <code>enum</code> or <code>enum class</code> are integer values ​​underneath (some kind of int). It's not worth passing them over <code>const&</code> for optimization.
* <!-- .element: class="fragment fade-in" -->  Max 2 blank lines. Usually one is enough. 2 empty lines cannot appear inside any blocks (ranges) like functions, classes, enums.
* <!-- .element: class="fragment fade-in" -->  Good practice - allocate vector capacity when known in advance.
* <!-- .element: class="fragment fade-in" -->  When do we use the conventions?
  * <!-- .element: class="fragment fade-in" -->  Group cooperation - obligatory. There is nothing worse than patchy formatting in your project. We are imposing on you the Chromium Modified Style so that there is no scuffle. You can enforce it at will, in particular in the Internal Code Review (i.e. inside the group, before sending us a Pull Request for review)
  * <!-- .element: class="fragment fade-in" -->  Individual work - you can use your own preferences, it is important that it is uniform.
  * <!-- .element: class="fragment fade-in" --> Don't be "code style nazi" and don't force your formatting style on other people if you comment on individual PR. Of course, it would be nice if everything has same formatting everywhere, but in fact, every company/project will use a different formatting. It is worth to get used to the fact that what you check does not always suit you. This mainly applies to new lines and {} brackets. 

___

* <!-- .element: class="fragment fade-in" --> <code>#include</code> - I (Łukasz) am not too Nazi commenting to you that:
  * <!-- .element: class="fragment fade-in" --> it is unsorted
  * <!-- .element: class="fragment fade-in" --> there is no new line
  * <!-- .element: class="fragment fade-in" --> to move it to cpp instead of sticking to hpp
  * <!-- .element: class="fragment fade-in" --> remove, because not used.
  
  Only when it catches my eye I give such a comment. But know that these are good practices and it is worth applying them.
  <!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Also, don't be Nazis and don't do the whole code review just to point out to someone unsorted headers or missing {} in one place. During group projects you'll give yourself a needles about such things inside the groups and this is how you learn the fastest :) To outside review should goes only the code checked by other group members. There is no blaming X that wrote that and he did not take care of it. The whole group gets a beating evenly ;)
