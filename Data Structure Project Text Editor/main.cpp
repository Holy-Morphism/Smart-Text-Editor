#include"TriTree.h"
int main()
{
	TriTree tree;
	string* arr = NULL;
	int size = tree.Suggestion("app", arr);
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << endl;
	}
}