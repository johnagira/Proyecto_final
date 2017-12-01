#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//variables identificadoras
int Cont_facturas = 0;

//estructuras para arboles

struct NodoCliente{
	//int id;
	int cedula;
	char nombre[20];
	char direccion[20];
	char telefono[20];
	int puntos;
	NodoCliente *izq,*der;
	NodoCliente *padre;
} *ArbolCliente=NULL;

struct NodoFactura{
	int id;
	char nombre_cliente[20];
	int cedula_cliente;
	int Combustible; //1 corriente , 2 diesel 3 gas natural
	int valor;
	float galones;
	NodoFactura *sig;
} *Listafactura=NULL;


//menu principal
void menu_Principal();

//variables globales
int ValorCorriente = 8000;
int ValorDiesel = 6000;
int ValorGasNatural = 4000;

int ExistenciaValorCorriente = 10000000;
int ExistenciaValorDiesel = 10000000;
int ExistenciaValorGas = 10000000;

//funciones generales
void CambiarPreciosCombustibles();
void menu_cliente();
void crear_cliente(NodoCliente *&,NodoCliente *&);
void insertarNodoCliente(NodoCliente *&,NodoCliente *&,int,NodoCliente*);
bool modificar_cliente(NodoCliente *,int);
bool buscar_En_Arbol_cliente(NodoCliente *,int);
void mostrar_Arbol_cliente(NodoCliente *,int);
void eliminar_cliente(NodoCliente *,int);

void ver_puntos_cliente(NodoCliente *,int);

void MenuFacturas();
void Nueva_Factura();
void MostrarFacturas();
NodoCliente* buscar_cliente_para_factura (NodoCliente *,int);
void ListarFacturas();
void EditarFacturas();

void venderGasolina();
void ComprarGasolina();


int main(int argc, char *argv[]) {
	menu_Principal(); //llama al menu principal
	return 0;
}

void menu_Principal(){
	int opcion;
	
	do{
		system("cls"); //limpia la pantalla
		printf("*** ESTACION DE GASOLINA - PROYECTO FINAL ***\n\n"); //titulo del proyecto
		
		printf("CORRIENTE : $%d\n",ValorCorriente);
		printf("DIESEL : $%d\n",ValorDiesel);
		printf("GAS NATURAL : $%d\n\n",ValorGasNatural);
		
		printf("1. Comprar combustible.\n");
		printf("2. Vender combustible.\n");
		printf("3. Facturas.\n");
		printf("4. Clientes.\n");
		printf("5. Ver puntos de clientes.\n");
		printf("6. Cambiar precios de combustibles.\n");
		printf("7. Salir.\n\n");
		
		printf("Elija una opcion : ");
		scanf("%d",&opcion);
		
		switch(opcion){
		case 1:
			ComprarGasolina();
			system("pause");
			break;
		case 2:
			venderGasolina();
			system("pause");
			break;
		case 3:
			MenuFacturas();
			break;
		case 4:
			menu_cliente();
			break;
		case 5:
			ver_puntos_cliente(ArbolCliente,0);
			system("pause");
			break;
		case 6:
			CambiarPreciosCombustibles();
			break;
		case 7:
			printf("\n Adios.");
			break;
		default:
			printf("\n No se reconoce su peticion. vuelva a intentarlo. \n");
			system("pause");
		}
	} while(opcion!=7);
}

