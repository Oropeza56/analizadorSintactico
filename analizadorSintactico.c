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


	
void T(){
	if(actual -> info =='(' ||actual -> info == 'a' || actual -> info == 'n' ||actual -> info == 'x' || actual -> info == '['){
		F();
		TP();
		return;
	}
	else{
		fprintf(erroresSintacticos, "ERROR EN (%d). Se esperaba '(', identificador, constante numérica entera, constante numérica real o '['\n", ubicacion);
		return;
		}
	}


	void F(){
		if(actual -> info == 'a'|| actual -> info == 'n'|| actual -> info == 'x'){
			siguiente();
			return;
		}else if (actual -> info == '['){
			Llama();
		}else if(actual -> info == '('){
			siguiente();
			E();
			if(actual -> info == ')'){
				siguiente();
			}
			else{
				fprintf(erroresSintacticos, "ERROR EN (%d). Se esperaba ')'", ubicacion);
			}
			return;
			else{
				fprintf(erroresSintacticos, "ERROR EN (%d). Se esperaba '(', '[', identificador, constante númerica entera o 
				constante númerica real\n", ubicacion);
			}
		}
	}
					
					
	void RP(){
		if(actual -> info == '>'|| actual -> info == '<'|| actual -> info == 'q'|| actual -> info == 'g'||actual -> info == 'd' || actual -> info == 'p' ){
			siguiente();
			return;
		}else{
			fprintf(erroresSintacticos, "ERROR EN (%d). Se esperaba un operador relacional", ubicacion);
		}
	}
					
	void S(){
		if(actual -> info == 'a'){
			A();
			return;
		}else if(actual -> info == 'i'){
			B();
			return;
		}else if(actual -> info == 'h'){
			H();
			return;
		}else if(actual -> info == 'm'){
			M();
			return;
		}else if(actual -> info == 't'){
			P();
			return;
		}else if(actual -> info == '['){
			Llama();
			return;
		}else if(actual -> info == 'v'){
			Devuelve();
			return;
		}else if(actual -> info == 's'){
			siguiente();
			if(actual -> info == ';'){
				siguiente();
			}else{
				fprintf(erroresSintacticos, "ERROR EN (%d). Se esperaba ';'", ubicacion);
			}
			return;
		}else{
			fprintf(erroresSintacticos, "ERROR EN (%d). Se esperaba un identificador, o la palabra reservada 'si', o la palabra reservada 'haz', 
			o la palabra reservada 'mientras', o la palabra reservada 'para', o la palabra reservada 'regresa', o una constante cadena, o '['"
			,ubicacion);
		}
	}
					
	
void M(){
	if(actual -> info == 'm'){
		siguiente(); 
		if(actual -> info == '('){
			siguiente();
		}else{
			fprintf(erroresSintacticos,"ERROR EN (%d). Se esperaba '('", ubicacion);
		}
		RPP();
		if(actual -> info ==')'){
			siguiente();
		}else{
			fprintf(erroresSintacticos, "ERROR EN (%d). Se esperaba ')'", ubicacion);
		}
		if(actual -> info == '{'){
			siguiente();
		}else{
			fprintf(erroresSintacticos, "ERROR EN (%d). Se esperaba '{'", ubicacion);
		}
		SP();
		if(actual -> info == '}'){
			siguiente();
		}else{
			fprintf(erroresSintacticos, "ERROR EN (%d). Se esperaba '}'", ubicacion);
		}
		return;
	}else{
		fprintf(erroresSintacticos, "ERROR EN (%d). Se esperaba la palabra reservada 'mientras'", ubicacion);
	}
}

