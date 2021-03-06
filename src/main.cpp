//
//  main.cpp
//  
//
//  Created by Bret Jackson on 1/29/17.
//
//

#include <stdio.h>

#include "ExampleApp.h"

using namespace basicgraphics;

int main(int argc, char** argv)
{
	// Initialize freeimage library
	//FreeImage_Initialise();

	ExampleApp *app = new ExampleApp(argc, argv, "Coordinate Frame example", 1280, 720);
	app->run();
	delete app;

	//FreeImage_DeInitialise();

	return 0;

}
