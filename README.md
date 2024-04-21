# Smart-Text-Editor

A console-based text editor that suggests words from a Dictionary and uses Huffman Encoding to store text. Suggested words are shown from a trie tree that is generated at runtime by reading the Dictionary.

## Information Consistency

A text editor is a type of program used for editing plain text files. A plain text file is represented and edited by showing all the characters as they are present in the file. The most commonly used character set is ASCII. Plain text files are more often being used for programming and configuration. Smart Text Editor is a tool that allows its user to perform text editing, smart word completion, saving, and opening a text file.

## Project Purpose

The purpose of this project is to develop a smart text editor in C++ that is based on the C++ platform and can be easily used by all users. If there are any changes required then a programmer can easily code and see the changes and it most adaptable.

## Project Features

Features of this project are described in the form of a user flow:

1. User creates a text file and starts writing (typing) something to it. 
2. As the user types each letter of the words, they are given suggestions (10 words at most) on the side of the screen.
3. User moves to the next word with pressing the ‘/’ button and chooses a word using the ‘;’ button.
4. To avoid spelling mistakes, the user must choose from the given list of words (Dictionary is fixed from a list provided in a text file).
5. Once written, the user cannot move the cursor backwards to edit their writing, they can only append text in the forward direction.
6. Once the user presses the ‘=’ button, all the written text so far is converted into a compressed form and saves the encoding into a text file.
7. Later, if the user wishes to open the file, the encoded/compressed text is loaded and decompressed to retrieve the original text. The original text is shown to the user, and the user may keep on typing further and then save the file again in the same fashion as above.
