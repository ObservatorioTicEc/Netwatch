/*
 * ClassPing.h
 *
 *  Created on: Apr 30, 2012
 *      Author: byron
 */

#ifndef CLASSPING_H_
#define CLASSPING_H_

#include "Analisis.h"

class ClassPing: public Analisis {
public:
	ClassPing();
	virtual ~ClassPing();
	char** analizar();
	char*** fragment_resultado();
	int* ncampos();
	int* get_num_pings();
	void set_params(char* params);
	void set_params2(char* params2);
	char* get_params();
	char* get_params2();


protected:
	int* num_pings;
	int* num_campos;
	char* params;
	char* params2;
	char** resultado;

};

#endif /* CLASSPING_H_ */
