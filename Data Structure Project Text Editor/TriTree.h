#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class TriTree {
	struct Node {
		char data;
		bool colour;
		Node* childeren[26] = { NULL };
		//array of childeren
		Node();
	};
	ifstream read;
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
	};
	void insert(Node*&, string, int);
	void suggestion(Node*&, string, StringList&, int length);
	void findword(Node*&, string, StringList&);
public:
	TriTree();
	void Display(Node*&);
};