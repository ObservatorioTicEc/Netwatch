/*
 * Analisis.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: byron
 */

#include "Analisis.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

short Analisis::na=0;

Analisis::Analisis() {
	// TODO Auto-generated constructor stub
	Analisis::na++;
}

Analisis::~Analisis() {
	// TODO Auto-generated destructor stub
	Analisis::na--;
	delete[] hostlist;

}

//Lectura de archivo con lista de hosts----------------------------------------------
void Analisis::readlist(const char* archivo) {
	string line;
	char** hostlist;
	char c;
	short unsigned n = 0, counter = 0;
	int number_lines;
	int linesize;

	ifstream myfile(archivo);
	if (myfile.is_open()) {
		myfile.seekg(0, ios::end);
		number_lines = myfile.tellg();
		myfile.seekg(0, ios::beg);
		for (int i = 0; i < number_lines; i++) {
			myfile.get(c); // get character from file
			if (c == '\n')
				n++;
		}
		hostlist = new char*[n];
		myfile.seekg(0, ios::beg);
		while (myfile.good()) {
			getline(myfile, line);
			if (line.size()) {
				linesize = line.size();
				hostlist[counter] = new char[linesize];
				strcpy(hostlist[counter], line.c_str());
				counter++;
			}
		}

		myfile.close();
		this->numhosts = counter;
	} else
		cout << "Archivo especificado no se puede abrir";

	this->hostlist = new char*[counter];

	for (int i = 0; i < counter; i++) {
		this->hostlist[i]=strdup(hostlist[i]);

	}

}

//Lectura de array con lista de hosts------------------------------------
void Analisis::readlist(char** list,int num_hosts) {

		this->numhosts=num_hosts;
		this->hostlist = new char*[num_hosts];
		for(int i=0;i<num_hosts;i++)
			this->hostlist[i]=strdup(list[i]);
}

//Retorna el número de hosts leídos desde la lista-----------------------
short unsigned Analisis::get_numhosts() {
	return this->numhosts;
}

//Retrona listado de hosts leida desde la lista-------------------------------------
char** Analisis::get_hostlist() {
	return this->hostlist;
}

char** Analisis::get_resultado(){
	return this->analizar();
}

char*** Analisis::get_resultado_fragmented(){
	return this->fragment_resultado();
}

void Analisis::print_resultado(){
	char** datos;
	datos=this->get_resultado();
	for(int i=0;i<this->numhosts;i++)
		cout<<*(datos+i);
}

int* Analisis::get_num_campos(){

	return this->ncampos();
}

void Analisis::print_resultado_fragmented(){
	char*** datos;
	int nh;
	int* nc;
	int k;
	nh=this->get_numhosts();
	nc=this->get_num_campos();

	datos=this->get_resultado_fragmented();
	for(int i=0;i<nh;i++)
	{
		k=*(nc+i);
		for(int j=0;j<k;j++)
		{
			cout<<(*(datos[i]+j));
		}


	}
}


