#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int rtn=0;
	char id[5];
	char nombre[50];
	char horasTrabajadas[50];
	char sueldo[50];
	Employee* pEmpleado = NULL;

	if(pFile!=NULL && pArrayListEmployee!=NULL){

		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo); //Realizo la primera lectura para evitar encabezados

		while(!feof(pFile)){

			fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo);
			pEmpleado = employee_newParametros(id,nombre,horasTrabajadas,sueldo);

			if(!ll_add(pArrayListEmployee, pEmpleado)){

				rtn= -1;
			}





		}
	}

    return rtn;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int rtn=0;
	int b=0;

	Employee* pEmpleado;
	pEmpleado = NULL;

	if(pFile!=NULL && pArrayListEmployee != NULL){


		while(!feof(pFile)){

			pEmpleado = employee_new();

			if(pEmpleado!=NULL){

				fread(pEmpleado, sizeof(Employee), 1, pFile);
				rtn=1;
				ll_add(pArrayListEmployee, pEmpleado);
			}


		}
	}else{
		rtn=-1;
	}
	fclose(pFile);

    return rtn; //Devuelve -1 si hubo error en la carga
}