void menu_cliente(){
	int opcion;
	
	do{
		system("cls"); //limpia la pantalla
		printf("*** GESTION DE CLIENTES ***\n\n"); //titulo del proyecto
		
		printf("1. Crear cliente.\n");
		printf("2. Mostrar arbol clientes.\n");
		printf("3. Modificar cliente.\n");
		printf("4. Buscar cliente.\n");
		printf("5. Eliminar cliente.\n");
		printf("6. regresar.\n\n");
		
		printf("Elija una opcion : ");
		scanf("%d",&opcion);
		int cedulabus;
		NodoCliente *padreini = NULL;
		switch(opcion){
		case 1:
			
			crear_cliente(ArbolCliente,padreini);
			break;
		case 2:
			mostrar_Arbol_cliente(ArbolCliente,0); //0 porque siempre queremos que imprima desde el inicio
			printf("\n");
			system("pause");
			break;
		case 3:
			printf("Por favor digite la cedula que desee modificar : ");
			scanf("%d",&cedulabus);
			modificar_cliente(ArbolCliente,cedulabus);
			printf("\n");
			system("pause");
			break;
		case 4:
			printf("Por favor digite la cedula que desee buscar : ");
			scanf("%d",&cedulabus);
			if(buscar_En_Arbol_cliente(ArbolCliente,cedulabus)){
				printf("La cedula ha sido encontrada en el arbol de clientes.\n");
			} else {
				printf("La cedula no ha sido encontrada, por favor rectifique.\n");
			}
			system("pause");
			break;
		case 5:
			printf("Por favor digite la cedula que desee eliminar : ");
			scanf("%d",&cedulabus);
			eliminar_cliente(ArbolCliente,cedulabus);
			printf("Consulta ejecutada correctamente.\n");
			system("pause");
			break;
		case 6:
			menu_Principal();
		default:
			printf("\n No se reconoce su peticion. vuelva a intentarlo. \n");
			system("pause");
		}
	} while(opcion!=6);
}

void CambiarPreciosCombustibles(){
	system("cls"); //limpia la pantalla
	printf("*** ESTACION DE GASOLINA - PROYECTO FINAL ***\n\n"); //titulo del proyecto
	
	printf("CORRIENTE - PRECIO ANTERIOR $%d  - NUEVO PRECIO : ",ValorCorriente);scanf("%d",&ValorCorriente);
	printf("DIESEL - PRECIO ANTERIOR $%d  - NUEVO PRECIO : ",ValorDiesel);scanf("%d",&ValorDiesel);
	printf("GAS NATURAL - PRECIO ANTERIOR $%d  - NUEVO PRECIO : ",ValorGasNatural);scanf("%d",&ValorGasNatural);
	
	printf("\n\n Datos modificados correctamente.\n");
	system("pause");
	menu_Principal();
}

void crear_cliente(NodoCliente *&ArbolCliente,NodoCliente *&padre){
	system("cls"); //limpia la pantalla
	printf("*** CREAR CLIENTE ***\n\n"); //titulo del proyecto
	
	NodoCliente * NuevoNodo = (NodoCliente*)malloc(sizeof(NodoCliente)); //asigno espacio en memoria
	
	fflush(stdin);//agrega los datos del cliente
	printf("Ingrese la cedula del cliente : "); int ced;
	scanf("%d",&ced);
	NuevoNodo->cedula = ced;
	fflush(stdin);
	printf("\nIngrese el nombre completo del cliente : ");
	fgets(NuevoNodo->nombre,20,stdin);
	fflush(stdin);
	printf("\nIngrese la direccion del cliente : ");
	fgets(NuevoNodo->direccion,20,stdin);
	fflush(stdin);
	printf("\nIngrese el telefono del cliente : ");
	fgets(NuevoNodo->telefono,20,stdin);
	fflush(stdin);
	NuevoNodo->izq=NULL;
	NuevoNodo->der=NULL;
	NuevoNodo->padre=padre;
	//ya el nodo esta listo para agregarse al arbol
	
	insertarNodoCliente(ArbolCliente,NuevoNodo,ced,padre); //agregar al arbol donde pertenezca
	
	printf("\nEl cliente se ha creado satisfactoriamente.\n");
	system("pause");
}


void insertarNodoCliente(NodoCliente *&ArbolCliente,NodoCliente *&nodonuevo,int cedulanueva,NodoCliente* nodopadre){
	
	if(ArbolCliente==NULL) { //Si el arbol esta vacio
		ArbolCliente = nodonuevo; //asigne este nodo como raiz principal
		printf("\n. arbol null\n");
	} else { //si el arbol tiene un nodo o mas
		int cedularaiz = ArbolCliente->cedula; //toma el valor de la cedula del nodo raiz actual
		printf("\n. vooy a ver la raiz %d - %d\n",cedularaiz,cedulanueva);
		if(cedulanueva < cedularaiz){
			printf("\n. 1 opcion es menor\n");
			insertarNodoCliente(ArbolCliente->izq,nodonuevo,cedulanueva,nodopadre);
		} else {
			printf("\n. 2 opcion es mayor\n");
			insertarNodoCliente(ArbolCliente->der,nodonuevo,cedulanueva,nodopadre);
		}
	}
}

