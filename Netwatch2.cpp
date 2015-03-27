/*
 * Netwatch2.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: byron
 */
#include <iostream>
#include <stdio.h>
#include </home/byron/workspace/Netwatch2/clases/Analisis.h>
#include </home/byron/workspace/Netwatch2/clases/ClassPing.h>
#include <string.h>
#include <cstdlib>
using namespace std;

int main(int argc,char** argv) {
	char** datos;
	char** lista;
	char* archivo;
	int num_hosts;
	archivo=NULL;

	Analisis* a1 = new ClassPing;
	if (argc==1)archivo=strdup("/home/byron/example.txt");
	if (argc==2)archivo=strdup(argv[1]);
	if (argc>2)
	{
		if(argc-2<atoi(argv[1]))
		{
			cout<<"\nError, numero de argumentos mayor a cantidad de argumentos\n";
			return(1);
		}
		num_hosts=atoi(argv[1]);
		lista = new char* [num_hosts];
		for(int i=0;i<num_hosts;i++)
			lista[i]=strdup(argv[i+2]);
		a1->readlist(lista,num_hosts);
	}

	if (archivo!=NULL)
		a1->readlist(archivo);

	datos=new char*[a1->get_numhosts()];
	for(int i=0;i<a1->get_numhosts();i++)
		datos[i]=new char[150];
/*
	datos=a1->analizar();
	for(int i=0;i<a1->get_numhosts();i++)
		cout<<datos[i];
*/
/*
	a1->fragment_resultado();

	for(int i=0;i<a1->get_numhosts();i++)
	{
        int fragmento=16;

        printf("%-20s\t",*(a1->get_hostlist()+i));
     //   printf("%5s\t",*(*(a1->resultado_fragmented+i)+5));

       // if(fragmento<*(a1->get_num_campos()+i))
         //       printf("%5s\n",*(*(a1->resultado_fragmented+i)+fragmento));
        else
                printf("%5s\n","nulo");


	}
*/
	a1->print_resultado();

	a1->fragment_resultado();

	a1->print_resultado_fragmented();

	cout<<"\n"<<Analisis::na<<endl;
	delete[] datos;
	return (0);
}
