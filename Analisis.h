/*
 * Analisis.h
 *
 *  Created on: Apr 30, 2012
 *      Author: byron
 */

#ifndef ANALISIS_H_
#define ANALISIS_H_

class Analisis {
public:
	Analisis();
	short unsigned get_numhosts();
	char** get_hostlist();
	void readlist(const char* archivo);
	void readlist(char** lista,int num_hosts);
	int* get_num_campos();
	char** get_resultado();
	char*** get_resultado_fragmented();
	void print_resultado();
	void print_resultado_fragmented();
	void grafic_resultado_fragmented();
	virtual char** analizar()=0;
	virtual char*** fragment_resultado()=0;
	virtual int* ncampos()=0;
	virtual ~Analisis();

	static short na;

protected:
	int numhosts;
	char** hostlist;
	char*** resultado_fragmented;
};

#endif /* ANALISIS_H_ */
