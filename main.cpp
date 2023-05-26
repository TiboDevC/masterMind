#include <algorithm>
#include <array>
#include <iostream>
#include <random>

class Mastermind {
private:
    constexpr static int MaxCodeLength = 4;
    constexpr static int MaxNumColors = 6;
    constexpr static int MaxAttempts = 10;

    typedef std::array<int, MaxCodeLength> Combination;

    Combination secretCode{};
    int currentAttempt;
    bool gameOver;

    std::random_device rd;
    std::mt19937 mt;

    enum {
        INVALID,
        CORRECT_POSITION,
        CORRECT_COLOR,
    };

public:
    Mastermind()
        : currentAttempt(0), gameOver(false) {
        generateSecretCode();
    }

    void play() {
        std::cout << "Welcome to Mastermind!" << std::endl;
        std::cout << "Guess the secret code by entering numbers separated by spaces." << std::endl;
        std::cout << "Max number of attempts: " << MaxAttempts << std::endl;
        std::cout << "Code length: " << MaxCodeLength << std::endl;
        std::cout << "Available numbers: ";
        for (int i = 1; i <= MaxNumColors; ++i) { std::cout << i << " "; }
        std::cout << std::endl;

        while (!gameOver) {
            std::cout << "Attempt #" << currentAttempt + 1 << ": ";
            const Combination guess = getGuess();
            Combination result = checkGuess(guess);

            std::shuffle(result.begin(), result.end(), mt);

            std::cout << "Result: ";
            for (int i: result) { std::cout << i << " "; }
            std::cout << std::endl;

            if (std::ranges::all_of(result.cbegin(), result.cend(), [](int i) { return i == CORRECT_POSITION; })) {
                std::cout << "Congratulations! You guessed the secret code!" << std::endl;
                gameOver = true;
            } else if (currentAttempt + 1 >= MaxAttempts) {
                std::cout << "Game over! You couldn't guess the secret code." << std::endl;
                std::cout << "The secret code was: ";
                for (int i: secretCode) { std::cout << i << " "; }
                std::cout << std::endl;
                gameOver = true;
            } else {
                ++currentAttempt;
            }
        }
    }

private:
    void generateSecretCode() {
        mt.seed(rd());
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, MaxNumColors);

        for (int i = 0; i < MaxCodeLength; ++i) { secretCode.at(i) = dis(gen); }

#if 1
        std::cout << "The secret code is: ";
        for (int i: secretCode) { std::cout << i << " "; }
        std::cout << std::endl;
#endif
    }

    static Combination getGuess() {
        Combination guess{};
        int num;
        for (int i = 0; i < MaxCodeLength && std::cin >> num; ++i) { guess.at(i) = num; }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return guess;
    }

    constexpr Combination checkGuess(const Combination &guess) {
        Combination result{};

        Combination secretCodeCopy = secretCode;
        Combination guessCopy = guess;

        // Check for exact matches
        for (int i = 0; i < MaxCodeLength; ++i) {
            if (secretCodeCopy.at(i) == guessCopy.at(i)) {
                result.at(i) = CORRECT_POSITION;
                secretCodeCopy.at(i) = INVALID;
                guessCopy.at(i) = INVALID;
            }
        }

        // Check for color matches
        for (int i = 0; i < MaxCodeLength; ++i) {
            if (guessCopy.at(i) != INVALID) {
                auto it = std::find(secretCodeCopy.begin(), secretCodeCopy.end(), guessCopy.at(i));
                if (it != secretCodeCopy.end()) {
                    result.at(i) = CORRECT_COLOR;
                    *it = INVALID;
                    guessCopy.at(i) = INVALID;
                }
            }
        }

        return result;
    }
};

int main() {
    Mastermind game;
    game.play();
    return 0;
}
