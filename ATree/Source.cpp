#include "Header.h"

#include <iostream>

using namespace std;
int main() {
	
	CBTree<int, Cless> a;
	a.insert(63);
	a.insert(33);
	a.insert(88);
	a.insert(15);
	a.insert(38);
	a.insert(67);
	a.insert(93);
	a.insert(8);
	a.insert(50);
	a.insert(65);
	a.insert(110);

	a.remove(8);
	a.remove(93);
	a.remove(63);
	//a.insert(70);

	CBTree<int, Cless>::Iterator_in_order it(a);

	//recorrido inorden
	cout << endl << " in_order " << endl;
		for ( it.begin(); it.end(); it++) {
		cout <<" "  <<*it;
		
	}
	
		//recorrido preorden
	cout << endl <<" pre_order " <<endl;
	CBTree<int, Cless>::Iterator_pre_order itpre(a);
		
		for (itpre.begin(); itpre.end(); itpre++) {
			cout << " " << *itpre;
		}

		//recorrido postorden
		cout << endl << " post_order " << endl;
		CBTree<int, Cless>::Iterator_post_order itpost(a);

		for (itpost.begin(); itpost.end(); itpost++) {
			cout << " " << *itpost;
		}
	
	return 0;
}