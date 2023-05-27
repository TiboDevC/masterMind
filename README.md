# Mastermind Game

Mastermind is a classic code-breaking game where the player attempts to guess the secret code within a limited number of
attempts. This repository contains a C++ implementation of the Mastermind game running in the console.

## Rules of the Game

1. The game generates a random secret code consisting of a sequence of colored pegs.
2. The player's goal is to guess the secret code within a limited number of turns.
3. After each guess, the game provides feedback in the form of numbers:
    - A `2` peg indicates a correct color and position.
    - A `1` peg indicates a correct color but in the wrong position.
4. Using the feedback, the player must deduce the correct code and make subsequent guesses.
5. The game ends when the player either guesses the correct code or runs out of turns.

## How to Run

1. Clone the repository to your local machine.
2. Run `make` in the root directory
3. Run the compiled executable `./objs/mastermind`
4. Follow the on-screen instructions to play the game.

Enjoy playing Mastermind!
