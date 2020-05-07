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
		/**
		* This method initalizes all of the variables and the settings
		* for the application and calls the setup methods for the visualizers.
		*/
		void setup();

		/**
		* This method calls the update method in the SongVisualizer
		* if that is which visualizer the user selected.
		*/
		void update();

		/**
		* This is the main GUI method that choose between which of the three
		* screens is being drawn and calls the necessary methods to do so.
		*/
		void draw();

		/**
		* This calls the same method inside the InteractiveSineVisualizer
		* if that is the visualizer the user selected.
		*/
		void mouseMove(ci::app::MouseEvent event);

		/**
		* This method manages the logic for which visualizer mode is selected
		* and when the play button is clicked. As a result of any of these events
		* happening, then the respective booleans are updated.
		*/
		void mouseDown(ci::app::MouseEvent event);

		/**
		* This calls same method on the respective visualizer that was selected.
		*/
		void shutdown();

	private:
		/**
		* This prints the title of the application and draws a box that changes
		* color every frame around it.
		*/
		void PrintTitle() const;

		/**
		* This method prints the text for the lines that setup the conditions
		* of the visualizer you are going to run.
		*/
		void PrintChoose() const;

		/**
		* This method displays the images for the two patterns you can choose
		* between and for the play button.
		*/
		void DisplayImages() const;

		/**
		* This method draws a white rectangle around the pattern that the user
		* has selected (as told by the booleans).
		*/
		void DrawSelectionRect();

		bool on_visualizer_screen_;
		bool selected_sine_visualizer_;
		bool selected_song_visualizer_;

		InteractiveSineVisualizer sine_visualizer_;
		SongVisualizer song_visualizer_;
	};

	/**
	* This method takes in parameters to create a TextBox that is used to display
	* the text on the screen.
	* @param text The string for the text being displayed.
	* @param color The color of the text.
	* @param font_size The size of the font to be displayed.
	* @param size The size of the text box.
	* @param loc The location of the top right corner for the text box to be
	* displayed.
	*/
	void PrintText(const std::string& text, const ci::ColorA& color,
		float font_size, const ci::Vec2i& size, const ci::Vec2f& loc);
}  // namespace visualizer

#endif