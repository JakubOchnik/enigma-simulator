# Simple Enigma machnine simulator
A C program which simulates the Enigma machine. It encrypts numerical messages.
## Synopsis
Written entirely in C language. I created it as a project for Algorithms and Data Structures classes. It took about a week to complete. The hardest part was definitely trying to understand the Enigma machine in-depths.
## How does it work?
In short, in Enigma, there are rotors and reflectors. Rotors rotate with every press of a key. Both reflectors and rotors consist of a user-specified alphabet permutation. In this case, the alphabet stands for numbers. When a key is pushed, a signal traverses from start through each rotor to reflector. There it gets reversed and goes back a different path. It returns to a different starting position, owned by another letter. And that's the finish, it's our encoded number.
## Rotor movement
In this case, only 3 first rotors move. The first one rotates every time a key is pressed. The second one rotates every time the first rotor reaches a turnover position (user-specified) and so on. More information about the rotor movement can be found here: [Enigma Turnover](https://en.wikipedia.org/wiki/Enigma_machine#Turnover)
The simulation also includes a rotor double-stepping mechanism, which is well-explained here: [Enigma double-stepping](http://www.intelligenia.org/downloads/rotors1.pdf)
