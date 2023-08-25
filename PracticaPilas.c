#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define p printf
#define s scanf

typedef struct
{
  long int cod;
  char desc[25];
  int cant;
  float pre;
} registro;

typedef struct elemento
{
  registro datos;
  struct elemento *sig;
} nodo;

int menu(void);
void cargarPila(nodo **,registro[],int);
void mostrar(FILE *);
void listar(nodo *);
void linea(int);
int pilaVacia(nodo*);
void apilar(nodo**,nodo*);
nodo* ingresarDato(int,registro[]);
void eliminarPila(nodo**);
void cargarArchivo(FILE*,nodo*);
nodo desapilar(nodo**);

int main()
{
    system("color 04");
    nodo *stock;
    nodo *cabeza2;
    FILE *archivo;
    char *nomArch="Stock.dat";

    if((archivo=fopen(nomArch,"wb"))==NULL)
        p("\t\t***ERROR: no se pudo crear el archivo [%s]",nomArch);
    else
    {
        stock = NULL;
        cabeza2 = NULL;

        registro info[] = {
        {100235, "Nebulizador", 50, 145.20},
        {100312, "Tensiometro", 120, 159.35},
        {200045, "Caloventor", 35, 46.00},
        {200511, "Estufa halogena", 15, 72.58},
        {400805, "Afeitadora", 100, 215.40},
        {400322, "Cortadora de Cabello", 210, 29.45}
        };

        registro infocom[] = {
        {500100, "Reproductor de DVD", 24, 200.53},
        {100312, "Tensiometro", 50, 159.35},
        {500235, "Televisor 21", 30, 565.60},
        {200511, "Estufa halogena", 30, 72.58}
        };

        int op;
        do
        {
            op=menu();
            switch(op)
            {
                case 1:
                    system("cls");
                    cargarPila(&stock,info,6);
                    cargarPila(&cabeza2,infocom,4);
                    p("\t\t-DATOS CARGADOS-\n");
                    p("\n");
                    system("Pause");
                    op=10;
                    break;
                case 2:
                    break;
                case 3:
                    if(pilaVacia(stock)==1)
                    {
                        system("cls");
                        p("\t\t***PILA VACIA***\n");
                    }
                    else
                    {
                        system("cls");
                        p("\t\t\t-STOCK-\n");
                        p("\t  COD\tDESC\tCANT\tPRECIO\n");
                        listar(stock);
                    }
                    p("\n");
                    system("Pause");
                    op=10;
                    break;
                case 4:
                    system("cls");
                    cargarArchivo(archivo,stock);
                    p("\t\t-ARCHIVO CARGADO-\n");
                    mostrar(archivo);
                    system("Pause");
                    op=10;
                    break;
                case 5:
                    system("cls");
                    eliminarPila(&stock);
                    p("\t\t-CERRANDO EL PROGRAMA-\n");
                    system("Pause");
                    break;
            }
        }while(op<1 || op>5);


        free(stock);
        free(cabeza2);
        fclose(archivo);
    }

    return 0;
}

int menu(void)
{
  int op;
  do
  {
    system("cls");
    printf("\n\t\t\t\t MENU DE OPCIONES (PILAS)\n\n");
    printf("\n\n\t\t\t\t - CARGAR DATOS INICIALES   <1>\n");
    printf("\n\n\t\t\t\t - AGREGAR DATOS   <2>\n");
    printf("\n\n\t\t\t\t - LISTAR DATOS   <3>\n");
    printf("\n\n\t\t\t\t - CARGAR EN ARCHIVO  <4>\n");
    printf("\n\n\t\t\t\t - BORRAR Y SALIR   <5>\n");
    printf("\n\n\t\t\t\t - INGRESE OPCION  [1-5]:  ");
    scanf("%d", &op);
  } while (op < 1 || op > 5);
  return op;
}

void cargarPila(nodo**x,registro y[], int z)
{
    int i;
    nodo *q;
    for(i=0;i<z;i++)
    {
          q=ingresarDato(i,y);
          apilar(&(*x),q);
     }
}

void mostrar(FILE *x)
{
    registro r;
    p("\n\t\t CONTENIDO DE LOS REGISTROS EN EL ARCHIVO\n\n");
    p("\n\n Codigo\t\tNombre\t\t\tCantidad\t\tPrecio\n\n");
    rewind(x);
    fread(&r,sizeof(r),1,x);
	while(!feof(x))
	{
		p("\n\n%3d\t\t%-20s\t%6d\t\t\t%6.2f",r.cod,r.desc,r.cant,r.pre);
		fread(&r,sizeof(r),1,x);
	}
}

void listar(nodo *x)
{
    if (x)
    {
        p("%d, %s, %d, %.2f\n", x->datos.cod,x->datos.desc,x->datos.cant,x->datos.pre);
        listar(x->sig);
    }
}

void linea(int cant)
{
    p("\n");
    for(int i=0;i<cant;i++)
    {
        p("-");
    }
    p("\n");
}

int pilaVacia(nodo *p)
{
    if(p==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void apilar(nodo**p,nodo*q)
{
    q->sig=*p;
    *p=q;
}

nodo* ingresarDato(int i, registro y[])
{
    nodo *q;
    q=(nodo*)malloc(sizeof(nodo));
    q->datos=y[i];
    q->sig=NULL;
    return q;
}

void eliminarPila(nodo **x)
{
    nodo *aux;
    if (*x)
    {
        aux = *x;
        *x = aux->sig;
        free(aux);
        eliminarPila(x);
    }
}

void cargarArchivo(FILE *archivo, nodo *x)
{
    rewind(archivo);
    nodo y;

    while(pilaVacia(x)!=1)
    {
        y=desapilar(&x);
        fwrite(&y,sizeof(y),1,archivo);
        fseek(archivo,0l,SEEK_CUR);
    }

}

nodo desapilar(nodo**p)
{
    nodo dato, *aux;
    aux=*p;
    dato=**p;
    *p=(*p)->sig;
    free(aux);
    return dato;
}
