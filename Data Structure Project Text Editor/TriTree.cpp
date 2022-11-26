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
	string* arr = NULL;
	StringList wordlist;
	suggestion(root, "app", wordlist);
	arr = wordlist.StringArray();
	for (int i = 0; i < wordlist.Size(); i++)
	{
		cout << arr[i] << endl;
	}
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