# Simple Enigma machnine simulator
A C program which simulates the Enigma machine. It encrypts numerical messages.
## Synopsis
Written entirely in C language. I created it as a project for Algorithms and Data Structures classes. It took me about a week to complete. The hardest part was definitely trying to understand the Enigma machine in-depths.
## How does it work?
In short, in Enigma, there are rotors and reflectors. Rotors rotate with every press of a key. Both reflectors and rotors consist of a user-specified alphabet permutation. In this case, the alphabet stands for numbers. <br/>
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/6c/Enigma-action.svg/600px-Enigma-action.svg.png" align="center" height="30%" width="30%">
<br/>*A simple visualization of Enigma* [*(source)*](https://upload.wikimedia.org/wikipedia/commons/thumb/6/6c/Enigma-action.svg/600px-Enigma-action.svg.png)<br/><br/>
When a key is pushed, a signal traverses from its starting position to reflector, passing each rotor. In reflector it gets reversed and then goes back a different path. It returns to a different starting position, owned by another letter, which is the encoded output.
## Rotor movement
In this case, only 3 first rotors move. The first one rotates every time a key is pressed. The second one rotates every time the first rotor reaches a turnover position (user-specified) and so on. More information about the rotor movement can be found here: [Enigma Turnover](https://en.wikipedia.org/wiki/Enigma_machine#Turnover)
The simulation also includes a rotor double-stepping mechanism, which is well-explained here: [Enigma double-stepping](http://www.intelligenia.org/downloads/rotors1.pdf)
## User input
The input data can be split into two parts. The first one is defining a rotor. A user has to enter:
```
n - number of letters
l - number of rotors
Wid - definition of i-th rotor (a sequence of numbers from range: 1-n, separated by whitespaces)
Wit - number of turnover positions of i-th rotor
Witl - turnover letters of i-th rotor (Wit numbers from range 1-n)
l - number of reflectors
R - definition of i-th reflector
```
The second part is defining a problem configuration.
```
p - number of messages to encrypt
k - number of rotors of i-th machine (number from range: 1-l)
K - k pairs: rotor number followed by its starting position
r - index of reflector to use in i-th machine (number from range: 0 - l-1)
M - a message to encrypt in i-th machine (a sequence of numbers to encrypt separated by whitespaces and ending with 0)
```
## Example input and output
### Input:
```
4
4
1 2 4 3
1 2  
3 2 1 4 
0
4 3 1 2
0
3 2 1 4
0
3
2 1 4 3
4 3 2 1
1 2 4 3
6
1 0 4 2
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
1 0 4 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
1 0 4 1
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0 
1 2 4 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
1 3 4 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
2 0 4 0 1 0
1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 1 1 1 1 2 2 2 2 3 3 3 3 4 4 4 4 0
```
### Output:
```
1 1 1 3 2 4 2 2 4 3 4 1 3 2 3 4
2 3 2 3 1 4 1 4 4 1 4 1 3 2 3 2
3 4 3 4 4 3 4 3 1 2 1 2 2 1 2 1
2 3 2 3 1 4 1 4 4 1 4 1 3 2 3 2
4 4 4 4 3 3 3 3 2 2 2 2 1 1 1 1
2 2 4 2 3 4 1 4 4 4 2 4 1 2 3 2 2 2 4 2 3 4 1 4 4 4 2 4 1 2 3 2
```