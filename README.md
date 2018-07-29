# Encryption/Decryption tools and Memory challenge game in C++

# About the project:
This project is the first out of three assignments for my FIT1048 (Foundations of C++) unit. The program has a command-line interface and written using Microsoft Visual Studio 2013 IDE. The program contains two main functionalities: 
1. Encryption/decryption of plaintext(s)/ciphertext(s) as an input argument or within a text file with simple cipher algorithm
2. Memory challenge game

Below contains the descriptions of the two main functionalities which are directly taken from the assignment brief.

# 1. Encryption/Decryption tools with simple cipher algorithm:
#### In this task you are to write a basic code breaking application. The objective of the program is to accept a word and either encrypt or decrypt, based on a key. The key itself is generated from a codeword that the user types in at the start of the program. The program will run as follows:

- The user indicates if they wish to encrypt or decrypt a message

- The user types in the message (no spaces) they wish to encrypt/decrypt

- The user types in the codeword

- The program will turn the codeword into an integer-based key. How this is done is described
below.

- The program will then encrypt/decrypt the message based on the key and display it for the
user. Rules for encryption/decryption are described below.

- You are only required to perform basic input validation. You can expect that the user will
type in a valid message.

#### Key Generation:

- The user must type in a codeword that is 4 characters long. It should just be letters (you do
not need to put in validation as standard… you can assume the user will just put in letters).

- Each character is converted to its corresponding number, i.e a = 1, b = 2, etc. Add all the
numbers up.

- With this resulting number, you must arrive at a single digit number. To do this, you add up
the single digits in the number, and repeat the process until you have a single digit. For
example, if the codeword is “matt”, then this is…

  - 13 + 1 + 20 + 20 = 54

  - 5 + 4 = 9

#### Encryption/Decryption:

- To encrypt a message, you shift each letter in the word you are encrypting forward by the
amount corresponding to the keyword. For example, if I wanted to encrypt the message
“awesome” using the codeword “matt”, then it would become “jfnbxvn”. Also notice that
the alphabet wraps around itself, meaning that when an ‘r’ is encrypted with the key 9, it
turns into an ‘a’.

- To decrypt a message, you shift each letter in the word you are encrypting backward by the
amount corresponding to the keyword.

#### Extra Functionality:
- Allowing messages with spaces and special characters

- Full data validation

- Extra coding measures for extra security

- Saving and reading messages from file

#### Note:
- Message can only contains lower case alphabet letter, spaces, and special characters. In addition, the first character of the message must be a lower case alphabet letter
  - Upper case alphabet letter and numerical digit are considered invalid values
- Number of messages to be stored in the “messages.txt” file must be in the range of 1 to 10

# 2. Memory challenge game

#### In this task you are to write a 2-player game called Memory Challenge. The objective of this game is to identify more sets of pairs hidden in the game board than your opponent. The game plays as follows:
- A 6x6 game board is randomly initialised with 18 pairs of characters (these can be numbers,
letters, or anything else, as long as you have 18 sets of unique pairs in the board). For
example, in the board you may have 2 a’s, 2 b’s, and so on. These are hidden from the
players.
- The players enter their names
- The program randomly decides who will start
- The player then chooses two cells on the board. Each cell will show its contents. If they
identify two characters the same, they remain displayed in their cells and that player scores
one point. If they do not identify a pair, then both cells contents hide again and the player
scores nothing. It is then the next players turn.
- This repeats until all cells have been cleared. The player with the highest number of points
wins.

Please note, you must include a “Test Mode” where the contents of cells is always shown. This is so
you (and the marker) can test your program easily. This mode should be able to be turned on and off
by the player (either once at the start of the game, or at any time throughout the game). When
turned on the game board will be shown at the start of each turn.

#### Extra Functionality:
- Playing against a computer opponent
- The ability to save the state of a game
- Keeping a running leaderboard for the game that is persistent

#### Note:
- All the required input are validated
- Characters inside the board can only be unique pairs of a to r
  - i.e. a a, b b, …, r r
- Player name can only be a combination of upper/lower case alphabet letter. In addition, it must be a single word
- When playing in single player mode, computer is represented as player2
- After the user has finished the game (winner of the game /draw game has been shown), previous saved game state is not available anymore. The user needs to start a new game
- Leaderboard feature in this application is persistent in the sense that when the application has been closed, the previous game score still exists in the “leaderboard.txt” file and can be added with new ones and will be sorted in descending order. In addition, all score except the computer’s score is added to the “leaderboard.txt” file
