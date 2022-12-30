# Smart-Text-Editor
A console based text editor that will suggest words from a Dictionary
Uses Huffman Encoding to store text.
Suggested words are shown form a trie tree that is generated at runtime by reading the Dictionary.
1. INFORMATION CONSISTENCY :
A text editor is a type of program used for editing plain text files. 
A plain text file is represented and edited by showing all the characters as they are present in the file. 
The most commonly used character set is ASCII, especially recently, as plain text files are more often being used for programming and configuration, and less frequently for documentation (e.g. detailed instructions, user guides) than in the past.
Smart Text Editor is a tool that allows its user to perform text editing, smart word completion, saving and opening a text file.
2. PROJECT PURPOSE :
To develop a smart text editor in C++ that is based on C++ platform and can be easily used by all the users. If there are any changes required then a programmer can easily code and see the changes and it most adaptable.
3. PROJECT FEATURES :
Features of this project are described in the form of a story or primary user flow:
User creates text file and starts writing(typing) something to it. 
Just as in a typical text editor, user types the words separated by spaces to form sentences which are separated by full stops etc. At any point of time as user is typing a word, user is suggested words completion in following:
User typed word so far: ba Suggested Completions: bat, bar, ball
User typed word so far: bal Suggested Completions: ball, balm, bald
Basically, after writing each letter of the words, user is given suggestions(10 words at most) on side of the screen, user moves to next word with pressing ‘/’ button and choses a word using ‘;’ button.
For the purpose of avoiding any spelling mistakes, user must choose from given list of words.
(Dictionary is fixed from a list provided in a text file).
Once written, user can not move the cursor backwards to edit his writing, can only append text in forward direction.
Once user presses the ‘=’ button, all the written text so far is converted into a compressed form and save the encoding into a text file.
Later, if user wishes to open the file, encoded/compressed text is loaded and decompressed to retrieve the original text, original text is shown to the user, and user may keep on typing further and then save the file again in the same fashion as above.
