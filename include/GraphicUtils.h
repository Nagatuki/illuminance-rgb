#pragma once

#include <windows.h>

#include <GL/gl.h>
#include <GL/glut.h>
#include <FTGL/ftgl.h> // •¶Žš•`‰æ—p

#include <memory>
#include <string>
#include <vector>

namespace gui {
	// color
	enum class COLOR {
		MAGENTA,
		CYAN,
		YELLOW,
		RED,
		GREEN,
		BLUE,
		WHITE,
		BLACK,
		GRAY,
	};


	// Utilities
	void drawString(const char* string, void* font);
	void drawPrompts(const char* string, double pos[2], COLOR color, void* font = GLUT_BITMAP_HELVETICA_18);
	void drawLine(double pos1[2], double pos2[2], COLOR color, double thickness);
	void drawCross(double center[2], double width, double height, COLOR color, double thickness);
	void drawCircle(double center[2], double radius, COLOR color, double thickness);
	void drawCircleFill(double center[2], double radius, COLOR color);
	void drawArc(double center[2], double radius, COLOR color, double thickness, double startAng, double stopAng);
	void drawSphere(double center[3], double radius, COLOR color);
	void drawSquareFill(double pos[4][2], COLOR color);
	void drawRing(double center[2], double innerRadius, double outerRadius, COLOR color);
	void drawLackingRing(double center[2], double innerRadius, double outerRadius, double startAng, double stopAng, COLOR color);
	void drawCube(double center[3], double width, double height, COLOR color);

	enum class TextAlignment {
		LEFT,
		CENTER,
		RIGHT
	};

	// freetype‚ÆFTGL‚ð—p‚¢‚½•¶Žš•`‰æ
	// http://slis.tsukuba.ac.jp/~fujisawa.makoto.fu/lecture/iml/text/screen_character.html
	class DrawStringFTGL {
	private:
		static COLOR color;
		static unsigned long fontSize;
		static std::string fontFilePath;
		static std::unique_ptr<FTPixmapFont> pFont;

	public:
		static const std::string MSGOTHIC;
		static const std::string TIMESNEWROMAN;

		static void setFont(const std::string fontFilePath);
		static void setFontSize(const unsigned long fontSize);
		static void setColor(const COLOR color);
		static void draw(std::string& text, double pos[2], TextAlignment align = TextAlignment::LEFT);
		//static void draw(std::vector<std::string>& texts, double pos[2], TextAlignment align = TextAlignment::LEFT);
		//static void draw(std::vector<std::wstring>& texts, double pos[2]);
	};

}

