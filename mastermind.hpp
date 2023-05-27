#ifndef MASTERMIND_MASTERMIND_HPP
#define MASTERMIND_MASTERMIND_HPP

#include <array>
#include <random>

class Mastermind {
private:
    enum {
        INVALID_COLOR,
        CORRECT_COLOR,
        CORRECT_POSITION,
    };

    constexpr static int MaxCodeLength = 4;
    constexpr static int MaxNumColors = 6;
    constexpr static int MaxAttempts = 10;

    typedef std::array<int, MaxCodeLength> Combination;

    Combination secretCode{};
    int currentAttempt;
    bool gameOver;

    std::random_device rd;
    std::mt19937 mt;

public:
    Mastermind()
        : currentAttempt(0), gameOver(false) {
        generateSecretCode();
    }

    void play();

private:
    void generateSecretCode();

    static Combination getGuess();

    constexpr Combination checkGuess(const Combination &guess);

    template<typename T, size_t N>
    bool allElementsEqual(const std::array<T, N> &arr, T value);
};

#endif//MASTERMIND_MASTERMIND_HPP
