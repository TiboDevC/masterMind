#include "mastermind.hpp"

#include <algorithm>
#include <iostream>

void Mastermind::play() {
    std::cout << "Welcome to Mastermind!" << std::endl;
    std::cout << "Guess the secret code by entering numbers separated by spaces." << std::endl;
    std::cout << "Max number of attempts: " << MaxAttempts << std::endl;
    std::cout << "Code length: " << MaxCodeLength << std::endl;
    std::cout << "BLANK: invalid position and invalid color" << std::endl;
    std::cout << "WHITE: invalid position and correct color" << std::endl;
    std::cout << "BLACK: correct position and correct color" << std::endl;
    std::cout << "Available numbers: ";
    for (int i = 1; i <= MaxNumColors; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    while (not gameOver) {
        std::cout << "Attempt #" << currentAttempt + 1 << ": ";
        const Combination guess = getGuess();
        Combination result = checkGuess(guess);

        displayResult(result);

        if (allElementsEqual(result, static_cast<int>(CORRECT_POSITION))) {
            std::cout << "Congratulations! You guessed the secret code!" << std::endl;
            gameOver = true;
        } else if (currentAttempt + 1 >= MaxAttempts) {
            std::cout << "Game over! You couldn't guess the secret code." << std::endl;
            std::cout << "The secret code was: ";
            for (int i: secretCode) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            gameOver = true;
        } else {
            ++currentAttempt;
        }
    }
}


void Mastermind::generateSecretCode() {
    mt.seed(rd());
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, MaxNumColors);

    for (int i = 0; i < MaxCodeLength; ++i) {
        secretCode.at(i) = dis(gen);
    }

#if 1
    std::cout << "The secret code is: ";
    for (int i: secretCode) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
#endif
}

Mastermind::Combination Mastermind::getGuess() {
    Combination guess{};
    int num;
    for (int i = 0; i < MaxCodeLength && std::cin >> num; ++i) {
        guess.at(i) = num;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return guess;
}

constexpr Mastermind::Combination Mastermind::checkGuess(const Combination &guess) {
    Combination result{};

    Combination secretCodeCopy = secretCode;
    Combination guessCopy = guess;

    // Check for exact matches
    for (int i = 0; i < MaxCodeLength; ++i) {
        if (secretCodeCopy.at(i) == guessCopy.at(i)) {
            result.at(i) = CORRECT_POSITION;
            secretCodeCopy.at(i) = INVALID_COLOR;
            guessCopy.at(i) = INVALID_COLOR;
        }
    }

    // Check for color matches
    for (int i = 0; i < MaxCodeLength; ++i) {
        if (guessCopy.at(i) != INVALID_COLOR) {
            auto it = std::find(secretCodeCopy.begin(), secretCodeCopy.end(), guessCopy.at(i));
            if (it != secretCodeCopy.end()) {
                result.at(i) = CORRECT_COLOR;
                *it = INVALID_COLOR;
                guessCopy.at(i) = INVALID_COLOR;
            }
        }
    }

    return result;
}

void Mastermind::displayResult(Mastermind::Combination &result) {
    std::shuffle(result.begin(), result.end(), mt);

    std::cout << "Result: ";
    for (const auto &i: result) {
        switch (i) {
            case INVALID_COLOR:
                std::cout << "BLANK ";
                break;
            case CORRECT_COLOR:
                std::cout << "WHITE ";
                break;
            case CORRECT_POSITION:
                std::cout << "BLACK ";
                break;
            default:
                break;
        }
    }
    std::cout << std::endl;
}

template<typename T, size_t N>
bool Mastermind::allElementsEqual(const std::array<T, N> &arr, T value) {
    for (const auto &element: arr) {
        if (element != value) {
            return false;
        }
    }
    return true;
}
