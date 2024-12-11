#pragma once

namespace gui {
	class GraphicSetting {
	public:
		GraphicSetting();
		int get_width_mm() const;
		int get_width_pixel() const;
		void load_setting();

	private:
		int width_mm;
		int width_pixel;
	};
}

