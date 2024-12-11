#include "GraphicUtils.h"
#include "Graphic.h"

#include <iostream>

namespace gui_impl {
	const double magenta[3] = { 0.6, 0, 0.6 };
	const double cyan[3] = { 0, 0.6, 0.6 };
	const double yellow[3] = { 0.6, 0.6 ,0 };
	const double red[3] = { 0.6, 0, 0 };
	const double green[3] = { 0, 0.6, 0 };
	const double blue[3] = { 0, 0, 0.6 };
	const double white[3] = { 0.7, 0.7, 0.7 };
	const double black[3] = { 0, 0, 0 };
	const double gray[3] = { 0.4, 0.4,0.4 };
	const double PI = acos(-1);
}


namespace gui {
	// êF
	void getColor(COLOR c, double color[3]) {
		switch (c) {
		case (COLOR::MAGENTA):
			memcpy(color, gui_impl::magenta, sizeof(gui_impl::magenta));
			break;
		case (COLOR::CYAN):
			memcpy(color, gui_impl::cyan, sizeof(gui_impl::cyan));
			break;
		case (COLOR::YELLOW):
			memcpy(color, gui_impl::yellow, sizeof(gui_impl::yellow));
			break;
		case (COLOR::RED):
			memcpy(color, gui_impl::red, sizeof(gui_impl::red));
			break;
		case (COLOR::GREEN):
			memcpy(color, gui_impl::green, sizeof(gui_impl::green));
			break;
		case (COLOR::BLUE):
			memcpy(color, gui_impl::blue, sizeof(gui_impl::blue));
			break;
		case (COLOR::WHITE):
			memcpy(color, gui_impl::white, sizeof(gui_impl::white));
			break;
		case (COLOR::BLACK):
			memcpy(color, gui_impl::black, sizeof(gui_impl::black));
			break;
		case (COLOR::GRAY):
			memcpy(color, gui_impl::gray, sizeof(gui_impl::gray));
			break;
		default:
			memcpy(color, gui_impl::white, sizeof(gui_impl::white));
			break;
		}
	}


	// ï∂éöï`âÊóp
	std::unique_ptr<FTPixmapFont> pFont;


	/******************************************************************************
	 Draws a string using OpenGL. (from ShapeManipulation main.cpp)
	******************************************************************************/
	void drawString(const char* string, void* font) {
		for (; *string != '\0'; ++string) {
			glutBitmapCharacter(font, *string);
		}
	}


	/******************************************************************************
	 Draws string prompts at the bottom of the screen. (from ShapeManipulation main.cpp)
	******************************************************************************/
	void drawPrompts(const char* string, double pos[2], COLOR color, void* font) {
		glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 1000, 0, 1000, 0, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		//êF
		double targetCol[3] = { 0,0,0 };
		getColor(color, targetCol);
		glColor3d(targetCol[0], targetCol[1], targetCol[2]);
		glEnable(GL_COLOR_MATERIAL);

		//à íu
		glRasterPos2f(pos[0], pos[1]);

		//ï∂éö
		drawString(string, font);

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glPopAttrib();
	}

	void drawLine(double pos1[2], double pos2[2], COLOR color, double thickness) {
		// 2Dï`âÊÇ»ÇÃÇ≈åıåπèàóùÇñ≥å¯Ç…
		glDisable(GL_LIGHTING);

		// êF
		double targetCol[3] = { 0,0,0 };
		getColor(color, targetCol);
		glColor3d(targetCol[0], targetCol[1], targetCol[2]);
		glEnable(GL_COLOR_MATERIAL);

		// ëæÇ≥
		glLineWidth(thickness);

		// ï`âÊ
		glBegin(GL_LINES);
		glVertex2f(pos1[0], pos1[1]);
		glVertex2f(pos2[0], pos2[1]);
		glEnd();

		glEnable(GL_LIGHTING);
	}

	void drawCross(double center[2], double width, double height, COLOR color, double thickness) {
		// 2Dï`âÊÇ»ÇÃÇ≈åıåπèàóùÇñ≥å¯Ç…
		// http://ankohouse.sblo.jp/article/100867598.html
		glDisable(GL_LIGHTING);

		// êF
		double targetCol[3] = { 0,0,0 };
		getColor(color, targetCol);
		glColor3d(targetCol[0], targetCol[1], targetCol[2]);
		glEnable(GL_COLOR_MATERIAL);

		// ëæÇ≥
		glLineWidth(thickness);

		// ï`âÊ
		glBegin(GL_LINES);
		glVertex2f(center[0] - width / 2, center[1]);
		glVertex2f(center[0] + width / 2, center[1]);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(center[0], center[1] - height / 2);
		glVertex2f(center[0], center[1] + height / 2);
		glEnd();

		glEnable(GL_LIGHTING);
	}

	void drawCircle(double center[2], double radius, COLOR color, double thickness) {
		drawArc(center, radius, color, thickness, 0, 360);
	}

