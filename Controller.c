#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "input.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */


int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	FILE *pArchivo = NULL;

	int rtn;
	rtn = 0;

	pArchivo=fopen(path,"r");
	if(pArchivo != NULL && pArrayListEmployee != NULL){

		if(ll_isEmpty(pArrayListEmployee)){ //Verifica si la linked list esta vacia para cargar los nuevos elementos

			if(parser_EmployeeFromText(pArchivo , pArrayListEmployee)){

				rtn = 1;

			}
		}else{
			rtn = 2;
		}

	}

	fclose(pArchivo);

	return rtn;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE *pArchivo = NULL;

	int rtn;
	rtn = 0;

	pArchivo=fopen(path,"rb");

	if(pArchivo != NULL && pArrayListEmployee != NULL){
		if(!ll_isEmpty(pArrayListEmployee)){
			if(parser_EmployeeFromBinary(pArchivo , pArrayListEmployee)){

				rtn=1;
			}
		}

	}

	fclose(pArchivo);

    return rtn;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	Employee* pEmpleado;
	pEmpleado = employee_new();

	int id;
	id = employee_getNewId(pArrayListEmployee); //Obtengo nuevo id

	int rtn = 0;
	char nombre[50];
	int horasTrabajadas;
	int sueldo;

	if(employee_requestData(nombre, &horasTrabajadas, &sueldo)){
		SetParametros(pEmpleado, id, nombre, horasTrabajadas, sueldo);

		if(pEmpleado != NULL){
			ll_add(pArrayListEmployee, pEmpleado);
			rtn = 1;
		}


	}


    return rtn;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int rtn = 0;
	rtn = 0;
	int id;
	int index = 0;
	int idMayor;
	int option;

	int flag = 0;
	Employee* pEmpleado;
	Employee* auxEmpleado;
	auxEmpleado = NULL;
	pEmpleado = employee_new();

	if(pArrayListEmployee != NULL)
	{
		if(!ll_isEmpty(pArrayListEmployee)){

			if(CargarUnEntero("Desea mostrar la lista de empleados? (1=SI 0=NO)",0,1)){
				controller_ListEmployee(pArrayListEmployee);
			}

			idMayor = controller_mayorId(pArrayListEmployee);
			id = CargarUnEntero("Ingrese id del empleado que desea modificar:\n",0,idMayor);
			index = employee_getIndexById(pArrayListEmployee, id);
			if(index!=-1)
			{
				pEmpleado = (Employee*) ll_get(pArrayListEmployee, index);

				printf("| %4s | %18s | %20s | %20s |\n", "ID:", "NOMBRE", "HORAS TRABAJADAS:", "SALARIO:");
				employee_showOne(pEmpleado);
				auxEmpleado = pEmpleado;

				do{
					option=CargarUnEntero("Ingrese campo a modificar\n1. Nombre\n2.Horas trabajadas\n3. Sueldo\n0. Salir",0,3);
					switch(option)
					{
						case 1:
							CargarUnaCadena("Ingrese nombre:\n", auxEmpleado->nombre);
							flag = 1;
							break;

						case 2:
							auxEmpleado->horasTrabajadas = CargarUnEntero("Ingrese cantidad de horas trabajadas",0,1000);
							flag = 1;
							break;

						case 3:
							auxEmpleado->sueldo = CargarUnEntero("Ingrese sueldo:",0,999999);
							flag = 1;
							break;

					}
				}while(option!=0);
				if(flag == 1){
					if(CargarUnEntero("Desea guardar los cambios realizados? (1=SI 0=NO)",0,1)){
						rtn = 1;
						pEmpleado = auxEmpleado;
					}
				}
			}else{
				if(CargarUnEntero("Dato no encontrado\nDesea continuar buscando? (1=SI 0=NO)",0,1))
				{
					controller_editEmployee(pArrayListEmployee);
				}
			}
		}else{
			rtn = 2;
		}
	}
    return rtn;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	Employee* pEmpleado;
	pEmpleado = NULL;
	int id;
	int idMayor;
	int rtn = 0;
	int index;

	if(pArrayListEmployee != NULL)
		{
			if(!ll_isEmpty(pArrayListEmployee)){

				if(CargarUnEntero("Desea mostrar la lista de empleados? (1=SI 0=NO)",0,1)){
					controller_ListEmployee(pArrayListEmployee);
				}
				idMayor = controller_mayorId(pArrayListEmployee);
				id = CargarUnEntero("Ingrese id del empleado que desea eliminar:\n",0,idMayor);
				index = employee_getIndexById(pArrayListEmployee, id);
				if(index != -1){
					pEmpleado = (Employee*) ll_get(pArrayListEmployee, index);
					if(pEmpleado!=NULL)
					{
						printf("| %4s | %18s | %20s | %20s |\n", "ID:", "NOMBRE", "HORAS TRABAJADAS", "SALARIO");
						employee_showOne(pEmpleado);

						if(CargarUnEntero("Esta seguro que desea eliminar el empleado seleccionado? (1=SI 0=NO): \n",0,1)){
							ll_remove(pArrayListEmployee, index);
							rtn = 1;
						}

					}
				}else{
					if(CargarUnEntero("Dato no encontrado\nDesea continuar buscando? (1=SI 0=NO)",0,1))
					{
						controller_removeEmployee(pArrayListEmployee);
					}
				}

			}else{
				rtn = 2;
			}
		}

    return rtn;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return (-1) array vacio; (0) accion cancelada, (1) exito
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int rtn = -1;
    int i;
    int cont=0;
    int len;
    Employee* pEmpleado;
    pEmpleado = NULL;
    if(pArrayListEmployee!=NULL){
    	len = ll_len(pArrayListEmployee);
    	printf("| %4s | %18s | %20s | %20s |\n", "ID:", "NOMBRE", "HORAS TRABAJADAS", "SALARIO");
    	for(i=0; i<len; i++){

        	cont++;
        	pEmpleado=ll_get(pArrayListEmployee, i);

        	if(pEmpleado != NULL){

        		rtn=1;
        		employee_showOne(pEmpleado);
        	}
        	if(cont==100){
        		cont=0;
        		system("pause");
        	}

        }
    }else{
    	rtn=-1;
    }



	return rtn;
}

