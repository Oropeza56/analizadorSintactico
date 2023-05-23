#include <stdio.h>
#include "tokens.h"

//FUNCIONES
//Todos los NO TERMINALES

void analizadorSintactico(ListaAtomos* l, FILE *archivoSalida);
void siguiente();
void Program();
void otraFunc();
void Func();
void Param();
void otroParam();
void Cuerpo();
void Decl();
void D();
void Tipo();
void DP();
void V();
void C();
void A();
void AP();
void E();
void EP();
void T();
void TP();
void F();
void R();
void RP();
void VP();
void S();
void SP();
void M();
void RPP();
void B();
void BP();
void P();
void PP();
void CP();
void H();
void HP();
void Devuelve();
void valor();
void Llama();
void arg();
void otroArg();


/*Se ocuparan apuntadores para guardar direcciones e ir recorriendo 
nuestro archivo*/

NodoApuntador* actual;
int ubicacion;
FILE *erroresSintacticos;


//Se inicializa el apuntador y el archivo donde se almacenaran 
// los errores sintacticos

void analizadorSintactico(ListaAtomos* l, FILE *archivoSalida){
    erroresSintacticos = fopen("erroresSintacticos.txt", "w");
    actual = l->head;
    ubicacion = 1;
    Program();
    if(actual == NULL){
        fprintf(archivoSalida,"EL ARCHIVO ES SINTACTICAMENTE CORRECTO\n");
    } else {
        fprintf(archivoSalida,"EL ARCHIVO ES SINTACTICAMENTE INCORRECTO\n");
    }
}

void siguiente(){
	actual=actual->next;
    ubicacion++;
}

void Program(){
	//           ent                real				simb			large		  
if(actual->info=='e'||actual->info=='r'||actual->info=='b'||actual->info=='l'){
        Decl();
        Func();
        otraFunc();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba la declaracion de una funcion\n",ubicacion);
    }

}

void otraFuncion
