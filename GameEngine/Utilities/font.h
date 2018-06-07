#pragma once
#include <map>
#include <Gl/glew.h>
#include "../Graphics/texture.h"
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H 

/**
 * @brief Class respresenting a font
 */
class Font
{
public:
	/**
	 * @brief	Struct representing a single font's character
	 */
	struct Character
	{

		/**
		 * @brief pointer to character's texture
		 */
		const Texture* texture;
		/**
		 * @brief check freetype glyph metrics
		 */
		glm::ivec2 size;
		/**
		 * @brief check freetype glyph metrics
		 */
		glm::ivec2 _bearing;
		/**
		 * @brief check freetype glyph metrics
		 */
		unsigned int advance;

		~Character()
		{
			delete texture;
		}
	};
private:
	std::map<char, Character> _characters;
public:
	/**
	 * @brief		Creates font and all ascii characters
	 * @param path	path to where the font is stored
	 * @param size	size of the font
	 */
	Font(const std::string& path, unsigned int size);

	/**
	 * @param text text to measure
	 * @return width and height of text
	 */
	glm::vec2 getTextSize(const std::string& text) const;

	/**
	 * @param character which character
	 * @return			struct with character's info and texture
	 */
	const Character& getCharacter(char character) const;

	~Font() = default;
};

