#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define p printf
#define s scanf

typedef struct nodo
{
	int nro;
	struct nodo *sig;
}nodo;

int menu(void);
void listar(nodo*);
int pilaVacia(nodo*);
nodo* ingresarDato(void);
void apilar(nodo**,nodo*);
nodo *buscar(nodo*, int);
nodo desapilar(nodo**);
void eliminar(nodo**);

int main()
{
	int op;
	nodo *nros = NULL;//Pila original.
	nodo *secuazOne;//Pila auxiliar 1.
	
	do
	{
		op = menu();
		switch(op)
		{
			case 1:
				if(pilaVacia(nros)==1)
				{
					system("cls");
					system("color 09");
					listar(nros);
					system("Pause");
				}
				else
				{
					system("cls");
					system("color 09");
					p("\t\t-La pila esta vacia-\n");
					system("Pause");
				}
				op = 10;
				break;
			case 2:
				system("cls");
				system("color 04");
				
				int i, j;
				p("-Cuantos nros desea ingresar?-\n");
				s("%d",&j);
				for(i=0;i<j;i++)
				{
					secuazOne = ingresarDato();
					apilar(&nros,secuazOne);
				}
				
				system("Pause");
				op = 10;
				break;
			case 3:
				system("cls");
				system("color 02");
				
				int num;
				p("-Ingrese el nro que desea buscar en la pila-\n");
				s("%d",&num);
				
				secuazOne = buscar(nros,num);
				
				if(secuazOne == NULL)
					p("\n\t\t-No se encontro el nro ingresado-\n");
				else
				{
					p("\n\t\t-El nro ingresado esta en la pila-\n");
				}
				
				system("Pause");
				op = 10;
				break;
			case 4:
				system("cls");
				system("color 05");
				
				int flag = 0;//Frena el while.
				nodo dato;
				
				p("-Desea eliminar un nro de la pila? '1'-->SI//'0'-->NO-\n");
				s("%d",&flag);
				
				while(flag<0 || flag>1)
				{
					p("-El nro ingresado no corresponde a ninguna opcion, ingrese de nuevo: '1'-->SI//'0'-->NO-");
					s("%d",&flag);	
				}
				
				while(flag == 1)
				{
					if(pilaVacia(nros)==0)
					{
						p("\t\t-La pila esta vacia-\n");
						break;
					}
					dato = desapilar(&nros);	
					p("-Nro a eliminar: %d-\n",dato.nro);
					system("Pause");
					p("\t\t-El nro fue eliminado de la pila-\n");
					p("-Desea eliminar otro? '1'-->SI//'0'-->NO-\n");
					s("%d",&flag);
					while(flag<0 || flag>1)
					{
						p("-El nro ingresado no corresponde a ninguna opcion, ingrese de nuevo: '1'-->SI//'0'-->NO-");
						s("%d",&flag);	
					}
					system("cls");
				}
				
				system("Pause");
				op = 10;
				break;
			case 5:
				system("cls");
				system("color 03");
				
				p("\t\t-Vaciando la pila...-\n");
				system("Pause");
				
				eliminar(&nros);
				
				p("\t\t-Pila vacia!-\n");
				
				system("Pause");
				op = 10;
				break;
			case 6:
				system("cls");
				system("color 06");
				
				p("\t\t-Cerrando el programa...-\n");
				system("Pause");
				break;
		}
	}while(op<1 || op>6);
	
	free(nros);
	free(secuazOne);
	
	return 0;	
}

int menu()
{
	system("cls");
	system("color 08");

	int op;
	
	p("\t\t-MENU PRINCIPAL-\n");
	p("\t\t-[1]Mostrar los datos de la pila\n");//Listar
	p("\t\t-[2]Ingresar un nuevo dato\n");
	p("\t\t-[3]Buscar un dato\n");
	p("\t\t-[4]Eliminar un dato\n");
	p("\t\t-[5]Vaciar la pila\n");
	p("\t\t-[6]Salir\n");
	s("%d",&op);
	
	return op;
}

void listar(nodo *x)
{
    if (x)
    {
        p("%d\n",x->nro);
        listar(x->sig);
    }
}

int pilaVacia(nodo*x)
{
	return((x==NULL)?0:1);
}

nodo* ingresarDato(void)
{
   int nro;
   nodo *q;
   q=(nodo*)malloc(sizeof(nodo));
   p("Ingrese un numero:\n");
   s("%d",&nro);
   q->nro=nro;
   q->sig=NULL;
    return q;
}

void apilar(nodo**p,nodo*q)
{
   q->sig=*p;
   *p=q;
}

nodo* buscar(nodo *x, int y)
{
    if (!x)
        return (NULL);
    else if (y == x->nro)
        return (x);
    else
        return (buscar(x->sig, y));
}

nodo desapilar(nodo**p)
{
	nodo dato,*aux;
	aux=*p;
	dato=**p;
	*p=(*p)->sig;
	free(aux);
	return dato;
}

void eliminar(nodo **x)
{
    nodo *aux;
    if (*x)
    {
        aux = *x;
        *x = aux->sig;
        free(aux);
        eliminar(x);
    }
}
