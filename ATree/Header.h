#pragma once
#include <stack>

using namespace std;
 
//para RECORRIDO REVERSA
const int ir_izq = 2;
const int ir_der = 1;
const int h_izq = 1;
const int h_der = 0;
/*
//PARA RECORRIDO INORDEN
const int ir_izq = 1;
const int ir_der = 2;
const int h_izq = 0;
const int h_der = 1;
*/
template<class T>
struct CBNode
{
	T m_data;
	CBNode *m_son[2];
	CBNode(T dato);

};

template<class T>
CBNode <T> ::CBNode(T dato) {
	m_data = dato;
	m_son[0] = 0;
	m_son[1] = 0;
}

template<class T, class C>
class CBTree
{
public:

	class Iterator_post_order
	{
	public:

		stack<CBNode<T>*> ppadres;
		stack<int> pila;
		CBNode<T> **q;
		Iterator_post_order(CBTree<T, C> &arbol);
		int cnodos;
		int tnodos;

		T operator *();
		int operator ++(int d);
		int begin();
		bool end();

		Iterator_post_order();
		~Iterator_post_order();

	private:

	};


	class Iterator_pre_order
	{
	public:
		stack<CBNode<T>*> ppadres;
		stack<int> pila;
		CBNode<T> **q;
		Iterator_pre_order(CBTree<T, C> &arbol);
		int cnodos;
		int tnodos;

		T operator *();
		int operator ++(int d);
		int begin();
		bool end();

		Iterator_pre_order();
		~Iterator_pre_order();

	private:

	};

	class Iterator_reverse
	{
	public:
		stack<CBNode<T>*> ppadres;
		stack<int> pila;
		CBNode<T> **q;
		Iterator_reverse(CBTree<T, C> &arbol);
		int cnodos;
		int tnodos;

		T operator *();
		int operator ++(int d);
		int begin();
		bool end();

		Iterator_reverse();
		~Iterator_reverse();

	private:

	};



	class Iterator_in_order
	{
	public:
		stack<CBNode<T>*> ppadres;
		stack<int> pila;
		CBNode<T> **q;
		Iterator_in_order(CBTree<T, C> &arbol);
		int cnodos;
		int tnodos;

		T operator *();
		int operator ++(int d);
		int begin();
		bool end();

		Iterator_in_order();
		~Iterator_in_order();

	private:

	};

	int nnodos;


	CBNode<T> *m_root;
	C m_c; // function object
	bool find(T x, CBNode <T> **&p);
	bool insert(T x);
	bool remove(T x);
	CBNode<T>**Rep(CBNode<T> **p);



	CBTree();
	~CBTree();


};


struct Cless
{
	bool operator()(int a, int b) {
		return a < b;
	}
};

struct Cgreat
{
	bool operator()(int a, int b) {
		return a > b;
	}
};


template<class T, class C>
CBTree<T, C>::CBTree() {
	m_root = 0;
	nnodos = 0;

};


template<class T, class C>
CBTree<T, C>::~CBTree() {

};

template<class T, class C>
bool CBTree<T, C>::find(T x, CBNode<T> **&p) {

	for (p = &m_root; *p && (*p)->m_data != x; p = &((*p)->m_son[m_c((*p)->m_data, x)]))
	{

	}

	return *p != 0;
};

template<class T, class C>
bool CBTree <T, C>::insert(T x) {
	CBNode <T> **p;
	if (find(x, p)) return 0;

	*p = new CBNode<T>(x);
	nnodos++;
	return 1;
};

template<class T, class C>
bool CBTree<T, C>::remove(T x) {
	CBNode <T> **p;
	if (!find(x, p)) return 0;
	if ((*p)->m_son[0] && (*p)->m_son[1]) {
		CBNode<T> **q = Rep(p);
		(*p)->m_data = (*q)->m_data;
		p = q;

	}
	CBNode <T>  *t = *p;
	*p = (*p)->m_son[!(*p)->m_son[0]];
	nnodos--;
	delete t;

	return 1;
};

template<class T, class C>
CBNode<T>** CBTree<T, C>::Rep(CBNode<T> **p) {
	p = &((*p)->m_son[0]);
	while ((*p)->m_son[1] != 0)
		p = &((*p)->m_son[1]);

	return p;
};

