#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<queue>
using namespace std;

class TriTree {
	struct Node {
		char data;
		bool colour;
		Node* childeren[26] = { NULL };//array of childeren
		Node(char,bool);
	};
	ifstream read;
	ofstream write;
	Node* root;
	class StringList {
		struct Node {
			string data;
			Node* next;
			Node(string);
		};
		Node* head, * current;
		int count;
	public:
		StringList();
		void Insert(string);
		string*& StringArray();
		int Size();
		~StringList();
	};
	
	void insert(Node*&, string);
	void suggestion(Node*&, string, StringList&, int length);
	void findword(Node*&, string, StringList&);
	void deletetree(Node*&);
	void savetofile();
	void readfromfile();
	void insertfromfile(Node*&,char, bool);
public:
	TriTree();
	void Display(Node*&);
	int Suggestion(string,string*&);
	~TriTree();
};