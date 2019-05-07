#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include<conio.h>
#define MAX_NUM_ALUMNOS 200

/*#define NOMBRE 1
#define APELLIDO 2
#define MATRICULA 3
#define NOTA1 4
#define NOTA2 5*/
typedef struct
{
char nombre[51];
char apellido[51];
char matricula[51];
float nota1;
float nota2;
}alumno;


alumno PedirAlumno(); 
void NuevoAlumno(alumno ficha[], int num,alumno c);
void ImprimirCabecera();
void ImprimirPie();
void MostrarFicha(alumno ficha[], int num);
void MostrarAlumno(alumno c);
int LeerFicha(char fichero[], alumno ficha[], int num);
int LeerAlumno(FILE* f, alumno c);
int GuardarFicha(char fichero[],alumno ficha[], int num);
int GuardarAlumno(FILE* f,alumno c);


void main()
{
	alumno ficha [MAX_NUM_ALUMNOS];
	int num_alumnos=0;
	int opcion=0;
	alumno c;
	int n;
	FILE *f;
	f=fopen("Ficha.txt","a");
	LeerFicha("Ficha.txt",ficha,num_alumnos);
	do
	{
		opcion=Menu();
		switch(opcion)
		{
			case 0 : printf("Saliendo del programa\n");
			break;
			case 1: c=PedirAlumno (); //llamadas a funciones
				NuevoAlumno(ficha,num_alumnos,c); 
			break;
			case 2: MostrarFicha (ficha,num_alumnos); 
			break;
		/*	case 3: Buscar(ficha,num_alumnos); 
			break;
			case 4: n=MenuCampo();
			{
				OrdenarFicha(ficha,num_alumnos,n); 
				MostrarFicha(ficha,num_alumnos); 
			}
			break;
			case 5: MostrarFicha(ficha,num_alumnos);
			{
				printf("Numero de alumnos a eliminar:\n");
				scanf("%d",&n);
				fflush(stdin);
				EliminarAlumno(ficha,&num_alumnos,n); 
				MostrarFicha(ficha,num_alumnos); 
			}
			break;*/
		}
		printf("Pulse una tecla para continuar...\n");
		getch();
		system("cls");
	}
	while(opcion!=0 || opcion<=6);
	GuardarFicha("Ficha.txt",ficha,num_alumnos);
	} //Fin de la funcion principal donde llamamos a las funciones anteriormente definidas




int Menu()
{
int opcion=-1;

do
{
printf(".........Menu Principal.......\n");
printf("0-Salir\n");
printf("1-Nuevo alumno\n");
printf("2-Mostrar ficha\n");
printf("3-Buscar Alumno\n");
printf("4-Ordenar fichas\n");
printf("5-Eliminar alumno\n");
printf("Elija una opcion: ");
fflush(stdin);
scanf("%d", &opcion);
}
while(opcion<0 || opcion>6);
return opcion;
}



//Se pide un alumno que se devuelve en return
alumno PedirAlumno()
{
	alumno c;
	fflush(stdin);
	printf("Nombre: ");
	gets(c.nombre);
	printf("Apellido: ");
	gets(c.apellido);
	printf("Matricula: ");
	gets(c.matricula);
	printf("Nota1: ");
	scanf("%f", &c.nota1);
	printf("Nota2: ");
	scanf("%f", &c.nota2);
	fflush(stdin);
	return c;
}


void NuevoAlumno(alumno ficha[], int num, alumno c)
{
	int n=num;
	if (n<MAX_NUM_ALUMNOS)
	{
		ficha[n]=c;
		n++;
	}
	num=n;
}

int LeerFicha(char fichero[],alumno ficha[],int num)
{
	alumno alumn;
	int n=0;
	FILE* f=fopen(fichero,"r");
	if(f==NULL)
		return 0;
	while(LeerAlumno(f,alumn))
	{
		ficha[n]=alumn;
		n++;
	}
	num=n;
	fclose(f);
	return 1;
}

//funcion que nos lee el alumno introducido
int LeerAlumno(FILE* f,alumno c)
{
	if(f==NULL)
	return 0;
	if(5==fscanf(f,"%s %s %s %f %f", c.nombre,c.apellido,c.matricula,&c.nota1,&c.nota2))
	return 1;
	return 0;
}

void MostrarFicha(alumno ficha[],int num)
{
	int i;
	ImprimirCabecera();
	for(i=0;i<num;i++)
	{
		printf("alumno %d: ",i);
		MostrarAlumno(ficha[i]);
	}
	ImprimirPie();
}

void ImprimirCabecera()
{
	printf("******************************************************\n");
	printf("#: %-10s %-10s %-10s %-10s %-10s\n","Nombre","Apellido","Matricula", "Nota1", "Nota2");
	printf("******************************************************\n");
}


void ImprimirPie()
{
	printf("******************************************************\n");
}


//funcion que imprime todos los campos del alumno c
void MostrarAlumno(alumno c)
{
	printf("%-10s %-10s %-10s %-2f %-2f \n",c.nombre,c.apellido,c.matricula,c.nota1,c.nota2);
}


int GuardarFicha(char fichero[],alumno ficha[],int num)
{	
	int i;
	FILE* f=fopen(fichero, "a");
	if(f==NULL)
	return 0;
	for(i=0;i<num;i++)
		{
			GuardarAlumno(f,ficha[i]);
		}
	fclose(f);
	return 1;
}


//funcion que nos guarda el alumno en el fichero
int GuardarAlumno(FILE* f ,alumno c)
{
	if(f==NULL)
	return 0;
	if(5==fprintf(f,"%s %s %s %f %f\n", c.nombre,c.apellido,c.matricula,c.nota1,c.nota2))
	return 1;
	
	return 0;
}
