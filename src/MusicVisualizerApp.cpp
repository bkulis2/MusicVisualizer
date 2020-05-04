#include <cinder/app/AppBasic.h>
#include <cinder/app/App.h>
#include <cinder/app/Renderer.h>
#include <cinder/audio/Output.h>
#include <cinder/audio/Callback.h>
#include <cinder/CinderMath.h>
#include <cinder/Text.h>
#include <cinder/gl/Texture.h>
#include <cinder/Rand.h>
#include <cinder/ImageIo.h>

#include "MusicVisualizerApp.h"

using ci::app::App;
using ci::app::RendererGl;

namespace visualizer {

	void MusicVisualizerApp::setup() {
		setFrameRate(60.0f);
		setWindowSize(800, 800);

		on_visualizer_screen_ = false;
		selected_interactive_sine_ = false;
		selected_frequency_visualizer_ = false;

		ci::gl::enable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		ci::gl::color(ci::ColorAf::white());

		sine_.setup();
	}

	void MusicVisualizerApp::draw() {
		ci::gl::enableAlphaBlending();
		if (!on_visualizer_screen_) {
			ci::gl::clear(ci::ColorAf(0.5, 0, 0.5));
			PrintTitle();
			PrintChoose();
			DrawPlayButton();
			DisplayPictures();
			DrawSelectionRect();
		} else if (selected_interactive_sine_) {
			ci::gl::clear(ci::ColorAf::black());
			cinder::gl::color(ci::ColorAf::white());
			sine_.draw();
		} else if (selected_frequency_visualizer_) {

		}
	}
	

	void MusicVisualizerApp::mouseMove(ci::app::MouseEvent event) {
		sine_.mouseMove(event);
	}

	void MusicVisualizerApp::mouseDown(ci::app::MouseEvent event) {
		if (event.isLeft() && (event.getX() >= 650 && event.getX() <= 770) &&
			(event.getY() >= 700 && event.getY() <= 750)) {
			on_visualizer_screen_ = true;
		}
		else if (event.isLeft() && (event.getX() >= 100 && event.getX() <= 300) &&
			(event.getY() >= 500 && event.getY() <= 700)) {
			selected_interactive_sine_ = true;
			selected_frequency_visualizer_ = false;
		}
		else if (event.isLeft() && (event.getX() >= 400 && event.getX() <= 600) &&
			(event.getY() >= 500 && event.getY() <= 700)) {
			selected_interactive_sine_ = false;
			selected_frequency_visualizer_ = true;
		}
	}

	void MusicVisualizerApp::shutdown() {
		sine_.shutdown();
	}

	void MusicVisualizerApp::PrintTitle() const {
		ci::gl::color(ci::Rand::randFloat(), ci::Rand::randFloat(),
			ci::Rand::randFloat());
		ci::gl::drawStrokedRect(ci::Rectf(ci::app::getWindowWidth() / 2 - 170.0f, 70,
			ci::app::getWindowWidth() / 2 + 170.0f, 230));
		PrintText("Music\nVisualizer\n", ci::ColorAf::black(), 80.0f, ci::Vec2i(500, 150),
			ci::Vec2f((float) ci::app::getWindowWidth() / 2, 150.0f));
	}

	void MusicVisualizerApp::PrintChoose() const {
		ci::gl::color(0, 0, 0);
		float font_size = 40.0f;
		PrintText("Song File You Chose:", ci::ColorAf::white(), font_size,
			ci::Vec2i(1000, 150), ci::Vec2f(170.0f, ci::app::getWindowHeight() / 2 - 50.0f));
		PrintText("src name", ci::ColorAf(1, 0, 0), font_size, ci::Vec2i(1000, 150),
			ci::Vec2f(ci::app::getWindowWidth() / 2 + 25.0f, ci::app::getWindowHeight() / 2 - 50.0f));
		PrintText("Choose Your Pattern: ", ci::ColorAf::white(), font_size,
			ci::Vec2i(1000, 150), ci::Vec2f(170.0f, ci::app::getWindowHeight() / 2 + 50.0f));
	}

	void MusicVisualizerApp::DrawPlayButton() const {
		ci::gl::color(0.0f, 0.0f, 0.7f);
		ci::Rectf rect(650.0f, 700.0f, 770.0f, 750.0f);
		ci::gl::drawSolidRect(rect);
		PrintText("Play Pattern", ci::ColorAf::white(), 20.0f, ci::Vec2i(70, 50),
			ci::Vec2f(710.0f, 725.0f));
	}

	void MusicVisualizerApp::DisplayPictures() {
		auto texture_one = ci::gl::Texture(ci::loadImage(ci::app::loadAsset("sine.png")));
		const ci::Vec2f loc1(100.0f, 500.0f);
		ci::gl::draw(texture_one, loc1);
		auto texture_two = ci::gl::Texture(ci::loadImage(ci::app::loadAsset("visualizer.png")));
		const ci::Vec2f loc2 (400.0f, 500.0f);
		ci::gl::draw(texture_two, loc2);
	}

	void MusicVisualizerApp::DrawSelectionRect() {
		if (selected_interactive_sine_) {
			cinder::gl::color(cinder::Color::white());
			ci::Rectf rect(90.0f, 490.0f, 310.0f, 710.0f);
			cinder::gl::drawStrokedRect(rect);
		} else if (selected_frequency_visualizer_) {
			cinder::gl::color(cinder::Color::white());
			ci::Rectf rect(390.0f, 490.0f, 610.0f, 710.0f);
			cinder::gl::drawStrokedRect(rect);
		}
	}

	void PrintText(const std::string& text, const ci::ColorA& color, float font_size,
		const ci::Vec2i& size, const ci::Vec2f& loc) {
		ci::gl::color(color);
		auto box = ci::TextBox()
			.alignment(ci::TextBox::CENTER)
			.font(ci::Font("Roboto", font_size))
			.size(size)
			.color(color)
			.backgroundColor(ci::ColorA(0, 0, 0, 0))
			.text(text);

		const auto box_size = box.getSize();
		const ci::Vec2f location (loc.x - box_size.x / 2, loc.y - box_size.y / 2);
		auto texture = ci::gl::Texture(box.render());
		ci::gl::draw(texture, location);
	}

} //namespace visualizer

// Start application
CINDER_APP_BASIC(visualizer::MusicVisualizerApp, RendererGl)