void mostrar_Arbol_cliente(NodoCliente *Arbol,int cont){
	if(Arbol == NULL){
		printf("\n");
		return;
	} else {
		mostrar_Arbol_cliente(Arbol->der,cont + 1);
		for(int i=0;i<cont;i++){
			printf("      ");
		}
		printf("%d",Arbol->cedula);
		mostrar_Arbol_cliente(Arbol->izq,cont + 1);
	}
}

void ver_puntos_cliente(NodoCliente *Arbol,int cont){
	if(Arbol == NULL){
		printf("\n");
		return;
	} else {
		ver_puntos_cliente(Arbol->der,cont + 1);
		printf("-----------------------------------------\n");
		printf("cedula : %d\n",Arbol->cedula);
		printf("Nombre : %s",Arbol->nombre);
		printf("puntos : %d\n",Arbol->puntos);
		printf("\n-----------------------------------------\n\n\n");
		ver_puntos_cliente(Arbol->izq,cont + 1);
	}
}

bool modificar_cliente(NodoCliente *Arbol,int cedulaB){
	if(Arbol==NULL){
		return false;
	}else if(Arbol->cedula == cedulaB){
		printf("\n\n registro \n");
		printf("Cedula : %d\n",Arbol->cedula);
		printf("Nombre : %s\n",Arbol->nombre);
		printf("Direccion : %s\n",Arbol->direccion);
		printf("telefono : %s\n",Arbol->telefono);
		printf("Puntos : %d\n\n",Arbol->puntos);
		
		fflush(stdin);//agrega los datos del cliente
		printf("Ingrese la nueva cedula del cliente : "); int ced;
		scanf("%d",&ced);
		Arbol->cedula = ced;
		fflush(stdin);
		printf("\nIngrese el nuevo nombre completo del cliente : ");
		fgets(Arbol->nombre,20,stdin);
		fflush(stdin);
		printf("\nIngrese la nueva direccion del cliente : ");
		fgets(Arbol->direccion,20,stdin);
		fflush(stdin);
		printf("\nIngrese el nuevo telefono del cliente : ");
		fgets(Arbol->telefono,20,stdin);
		fflush(stdin);
		
		printf("\n\nDatos modificados correctamente.\n");
		
	} else if(cedulaB < Arbol->cedula){
		return buscar_En_Arbol_cliente(Arbol->izq,cedulaB);
	} else {
		return buscar_En_Arbol_cliente(Arbol->der,cedulaB);
	}
}

bool buscar_En_Arbol_cliente(NodoCliente *Arbol,int cedulaB){
	if(Arbol==NULL){
		return false;
	}else if(Arbol->cedula == cedulaB){
		return true;
	}else if(cedulaB < Arbol->cedula){
		return buscar_En_Arbol_cliente(Arbol->izq,cedulaB);
	}else {
		return buscar_En_Arbol_cliente(Arbol->der,cedulaB);
	}
}

void eliminar_cliente(NodoCliente *arbol,int cedulaE){
	if(arbol==NULL){
		return;
	} else if(cedulaE < arbol->cedula){
		eliminar_cliente(arbol->izq,cedulaE);
	} else if(cedulaE > arbol->cedula){
		eliminar_cliente(arbol->der,cedulaE);
	}else {
		
	}
}

NodoCliente *tieneizquierdo(NodoCliente *arbol){
	if(arbol == NULL){
		return NULL;
	}
	
	if(arbol->izq){
		return tieneizquierdo(arbol->izq);
	}else {
		return arbol;
	}
}

void reemplazar(NodoCliente *arbol,NodoCliente *nuevonodo){
	if(arbol->padre){
		if(arbol->cedula == arbol->padre->izq->cedula){
			arbol->padre->izq = nuevonodo;
		}
		else if (arbol->cedula == arbol->padre->der->cedula){
			arbol->padre->der = nuevonodo;
		}
	}
	if(nuevonodo){
		nuevonodo->padre = arbol->padre;
	}
}