// ------------------------in order------------------------------------------------------
#pragma region inorden
template<class T, class C>
inline CBTree<T, C>::Iterator_in_order::Iterator_in_order(CBTree<T, C> &arbol)
{
	tnodos = arbol.nnodos;
	q = &(arbol.m_root);
	begin();

}

template<class T, class C>
inline T CBTree<T, C>::Iterator_in_order::operator*()
{

	return (*q)->m_data;
}

template<class T, class C>
inline int CBTree<T, C>::Iterator_in_order::operator++(int d)
{
	cnodos++;
	if (((*q)->m_son[1] != 0)) {
		ppadres.push(*q);
		pila.push(2);
		q = &((*q)->m_son[1]);
		while ((*q)->m_son[0] != 0)
		{
			ppadres.push(*q);
			pila.push(1);
			q = &((*q)->m_son[0]);
		}

	}
	else {

		while (!(pila.empty()) && (pila.top() == 2)) {

			q = &(ppadres.top());
			ppadres.pop();
			pila.pop();
		}
		if (pila.empty())
			return -1;

		q = &(ppadres.top());
		ppadres.pop();
		pila.pop();


	}


	return int();
}

template<class T, class C>
inline int CBTree<T, C>::Iterator_in_order::begin()
{
	cnodos = 0;
	while ((*q)->m_son[0] != 0) {
		ppadres.push(*q);
		pila.push(1);
		q = &((*q)->m_son[0]);
	}
	return 0;
}

template<class T, class C>
inline bool CBTree<T, C>::Iterator_in_order::end()
{
	if (cnodos < tnodos)
		return true;
	return false;
}

template<class T, class C>
CBTree<T, C>::Iterator_in_order::Iterator_in_order() {
	q = 0;

};


template<class T, class C>
CBTree<T, C>::Iterator_in_order::~Iterator_in_order() {

};
#pragma endregion

// ----------------------------------------preorden-------------------------------------------------------
#pragma region preorden
template<class T, class C>
inline CBTree<T, C>::Iterator_pre_order::Iterator_pre_order(CBTree<T, C>& arbol)
{
	tnodos = arbol.nnodos;
	q = &(arbol.m_root);
	pila.push(0);
	begin();
}

template<class T, class C>
inline T CBTree<T, C>::Iterator_pre_order::operator*()
{
	return (*q)->m_data;
}

template<class T, class C>
inline int CBTree<T, C>::Iterator_pre_order::operator++(int d)
{
	cnodos++;
	//pila.push(0);


	if ((*q)->m_son[0] != 0 || (*q)->m_son[1] != 0) {
		ppadres.push(*q);

		if ((*q)->m_son[0] != 0)
		{
			q = &((*q)->m_son[0]);
			pila.push(1);
		}
		else {
			q = &((*q)->m_son[1]);
			pila.push(2);
		}
	}
	else {

		while (!ppadres.empty() && ((*q)->m_son[1] == 0 || (*q)->m_son[0] == 0))
		{
			q = &(ppadres.top());
			ppadres.pop();
		}

		if ((*q)->m_son[1] != 0) {
			q = &((*q)->m_son[1]);
			pila.pop();
			pila.push(2);
		}

	}

	return int();
}

template<class T, class C>
inline int CBTree<T, C>::Iterator_pre_order::begin()
{
	cnodos = 0;
	return 0;
}

template<class T, class C>
inline bool CBTree<T, C>::Iterator_pre_order::end()
{

	if (cnodos < tnodos)
		return true;
	return false;
}

template<class T, class C>
inline CBTree<T, C>::Iterator_pre_order::Iterator_pre_order()
{
	q = 0;
}

template<class T, class C>
inline CBTree<T, C>::Iterator_pre_order::~Iterator_pre_order()
{
}
#pragma	endregion

//----------------post_order-----------------------------
#pragma region postorden
template<class T, class C>
inline CBTree<T, C>::Iterator_post_order::Iterator_post_order(CBTree<T, C>& arbol)
{
	tnodos = arbol.nnodos;
	q = &(arbol.m_root);
	begin();

}

