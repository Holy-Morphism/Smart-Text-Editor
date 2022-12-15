#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;
int height = 0;
class Huffman
{
public:
	int val;
	char letter;
	Huffman* left;
	Huffman* right;
	Huffman* next;
	Huffman()
	{
		this->val = 0;
		this->letter = 0;
		this->left = NULL;
		this->right = NULL;
		this->next = NULL;
	}
	~Huffman()
	{

	}
	Huffman(int val, char ch)
	{
		this->val = val;
		this->letter = ch;
		this->left = NULL;
		this->right = NULL;
		this->next = NULL;
	}
};
class PriorityQueues
{
	Huffman* top;
public:
	PriorityQueues()
	{
		top = NULL;
	}
	Huffman* Get_top()
	{
		return top;
	}
	void enqueue_Tree(Huffman* node, Huffman*& top)
	{
		node->next = top;
		top = node;
		sort(top);
	}
	void enqueue(char ch, int freq)
	{
		Huffman* Newnode = new Huffman(freq, ch);
		Newnode->next = NULL;
		if (top == NULL)
		{
			top = Newnode;
		}
		else
		{
			Huffman* current = top;
			while (current->next != NULL)
			{
				current = current->next;
			}
			current->next = Newnode;

		}
	}

	void pop_queue(Huffman*& top)
	{
		if (top->next != NULL || top != NULL)
		{
			Huffman* temp;
			temp = top;
			top = top->next;
			delete temp;
			temp = NULL;
		}
	}
	void sort(Huffman* obj) // sorts the priority queue linked list
	{
		if (obj->next == NULL)
			return;
		Huffman* current = obj;
		Huffman* current2 = obj;
		Huffman* temp = new Huffman;
		while (current != NULL)
		{

			while (current2 != NULL)
			{

				if (current->val < current2->val && current != current2)
				{
					temp->left = current->left;
					temp->right = current->right;
					temp->val = current->val;
					temp->letter = current->letter;

					current->left = current2->left;
					current->right = current2->right;
					current->val = current2->val;
					current->letter = current2->letter;

					current2->left = temp->left;
					current2->right = temp->right;
					current2->val = temp->val;
					current2->letter = temp->letter;

				}
				current2 = current2->next;
			}
			current = current->next;
			current2 = obj;
		}

	}

	Huffman*& maketree(Huffman*& top) // creates the huffman tree from priority queue
	{

		while (top->next != NULL)
		{
			Huffman* left = new Huffman;
			left->val = top->val;
			left->right = top->right;
			left->left = top->left;
			left->next = top->next;
			left->letter = top->letter;
			pop_queue(top);

			Huffman* right = new Huffman;
			right->val = top->val;
			right->right = top->right;
			right->left = top->left;
			right->next = top->next;
			right->letter = top->letter;
			pop_queue(top);

			Huffman* newNode = new Huffman(left->val + right->val, '~');
			newNode->left = left;
			newNode->right = right;
			newNode->next = NULL;

			enqueue_Tree(newNode, top);
		}

		return top;
	}

};

Huffman* FrequencyCounter(string s) // countes frequency of characters
{
	int freq_array[28];
	char char_array[28], ch = 'a';
	for (int i = 0; i < 28; i++)
	{
		if (i == 26)
		{
			char_array[i] = ' ';
			freq_array[i] = 0;
		}
		else if (i == 27)
		{
			char_array[i] = '#';
			freq_array[i] = 0;
		}
		else
		{
			char_array[i] = ch;
			freq_array[i] = 0;
		}
		++ch;
	}
	for (int i = 0; i < 28; i++)
	{
		for (unsigned int j = 0; j < s.length(); j++)
		{

			if (char_array[i] == s[j])
			{
				freq_array[i]++;
			}

		}
	}

	vector<pair<char, int>> vec;

	for (int i = 0; i < 28; i++)
	{
		if (freq_array[i] != 0)
		{
			vec.push_back(make_pair(char_array[i], freq_array[i]));
		}
	}

	vector<pair<char, int>>::iterator iter = vec.begin();
	PriorityQueues que;

	iter = vec.begin();
	for (iter; iter < vec.end(); iter++)
	{
		que.enqueue(iter->first, iter->second);
	}
	que.sort(que.Get_top()); // to sort the priority queue
	Huffman* var_top = que.Get_top();
	var_top = que.maketree(var_top); //to convert the priority queue to tree
	return var_top;
}

void helperfunc_encoder(Huffman*& root, string str, char* arr1, string* arr2) //encodes the binary values
{
	if (root->right == NULL && root->left == NULL)
	{

		if (root->letter != '~')
		{
			if (root->letter == 32)
			{
				arr1[26] = ' ';
				arr2[26] = str;
			}
			else if (root->letter == 35)
			{
				arr1[27] = '#';
				arr2[27] = str;
			}
			else
			{
				int index = root->letter - 'a';
				arr1[index] = root->letter;
				arr2[index] = str;
			}
			return;
		}
	}
	else
	{
		if (root->letter != '~')
		{
			if (root->letter == 32)
			{
				arr1[26] = ' ';
				arr2[26] = str;
			}
			else if (root->letter == 35)
			{
				arr1[27] = '#';
				arr2[27] = str;
			}
			else
			{
				int index = root->letter - 'a';
				arr1[index] = root->letter;
				arr2[index] = str;
			}
		}
		if (root->left != NULL)
		{
			helperfunc_encoder(root->left, str + '0', arr1, arr2);
		}

		if (root->right != NULL)
		{
			helperfunc_encoder(root->right, str + '1', arr1, arr2);
		}
	}
}