/** \brief Ordenar empleados
 *
 * \param puntero al array con la lista de empleados cargada
 * \param pArrayListEmployee LinkedList*
 * \return (-1) array vacio; (0) accion cancelada, (1) exito
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int rtn = -1;
	int option;
	int criterio;
	if(pArrayListEmployee!=NULL)
	{
		if(!ll_isEmpty(pArrayListEmployee))
		{

			option=CargarUnEntero("Ingrese campo por el que desea ordenar:\n1-Id\n2-Nombre\n3-Horas Trabajadas\n4-Sueldo\n0-Salir\n",0,4);


			if(option!=-1)
			{
				switch(option){

				case 1:
						criterio = CargarUnEntero("Ingrese criterio de ordenacion: (1-Ascendente 0-Descendente):\n",0,1);
						if(criterio!=-1){
							rtn = ll_sort(pArrayListEmployee, employee_sortById, criterio);
						}
					break;

				case 2:
						criterio = CargarUnEntero("Ingrese criterio de ordenacion: (1-Ascendente 0-Descendente):\n",0,1);
						if(criterio!=-1){
							rtn = ll_sort(pArrayListEmployee, employee_sortByName, criterio);
						}

					break;

				case 3:
						criterio = CargarUnEntero("Ingrese criterio de ordenacion: (1-Ascendente 0-Descendente):\n",0,1);
						if(criterio!=-1){
							rtn = ll_sort(pArrayListEmployee, employee_sortByHours, criterio);
						}
					break;

				case 4:
						criterio = CargarUnEntero("Ingrese criterio de ordenacion: (1-Ascendente 0-Descendente):\n",0,1);
						if(criterio!=-1){
							rtn = ll_sort(pArrayListEmployee, employee_sortBySalary, criterio);
						}
					break;
				case 0:
					rtn=0;
					break;
				}

			}
		}

	}

    return rtn;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pArchivo;
	Employee* pEmpleado;
	int rtn=0;
	int len;
	int id;
	char nombre[50];
	int horasTrabajadas;
	int sueldo;

	if(path != NULL && pArrayListEmployee!=NULL){

		len = ll_len(pArrayListEmployee);
		pArchivo = fopen(path,"w");
		if(pArchivo!= NULL){
			fprintf(pArchivo, "ID,NOMBRE,HORAS TRABAJADAS,SUELDO\n");
			for(int i=0; i<len; i++){

				pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);
				employee_getId(pEmpleado, &id);
				employee_getNombre(pEmpleado, nombre);
				employee_getHorasTrabajadas(pEmpleado, &horasTrabajadas);
				employee_getSueldo(pEmpleado, &sueldo);
				fprintf(pArchivo,"%d,%s,%d,%d\n", id, nombre, horasTrabajadas, sueldo);

			}
			rtn = 1;
		}
		fclose(pArchivo);
	}
    return rtn;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pArchivo;
	Employee* pEmpleado;
	pEmpleado = NULL;
	int rtn=0;
	int len;


	if(path != NULL && pArrayListEmployee!=NULL){

		len = ll_len(pArrayListEmployee);
		pArchivo = fopen(path,"w");
		if(pArchivo!= NULL){

			fprintf(pArchivo, "ID,NOMBRE,HORAS TRABAJADAS,SUELDO\n");
			for(int i=0; i<len; i++){

				pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);
				fwrite(pArchivo,sizeof(Employee),1,pArchivo);

			}
			rtn = 1;
		}
		fclose(pArchivo);
	}
    return rtn;
}




int controller_mayorId(LinkedList* pArrayListEmployee)
{
    int rtn = 0;
    if(pArrayListEmployee != NULL)
    {
        int len;
        int i;
        int b = 0; //bandera de primer ingreso

        Employee* pEmpleado;

        len = ll_len(pArrayListEmployee);

        for(i=0; i<len; i++)
        {
            pEmpleado = (Employee*) ll_get(pArrayListEmployee, i);

            if(b == 0 || rtn < pEmpleado->id)
            {
                rtn = pEmpleado->id;
                b = 1;
            }
        }
    }
    return rtn;
}


