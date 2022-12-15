#include"TriTree.h"

TriTree::Node::Node(char data = '-', bool colour = false)
{
	this->data = data;
	this->colour = colour;
}

TriTree::StringList::Node::Node(string str)
{
	data = str;
	next = NULL;
}

TriTree::StringList::StringList()
{
	head = current = NULL;
	count = 0;
}

void TriTree::StringList::Insert(string str)
{
	if (head)
	{
		current = head;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new Node(str);
	}
	else
	{
		head = new Node(str);
	}
	count++;
}

string*& TriTree::StringList::StringArray()
{
	string* temp = new string[count];
	current = head;
	int i = 0;
	while (current && i < count)
	{
		temp[i] = current->data;
		i++;
		current = current->next;
	}
	return temp;
}

int TriTree::StringList::Size()
{
	return count;
}

TriTree::StringList::~StringList()
{
	while (head)
	{
		current = head;
		head = head->next;
		delete current;
	}
	head = NULL;
}

void TriTree::insert(Node*& node, string str)
{
	/*
	* Every character has a designated index
	* If a character of the inserted word is not there , a new node is created
	* otherwise we move on to the next character of the word 
	* to move on every character of the word length is incremented 
	*/
	int length = 0;
	int index = str[length] - 'a';//Gives the designated index
	Node* current = node;
	while (length < str.length())//until the whole word is inserted
	{
		if (!current->childeren[index])//if the designated node of the character does not exist the character is inserted
		{
			current->childeren[index] = new Node(str[length]);
		}
		if (length == str.length() - 1)
		{
			/*
			* At the last character the colour assigned true
			* so to know where the word ends
			*/
			current->childeren[index]->colour = true;
		}
		current = current->childeren[index];//moves on the next node of the designatd index
		length++;
		index = str[length] - 'a';
	}
}

void TriTree::suggestion(Node*& node, string str, StringList& wordlist, int length = 0)
{
	/*
	* searches till the branches of the inserted word
	* the calls the findword function
	*/
	int index = int(str[length] - 'a');//Gives the designated index
	if (node->childeren[index])
	{
		if (length == str.length() - 1)//when the last character is reached, the continuing characters are now searched
		{
			findword(node->childeren[index], str, wordlist);//for searching continuing characters
			return;
		}
		suggestion(node->childeren[index], str, wordlist, length + 1);
	}
}

void TriTree::findword(Node*& node, string str, StringList& wordlist)
{
	for (int i = 0; i < 26; i++)//Looks at every index for every continuing word
	{
		if (node->childeren[i])//checks if node exists
		{
			string word = str;//the current string we want to continue
			if (node->childeren[i]->colour)
			{
				word += node->childeren[i]->data;//adds any found chaacter
				findword(node->childeren[i], word, wordlist);//checks recursively
				wordlist.Insert(word);//Inserts word into linked list
			}
			else
			{
				word += node->childeren[i]->data; // adds any found chaacter
				findword(node->childeren[i], word, wordlist);
			}
		}
	}
}

void TriTree::deletetree(Node*& node)
{
	for (int i = 0; i < 26; i++)
	{
		if (node->childeren[i])
		{
			deletetree(node->childeren[i]);
		}
	}
	delete node;
	node = NULL;
}

void TriTree::savetofile()//attempt at saving the tree 
{
	Node* nullnode = new Node;
	string line;
	write.open("tritree.txt");
	queue<Node*> nodequeue;
	nodequeue.push(root);
	while (!nodequeue.empty())
	{
		for (int i = 0; i < 26; i++)
		{
			if (nodequeue.front()->childeren[i])
			{
				nodequeue.push(nullnode);
			}
			else
			{
				nodequeue.push(nodequeue.front()->childeren[i]);
			}
		}
		write << nodequeue.front()->data << nodequeue.front()->colour << endl;
	}
	write.close();
}

void TriTree::readfromfile()
{
	string line = "";
	read.open("tritree.txt");
	getline(read, line);
	Node* current = root = new Node(line[0], int(line[1] - '0'));
	while (read.eof())
	{

		for (int i = 0; i < 26; i++)
		{
			current->childeren[i]->data = line[0];
			current->childeren[i]->colour = int(line[1]-'0');
		}
	}
	read.close();
}

void TriTree::insertfromfile(Node*& node, char data, bool colour)
{
	if (data != '-')
	{
		int index = data - 'a';
		if (node->childeren[index])
		{

		}
	}
}

//Public:
TriTree::TriTree()
{
	root = new Node;
	string line;
	read.open("dictionary.txt");
	while (getline(read, line)) {
		insert(root, line);
	}
	read.close();
}

void TriTree::Display(Node*& node)
{
	for (int i = 0; i < 26; i++)
	{
		if (node->childeren[i])
		{
			cout << node->childeren[i]->data << " ";
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (node->childeren[i])
		{
			Display(node->childeren[i]);
		}
	}
}

int TriTree::Suggestion(string str, string*& str_arr)
{
	/*
	* Takes any string as an argumant
	* Takes an empty string pointer as an argument
	* assignes suggested words
	* returns the size of string array
	*/
	StringList wordlist;
	suggestion(root, str, wordlist);
	str_arr = wordlist.StringArray();
	return wordlist.Size();
}

TriTree::~TriTree()
{
	deletetree(root);
}