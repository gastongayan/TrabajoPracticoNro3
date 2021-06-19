#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
void employee_delete(Employee* pEmpleado);

int SetParametros(Employee* pEmpleado, int id, char* nombre, int horasTrabajadas, int sueldo);
int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_showOne(Employee* pEmpleado);
int employee_requestData(char nombre[], int* horasTrabajadas, int* sueldo);
int employee_getNewId(LinkedList* pArrayListEmployee);
int employee_getIndexById(LinkedList* pArrayListEmployee, int id);

int employee_sortById(void* pEmpleadoUno, void* pEmpleadoDos);
int employee_sortByName(void* pEmpleadoUno, void* pEmpleadoDos);
int employee_sortBySalary(void* pEmpleadoUno, void* pEmpleadoDos);
int employee_sortByHours(void* pEmpleadoUno, void* pEmpleadoDos);
#endif // employee_H_INCLUDED
