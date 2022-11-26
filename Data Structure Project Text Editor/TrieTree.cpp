#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class StringList {
	struct Node {
		string data;
		Node* next;
		Node(string str)
		{
			data = str;
			next = NULL;
		}
	};
	Node* head, * current;
	int count;
public:
	StringList()
	{
		head = current = NULL;
		count = 0;
	}
	void Insert(string str)
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
	string*& StringArray()
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
	int size()
	{
		return count;
	}
};
class TriTree {
	struct Node {
		char data;
		bool colour;
		Node* childeren[26] = { NULL };
		//array of childeren
		Node()
		{
			data = '-';
			colour = false;
		}
	};
	ifstream read;
	Node* root;
public:
	TriTree()
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
		Suggestion(root, "app", wordlist);
		arr = wordlist.StringArray();
		for (int i = 0; i < wordlist.size(); i++)
		{
			cout << arr[i] << endl;
		}
	}
	void insert(Node*& node, string str, int length = 0)
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
	void Suggestion(Node*& node, string str, StringList& wordlist, int length = 0)
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
					Suggestion(node->childeren[i], str, wordlist, length + 1);
				}
			}
			else
			{
				return;
			}
		}
	}
	void findword(Node*& node, string str, StringList& wordlist)
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
	void Display(Node*& node)
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
};
int main()
{
	TriTree tree;
}