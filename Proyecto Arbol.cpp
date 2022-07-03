//Proyecto de Arboles
#include<iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

struct Nodo{
    int dato; //El arbol solo admite numeros enteros
    Nodo *der;
    Nodo *izq;
    Nodo *padre;
};
//Prototipos de funciones
void menu();
Nodo *crearNodo(int, Nodo *);
void insertarNodo(Nodo *&,int, Nodo *);
void mostrarArbol(Nodo*,int);
bool busqueda(Nodo *,int);
void preOrden(Nodo *);
void inOrden(Nodo *);
void postOrden(Nodo *);
void eliminar(Nodo *,int);
void eliminarNodo(Nodo *);
Nodo *minimo(Nodo *);
void reemplazar(Nodo *, Nodo *);
void destruirNodo(Nodo *);

Nodo *arbol = NULL;

int main(){
    menu();
    getch();
    return 0;
}
//Funcion menu
void menu(){
    int dato,opc,con=0;
    do{
        cout<<"\t::MENU::"<<endl;
        cout<<"1. Insertar un nuevo Nodo"<<endl;
        cout<<"2. Mostrar el arbol completo"<<endl;
        cout<<"3. Buscar un elemento en el arbol"<<endl;
        cout<<"4. Recorrido en PreOrden "<<endl;
        cout<<"5. Recorrido en InOrden "<<endl;
        cout<<"6. Recorrido en PostOrden "<<endl;
        cout<<"7. Eliminar un Nodo "<<endl;
        cout<<"8. Salir "<<endl;
        cout<<"Opcion: ";
        cin>>opc;

        switch(opc){
            case 1:  cout<<"\nDigite un numero: ";
                cin>>dato;
                insertarNodo(arbol,dato,NULL);
                cout<<"\n";
                system("pause");
                break;
            case 2: cout<<"\nMostrando el arbol completo:\n\n";
                mostrarArbol(arbol,con);
                cout<<"\n";
                system("pause");
                break;
            case 3: cout<<"\nDigite elemento a busucar: ";
                cin>>dato;
                if(busqueda(arbol,dato)==true){
                    cout<<"\nElemento "<<dato<<" se encontro en el arbol"<<endl;
                }else{
                    cout<<"\nElemento no encontrado\n";
                }
                cout<<"\n";
                system("pause");
                break;
            case 4: cout<<"\nRecorrido en PreOrden: ";
                preOrden(arbol);
                cout<<"\n\n";
                system("pause");
                break;
            case 5: cout<<"\nRecorrido en InOrden: ";
                inOrden(arbol);
                cout<<"\n\n";
                system("pause");
                break;
            case 6: cout<<"\nRecorrido en PostOrden: ";
                postOrden(arbol);
                cout<<"\n\n";
                system("pause");
                break;
            case 7: cout<<"\nDigite el numero a eliminar: ";
                cin>>dato;
                eliminar(arbol,dato);
                cout<<"\n\n";
                system("pause");
                break;
        }
        system("cls");
    }while (opc!=8);
}

//Funcion para crear un Nodo
Nodo *crearNodo(int n, Nodo *padre){
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->padre = padre;
    return nuevo_nodo;
}
//Funcion para insertar elementos al arbol
void insertarNodo(Nodo *&arbol, int n,Nodo *padre){
    if(arbol==NULL){//si arbol esta vacio
        Nodo *nuevo_nodo = crearNodo(n,padre);
        arbol = nuevo_nodo;
    }
    else{//si el arbol ya tiene Nodos
        int valorRaiz = arbol->dato;//Obtener valor Raiz
        if(n<valorRaiz){
            insertarNodo(arbol->izq,n,arbol);
        }
        else{
            insertarNodo(arbol->der,n,arbol);
        }
    }
}
//Funcion mostrar arbol completo
void mostrarArbol(Nodo *arbol, int cont){
    if(arbol==NULL){
        return;
    }
    else{
        mostrarArbol(arbol->der,cont+1);
        for(int i=0;i<cont;i++){
            cout<<"   ";
        }
        cout<<arbol->dato<<endl;
        mostrarArbol(arbol->izq,cont+1);
    }
}
//Funcion busqueda en el arbol
bool busqueda(Nodo *arbol,int n){
    if(arbol==NULL){
        return false;
    }else if(arbol->dato==n){
        return true;
    }else if(n<arbol->dato){
        return busqueda(arbol->izq,n);
    }else{
        return busqueda(arbol->der,n);
    }
}
//Funcion recorrido en profundidad - PreOrden
void preOrden(Nodo *arbol){
    if(arbol==NULL){
        return;
    }else{
        cout<<arbol->dato<<"  -  ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}
//Funcion recorrido en profundidad - InOrden
void inOrden(Nodo *arbol){
    if(arbol==NULL){
        return;
    }else{
        inOrden(arbol->izq);
        cout<<arbol->dato<<"  -  ";
        inOrden(arbol->der);
    }
}
//Funcion recorrido en profundidad - PostOrden
void postOrden(Nodo *arbol){
    if(arbol==NULL){
        return;
    }else{
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout<<arbol->dato<<"  -  ";
    }
}
//Funcion eliminar un nodo
void eliminar(Nodo *arbol,int n){
    if(arbol==NULL){//si el arbol esta vacio
        return;//no hacer nada
    }else if(n<arbol->dato){//Si el valor es menor
        eliminar(arbol->izq,n);//Buscar por la izq
    }else if(n>arbol->dato){//Si el valor es mayor
        eliminar(arbol->der,n);//Buscar por la der
    }else{//Si ya encontro el valor
        eliminarNodo(arbol);
    }
}
//Funcion para determinar el nodo mas izq posible
Nodo *minimo(Nodo *arbol){
    if(arbol==NULL){//si arbol esta vacio
        return NULL;//retornar nulo
    }if(arbol->izq){//si tiene hijo izq
        return minimo(arbol->izq);//buscamos la parte mas izq posible
    }else{//si no tiene hijo izq
        return arbol;//retornar el mismo nodo
    }
}
//Funcion para reemplazar dos nodos
void reemplazar(Nodo *arbol,Nodo *nuevoNodo){
    if(arbol->padre){
        if(arbol->dato == arbol->padre->izq->dato){
            arbol->padre->izq = nuevoNodo;
        }else if(arbol->dato == arbol->padre->der->dato){
            arbol->padre->der = nuevoNodo;
        }
    }if(nuevoNodo){
        nuevoNodo->padre = arbol->padre;
    }
}
//Funcion para destruir nodo
void destruirNodo(Nodo *nodo){
    nodo->izq = NULL;
    nodo->der = NULL;
    delete nodo;
}
//Funcion eliminar Nodo encontrado
void eliminarNodo(Nodo *nodoEliminar){
    if(nodoEliminar->izq && nodoEliminar->der){//
        Nodo *menor = minimo(nodoEliminar->der);
        nodoEliminar->dato=menor->dato;
        eliminarNodo(menor);
    }else if(nodoEliminar->izq){//si tiene hijo izq
        reemplazar(nodoEliminar,nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    }else if(nodoEliminar->der){//si tiene hijo der
        reemplazar(nodoEliminar,nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }else{//No tiene hijos
        reemplazar(nodoEliminar,NULL);
        destruirNodo(nodoEliminar);
    }
}
