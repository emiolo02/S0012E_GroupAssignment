//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "game.h"

//------------------------------------------------------------------------------
/**
*/
int
main(int argc, const char** argv)
{
	Game::GameApp app;
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();	
	return app.ExitCode();
}