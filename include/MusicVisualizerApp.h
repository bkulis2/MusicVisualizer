// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.

#include "InteractiveSineVisualizer.h"
#include "SongVisualizer.h"

#ifndef MUSICVISUALIZERAPP_H
#define MUSICVISUALIZERAPP_H

namespace visualizer {
	const float kFrameRate = 60.0f;
	const int kWidth = 800;
	const int kHeight = 800;

	const ci::Vec2f kSineImgLoc(kWidth / 2 - 300.0f, kHeight / 2 + 150.0f);
	const ci::Vec2f kNoteImgLoc(kWidth / 2.0f, kHeight / 2 + 150.0f);
	const ci::Vec2f kBtnImgLoc(kWidth - 180.0f, kHeight - 100.0f);

	const float kImgBorderSize = 10.0f;
	const float kImgDimension = 150.0f;
	const float kBtnHeightDimension = 60.0f;

	class MusicVisualizerApp : public ci::app::AppBasic {

	public:
		void setup();
		void update();
		void draw();
		void mouseMove(ci::app::MouseEvent event);
		void mouseDown(ci::app::MouseEvent event);
		void shutdown();

	private:
		void PrintTitle() const;
		void PrintChoose() const;
		void DisplayImages();
		void DrawSelectionRect();

		bool on_visualizer_screen_;
		bool selected_interactive_visualizer_;
		bool selected_song_visualizer_;

		InteractiveSineVisualizer sine_visualizer_;
		SongVisualizer song_visualizer_;
	};

	void PrintText(const std::string& text, const ci::ColorA& color, float font_size,
		const ci::Vec2i& size, const ci::Vec2f& loc);
} //namespace visualizer

#endif