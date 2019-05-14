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
void NuevoAlumno(alumno ficha[], int* num,alumno c);
void MostrarFicha(alumno ficha[], int num);
void MostrarAlumno(alumno c);
int LeerFicha(char fichero[], alumno ficha[], int* num);
int LeerAlumno(FILE* f, alumno* c);
int GuardarFicha(char fichero[],alumno ficha[], int num);
int GuardarAlumno(FILE* f,alumno c);
void Buscar(alumno ficha[], int num);
int MenuCampo();
void BuscarAlumno(alumno ficha[], int num,alumno c, int campo);
int Comparar(alumno c1, alumno c2,int campo);
void OrdenarFicha(alumno ficha[],int num, int campo);
void Intercambia (alumno* c1, alumno* c2);







void main()
{
	alumno ficha [MAX_NUM_ALUMNOS];
	int num_alumnos=0;
	int opcion=0;
	alumno c;
	int n;
	FILE *f;
	f=fopen("Ficha.txt","a");
	LeerFicha("Ficha.txt",ficha,&num_alumnos);
	do
	{
		opcion=Menu();
		switch(opcion)
		{
			case 0 : printf("Saliendo del programa\n");
			break;
			case 1: c=PedirAlumno (); //llamadas a funciones
				NuevoAlumno(ficha,&num_alumnos,c); 
			break;
			case 2: MostrarFicha (ficha,num_alumnos); 
			break;
			case 3: Buscar(ficha,num_alumnos); 
			break;
			case 4: n=MenuCampo();
			{
				OrdenarFicha(ficha,num_alumnos,n); 
				MostrarFicha(ficha,num_alumnos); 
			}
			break;
		
		}
		printf("Pulse una tecla para continuar...\n");
		getch();
		system("cls");
	}
	while(opcion!=0 || opcion<=6);
	GuardarFicha("Ficha.txt",ficha,num_alumnos);
	} //Fin de la funcion principal donde llamamos a las funciones anteriormente definidas



//Función que te muestra el menú
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


//Función que pide que introduzcas los datos del alumno
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

//función que calcula el número de alumnos que se han introducido
void NuevoAlumno(alumno ficha[], int* num, alumno c)
{
	int n=*num;
	if (n<MAX_NUM_ALUMNOS)
	{
		ficha[n]=c;
		n++;
	}
	*num=n;
}


//función que lee el fichero donde se han almacenado los datos del alumno
int LeerFicha(char fichero[],alumno ficha[],int* num)
{
	alumno alumn;
	int n=0;
	FILE* f=fopen(fichero,"r");
	if(f==NULL)
		return 0;
	while(LeerAlumno(f,&alumn))
	{
		ficha[n]=alumn;
		n++;
	}
	*num=n;
	fclose(f);
	return 1;
}


//funcion que nos lee el alumno introducido
int LeerAlumno(FILE* f,alumno* c)
{
	if(f==NULL)
		return 0;
	if(5==fscanf(f,"%s %s %s %f %f", c->nombre,c->apellido,c->matricula,&c->nota1,&c->nota2))
		return 1;
	return 0;
}


//función que imprime los datos del alumno
void MostrarFicha(alumno ficha[],int num)
{
	int i;
	printf("************************************************************\n");
	printf(":	%-10s %-10s %-10s %-10s %-10s\n","Nombre","Apellido","Matricula", "Nota1", "Nota2");
	printf("************************************************************\n");	
	for(i=0;i<num;i++)
	{
		printf("alumno %d: ",i+1);
		MostrarAlumno(ficha[i]);
	}
	printf("***********************************************************\n");
}


//funcion que imprime todos los datos del alumno c
void MostrarAlumno(alumno c)
{
	printf("%-10s %-10s %-10s %-.2f %-.2f \n",c.nombre,c.apellido,c.matricula,c.nota1,c.nota2);
}


//función que guarda los datos de la ficha en el fichero
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


//funcion que nos guarda el alumno en la ficha del fichero
int GuardarAlumno(FILE* f ,alumno c)
{
	if(f==NULL)
		return 0;
	if(5==fprintf(f,"%s %s %s %f %f\n", c.nombre,c.apellido,c.matricula,c.nota1,c.nota2))
		return 1;
	return 0;
}


void Buscar(alumno ficha[],int num)
{
	alumno c;
	int campo=MenuCampo();
	switch(campo)
	{
		case 1: printf("Nombre a buscar: ");
			scanf("%s",c.nombre);
		break;
		case 2: printf("Apellido a buscar: ");
			scanf("%s",c.apellido);
		fflush(stdin);
		break;
		case 3: printf("Matricula a buscar: ");
			scanf("%s",c.matricula);
		fflush(stdin);
		break;
		case 4: printf("Nota1 a buscar: ");
			scanf("%f",&c.nota1);
		fflush(stdin);
		break;
		case 5: printf("Nota2 a buscar: ");
			scanf("%f",&c.nota2);
		fflush(stdin);
		break;
	}
	BuscarAlumno(ficha,num,c,campo);
}

int MenuCampo()
{
	int opcion=-1;
	printf(".........Seleccione Campo.....\n");
	printf("%d-Nombre\n",1);
	printf("%d-Apellido\n",2);
	printf("%d-Matricula\n",3);
	printf("%d-Nota1\n",4);
	printf("%d-Nota2\n",5);
	do
	{
	printf("Elija una opcion: ");
	fflush(stdin);
	scanf("%d",&opcion);
	}
	while(opcion<1 || opcion>5);
	return opcion;
}

//funcion que nos permite buscar a un alumno
void BuscarAlumno(alumno ficha[],int num,alumno c,int campo)
{
	int i;
	printf("************************************************************\n");
	printf(":	%-10s %-10s %-10s %-10s %-10s\n","Nombre","Apellido","Matricula", "Nota1", "Nota2");
	printf("************************************************************\n");	
	for (i=0;i<num;i++)
	{
		if(0==Comparar(ficha[i],c,campo))
		{
			printf("%d: ",i);
			MostrarAlumno(ficha[i]);
		}
	}
	printf("***********************************************************\n");
}


//funcion que nos compara varios alumnos
int Comparar(alumno c1, alumno c2,int campo)
{
	if(campo==1)
		return strcmp(c1.nombre,c2.nombre);
		
	if(campo==2)
		return strcmp(c1.apellido,c2.apellido);

	if(campo==3)
	{
		if(c1.matricula<c2.matricula)
			return -1;
		else if(c1.matricula>c2.matricula)
			return 1;
		else
			return 0;
	}
	
	if(campo==4)
	{
		if(c1.nota1<c2.nota1)
			return -1;
		else if(c1.nota1>c2.nota1)
			return 1;
		else
			return 0;
	}
	
	if(campo==5)
	{
		if(c1.nota2<c2.nota2)
			return -1;
		else if(c1.nota2>c2.nota2)
			return 1;
		else
			return 0;
	}

return -1;
}


void OrdenarFicha(alumno ficha[],int num,int campo)
{
	int i,j;
	for(i=0;i<num-1;i++)
	{
		for(j=i+1;j<num;j++)
		{
			if(0<Comparar(ficha[i], ficha[j], campo))
			Intercambia(&ficha[i],&ficha[j]);
		}
	}
}

//funcion que nos intercambia varios alumnos
void Intercambia(alumno* c1,alumno* c2)
{
	alumno aux=*c1;
	*c1=*c2;
	*c2=aux;
}

