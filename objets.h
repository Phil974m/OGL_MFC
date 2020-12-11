//#include "OGLControl.h"
#ifndef OBJET_H
#define OBJET_H

class OGLControl;

class objet : public OGLControl 
{
public:
	objet();
	virtual ~objet();
public:
	int carre(bool state);
	int triangle(bool state);
};
#endif