	void drawCircleFill(double center[2], double radius, COLOR color) {
		// 2Dï`âÊÇ»ÇÃÇ≈åıåπèàóùÇñ≥å¯Ç…
		glDisable(GL_LIGHTING);

		// êF
		double targetCol[3] = { 0,0,0 };
		getColor(color, targetCol);
		glColor3d(targetCol[0], targetCol[1], targetCol[2]);
		glEnable(GL_COLOR_MATERIAL);

		// ï`âÊ
		for (double th1 = 0; th1 <= 360; th1 += 1.0) {
			double th2 = th1 + 10.0;
			double th1_rad = th1 / 180.0 * gui_impl::PI;
			double th2_rad = th2 / 180.0 * gui_impl::PI;

			float x1 = radius * cos(th1_rad) + center[0];
			float y1 = radius * sin(th1_rad) + center[1];
			float x2 = radius * cos(th2_rad) + center[0];
			float y2 = radius * sin(th2_rad) + center[1];

			glBegin(GL_TRIANGLES);
			glVertex2f(center[0], center[1]);
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
			glEnd();
		}

		glEnable(GL_LIGHTING);
	}

	void drawArc(double center[2], double radius, COLOR color, double thickness, double startAng, double stopAng) {
		// 2Dï`âÊÇ»ÇÃÇ≈åıåπèàóùÇñ≥å¯Ç…
		glDisable(GL_LIGHTING);

		// êF
		double targetCol[3] = { 0,0,0 };
		getColor(color, targetCol);
		glColor3d(targetCol[0], targetCol[1], targetCol[2]);
		glEnable(GL_COLOR_MATERIAL);

		// ëæÇ≥
		glLineWidth(thickness);

		// ï`âÊ
		for (double th1 = startAng; th1 <= stopAng - 10; th1 += 1.0) {
			double th2 = th1 + 10.0;
			double th1_rad = th1 / 180.0 * gui_impl::PI;
			double th2_rad = th2 / 180.0 * gui_impl::PI;

			float x1 = radius * cos(th1_rad) + center[0];
			float y1 = radius * sin(th1_rad) + center[1];
			float x2 = radius * cos(th2_rad) + center[0];
			float y2 = radius * sin(th2_rad) + center[1];

			glBegin(GL_LINES);
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
			glEnd();
		}

		glEnable(GL_LIGHTING);
	}

	void drawSphere(double center[3], double radius, COLOR color) {
		// êF
		double targetCol[3] = { 0, 0, 0 };
		getColor(color, targetCol);
		glEnable(GL_COLOR_MATERIAL);

		// ï`âÊ
		glPushMatrix();
		glColor3d(targetCol[0], targetCol[1], targetCol[2]);
		glTranslated(center[0], center[1], center[2]);
		glutSolidSphere(radius, 32, 32);
		glPopMatrix();
	}

	void drawSquareFill(double pos[4][2], COLOR color) {
		// 2Dï`âÊÇ»ÇÃÇ≈åıåπèàóùÇñ≥å¯Ç…
		glDisable(GL_LIGHTING);

		// êF
		double targetCol[3] = { 0,0,0 };
		getColor(color, targetCol);
		glColor3d(targetCol[0], targetCol[1], targetCol[2]);
		glEnable(GL_COLOR_MATERIAL);

		// ï`âÊ
		//glBegin(GL_QUADS);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 4; ++i) {
			glVertex2f(pos[i][0], pos[i][1]);
		}
		glEnd();

