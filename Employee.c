
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "input.h"

Employee* employee_new()
{
	Employee* pEmpleado;
	pEmpleado = (Employee*) calloc(sizeof(Employee),1);
	return pEmpleado;
}

int employee_showOne(Employee* pEmpleado){

	int rtn;
	rtn=0;

	int id;
	char nombre[50];
	int horasTrabajadas;
	int sueldo;

	if(pEmpleado!=NULL){
		employee_getId(pEmpleado, &id);
		employee_getNombre(pEmpleado, nombre );
		employee_getHorasTrabajadas(pEmpleado, &horasTrabajadas);
		employee_getSueldo(pEmpleado, &sueldo);
		{
			printf("| %4d | %18s | %20d | %20d |\n", id, nombre, horasTrabajadas, sueldo);
			rtn=1;
		}

	}
	return rtn;
}
int SetParametros(Employee* pEmpleado, int id, char* nombre, int horasTrabajadas, int sueldo){

	int rtn=0;

	if(pEmpleado!=NULL){
		if(employee_setId(pEmpleado, id) &&	employee_setNombre(pEmpleado, nombre)&&	employee_setHorasTrabajadas(pEmpleado, horasTrabajadas)&& employee_setSueldo(pEmpleado, sueldo))
		{
			rtn=1;
		}else{
			employee_delete(pEmpleado);
			pEmpleado=NULL;
		}

	}
	return rtn;
}
void employee_delete(Employee* pEmpleado){

	if(pEmpleado != NULL)
	{
		free(pEmpleado);
	}

}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* pEmpleado;

	int id;
	int horasTrabajadas;
	int sueldo;

	pEmpleado = employee_new();

	if(pEmpleado!=NULL)
	{
		if(idStr!=NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
		{
			id=atoi(idStr);
			horasTrabajadas=atoi(horasTrabajadasStr);
			sueldo=atoi(sueldoStr);
			if(SetParametros(pEmpleado,id,nombreStr,horasTrabajadas,sueldo)==0){
				employee_delete(pEmpleado);
			}
		}





	}
	return pEmpleado;
}

int employee_setId(Employee* this,int id)
{
	int rtn;
	rtn=0;

	if(this != NULL && id>0)
	{

		this->id=id;
		rtn = 1;

	}
	return rtn;
}
int employee_getId(Employee* this,int* id)
{
    int rtn;
	rtn = 0;

    if(this != NULL && id != NULL)
    {
        *id = this->id;
        rtn = 1;
    }

    return rtn;
}
int employee_setNombre(Employee* this,char* nombre)
{
	int rtn;
	rtn=0;

	if(this != NULL && strlen(nombre)>0)
	{

		strcpy(this->nombre,nombre);
		rtn = 1;

	}
	return rtn;
}
int employee_getNombre(Employee* this,char* nombre)
{
    int rtn;
	rtn = 0;

    if(this != NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        rtn = 1;
    }

    return rtn;
}


int employee_setHorasTrabajadas(Employee* this, int horasTrabajadas)
{
	int rtn;
	rtn=0;

	if(this != NULL && horasTrabajadas>-1)
	{

		this->horasTrabajadas = horasTrabajadas;
		rtn = 1;

	}

	return rtn;
}
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int rtn;
    rtn = 0;

    if(this != NULL && horasTrabajadas != NULL)
    {
        *horasTrabajadas = this->horasTrabajadas;
        rtn = 1;
    }

    return rtn;
}


int employee_setSueldo(Employee* this, int sueldo)
{
	int rtn;
	rtn=0;

	if(this != NULL && sueldo>-1)
	{

		this->sueldo=sueldo;
		rtn = 1;

	}
	return rtn;
}


int employee_getSueldo(Employee* this,int* sueldo)
{
    int rtn;
    rtn = 0;

    if(this != NULL && sueldo != NULL)
    {
        *sueldo = this->sueldo;
        rtn = 1;
    }

    return rtn;
}



int employee_getNewId(LinkedList* pArrayListEmployee)
{
    int rtn = -1;
    if(pArrayListEmployee != NULL)
    {
        rtn = controller_mayorId(pArrayListEmployee);
        rtn++;
    }
    return rtn;
}
int employee_requestData(char nombre[], int* horasTrabajadas, int* sueldo){
	int rtn=0;
//validar
	CargarUnaCadena("Ingrese nombre del empleado:\n", nombre);
	*horasTrabajadas = CargarUnEntero("Ingrese cantidad de horas trabajadas:\n",0,1000);
	*sueldo=CargarUnEntero("Ingrese sueldo percibido:\n",0,999999);
	rtn = 1;
	return rtn;
}

int employee_getIndexById(LinkedList* pArrayListEmployee, int id)
{
	Employee* pEmpleado;
	pEmpleado = NULL;
	int rtn = -1;
	int len;
	int i;
	len = ll_len(pArrayListEmployee);

	for(i=0; i<len; i++){
		pEmpleado = (Employee*)ll_get(pArrayListEmployee, i);
		if(pEmpleado!=NULL)
		{
			if(pEmpleado->id == id){
				rtn = i;
				break;
			}
		}
	}
	return rtn;
}
int employee_sortById(void* pEmpleadoUno, void* pEmpleadoDos)
{
    int rtn = -1;
    int idUno;
    int idDos;

    Employee* e1=(Employee*) pEmpleadoUno;
    Employee* e2=(Employee*) pEmpleadoDos;
    employee_getId(e1, &idUno);
    employee_getId(e2, &idDos);

    if(idUno > idDos)
    {
        rtn = 1;
    }
    else
    {
        if(idUno == idDos)
        {
        	rtn = 0;
        }
    }

    return rtn;
}
int employee_sortByHours(void* pEmpleadoUno, void* pEmpleadoDos)
{
    int rtn = -1;
    int horaUno;
    int horaDos;

    Employee* e1=(Employee*) pEmpleadoUno;
    Employee* e2=(Employee*) pEmpleadoDos;
    employee_getHorasTrabajadas(e1, &horaUno);
    employee_getHorasTrabajadas(e2, &horaDos);

    if(horaUno > horaDos)
    {
        rtn = 1;
    }
    else
    {
        if(horaUno == horaDos)
        {
        	rtn = 0;
        }
    }

    return rtn;
}
int employee_sortBySalary(void* pEmpleadoUno, void* pEmpleadoDos)
{
    int rtn = -1;
    int sueldoUno;
    int sueldoDos;

    Employee* e1=(Employee*) pEmpleadoUno;
    Employee* e2=(Employee*) pEmpleadoDos;
    employee_getSueldo(e1, &sueldoUno);
    employee_getSueldo(e2, &sueldoDos);

    if(sueldoUno > sueldoDos)
    {
        rtn = 1;
    }
    else
    {
        if(sueldoUno == sueldoDos)
        {
        	rtn = 0;
        }
    }

    return rtn;
}
int employee_sortByName(void* pEmpleadoUno, void* pEmpleadoDos)
{
    int rtn = -1;
    char nombreUno[50];
    char nombreDos[50];

    Employee* e1=(Employee*) pEmpleadoUno;
    Employee* e2=(Employee*) pEmpleadoDos;
    employee_getNombre(e1, nombreUno);
    employee_getNombre(e2, nombreDos);

    rtn=strcmp(nombreUno,nombreDos);

    return rtn;
}
