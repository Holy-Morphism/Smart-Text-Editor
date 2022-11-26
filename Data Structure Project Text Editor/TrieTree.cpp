#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class TriTree {
	struct Node {
		char data;
		bool colour;
		Node* childeren[26]={NULL};
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
			insert(root,line);
		}
		read.close();
		Display(root);
	}
	void insert(Node*& node, string str, int length = 0)
	{
		if (length < str.length())
		{
			for (int i = 0; i < 26 ; i++)
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
	void Display(Node*& node)
	{
		for (int i = 0; i < 26; i++)
		{
			if (node->childeren[i])
			{
				cout << node->childeren[i]->data<<" ";
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