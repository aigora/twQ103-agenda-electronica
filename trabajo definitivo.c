#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include<conio.h>
#define MAX_NUM_ALUMNOS 200


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
void MostrarTodosAlumnos(alumno ficha[], int num);
int LeerTodosAlumnos(char fichero[], alumno ficha[], int* num);
int LeerAlumno(FILE* f, alumno* c);
int GuardarAlumno(FILE* f,alumno c);
void BuscarAlumno(alumno ficha[], int num);
int Menu2();
int CompararAlumnos(alumno c1, alumno c2,int campo);
void OrdenarAlumnos(alumno ficha[],int num, int campo);
void IntercambiaAlumnos(alumno* c1, alumno* c2);
void EliminarAlumno(alumno ficha[], int* num, int i);
 int GuardarFicha(char fichero[],alumno ficha[],int num);


void main()
{
	int result=0;
	alumno ficha [MAX_NUM_ALUMNOS];
	int num_alumnos=0;
	int opcion=0;
	alumno c;
	int n;
	FILE *f;
	f=fopen("Ficha.txt","a");
	fflush(f);
	LeerTodosAlumnos("Ficha.txt",ficha,&num_alumnos);
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
			case 2: MostrarTodosAlumnos (ficha,num_alumnos); 
			break;
			case 3: 
			{
				printf("¿Por que dato del alumno desea buscarle?\n");
				BuscarAlumno(ficha,num_alumnos); 
			}
			break;
			case 4: 
			{
				n=Menu2();
				printf("¿Por que dato del alumno desea ordenar?\n");
				OrdenarAlumnos(ficha,num_alumnos,n); 
				MostrarTodosAlumnos(ficha,num_alumnos); 
			}
			break;
			case 5: 
			{
				printf("Cuantos alumnos desea eliminar :\n");
				MostrarTodosAlumnos(ficha,num_alumnos);
				scanf("%d",&n);
				fflush(stdin);
				EliminarAlumno(ficha,&num_alumnos,n); 
				MostrarTodosAlumnos(ficha,num_alumnos); 
			}
			break;
		}
		printf("Pulse una tecla para continuar...\n");
		getch();
		system("cls");
		
	}
	while(opcion!=0 && opcion<=6);
	
	result=GuardarFicha("Ficha.txt",ficha,num_alumnos);
	if(result==0){
	    printf("Fallo al escribir en fichero\n");
	}
	} //Fin de la funcion principal donde llamamos a las funciones anteriormente definidas



//Función que te muestra el menú
int Menu()
{
	int opcion=-1;
	
	do
	{
		printf(".........Menu Principal.......\n");
		printf(" .......Que desea hacer?......\n");
		printf("0-Salir\n");
		printf("1-Introducir a un nuevo alumno\n");
		printf("2-Mostrar todos los alumnos\n");
		printf("3-Buscar alumno\n");
		printf("4-Ordenar alumnos\n");
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
int LeerTodosAlumnos(char fichero[],alumno ficha[],int* num)
{
	alumno alumn;
	int n=0;
	FILE* j=fopen(fichero,"r");
	fflush(j);
	if(j==NULL)
		return 0;
	while(LeerAlumno(j,&alumn))
	{
		ficha[n]=alumn;
		n++;
	}
	*num=n;
	fclose(j);
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
void MostrarTodosAlumnos(alumno ficha[],int num)
{
	int i;
	printf("************************************************************\n");
	printf(":	%-10s %-10s %-10s %-10s %-10s\n","Nombre","Apellido","Matricula", "Nota1", "Nota2");
	printf("************************************************************\n");	
	for(i=0;i<num;i++)
	{
		printf("alumno %d: ",i+1);
		printf("%-10s %-10s %-10s %-.2f %-.2f \n",ficha[i].nombre,ficha[i].apellido,ficha[i].matricula,ficha[i].nota1,ficha[i].nota2);	
	}
	printf("***********************************************************\n");
}



//función que guarda los datos de la ficha en el fichero
int GuardarFicha(char fichero[],alumno ficha[],int num)
{	
	int i;
	FILE* qwe=fopen(fichero, "a+");
	fflush(qwe);
	if(qwe==NULL)
		return 0;
		fprintf(qwe,"***************************************************************************\n");
	for(i=0;i<num;i++)
	{
        fprintf(qwe," %s %s %s %f %f\n", ficha[i].nombre,ficha[i].apellido,ficha[i].matricula,ficha[i].nota1,ficha[i].nota2);
	}
	fprintf(qwe,"***************************************************************************\n");
	fclose(qwe);
	return 1;
}




void BuscarAlumno(alumno ficha[],int num)
{
	alumno c;
	int i;
	int campo=Menu2();
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
	//BuscarAlumno(ficha,num,c,campo);
	printf("--------------------------------------------------------------\n");
	printf(":	%-10s %-10s %-10s %-10s %-10s\n","Nombre","Apellido","Matricula", "Nota1", "Nota2");
	printf("--------------------------------------------------------------\n");	
	for (i=0;i<num;i++)
	{
		if(0==CompararAlumnos(ficha[i],c,campo))
		{
			printf("%d: ",i);
			printf("%-10s %-10s %-10s %-.2f %-.2f \n",ficha[i].nombre,ficha[i].apellido,ficha[i].matricula,ficha[i].nota1,ficha[i].nota2);	

		}
	}
	printf("---------------------------------------------------------------\n");
}


int Menu2()
{
	int opcion=-1;
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



//funcion que nos compara varios alumnos
int CompararAlumnos(alumno c1, alumno c2,int campo)
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


void OrdenarAlumnos(alumno ficha[],int num,int campo)
{
	int i,j, aux;
	for(i=0;i<num-1;i++)
	{
		for(j=i+1;j<num;j++)
		{
			if(0<CompararAlumnos(ficha[i], ficha[j], campo))
			IntercambiaAlumnos(&ficha[i],&ficha[j]);
		}
	}
}

//funcion que nos intercambia varios alumnos
void IntercambiaAlumnos(alumno* c1,alumno* c2)
{
	alumno aux=*c1;
	*c1=*c2;
	*c2=aux;
}


void EliminarAlumno(alumno ficha[], int* num, int n)
{
	int i;
	int numero=*num;
	if(n<0 || n>=numero)
		return;
	for(i=n;i<numero-1;i++)
		ficha[i]=ficha[i+1];
	*num=numero-1;
}