template<class T, class C>
inline T CBTree<T, C>::Iterator_post_order::operator*()
{
	return (*q)->m_data;
}

template<class T, class C>
inline int CBTree<T, C>::Iterator_post_order::operator++(int d)
{
	cnodos++;
	//Necesito un padre para avanzar
	if (ppadres.size() == 0)
	{
		//soy huerfano, no hay a donde ir, no tengo futuro.
		return 0;
	}
	//dos casos diferentes, soy hijo izquierdo o derecho?
	if (pila.top() == 1)
	{
		//soy hijo izquierdo
		//ahora sere el padre
		q = &(ppadres.top());
		ppadres.pop();
		pila.pop();
		//hay hijo derecho?
		if ((*q)->m_son[1] == 0)
		{
			//no
			return 1;
		}
		else
		{
			//si
			ppadres.push(*q);
			pila.push(2);
			q = &((*q)->m_son[1]);
			//buscar el ultimo hijo izquierdo
			while ((*q)->m_son[0] != 0)
			{
				ppadres.push(*q);
				pila.push(1);
				q = &((*q)->m_son[0]);
			}
		}
	}
	else if(pila.top()==2)
	{
		//soy hijo derecho
		//ahora sere el padre
		q = &(ppadres.top());
		ppadres.pop();
		pila.pop();
		//por la naturaleza de la vida... que diga el iterador. no hay mas que hacer.
		return 2;
	}
	else
	{
		//si no soy hijo derecho ni hijo izquierdo, que soy?
		return 0;
	}
	
	return int();
}

template<class T, class C>
inline int CBTree<T, C>::Iterator_post_order::begin()
{
	cnodos = 0;
	while ((*q)->m_son[0] != 0) {
		ppadres.push(*q);
		pila.push(1);
		q = &((*q)->m_son[0]);
		cnodos++;
	}
	return 0;
}

template<class T, class C>
inline bool CBTree<T, C>::Iterator_post_order::end()
{
	if (cnodos < tnodos)
		return true;
	return false;
}

template<class T, class C>
inline CBTree<T, C>::Iterator_post_order::Iterator_post_order()
{
	q = 0;
}

template<class T, class C>
inline CBTree<T, C>::Iterator_post_order::~Iterator_post_order()
{
}
#pragma endregion

//-----------------------------------------reverse-----------------------------------------


template<class T, class C>
inline CBTree<T, C>::Iterator_reverse::Iterator_reverse(CBTree<T, C>& arbol)
{
	tnodos = arbol.nnodos;
	q = &(arbol.m_root);
	begin();
}

template<class T, class C>
inline T CBTree<T, C>::Iterator_reverse::operator*()
{
	return (*q)->m_data;
}

template<class T, class C>
inline int CBTree<T, C>::Iterator_reverse::operator++(int d)
{
	cnodos++;
	if (((*q)->m_son[h_der] != 0)) {
		ppadres.push(*q);
		pila.push(ir_der);
		q = &((*q)->m_son[h_der]);
		while ((*q)->m_son[h_izq] != 0)
		{
			ppadres.push(*q);
			pila.push(ir_izq);
			q = &((*q)->m_son[h_izq]);
		}

	}
	else {

		while (!(pila.empty()) && (pila.top() == ir_der)) {

			q = &(ppadres.top());
			ppadres.pop();
			pila.pop();
		}
		if (pila.empty())
			return -1;

		q = &(ppadres.top());
		ppadres.pop();
		pila.pop();


	}


	return int();
}

template<class T, class C>
inline int CBTree<T, C>::Iterator_reverse::begin()
{
	cnodos = 0;
	while ((*q)->m_son[h_izq] != 0) {
		ppadres.push(*q);
		pila.push(ir_izq);
		q = &((*q)->m_son[h_izq]);
	}
	return 0;
}

template<class T, class C>
inline bool CBTree<T, C>::Iterator_reverse::end()
{
	if (cnodos < tnodos)
		return true;
	return false;
}

template<class T, class C>
inline CBTree<T, C>::Iterator_reverse::Iterator_reverse()
{
	q = 0;

}

template<class T, class C>
inline CBTree<T, C>::Iterator_reverse::~Iterator_reverse()
{
}
