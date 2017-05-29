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
		string color = "vermelho";
		if (no->color==black) color="preto";
		string pai = "NIL", left="NIL", right="NIL";
		if (no->pai!=NULL && no->pai!=sentinela) pai = no->pai->key;
		if (no->left!=NULL && no->left!=sentinela) left = no->left->key;
		if (no->right!=NULL && no->right!=sentinela) right = no->right->key;
		cout<<"("<< pai <<", "<<no->key<<", "<<color<<", "<<nivel<<", "<<left<<", "<<right<<")"<<endl;
	}
}



void RBInsert(RBTree *T, RBElement *z); // insere um elemento z em T
void RB_Insert_Fixup(RBTree *T, RBElement *z); // mantém as propriedades da árvore T, que possivelmente foram violadas pelo nó x
void Right_Rotate(RBTree *T, RBElement *y); // Rotaciona à direita uma subárvore de raiz z
void Left_Rotate(RBTree *T, RBElement *z); // Rotaciona à esquerda uma subárvore de raiz z
void RB_Delete(RBTree *T, RBElement *z); // deleta um elemento z de T, mantendo as pripriedades de T
void RB_Transplant(RBTree *T, RBElement *z, RBElement *y); // coloca o elemento y em z
RBElement *Tree_Minimum(RBTree *T, RBElement *z); // retorna o menor elemento de uma subarvore de raiz z
void RB_Delete_Fixup(RBTree *T, RBElement *x); //// mantém as propriedades da árvore T, que possivelmente foram violadas pelo nó x
RBElement * Search(RBTree *T, string c); // busca por uma chave c
void RBPrint(RBTree *T); // percurso in ordem
void RBCheck(RBTree *T); // "desenha" a árvore
bool isRNTree(RBTree *T); // retorna true se T é uma RN tree


