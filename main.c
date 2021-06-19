#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "input.h"
/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.dat (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.bin (modo binario).
    10. Salir
*****************************************************/



int main()
{

    setbuf(stdout,NULL);
    int rtn = 0;

    int flag = 0;
    LinkedList* listaEmpleados = ll_newLinkedList(); //Creacion de espacio en el heap
    int option = 0;



    do{
    	printf("MENU\n");
    	printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n2. Cargar los datos de los empleados desde el archivo data.dat (modo binario).\n3. Alta de empleado\n4. Modificar datos de empleado\n5. Baja de empleado\n6. Listar empleados\n7. Ordenar empleados\n8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n9. Guardar los datos de los empleados en el archivo data.bin (modo binario).\n10. Salir\n\n");
    	option = CargarUnEntero("Ingrese una opcion", 1, 10);
        switch(option)
        {
        case 1:

            rtn = controller_loadFromText("data.csv", listaEmpleados);

            if(rtn != -1){
            	switch (rtn){

            	case 0:

					printf("Error en carga de archivo.\n");
					break;

            	case 1:

					printf("Archivo cargado\n");
					system("pause");
					flag=1;
					break;

				case 2:

					printf("La lista se encuentra cargada.\n");
					break;
            	}
			}else{
				printf("La lista se encuentra cargada.\n");
			}

        break;

        case 2:
        	if(flag == 1){
        		rtn = controller_loadFromBinary("data.bin", listaEmpleados);
					if(rtn != -1){
						switch (rtn){
							case 1:

								printf("Archivo cargado\n");
								flag = 1;
								break;

							case 0:

								printf("Error en carga de archivo.\n");
								break;

							case 2:

								printf("La lista ya se encuentra cargada.\n");
								break;

						}
					}else{
						printf("Error en carga de archivos.\n");
					}

        	}


			break;

        case 3:

        	rtn = controller_addEmployee(listaEmpleados);

        	break;

        case 4: //4. Modificar datos de empleado

        	rtn = controller_editEmployee(listaEmpleados);
        	if(flag==1){
        		switch(rtn){

				case 0:
					printf("No se realizaron cambios en el empleado\n");
					system("pause");
					break;

				case 1:
					printf("Datos guardados con exito\n");
					system("pause");
					break;

				case 2:
					printf("Lista vacia\n");
					system("pause");
					break;
				}
        	}





            	break;


		case 5: //5. Baja de empleado
			rtn = controller_removeEmployee(listaEmpleados);

        	switch(rtn){
        	//rtn devuelve (1) en caso de borrado con exito, (0) si cancela el usuario y (2) en caso de array vacio
        	case 0:
        		printf("BAJA CANCELADA POR USUARIO\n");
        		system("pause");
        		break;

        	case 1:
        		printf("Datos borrados con exito\n");
        		system("pause");
        		break;

        	case 2:
        		printf("LISTA VACIA\n");
        		system("pause");
				break;
        	}
        	break;
		case 6: //6. Listar empleados

			if(!controller_ListEmployee(listaEmpleados))
			{
				printf("Error en impresion de datos, la lista no se encuentra cargada\n");
				system("pause");
			}
				break;

		case 7: //7. Ordenar empleados
			if(flag==1){
				rtn= controller_sortEmployee(listaEmpleados);

				switch(rtn){
				//rtn devuelve (1) en caso de ordenado con exito, (0) si cancela el usuario y (-1) en caso de array vacio
				case 1:
					printf("LISTA ORDENADA\n");
					system("pause");
					break;

				case 0:
					printf("ACCION CANCELADA POR USUARIO\n");
					system("pause");
					break;

				case -1:
					printf("Error, lista vacia\n");
					system("pause");
					break;
				}
			}
			break;

		case 8: //8. Guardar los datos de los empleados en el archivo data.csv (modo texto).

			if(controller_saveAsText("data.csv", listaEmpleados)){
				printf("DATOS GUARDADOS EN ARCHIVO CSV CON EXITO\n");
				system("pause");
			}else{
				printf("Error, lista vacia.\n");
				system("pause");
			}

			break;

		case 9: //9. Guardar los datos de los empleados en el archivo data.csv (modo binario).

			if(controller_saveAsBinary("data.bin", listaEmpleados)){
				printf("DATOS GUARDADOS EN ARCHIVO BINARIO CON EXITO\n");
				system("pause");
			}else{
				printf("Error, lista vacia.\n");
				system("pause");
			}

			break;

		case 10: //10. Salir

			printf("-----FIN DEL PROGRAMA-----");
			if(ll_deleteLinkedList(listaEmpleados))
			{
				printf("Borrado de cache exitoso");
			}
			break;
        }
    }while(option != 10);
    return 0;
}

