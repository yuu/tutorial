# Hangman

[Specific][1]

Purposes:
- First, the program is designed to give you some practice writing programs that manipulate strings and files.
- Second, by extending the program using the graphical tools from Chapter 9,
  you will have a chance to work with multiple classes in a single application.

When the user plays Hangman, the computer first selects a secret word at random from a list built into the program.

```c++
std::vector<std::string> secret_word = {foo, bar, fizz, bazz};
std::random_device rnd;
std::mt19937 mt(rnd());
std::uniform_int_distribution<> r(0, 3);
auto rf = [&]() -> auto { return r(mt); };

auto select_word = [&] -> auto { secret_word.at(rf()); };
```

The program then prints out a row of dashes(one for each latter in the secret word)
and asks the user to guess a letter.

If the user guesses a letter that is in the word, the word is redisplayed with
all instances of that letter shown in the current positions,

```c++

static int index = 0;

for (auto &&letter : secret_word)
    std::cout << letter.at(index) << std::endl;

// asks the user to guess a letter, the latter 
char ask;
for (auto &&letter : secret_word) {
    std::cout << letter.at(index);
    
    if (strcmp(&letter.at(index+1)), &ask) == 0) {
        std::cout << ask << std::endl;
    }
}

```


[1]: https://web.stanford.edu/class/archive/cs/cs106a/cs106a.1124/handouts/200%20Assignment%204.pdf

## Table of Contents
* [Usage](#usage)
* [Requirements](#requirements)

## Usage

## Requirements
