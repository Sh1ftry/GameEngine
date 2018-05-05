#pragma once
#include <map>
#include <Gl/glew.h>
#include "texture.h"
#include <iostream>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H 

class Font
{
public:
	struct Character
	{
		const Texture* texture;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;
	};
private:
	std::map<char, Character> _characters;
public:
	Font(const std::string path, unsigned int size)
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			throw std::runtime_error("Failed to initialize FreeType library!");
		}

		FT_Face face;
		if (FT_New_Face(ft, path.c_str(), 0, &face))
		{
			FT_Done_Face(face);
			throw std::invalid_argument("Font '" + path + "' does not exist!");
		}

		FT_Set_Pixel_Sizes(face, 0, size);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				FT_Done_Face(face);
				FT_Done_FreeType(ft);
				const std::string glyph = std::string(1, c);
				throw std::runtime_error("Failed to load '" + glyph + "' glyph from '" + path + "' font!");
			}
			
			GLuint id;
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED,GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			const Texture* texture = new const Texture(id, face->glyph->bitmap.rows, face->glyph->bitmap.width, 1, 1);
			
			const Character character =
			{
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			
			_characters[c] = character;
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	const Character& getCharacter(char character) const
	{
		return _characters.at(character);
	}

	//TODO
	//CLEAER TEXTURES
	~Font() = default;
};

