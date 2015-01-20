#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Item {
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
};

Item* concatenate(Item* head1, Item* head2);  // returns head pointer to new list
void removeEvens(Item*& head);
double findAverage(Item* head);
double findAverageHelper(Item* head, double count, double sum);
Item* concatenateHelper(Item* head1, Item* head2, Item*& head3);
void removeEvensHelper(Item*&head, Item* prev, Item *& initialHead);
void printList(std::ostream& ofile, Item* head);
void append(Item*& head1, int num);
void displayList(Item* head1);

void destroyList(Item*& head);


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cerr << "Please enter an input file and an output file.";
		return 1;
	}
    Item *head1 = NULL;
	Item *head2 = NULL;
	Item *head3 = NULL;
	double avg = 0;
	const int SIZE = 81;
	char input[SIZE];

	string line;

	ifstream inFile;
	ofstream outFile;

	inFile.open (argv[1], ios::in);


	for (int i = 0; getline(inFile,line) && i < 2; i++)
	{
		  if (i == 0)
		  {
		    	 int num;
		    	 istringstream iss(line, istringstream::in);
		    	 while (iss >> num)
		    	 {
		    	     append(head1, num);
		    	 }
		  }
		  else if (i == 1)
		  {
		    	  int num;
		    	  istringstream iss(line, istringstream::in);
		    	  while (iss >> num)
		    	  {
		    	      append(head2, num);
		    	  }
		  }
    }
	inFile.close();
	outFile.open(argv[2], ios::out);

	displayList(head1);
	cout << endl;

	displayList(head2);
	cout << endl;

     head3 = concatenate(head1, head2);
     printList(outFile, head3);
	displayList(head3);
	cout << endl;
	removeEvens(head3);
	printList(outFile, head3);
	displayList(head3);
	cout << endl;

	avg = findAverage(head3);
	cout << avg << endl;
	printList(outFile, head3);
	outFile << avg << endl;
	outFile.close();
	cout << "Reading output.txt" << endl;
	inFile.open (argv[2], ios::in);
	inFile.getline(input, SIZE);
	while (!inFile.eof())
	{
		cout << input << endl;
		inFile.getline(input, SIZE);
	}
//	destroyList(head1);
//	destroyList(head2);
//	destroyList(head3);
	cout << "Reading lists" << endl;
//	displayList(head1);
//	cout << endl;
//	displayList(head2);
//	cout << endl;
//	displayList(head3);
//	cout << endl;

	cout << "Done." << endl;
	return 0;
}

void append(Item *& head, int num)
{
	Item *newElement = new Item(num, NULL);
	Item *nodePtr;

	if (!head)
		head = newElement;
	else {
		nodePtr = head;
		while (nodePtr->next)
			nodePtr = nodePtr->next;
		nodePtr->next = newElement;
	}
}

void displayList(Item * nodePtr)
{
	while (nodePtr)
	{
		cout << nodePtr->val << " ";

		nodePtr = nodePtr->next;
	}
}

Item* concatenate(Item* head1, Item* head2) {
	Item* head3 = NULL;
	concatenateHelper(head1, head2, head3);
	return head3;

}

Item* concatenateHelper(Item* head1, Item* head2, Item*& head3) {
	if (head1) {
			append(head3, head1->val);
			concatenateHelper(head1->next, head2, head3);
		}
	else if (head2) {
			append(head3, head2->val);
			concatenateHelper(head1, head2->next, head3);
		}
	return head3;
}

void removeEvens(Item*& head) {
	Item *prev = NULL;
	Item *initialHead = NULL; // keep track of initial head position
	if (!head) {
		return;
	}
	if (head->val %2 == 0)
	{
		prev = head;
		delete head;
		head = prev->next;
	}
	initialHead = head;
	removeEvensHelper(head, prev, initialHead);
}

void removeEvensHelper(Item *&head, Item *prev, Item *&initialHead) {

	if (head && (head->val)%2 != 0) {
		prev = head;
		head = prev->next;
	}
	if (head && (head->val)%2 == 0) {
		prev->next = head->next;
		delete head;
		head = prev->next;
	}
	if (head)
	{
		removeEvensHelper(head, prev, initialHead);
	}
	else {
		head = initialHead;
		return;
	}
}

double findAverage(Item* head) {
	if (!head)
		return 0;
	else {
				return findAverageHelper(head, 0, 0);
	}

}

double findAverageHelper(Item* head, double count, double sum) {

	double avg = 0;
	if (head) {
		sum+=head->val;
		count++;
		avg = findAverageHelper(head->next, count, sum);
	}
	else
		return sum/count;
	return avg;
}

void printList(std::ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);
  }
}
/*
void destroyList(Item*& head)
{
	Item *ptr = head;
	Item *nextPtr;
	if (ptr)
	{
		nextPtr = head -> next;
		delete head;
		ptr = nextPtr;
	}
}
*/
