#pragma once

#include "GraphicSetting.h"

namespace gui {
	class Graphic {
	public:
		static void initialize(int argc, char** argv);
		static void loop();

		static double pixel_to_world_unit(double pixel);
		//static int world_coord_to_pixel(double value);

		static void set_graphic_setting(GraphicSetting setting);

		static void set_color(double r, double g, double b);
		static void set_flag(bool flag);

	private:
		static double color_r;
		static double color_g;
		static double color_b;
		static bool flag;

		static int width_pixel;
		static int height_pixel;
		static double width_world;
		static double height_world;

		static bool is_fullscreen;
		static int window_pos_x;
		static int window_pos_y;

		static GraphicSetting setting;

		static void draw();
		static void glut_display();
		static void glut_reshape(int width, int height);
		static void glut_idle();
		static void glut_menu(int);
		static void glut_keyboard(unsigned char key, int x, int y);
		static void glut_special_keyboard(int key, int x, int y);

		static void toggle_fullscreen(bool is_fullscreen);

		// static void update_workspace();

		static void draw_flag();
	};
}

