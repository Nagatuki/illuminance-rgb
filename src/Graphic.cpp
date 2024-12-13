#include "Graphic.h"

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include <cmath>
#include <iostream>

namespace gui_impl {
	double placeholder_width = 50;
	double placeholder_height = 50;
	double placeholder_interval = 10;
	double que_radius = 20;

	void cwh_to_corners(double center[2], double width, double height, double corner[4][2]) {
		corner[0][0] = center[0] - width / 2;
		corner[0][1] = center[1] - height / 2;

		corner[1][0] = center[0] + width / 2;
		corner[1][1] = center[1] - height / 2;

		corner[2][0] = center[0] + width / 2;
		corner[2][1] = center[1] + height / 2;

		corner[3][0] = center[0] - width / 2;
		corner[3][1] = center[1] + height / 2;
	}

	void drawSquareFill(double pos[4][2], double r, double g, double b) {
		// 2D描画なので光源処理を無効に
		glDisable(GL_LIGHTING);

		// 色
		glColor3d(r, g, b);
		glEnable(GL_COLOR_MATERIAL);

		// 描画
		//glBegin(GL_QUADS);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 4; ++i) {
			glVertex2f(pos[i][0], pos[i][1]);
		}
		glEnd();

		glEnable(GL_LIGHTING);
	}
}

namespace gui {
	int Graphic::width_pixel = 1920;
	int Graphic::height_pixel = 1080;
	double Graphic::width_world = 100;
	double Graphic::height_world = 100;

	bool Graphic::is_fullscreen = false;
	int Graphic::window_pos_x = 0;
	int Graphic::window_pos_y = 0;

	double Graphic::color_r = 0;
	double Graphic::color_g = 0;
	double Graphic::color_b = 0;
	bool Graphic::flag = false;

	GraphicSetting Graphic::setting = GraphicSetting();

	void Graphic::initialize(int argc, char** argv) {
		Graphic::is_fullscreen = false;

		glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

		glutInitWindowPosition(100, 0);
		glutInitWindowSize(1000, 1000);
		glutCreateWindow("Task");

		// Set glut callback functions.
		glutDisplayFunc(glut_display);
		glutReshapeFunc(glut_reshape);
		glutIdleFunc(glut_idle);

		//GLUI_Master.set_glutKeyboardFunc(glutKeyboard);
		glutKeyboardFunc(glut_keyboard);
		glutSpecialFunc(glut_special_keyboard);

		glutCreateMenu(glut_menu);
		glutAddMenuEntry("Quit", 0);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		//  Sets up general OpenGL rendering properties: lights, depth buffering, etc.
		static const GLfloat light_model_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		static const GLfloat light0_diffuse[] = { 0.9f, 0.9f, 0.9f, 0.9f };
		static const GLfloat light0_direction[] = { 0.0f, -0.4f, 1.0f, 0.0f };

		// Enable depth buffering for hidden surface removal.
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);

		// Cull back faces.
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);

		// Setup other misc features.
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		glShadeModel(GL_SMOOTH);

		// Setup lighting model.
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
		glEnable(GL_LIGHT0);
	}

	void Graphic::loop() {
		glutMainLoop();
	}

	double Graphic::pixel_to_world_unit(double pixel) {
		double world_unit = pixel * Graphic::width_world * 2 / Graphic::width_pixel;
		return world_unit;
	}

	void Graphic::set_graphic_setting(GraphicSetting setting) {
		Graphic::setting = setting;
	}

	void Graphic::glut_display() {
		Graphic::draw();
		glutSwapBuffers();
	}

	void Graphic::glut_reshape(int width_px, int height_px) {
		std::cout << "width = " << width_px << std::endl;
		std::cout << "height = " << height_px << std::endl;
		Graphic::width_pixel = width_px;  // [pixels]
		Graphic::height_pixel = height_px;  // [pixels]

		glViewport(0, 0, width_px, height_px);

		double max_width_mm = Graphic::setting.get_width_mm();  // 実世界でのスクリーンサイズ, 実際に測定する
		double max_width_px = Graphic::setting.get_width_pixel();  // ウィンドウを最大化した時のピクセル数, ウィンドウごとに設定

		//ウインドウを最大化した時に、表示されるサイズを実サイズへ合わせる
		double w = max_width_mm * (width_px / max_width_px) / 2.0;
		double h = w * (double)height_px / width_px;
		gui::Graphic::width_world = w;
		gui::Graphic::height_world = h;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-w, w, -h, h);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLoadIdentity();
	}

	void Graphic::glut_idle() {
		// 描画時以外に回し続けたい処理をここに書く
		// 以前までは、エラーチェックをここで行っていた
		glutPostRedisplay();
	}

	void Graphic::glut_menu(int ID) {
		switch (ID) {
		case 0:
			exit(0);
			break;
		}
	}

	void Graphic::glut_keyboard(unsigned char key, int x, int y) {
		if (key == 27) {  // ESCキー
			if (Graphic::is_fullscreen) {
				toggle_fullscreen(false);  // 全画面解除
			}
		}
	}

	void Graphic::glut_special_keyboard(int key, int x, int y) {
		if (key == GLUT_KEY_F11) {
			toggle_fullscreen(!Graphic::is_fullscreen);  // 全画面の切り替え
		}
	}

	void Graphic::draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glClearColor(Graphic::color_r, Graphic::color_g, Graphic::color_b, 1.0);

		if (Graphic::flag) {
			Graphic::draw_flag();
		}
	}

	void Graphic::toggle_fullscreen(bool is_fullscreen) {
		Graphic::is_fullscreen = is_fullscreen;
		if (is_fullscreen) {
			// 全画面モードに切り替え
			Graphic::window_pos_x = glutGet(GLUT_WINDOW_X);
			Graphic::window_pos_y = glutGet(GLUT_WINDOW_Y);
			glutFullScreen();
		}
		else {
			// 全画面を解除
			glutReshapeWindow(Graphic::width_pixel, Graphic::height_pixel);
			glutPositionWindow(Graphic::window_pos_x, Graphic::window_pos_y);
		}
	}

	void Graphic::draw_flag() {
		double case_width = 31;
		double case_height = 36;
		double flag_width = 10;
		double flag_height = 20;

		double pos[2] = {
			Graphic::width_world - case_width / 2,
			Graphic::height_world - case_height / 2,
		};


		double corners[4][2];
		gui_impl::cwh_to_corners(pos, flag_width, flag_height, corners);
		gui_impl::drawSquareFill(corners, 1, 1, 1);
	}

	void Graphic::set_color(double r, double g, double b) {
		Graphic::color_r = r;
		Graphic::color_g = g;
		Graphic::color_b = b;
	}

	void Graphic::set_flag(bool flag) {
		Graphic::flag = flag;
	}
}
