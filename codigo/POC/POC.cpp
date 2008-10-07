// POC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "POC.h"
#include "Framework.h"

int main( int argc, char **argv ){

	Framework framework = Framework(800, 600);
	

	framework.Init();
	framework.Start();
}


