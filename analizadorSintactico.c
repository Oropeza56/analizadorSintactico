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
if(actual->info=='e'||actual->info=='r'||actual->info=='b'||actual->info=='l' ||actual->info =='['){
        Decl();
        if (actual->info == '[') {
        	siguiente();
        }else{
         fprintf(erroresSintacticos,"ERROR EN (%d) falta '['\n",ubicacion);
        }
        Func();
        otraFunc();
	         if (actual->info == ']') {
        	siguiente();
        }else{
         fprintf(erroresSintacticos,"ERROR EN (%d) falta ']'\n",ubicacion);
        }
    } else {
        fprintf(erroresSintacticos,"ERROR EN (%d) al declarar una funcion\n",ubicacion);
        return;
    }

}

void otraFuncion(){
	if (actual == NULL){
		return;
	}else if(actual->info=='e'||actual->info=='r'||actual->info=='b'||actual->info=='l'){
	Func();
	otraFunc();	
	}else{
	 fprintf(erroresSintacticos, "ERROR EN (%d) al declarar una función o el fin archivo\n", ubicacion);	
	}

}

// funcion -> tipo + a + ( + param + ) + { + cuerpo + }
void Func(){
	if(actual->info=='e'||actual->info=='r'||actual->info=='b'||actual->info=='l'){
		Tipo();
		  if(actual->info == 'a'){
		  	siguiente();
		  }else{
		  	fprintf(erroresSintacticos, "ERROR EN (%d) falta el identificador \n", ubicacion );
		  	return;
		  }
		  if(actual->info == '('){
		  	siguiente();
		  }else{
		  fprintf(erroresSintacticos, "ERROR EN (%d) falta '('\n", ubicacion);
		 return;
		 }

		 Param();

		 if(actual->info == ')'){
		  	siguiente();
		  }else{
		  fprintf(erroresSintacticos, "ERROR EN (%d) falta ')'\n", ubicacion);
		 return;
		 }

		 if(actual->info == '{'){
		  	siguiente();
		  }else{
		  fprintf(erroresSintacticos, "ERROR EN (%d) falta '{'\n", ubicacion);
		 return;
		 }

		 Cuerpo();

		 if(actual->info == '}'){
		  	siguiente();
		  }else{
		  fprintf(erroresSintacticos, "ERROR EN (%d) falta '}'\n", ubicacion);
		 return;
		 }

	} else{
		fprintf(erroresSintacticos, "ERROR EN (%d) falta el tipo de dato \n", ubicacion);
	}
}

void Param(){
	if(actual->info=='e'||actual->info=='r'||actual->info=='b'||actual->info=='l'){
		Tipo();
		if(actual->info == 'a'){
			siguiente();
		}else{
			fprintf(erroresSintacticos, "ERROR EN (%d) falta el identificador\n", ubicacion );
			return;
		}
		otroParam();
	}else if (actual->info == ')'){
		return;
	}else{
		fprintf(erroresSintacticos, "ERROR EN (%d) falta el tipo de dato del parametro\n", ubicacion);
	}
}

void otroParam(){
	if (actual->info == ','){
		siguiente();
		Tipo();
		if (actual->info=='a'){
			siguiente();
		}else{
			fprintf(erroresSintacticos, "ERROR EN (%d) falta el identificador\n", );
			return;
		}
		otroParam();

	}else if (actual->info== ')'){
		return;
	}else{
		fprintf(erroresSintacticos, "ERROR EN (%d) falta el tipo de dato del parametro\n", ubicacion );
	}
}

void Cuerpo(){
	if(actual->info=='e'||actual->info=='r'||actual->info=='b'||actual->info=='l'||actual->info=='a'||actual->info=='i'||actual->info=='h'||actual->info=='m'||actual->info=='t'||actual->info=='['||actual->info=='v'||actual->info=='s'||actual->info=='}'){
		Decl();
		SP();
	}else{
		fprintf(erroresSintacticos, "ERROR EN (%d) falta cuerpo de funcion, '}' ó '['\n", ubicacion );
	}

}

void Decl(){
	if(actual->info=='['||actual->info=='a'||actual->info=='i'||actual->info=='h'||actual->info=='m'||actual->info=='t'||actual->info=='v'||actual->info=='s'||actual->info=='}'||){
		return;
	}else if(actual->info=='e'||actual->info=='r'||actual->info=='b'||actual->info=='l'){
		D();
		Decl();
	}else{
		fprintf(erroresSintacticos, "ERROR EN (%d) falta la declaración\n", ubicacion );
	}
}

void D(){
	if(actual->info=='e'||actual->info=='r'||actual->info=='b'||actual->info=='l'){
		Tiṕo();
		if (actual->info=='a'){
			siguiente();
		}else{
			fprintf(erroresSintacticos, "ERROR EN (%d) falta el identificador \n", ubicacion);
			return;
		}
		v();
		DP();
	}else{
		fprintf(erroresSintacticos, "ERROR EN (%d) falta el tipo de dato \n", ubicacion);
	}
}

void Tipo(){
	if(actual->info=='e'||actual->info=='r'||actual->info=='b'||actual->info=='l'){{
		siguiente();
	}
	fprintf(erroresSintacticos, "ERROR EN (%d) falta el tipo de dato\n", ubicacion);
}

void DP(){
	if (actual->info == ';'){
		siguiente();
		return:
	}else if (actual->info == ','){
	   siguiente();
	   if (actual->info== 'a'){
	   	 siguiente();
	   }else{
	   	fprintf(erroresSintacticos, "ERROR EN (%d) falta el identificador\n", ubicacion);
	   }
	   V();
	   DP();
	   return;
	}else{
		fprintf(erroresSintacticos, "ERROR EN (%d) falta ',' ó ';' \n", ubicacion);
	}
}

void V(){
	if (actual->info == '='){
		siguiente();
	    C();
	    return;
	}else{
		fprintf(erroresSintacticos, "ERROR EN (%d) falta '='\n", ubicacion);
		return;
	}
}

void C(){
	if(actual->info=='n'||actual->info=='c'||actual->info=='x'){
		siguiente();
		return;
	}else{
		fprintf(erroresSintacticos, "ERROR EN (%d) falta una constante númerica entera, cadena ó caracter\n", ubicacion);
	}
}

void A(){
	if (actual->info=='a'){
	   siguiente();
	   if (actual-> info =='=') {
	   	siguiente();
	   }else{
	   	fprintf(erroresSintacticos, "ERROR EN (%d) falta '='\n", ubicacion)
	   }
	   AP();
	   if (actual->info==';')  {
	   	siguiente();
	   }else{
	   	fprintf(erroresSintacticos, "ERROR EN (%d) falta ';'\n", ubicacion );
	   }
	}else{
	   	fprintf(erroresSintacticos, "ERROR EN (%d) falta el identificador\n", ubicacion );
	   	return;
	}
}

void AP(){
	if (actual->info=='c'){
		 siguiente();
		 return;
		}else if (actual->info== '('|| actual->info == 'a'|| actual->info == 'n'|| actual->info == 'x'|| actual->info == '[' ){
		 	E();
		 	return	
		}else{
			fprintf(erroresSintacticos, "ERROR EN (%d) falta '(', identificador, constante númerica entera, constante númerica real, constante númerica real ó '[' \n", ubicacion);
			return;
		}
}

void E(){
	if (actual->info== '('|| actual->info == 'a'|| actual->info == 'n'|| actual->info == 'x'|| actual->info == '[' ){
		T();
		EP();
		return;	
	}
}