int getHeight(Huffman* root) //gets height
{
	if (root == NULL)
		return 0;

	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);

	return max(leftHeight, rightHeight) + 1;
}
void store_HuffmanTree_to_File(int* arr1, char* arr2, int nodes) //stores huffman to file
{
	ofstream write1("treeval.txt");
	ofstream write2("treechar.txt");
	ofstream write3("data.txt");
	write3 << nodes << endl;
	write3 << height << endl;
	write3.close();
	for (int i = 0; i < nodes; i++)
	{

		write1 << arr1[i] << " ";
		if (arr2[i] == ' ')
		{
			write2 << '*' << " ";
			continue;
		}
		write2 << arr2[i] << " ";
	}
	write1.close();
	write2.close();

}
void insert_array(Huffman* root, int* arr1, char* arr2, int index) // converts tree to array
{
	if (root == NULL)
	{
		return;
	}

	arr1[index] = root->val;
	arr2[index] = root->letter;

	if (root->left != NULL)
	{
		insert_array(root->left, arr1, arr2, 2 * index + 1);
	}
	if (root->right != NULL)
	{

		insert_array(root->right, arr1, arr2, 2 * index + 2);
	}
}
void tree_to_array(Huffman* root, int*& arr1, char*& arr2, int no_nodes)
{
	for (int i = 0; i < no_nodes; i++)
	{
		arr1[i] = -1;
		arr2[i] = '!';
	}

	insert_array(root, arr1, arr2, 0); // converts tree to array
	store_HuffmanTree_to_File(arr1, arr2, no_nodes); // stores the huffman tree to file
}
void maketree(Huffman*& root, int* arr1, char* arr2, int nodes, int index) //creates a huffman tree
{
	if (root == NULL || nodes == 0)
	{
		return;
	}

	int index2 = 2 * index + 1;

	if (index2 < nodes && arr1[index2] != -1 && arr1[index2] != '!')
	{
		root->left = new Huffman(arr1[index2], arr2[index2]);
		maketree(root->left, arr1, arr2, nodes, index2);
	}

	index2 = 2 * index + 2;

	if (index2 < nodes && arr1[index2] != -1 && arr1[index2] != '!')
	{
		root->right = new Huffman(arr1[index2], arr2[index2]);
		maketree(root->right, arr1, arr2, nodes, index2);
	}
}
Huffman* load_tree_from_file(int*& arr1, char*& arr2, int total_nodes) //loads tree from file
{
	ifstream read1("treeval.txt");
	ifstream read2("treechar.txt");
	int num; char ch;
	for (int i = 0; i < total_nodes; i++)
	{
		read1 >> num;
		arr1[i] = num;
		read2 >> ch;
		if (ch == '*')
		{
			ch = ' ';
		}
		arr2[i] = ch;;
	}
	read1.close(); read2.close();

	if (arr1[0] == -1 || arr2[0] == '!')
	{
		cout << "no array exists" << endl;
		return NULL;
	}

	Huffman* root = new Huffman(arr1[0], arr2[0]); // creates a root node from the array
	maketree(root, arr1, arr2, total_nodes, 0); // makes the huffman tree

	return root;
}
string encoder(string str)
{
	char ch_array[28] = { '\0' };
	string bin_array[28] = { "\0" };
	ch_array[26] = ' ';
	ch_array[27] = '#';
	string code;

	Huffman* var = FrequencyCounter(str); // makes huffman tree
	helperfunc_encoder(var, code, ch_array, bin_array); //encoder
	string coded_string = "";

	for (unsigned int i = 0; i < str.length(); i++)
	{
		for (int j = 0; j < 28; j++)
		{
			if (str[i] == ch_array[j])
			{
				coded_string += bin_array[j];
				break;
			}
		}
	}

	height = getHeight(var);
	int no_nodes = (int)(pow(2, height) - 1);

	int* store_tree_val = new int[no_nodes];
	char* store_tree_char = new char[no_nodes];
	tree_to_array(var, store_tree_val, store_tree_char, no_nodes);

	return coded_string;
}
string helperfunc_decoder(Huffman* root, string str, unsigned int& i) // traverses the tree to find characters
{
	string str2 = "";
	while (i <= str.size())
	{
		if (root->letter != '~')
		{
			str2 = str2 + root->letter;
			return str2;
		}
		else if (str[i] == '0')
		{
			if (root->left)
			{
				root = root->left;
				i++;

			}
			else
			{
				return str2;
			}
		}
		else if (str[i] == '1')
		{
			if (root->right)
			{
				root = root->right;
				i++;
			}
			else
			{
				return str2;
			}
		}
	}

	return "";
}
string decoder(string encrypted_string)
{
	int num;
	ifstream read3("data.txt"); // reads previously stored height and count of max nodes
	read3 >> num;
	int no_nodes = num;
	read3 >> num;
	height = num;
	read3.close();
	int* get_tree_val = new int[no_nodes];
	char* get_tree_char = new char[no_nodes];
	for (int i = 0; i < no_nodes; i++)
	{
		get_tree_val[i] = -1;
		get_tree_char[i] = '!';
	}
	Huffman* ptr = load_tree_from_file(get_tree_val, get_tree_char, no_nodes); // reads tree from file makes it and returns the head ptr
	string decoded_string = "";

	for (unsigned int i = 0; i < encrypted_string.size();)
	{
		decoded_string += helperfunc_decoder(ptr, encrypted_string, i); //decodes the string
	}

	return decoded_string;
}