int main(int argc, const char * argv[]){
	// if (argc != 2) {
 //        cout << "Parameter error. Usage: " << argv[0] << " (input file) " << endl;
 //        exit (1);
 //    }
	sentinela = alocaElemento("", NULL,NULL,NULL, black); // elemento global para a sentinela da árvore (nó externo)
   	sentinela->pai = sentinela;
   	sentinela->left = sentinela;
   	sentinela->right = sentinela;
    //RBElement * root = alocaElemento("Aaaaa", sentinela,sentinela,sentinela, black); // elemento global para a sentinela da árvore (nó externo)
  	RBTree *T = (RBTree*)malloc(sizeof(RBTree));;
  	T->root=sentinela;
  	//T->root = root;
  	RBElement* n41 = alocaElemento("41", sentinela,sentinela,sentinela, red);
  	RBElement* n38 = alocaElemento("38", sentinela,sentinela,sentinela, red);
  	RBElement* n31 = alocaElemento("31", sentinela,sentinela,sentinela, red);
  	RBElement* n12 = alocaElemento("12", sentinela,sentinela,sentinela, red);
	RBElement* n19 = alocaElemento("19", sentinela,sentinela,sentinela, red);
	RBElement* n8  = alocaElemento("08", sentinela,sentinela,sentinela, red);
	
	cout<<"Primeira insersao: "<<endl;
	RBInsert(T,n41);
	RBCheck(T);
	cout<<"Segunda insersao: "<<endl;
	RBInsert(T,n38);
	RBCheck(T);
	cout<<"Terceira insersao: "<<endl;
	RBInsert(T,n31);
	RBCheck(T);
	cout<<endl;
	RBInsert(T,n12);
	RBCheck(T);
	cout<<endl;
	RBInsert(T,n19);
	RBCheck(T);
	cout<<endl;
	RBInsert(T,n8);
	RBCheck(T);
	cout<<endl;

	cout<<"\nDelete 8:"<<endl;
	RB_Delete(T,n8);
	RBCheck(T);
	cout<<endl;

	cout<<"\nDelete 12:"<<endl;
	RB_Delete(T,n12);
	RBCheck(T);
	cout<<endl;

	cout<<"\nDelete 19:"<<endl;
	RB_Delete(T,n19);
	RBCheck(T);
	cout<<endl;

	cout<<"\nDelete 31:"<<endl;
	RB_Delete(T,n31);
	RBCheck(T);
	cout<<endl;

	cout<<"\nDelete 38:"<<endl;
	RB_Delete(T,n38);
	RBCheck(T);
	cout<<endl;

	cout<<"\nDelete 41:"<<endl;
	RB_Delete(T,n41);
	RBCheck(T);
	cout<<endl;

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

void aux_RBCheck(RBElement *root, int nivel){
	if (root!=NULL && root!=sentinela){
		aux_RBCheck(root->left, nivel+1);
		printElement(root, nivel);
		aux_RBCheck(root->right, nivel+1);
	}
}
void RBCheck(RBTree *T){
	RBElement *root = T->root;
	aux_RBCheck(root, 1);
}

void RBInsert(RBTree *T, RBElement *z){
	RBElement * y = sentinela;
	RBElement * x = T->root; // elemento corrente
	while (x != sentinela){ // busca pela posicao correta de insersao
		y = x; // pai do elemento corrente
		if (z->key < x->key){
			x = x->left;
		}else{
			x = x->right;
		}
	}
	z->pai = y; // atribui o pai do novo elemento
	if(y==sentinela){
		T->root = z; // se a arvore é vazia, coloca-se a raiz (inicialmente)
	} else if (z->key < y->key){ // o novo elemento é menor
		y->left = z; // insere na esquerda
	} else { // maior
		y->right = z; // insere na direita
	}
	z->left = sentinela;
	z->right = sentinela;
	z->color = red; // cor vermelha para o novo elemento
	RB_Insert_Fixup(T,z); // reajusta a arvore
}
void RB_Insert_Fixup(RBTree *T, RBElement *z){
	while (z->pai->color == red){
		if (z->pai == z->pai->pai->left){ // o pai de z é fiho esquerdo
			RBElement *y = z->pai->pai->right; // tio
			if (y->color == red){ // se o tio é vermeho
				z->pai->color = black;
				y->color = black;
				z->pai->pai->color = red;
				z = z->pai->pai; // z agora é avô
			} else {
				if (z==z->pai->right){
					z = z->pai;
					Left_Rotate(T,z);
				}
				z->pai->color = black;
				z->pai->pai->color = red;
				Right_Rotate(T,z->pai->pai);
			}

		} else { // o pai de z é fiho direito

			RBElement *y = z->pai->pai->left; // tio esquerdo
			if (y->color == red){ // se o tio é vermeho
				z->pai->color = black;
				y->color = black;
				z->pai->pai->color = red;
				z = z->pai->pai; // z agora é avô
			} else {
				if (z==z->pai->left){
					z = z->pai;
					Right_Rotate(T,z);
				}
				z->pai->color = black;
				z->pai->pai->color = red;
				Left_Rotate(T,z->pai->pai);
			}
		}
	}
	T->root->color = black;
}

void RB_Transplant(RBTree *T, RBElement *z, RBElement *y){
	if (z->pai == sentinela){
		T->root = y; // caso onde z seja a raiz. A arvore agora tem somente um elemrento, y
	} else if (z==z->pai->left){
		z->pai->left = y;
	}else {
		z->pai->right = y;
	}
	y->pai = z->pai;
}

RBElement *Tree_Minimum(RBTree *T, RBElement *z){
	while (z->right != sentinela){
		z = z->right;
	}
	return z;
}

void RB_Delete(RBTree *T, RBElement *z){
	RBElement *y = z;
	Color corOriginalDeY = y->color;
	RBElement *x;
	if (z->left == sentinela){ // se z nao tem filho esquerdo
		x = z->right;
		RB_Transplant(T,z,z->right);
	} else if (z->right == sentinela){ // se z nao tem filho direito
		x = z->left;
		RB_Transplant(T, z,z->left);
	}else{
		y = Tree_Minimum(T,z->right);
		corOriginalDeY = y->color;
		x = y->right;
		if (y->pai == z){ // DESNECESSARIO
			x->pai = y;
		} else {
			RB_Transplant(T, y, y->right);
			y->right = z->right;
			y->right->pai = y;
		}
		RB_Transplant(T,z,y);
		y->left = z->left;
		y->left->pai = y;
		y->color = z->color;
	}

	if(corOriginalDeY == black){
		RB_Delete_Fixup(T,x);
	}
}

void RB_Delete_Fixup(RBTree *T, RBElement *x){
	while(x != T->root && x->color == black){
		if (x==x->pai->left){ // x é filho esquerdo
			RBElement *w = x->pai->right; // tio do double negro
			if (w->color == red){
				w->color = black;
				x->pai->color = red;
				Left_Rotate(T,x->pai);
				w = x->pai->right;
			}

			if (w->left->color == black && w->right->color == black){
				w->color = red;
				x = x->pai;
			} else{
				if (w->right->color == black){
					w->left->color = black;
					w->color = red;
					Right_Rotate(T,w);
					w = x->pai->right;
				}
				w->color = x->pai->color;
				x->pai->color = black;
				w->right->color = black;
				Left_Rotate(T, x->pai);
				x = T->root;
			}
		} else{// y é filho esquerdo

			RBElement *w = x->pai->left; // tio do double negro
			if (w->color == red){
				w->color = black;
				x->pai->color = red;
				Right_Rotate(T,x->pai);
				w = x->pai->left;
			}

			if (w->right->color == black && w->left->color == black){
				w->color = red;
				x = x->pai;
			} else{
				if (w->left->color == black){
					w->right->color = black;
					w->color = red;
					Left_Rotate(T,w);
					w = x->pai->left;
				}
				w->color = x->pai->color;
				x->pai->color = black;
				w->left->color = black;
				Right_Rotate(T, x->pai);
				x = T->root;
			}
		}
	}
	x->color = black;
}