void eliminar_nodo_cliente(NodoCliente * nodoparaborrar){
	if(nodoparaborrar->izq && nodoparaborrar->der){
		NodoCliente *menor = tieneizquierdo(nodoparaborrar->der);
		nodoparaborrar->cedula = menor->cedula;
		*(nodoparaborrar->direccion) = *(menor->direccion);
		*(nodoparaborrar->nombre) = *(menor->nombre);
		nodoparaborrar->puntos = menor->puntos;
		*(nodoparaborrar->telefono) = *(menor->telefono);
		eliminar_nodo_cliente(menor);
	}
	else if(nodoparaborrar->izq){
		reemplazar(nodoparaborrar,nodoparaborrar->izq);
		free(nodoparaborrar); //destruir el nodo
	}
	else if(nodoparaborrar->der){
		reemplazar(nodoparaborrar,nodoparaborrar->der);
		free(nodoparaborrar); //destruir el nodo
	}
	else {
		reemplazar(nodoparaborrar,NULL);
		free(nodoparaborrar);
	}
}

void MenuFacturas(){
	
	int opcion;
	
	do{
		system("cls"); //limpia la pantalla
		printf("*** GESTION DE FACTURAS ***\n\n"); //titulo del proyecto
		
		printf("1. Crear factura.\n");
		printf("2. Mostrar facturas.\n");;
		printf("3. regresar.\n\n");
		
		printf("Elija una opcion : ");
		scanf("%d",&opcion);
		switch(opcion){
		case 1:
			Nueva_Factura();
			break;
		case 2:
			MostrarFacturas();
			printf("\n");
			system("pause");
			break;
		case 3:
			menu_Principal();
			break;
			
		default:
			printf("\n No se reconoce su peticion. vuelva a intentarlo. \n");
			system("pause");
		}
	} while(opcion!=3);
	
	
}

void Nueva_Factura(){
	
	printf("\n\nNUEVA FACTURA");
	
	
	//BUSCAR CLIENTE
	char intentarbuscar = 'n';
	bool clienteEncontrado = false;
	NodoCliente *Nodoclien;
	
	do{
		fflush(stdin);
		printf("\nIngrese la cedula del cliente : ");int cedu;
		scanf("%d",&cedu);
		
		Nodoclien = buscar_cliente_para_factura(ArbolCliente,cedu);
		
		if(Nodoclien!=NULL){
			intentarbuscar = 'n';
			printf("\nNOMBRE DEL CLIENTE : %sDIRECCION : %d\tCEDULA : %d",Nodoclien->nombre,Nodoclien->direccion,Nodoclien->cedula);
			clienteEncontrado = true;
		}else {
			printf("\nno se ha podido encontrar el cliente. Desar volver a intentarlo ? (s. Si - n. No) : ");
			scanf("%c",&intentarbuscar);
			fflush(stdin);
			clienteEncontrado = false;
		}
		
	} while(intentarbuscar=='s');
	
	if(clienteEncontrado){
		NodoFactura *nuevonfac = (NodoFactura*)malloc(sizeof(NodoFactura));
		
		nuevonfac->id = Cont_facturas;
		nuevonfac->cedula_cliente = Nodoclien->cedula;
		*(nuevonfac->nombre_cliente)= *(Nodoclien->nombre);
		
		//combustible
		//1 corriente , 2 diesel 3 gas natural
		int combustible;
		do{
			printf("\n. que combustible desea llevar?  1. corriente	 2. diesel	 3. gas natural : "); scanf("%d",&combustible);
			
			if(combustible!=1 && combustible!=2 && combustible!=3){
				printf("\n no se reconoce su peticion.");
			}
			
		} while(combustible!=1 && combustible!=2 && combustible!=3);
		
		nuevonfac->Combustible=combustible;
		int valor;
		printf("\n Cuanto va a tanquear ? (ingrese el valor que desee ingresar) : ");scanf("%d",&valor);
		nuevonfac->valor = valor;
		float gal; //calcular los galones
		
		switch(combustible){
		case 1:
			gal = valor/ValorCorriente;
			ExistenciaValorCorriente = ExistenciaValorCorriente - valor;
			break;
		case 2:
			gal = valor/ValorDiesel;
			ExistenciaValorDiesel = ExistenciaValorDiesel - valor;
			break;
		case 3:
			gal = valor/ValorGasNatural;
			ExistenciaValorGas = ExistenciaValorGas - valor;
			break;
		}
		
		printf("\n Galones : %.3f",gal);
		
		nuevonfac->galones = gal;
		
		nuevonfac->sig = Listafactura;
		
		Listafactura=nuevonfac;
		int puntos = 0;
		puntos = valor/200;
		printf("\n por su compra usted acomula puntos (1 por cada 200 pesos) sus puntos para esta venta son : %d",puntos);
		int pactuales = Nodoclien->puntos;
		Nodoclien->puntos = pactuales + puntos;
		Cont_facturas++;
		printf("\n\n *** La factura se ha creado satisfactoriamente *** \n");
	}
	
	system("pause");
	MenuFacturas();
}

