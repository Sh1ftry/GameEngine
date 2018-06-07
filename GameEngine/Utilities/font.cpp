#include "font.h"

Font::Font(const std::string& path, unsigned int size)
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		Texture* texture = new Texture(id, face->glyph->bitmap.rows, face->glyph->bitmap.width, 1, 1);

		Character character =
		{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

		_characters[c] = character;
		character.texture = nullptr;
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

glm::vec2 Font::getTextSize(const std::string & text) const
{
	unsigned int width = 0;
	int xMin = 0;
	int xMax = 0;
	for(char character : text)
	{
		const Character& info = getCharacter(character);
		if (info._bearing.y > xMax) xMax = info._bearing.y;
		if (info.size.y - info._bearing.y > xMin) xMin = info.size.y - info._bearing.y;

		width += (info.advance >> 6);
	}
	return glm::vec2(width, xMax + xMin);
}

const Font::Character& Font::getCharacter(char character) const
{
	return _characters.at(character);
}
