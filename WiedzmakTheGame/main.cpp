#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "Graphics/window.h"
#include "Utilities/timer.h"
#include "Graphics/renderer.h"
#include "Utilities/resource_manager.h"
#include "character.h"
#include <vector>
#include "tile.h"
#include <sstream>
#include <irrKlang/irrKlang.h>
#include <iostream>
#include "WiedzmakGame.h"
#include "JSONParser.h"

#include <vld.h>

int main()
{
	std::cout << sizeof(Font) << std::endl;
	std::cout << sizeof(Texture) << std::endl;

	WiedzmakGame wiedzmak;
	try
	{
		wiedzmak.run();
	} catch(const std::exception& e)
	{
		std::cout << e.what();
	}

	ResourceManager::clearResources();
	return 0;
}