		glEnable(GL_LIGHTING);
	}

	void drawRing(double center[2], double innerRadius, double outerRadius, COLOR color) {
		drawLackingRing(center, innerRadius, outerRadius, 0, 360, color);
	}

	void drawLackingRing(
		double center[2],
		double innerRadius,
		double outerRadius,
		double startAng,
		double stopAng,
		COLOR color
	) {
		// 2Dï`âÊÇ»ÇÃÇ≈åıåπèàóùÇñ≥å¯Ç…
		glDisable(GL_LIGHTING);

		// êF
		double targetCol[3] = { 0,0,0 };
		getColor(color, targetCol);
		glColor3d(targetCol[0], targetCol[1], targetCol[2]);
		glEnable(GL_COLOR_MATERIAL);

		// ï`âÊ
		for (double th1 = startAng; th1 <= stopAng - 10; th1 += 1.0) {
			double th2 = th1 + 10.0;
			double th1_rad = th1 / 180.0 * gui_impl::PI;
			double th2_rad = th2 / 180.0 * gui_impl::PI;

			float x1 = innerRadius * cos(th1_rad) + center[0];
			float y1 = innerRadius * sin(th1_rad) + center[1];
			float x2 = outerRadius * cos(th1_rad) + center[0];
			float y2 = outerRadius * sin(th1_rad) + center[1];
			float x3 = outerRadius * cos(th2_rad) + center[0];
			float y3 = outerRadius * sin(th2_rad) + center[1];
			float x4 = innerRadius * cos(th2_rad) + center[0];
			float y4 = innerRadius * sin(th2_rad) + center[1];

			glBegin(GL_QUADS);
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
			glVertex2f(x3, y3);
			glVertex2f(x4, y4);
			glEnd();
		}

		glEnable(GL_LIGHTING);
	}

	void drawCube(double center[3], double width, double height, COLOR color) {
		double x, y;
		x = min(width, height);
		y = max(width, height);

		// êF
		double targetCol[3] = { 0, 0, 0 };
		getColor(color, targetCol);
		glEnable(GL_COLOR_MATERIAL);

		// ï`âÊ
		glPushMatrix();
		glColor3d(targetCol[0], targetCol[1], targetCol[2]);
		glTranslated(center[0], center[1], center[2]);
		glutSolidCube(x);
		glPopMatrix();

		for (int diff = -y / 2 + x / 2; diff < 0; diff += x) {
			glPushMatrix();
			glColor3d(targetCol[0], targetCol[1], targetCol[2]);
			if (width < height) {
				glTranslated(center[0], center[1] - diff, center[2]);
			}
			else {
				glTranslated(center[0] - diff, center[1], center[2]);
			}
			glutSolidCube(x);
			glPopMatrix();

			glPushMatrix();
			glColor3d(targetCol[0], targetCol[1], targetCol[2]);
			if (width < height) {
				glTranslated(center[0], center[1] + diff, center[2]);
			}
			else {
				glTranslated(center[0] + diff, center[1], center[2]);
			}
			glutSolidCube(x);
			glPopMatrix();
		}
	}

	/******************************************************************************
	 DrawStringFTGL
	******************************************************************************/
	// ÉtÉHÉìÉg
	const std::string DrawStringFTGL::MSGOTHIC = "C:\\Windows\\Fonts\\msgothic.ttc";
	const std::string DrawStringFTGL::TIMESNEWROMAN = "C:\\Windows\\Fonts\\times.ttf";

	COLOR DrawStringFTGL::color = COLOR::WHITE;
	unsigned long DrawStringFTGL::fontSize = 24;
	std::string DrawStringFTGL::fontFilePath = "";
	std::unique_ptr<FTPixmapFont> DrawStringFTGL::pFont;

	void DrawStringFTGL::setFont(const std::string fontFilePath) {
		std::string newFilePath = std::string(fontFilePath);

		if (DrawStringFTGL::fontFilePath == newFilePath) return;

		DrawStringFTGL::fontFilePath = newFilePath;
		DrawStringFTGL::pFont = std::make_unique<FTPixmapFont>(newFilePath.c_str());

		if (DrawStringFTGL::pFont->Error()) {
			std::cout << "Failed to open font " << newFilePath << std::endl;
			DrawStringFTGL::pFont.release();
			return;
		}

		DrawStringFTGL::pFont->FaceSize(fontSize);
	}

	void DrawStringFTGL::setFontSize(const unsigned long fontSize) {
		if (DrawStringFTGL::fontSize == fontSize) return;

		DrawStringFTGL::fontSize = fontSize;
		if (DrawStringFTGL::pFont) {
			DrawStringFTGL::pFont->FaceSize(fontSize);
		}
	}

	void DrawStringFTGL::setColor(const COLOR color) {
		DrawStringFTGL::color = color;
	}

	void DrawStringFTGL::draw(std::string& text, double pos[2], TextAlignment align) {
		// FontÇ™ñ¢ê›íËÇÃèÍçáÇÕñ≥éãÇ∑ÇÈ
		if (!pFont) return;

		//êF
		double targetCol[3] = { 0,0,0 };
		getColor(DrawStringFTGL::color, targetCol);
		glColor3d(targetCol[0], targetCol[1], targetCol[2]);
		glEnable(GL_COLOR_MATERIAL);

		// ï`âÊç¿ïW
		FTBBox bbox = pFont->BBox(text.c_str());
		double xPos = pos[0];

		if (align == TextAlignment::LEFT) {
			// ÇªÇÃÇ‹Ç‹xPosÇégóp
		}
		else if (align == TextAlignment::CENTER) {
			//double xDiffPx = bbox.Upper().X() / 2;
			double xDiffPx = (bbox.Upper().X() - bbox.Lower().X()) / 2;
			xPos -= Graphic::pixel_to_world_unit(xDiffPx);
		}
		else {
			//double xDiffPx = bbox.Upper().X();
			double xDiffPx = bbox.Upper().X() - bbox.Lower().X();
			xPos -= Graphic::pixel_to_world_unit(xDiffPx);
		}

		double yDiffPx = (bbox.Upper().Y() - bbox.Lower().Y()) / 2;
		double yPos = pos[1] - Graphic::pixel_to_world_unit(yDiffPx);

		glRasterPos2f(xPos, yPos);

		// FTGLÇ≈ï∂éöóÒÇï`âÊ
		text.push_back('\0');
		pFont->Render(text.c_str());
	}
}
