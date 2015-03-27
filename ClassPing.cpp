/*
 * ClassPing.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: byron
 */

#include "ClassPing.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

ClassPing::ClassPing() {
	char* parametros;
	char* parametros2;
	parametros = strdup(" -q -s8 -i0.2 -w1 ");
	parametros2 = strdup("|tail -2 ");
	this->set_params(parametros);
	this->set_params2(parametros2);
}

ClassPing::~ClassPing() {
	// TODO Auto-generated destructor stub
}
//Ejecuta ping simultaneo mediante proceso forked------------------------------
char** ClassPing::analizar() {

	FILE** in;
	char** buff;
	char** pingresult;
	short unsigned sizeofbuff;
	char comando[256];


	sizeofbuff = 512;
	buff = new char*[this->numhosts];
	in = new FILE*[this->numhosts];
	pingresult = new char*[this->numhosts];

	for (int i = 0; i < this->numhosts; i++) {
		strcpy(comando, "ping");
		strcat(comando,this->params);
		strcat(comando, this->hostlist[i]);
		strcat(comando,this->params2);
		buff[i] = new char[sizeofbuff];
		if (!(in[i] = popen(comando, "r"))) {
			return 0;
		}
	}

	for (int i = 0; i < this->numhosts; i++) {
		pingresult[i] = new char[sizeofbuff];
		strcpy(pingresult[i], "");
		while (fgets(buff[i], sizeofbuff, in[i]) != NULL) {
			strcat(pingresult[i], buff[i]);
		}
	}

	for (int i = 0; i < this->numhosts; i++) {
		pclose(in[i]);
	}
	delete[] in;
	delete[] buff;
	this->resultado=pingresult;
	return pingresult;

}
//Fragmenta el resultado del ping pingresult----------------------------------------------------
char*** ClassPing::fragment_resultado() {
	char* k;
	char** cp_pingresult; //Copia de pingresult para efectuar strtok sin afectar original
	char*** p;
	char*** parsed_pingresult;
	int n;

	cp_pingresult = new char*[this->numhosts];
	for (int i = 0; i < this->numhosts; i++) {
		cp_pingresult[i]=strdup(*(this->resultado+i));
	}

	parsed_pingresult = new char**[this->numhosts];
	p = new char**[this->numhosts];
	this->num_campos = new int[this->numhosts];
	for (int i = 0; i < this->numhosts; i++) {
		n = 0;
		parsed_pingresult[i] = new char*[100];
		k = strtok(cp_pingresult[i], " /%=");
		parsed_pingresult[i][n] = new char[strlen(k) + 1];
		while (k != NULL) {
			strcpy(parsed_pingresult[i][n], k);
			n++;
			k = strtok(NULL, " /%=");
			if (k)
				parsed_pingresult[i][n] = new char[strlen(k) + 1];
		}
		this->num_campos[i] = n;
		delete[] k;
	}

	delete[] cp_pingresult;
	delete[] p;
	return parsed_pingresult;
}

int* ClassPing::ncampos(){
	return this->num_campos;
}

char* ClassPing::get_params(){
	return this->params;
}

char* ClassPing::get_params2(){
	return this->params;
}

void ClassPing::set_params(char* parametros){
	this->params=strdup(parametros);
}

void ClassPing::set_params2(char* parametros2){
	this->params2=strdup(parametros2);
}
