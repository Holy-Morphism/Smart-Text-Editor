#include"TriTree.h"

TriTree::Node::Node()
{
	data = '-';
	colour = false;
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

void TriTree::insert(Node*& node, string str, int length = 0)
{
	if (length < str.length())
	{
		for (int i = 0; i < 26; i++)
		{
			if (node->childeren[i])
			{
				if (node->childeren[i]->data == str[length])
				{
					if (length == str.length() - 1)
					{
						node->childeren[i]->colour = true;
					}
					insert(node->childeren[i], str, length + 1);
					return;
				}
			}
			else
			{
				node->childeren[i] = new Node;
				node->childeren[i]->data = str[length];
				if (length == str.length() - 1)
				{
					node->childeren[i]->colour = true;
				}
				insert(node->childeren[i], str, length + 1);
				return;
			}
		}
	}
}

void TriTree::suggestion(Node*& node, string str, StringList& wordlist, int length = 0)
{
	for (int i = 0; i < 26; i++)
	{
		if (node->childeren[i])
		{
			if (node->childeren[i]->data == str[length])
			{
				if (length == str.length() - 1)
				{
					findword(node->childeren[i], str, wordlist);
					return;
				}
				suggestion(node->childeren[i], str, wordlist, length + 1);
			}
		}
		else
		{
			return;
		}
	}
}

void TriTree::findword(Node*& node, string str, StringList& wordlist)
{
	for (int i = 0; i < 26; i++)
	{
		if (node->childeren[i])
		{
			string word = "";
			word += str;
			if (node->childeren[i]->colour)
			{
				word += node->childeren[i]->data;
				wordlist.Insert(word);
				return;
			}
			else
			{
				word += node->childeren[i]->data;
				findword(node->childeren[i], word, wordlist);
			}
		}
		else
		{
			return;
		}
	}
}

void TriTree::deletetree(Node * &node)
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

//Public:
TriTree::TriTree()
{
	root = new Node;
	string line;
	read.open("Dictionary.txt");
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

int TriTree::Suggestion(string str,string*& str_arr)
{
	/*
	* Takes any string as an argumant
	* Takes an empty string pointer aas an argument
	* assignes suggested words
	* return the size of array
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