NodoCliente* buscar_cliente_para_factura (NodoCliente *Arbol,int cedulaB){
	if(Arbol==NULL){
		return NULL;
	}else if(Arbol->cedula == cedulaB){
		return Arbol;
	}else if(cedulaB < Arbol->cedula){
		return buscar_cliente_para_factura(Arbol->izq,cedulaB);
	}else {
		return buscar_cliente_para_factura(Arbol->der,cedulaB);
	}
}

void MostrarFacturas(){
	
	system("cls");
	printf("LISTADO DE FACTURAS");
	NodoFactura* aux = Listafactura;
	for(int i = 0; i < Cont_facturas;i++){
		int idfact = aux->id;
		fflush(stdin);
		printf("----------------------------------------------------------\n");
		printf("ID FACTURA : %d",aux->id);
		fflush(stdin);
		printf("\nNOMBRE : %s\n",aux->nombre_cliente);
		printf("CEDULA : %d\n",aux->cedula_cliente);
		
		int comb = aux->Combustible;
		
		switch(comb){
		case 1:
			printf("COMBUSTIBLE : CORRIENTE \n");
			break;
		case 2:
			printf("COMBUSTIBLE : DIESEL \n");
			break;
		case 3:
			printf("COMBUSTIBLE : GAS NATURAL \n");
			break;
		}
		
		printf("VALOR : %d\n",aux->valor);
		printf("GALONES : %.3f\n",aux->galones);
		printf("\n===================================================\n\n");
		aux=aux->sig;
	}
	
}


void venderGasolina(){
	int opc;
	do{
		printf("\n. 1. venta sin factura	2. venta con factura : ");scanf("%d",&opc);
		if(opc == 1){
			int combustible;
			do{
				printf("\n. que combustible desea llevar?  1. corriente	 2. diesel	 3. gas natural : "); scanf("%d",&combustible);
				
				if(combustible!=1 && combustible!=2 && combustible!=3){
					printf("\n no se reconoce su peticion.");
				}
				
			} while(combustible!=1 && combustible!=2 && combustible!=3);
			
			int valor;
			printf("\n. Valor de compra :  ");scanf("%d",&valor);
			float gal;
			switch(combustible){
			case 1:
				gal = valor/ValorCorriente;
				ExistenciaValorCorriente = ExistenciaValorCorriente - valor;
				break;
			case 2:
				gal = valor/ValorDiesel;
				ExistenciaValorDiesel = ExistenciaValorDiesel - valor;
				break;
			case 3:
				gal = valor/ValorGasNatural;
				ExistenciaValorGas = ExistenciaValorGas - valor;
				break;
			}
			
			printf("\n Galones : %.3f",gal);
			printf("\n *** Gracias por su compra ***");
		} else if(opc==2){
			Nueva_Factura();
		}
	} while(opc!=1 && opc!=2);
	
}
void ComprarGasolina(){
	int combustible;
	do{
		printf("\n. que combustible va a comprar  1. corriente	 2. diesel	 3. gas natural : "); scanf("%d",&combustible);
		
		if(combustible!=1 && combustible!=2 && combustible!=3){
			printf("\n no se reconoce su peticion.");
		}
		
	} while(combustible!=1 && combustible!=2 && combustible!=3);
	
	int valor;
	printf("\n Valor que va a comprar : ");scanf("%d",&valor);
	
	switch(combustible){
	case 1:
		ExistenciaValorCorriente = ExistenciaValorCorriente + valor;
		break;
	case 2:
		ExistenciaValorDiesel = ExistenciaValorDiesel + valor;
		break;
	case 3:
		ExistenciaValorGas = ExistenciaValorGas + valor;
		break;
	}
	
	printf("\n Compra realizada correctamente. ");
}
