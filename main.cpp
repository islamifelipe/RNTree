/*
#=======================================================================
# Islame Felipe DA COSTA FERNANDES --- Copyright 2017
#-----------------------------------------------------------------------
#
# This code implements basic operations of Red-black tree.
#
#=======================================================================
*/


#include <iostream>
#include <stdio.h> 
#include <map> 
#include <list>
#include <string>
#include <vector>
#include <cmath>
#include <stack>   
#include <utility>      // std::pair
using namespace std;



enum Color {red, black};

typedef struct node{
	string key; // conteudo do nó
	node *pai; // ponteiro para o pai
	node *left; // ponteiro para o filho esquerdo
	node *right; // ponteiro para o filho direito
	Color color; // cor do nó

} RBElement;

typedef struct t{
	RBElement *root; // raiz da árvore
}RBTree; // define o "tipo" árvore

RBElement * sentinela = NULL; 

RBElement * alocaElemento(string key, RBElement* pai, RBElement* left, RBElement* right, Color color){
	RBElement *ret = (RBElement*)malloc(sizeof(RBElement));;
	ret->key =  key;
	ret->pai =  pai;
	ret->left =  left;
	ret->right =  right;
	ret->color =  color;
	return ret;
}

void printElement(RBElement *no, int nivel){
	if (no!=NULL){
		string color = "vermelhor";
		if (no->color==black) color="preto";
		string pai = "NIL", left="NIL", right="NIL";
		if (no->pai!=NULL && no->pai!=sentinela) pai = no->pai->key;
		if (no->left!=NULL && no->left!=sentinela) left = no->left->key;
		if (no->right!=NULL && no->right!=sentinela) right = no->right->key;
		cout<<"("<< pai <<", "<<no->key<<", "<<color<<", "<<nivel<<", "<<left<<", "<<right<<")"<<endl;
	}
}



void RBInsert(RBTree *T, RBElement *z); // insere um elemento z em T
void RB_Insert_Fixup(RBTree *T, RBElement *x); // mantém as propriedades da árvore T, que possivelmente foram violadas pelo nó x
void Right_Rotate(RBTree *T, RBElement *y); // Rotaciona à direita uma subárvore de raiz z
void Left_Rotate(RBTree *T, RBElement *z); // Rotaciona à esquerda uma subárvore de raiz z
void RB_Delete(RBTree *T, RBElement *z); // deleta um elemento z de T, mantendo as pripriedades de T
void RB_Transplant(RBTree *T, RBElement *z, RBElement *y); // ??
RBElement *Tree_Minimum(RBTree *T, RBElement *z); // retorna o menor elemento de uma subarvore de raiz z
void RB_Delete_Fixup(RBTree *T, RBElement *x); //// mantém as propriedades da árvore T, que possivelmente foram violadas pelo nó x
RBElement * Search(RBTree *T, string c); // busca por uma chave c
void RBPrint(RBTree *T); // percurso in ordem
void RBCheck(RBTree *T); // "desenha" a árvore
bool isRNTree(RBTree *T); // retorna true se T é uma RN tree

int main(int argc, const char * argv[]){
	if (argc != 2) {
        cout << "Parameter error. Usage: " << argv[0] << " (input file) " << endl;
        exit (1);
    }
    sentinela = alocaElemento("", NULL,NULL,NULL, black); // elemento global para a sentinela da árvore (nó externo)
    RBElement * root = alocaElemento("Aaaaa", sentinela,sentinela,sentinela, black); // elemento global para a sentinela da árvore (nó externo)
  	RBTree *T = (RBTree*)malloc(sizeof(RBTree));;
  	T->root = root;
}

void Left_Rotate(RBTree *T, RBElement *z){
	if (T!=NULL && z!=NULL){
		RBElement *y = z->right;
		z->right = y->left;
		if (y->left != sentinela){
			y->left->pai = z;
		}
		y->pai = z->pai;
		if (z->pai == sentinela){
			T->root = y;
		} else if(z==z->pai->left){
			z->pai->left = y;
		} else {
			z->pai->right = y;
		}
		y->left = z;
		z->pai = y;
	}
}

void Right_Rotate(RBTree *T, RBElement *y){
	if (T!=NULL && y!=NULL){
		RBElement *x = y->left;
		y->left = x->right;
		if (x->right != sentinela){
			x->right->pai = y;
		}
		x->pai = y->pai;
		if (y->pai == sentinela){
			T->root = x;
		} else if (y==y->pai->right){
			y->pai->right = x;
		} else {
			y->pai->left = x;
		}
		x->right = y;
		y->pai = x;
	}
}

void aux_RBCheck(RBElement *root, ){

}
void RBCheck(RBTree *T){
	RBElement *root = T->root;
	while (root!=sentinela){

	}
}

