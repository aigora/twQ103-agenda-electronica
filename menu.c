#include<stdio.h>
#define N 100

int main()
{
	float notas[N];
	char opcion;
	int i;

	do
	{		
	fflush(stdin);
	printf("Buenos dias, bienvenido/a a su cuaderno de profesor digital\n");
	printf("Que desea hacer? \n");
	printf(" A - Introducir alumno \n B - introducir notas \n C - Buscar alumnos \n D - Eliminar alumnos\n E - Salir del programa \n");
	scanf("%c", &opcion);
	
	
	switch(opcion)
	{
		case'a': //se necesitar�n ficheros
		{

		}
		break;
		case'b': //para acumular las notas utilizaremos vectores
		{
	
		}
		break;
		case'c': //se necesitar�n ficheros
		{
			printf("Qu� alumno quieres buscar?");
		}
		break;
		case'd': //para eliminar alumnos, se necesitar�n ficheros
		{
	
		}
		break;
		case'e': //para salir del programa
		{
			printf("salimos del programa\n");	
		}
		break;
	}
	}
	while(opcion !='e');
}





