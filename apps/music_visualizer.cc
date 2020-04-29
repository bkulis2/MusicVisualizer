// Copyright (c) 2020 Benjamin Kulis. All rights reserved.

#include "music_visualizer.h"

#include <choreograph/Choreograph.h>
#include <cinder/Rand.h>
#include <cinder/Text.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/scoped.h>
#include <gflags/gflags.h>

namespace visualizer {

using ci::Color;
using ci::ColorA;
using ci::Rectf;
using ci::app::KeyEvent;

DECLARE_string(song);

MyApp::MyApp() : song_{FLAGS_song} {}

void MyApp::setup() {
  on_visualizer_screen_ = false;
  selected_spiral_pattern_ = false;
  selected_frequency_pattern_ = false;
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load(cinder::app::loadAsset(song_));
  song_voice_ = cinder::audio::Voice::create(sourceFile);
  SetupSpiralPattern();
}

void MyApp::update() {
  ch::Time t = static_cast<ch::Time>(timer_.getSeconds());
  timer_.start();
  ch::Timeline().step(t);
}

void MyApp::draw() {
  ci::gl::enableAlphaBlending();
  if (!on_visualizer_screen_) {
    ci::gl::clear(Color(0.5, 0, 0.5));
    PrintTitle();
    PrintChoose();
    DrawPlayButton();
    DisplayPictures();
    DrawSelectionRect();
  } else {
    ci::gl::clear(Color(0, 0, 0));
    DrawSpiralPattern();
    song_voice_->start();
  }
}

void MyApp::PrintTitle() const {
  ci::gl::color(ci::Rand::randFloat(), ci::Rand::randFloat(),
                ci::Rand::randFloat());
  ci::gl::drawStrokedRect(Rectf(getWindowWidth() / 2 - 170.0f, 70,
                                getWindowWidth() / 2 + 170.0f, 230));
  PrintText("Music\nVisualizer", Color::black(), 80, ci::ivec2{500, 150},
            ci::vec2{getWindowWidth() / 2, 150});
}

void MyApp::PrintChoose() const {
  ci::gl::color(0, 0, 0);
  float font_size = 40;
  PrintText("Song File You Chose:", Color::white(), font_size,
            ci::ivec2{1000, 150}, ci::vec2{170, getWindowHeight() / 2 - 50});
  PrintText(song_, Color(1, 0, 0), font_size, ci::ivec2{1000, 150},
            ci::vec2{getWindowWidth() / 2 + 25, getWindowHeight() / 2 - 50});
  PrintText("Choose Your Pattern: ", Color::white(), font_size,
            ci::ivec2{1000, 150}, ci::vec2{180, getWindowHeight() / 2 + 150});
}

void MyApp::DrawPlayButton() const {
  ci::gl::color(0.0f, 0.0f, 0.7f);
  ci::gl::lineWidth(3);
  Rectf rect(650.0f, 700.0f, 770.0f, 750.0f);
  ci::gl::drawSolidRect(rect);
  PrintText("Play Pattern", Color::white(), 20, ci::ivec2{70, 50},
            ci::vec2{710, 725});
}

void MyApp::DisplayPictures() {
  ci::gl::Texture2dRef texture_one =
      ci::gl::Texture2d::create(loadImage(loadAsset("spiral.jpg")));
  const ci::vec2 loc1 = {100, 600};
  ci::gl::draw(texture_one, loc1);

  ci::gl::Texture2dRef texture_two =
      ci::gl::Texture2d::create(loadImage(loadAsset("frequency.png")));
  const ci::vec2 loc2 = {400, 603};
  ci::gl::draw(texture_two, loc2);
}

void MyApp::DrawSelectionRect() {
  if (selected_spiral_pattern_) {
    cinder::gl::color(cinder::Color::white());
    Rectf rect(90.0f, 590.0f, 272.0f, 767.0f);
    cinder::gl::drawStrokedRect(rect);
  } else if (selected_frequency_pattern_) {
    cinder::gl::color(cinder::Color::white());
    Rectf rect(390.0f, 593.0f, 560.0f, 763.0f);
    cinder::gl::drawStrokedRect(rect);
  }
}

void MyApp::SetupSpiralPattern() {
  ch::PhraseRef<ci::vec2> bounce =
      ch::makeProcedure<ci::vec2>(2.0, [](ch::Time t, ch::Time duration) {
        return ci::vec2(0, sin(ch::easeInOutQuad(t) * 6 * M_PI) * 100.0f);
      });

  // ramp phrase
  auto w = static_cast<float>(ci::app::getWindowWidth());
  float x1 = w * 0.08f;
  float x2 = w - x1;
  ch::PhraseRef<ci::vec2> slide =
      makeRamp(ci::vec2(x1, 0), ci::vec2(x2, 0), 2.0f, ch::EaseInOutCubic());

  float center_y = ci::app::getWindowHeight() / 2.0f;
  ch::PhraseRef<ci::vec2> bounce_and_slide =
      makeAccumulator(ci::vec2(0, center_y), bounce, slide);

  ch::PhraseRef<ci::vec2> bounce_and_slide_negative = makeAccumulator(
      ci::vec2(w, center_y), bounce, slide,
      [](const ci::vec2& a, const ci::vec2& b) { return a - b; });

  ch::Timeline().apply(&_position_a, bounce_and_slide);
  ch::Timeline().apply(&_position_b, bounce_and_slide_negative);
  ch::Timeline().apply(&_reference_bounce, bounce);
  ch::Timeline().apply(&_reference_slide, slide);

  ch::Timeline().jumpTo(0);

  timer_.start();
}

void MyApp::DrawSpiralPattern() {
  cinder::gl::ScopedColor color(ci::Color(0.72f, 1.0f, 1.0f));
  ci::gl::drawSolidCircle(_position_a, 30.0f);

  ci::gl::color(ci::Color(0.96f, 1.0f, 1.0f));
  ci::gl::drawSolidCircle(_position_b, 30.0f);

  // References are translated for visibility.
  float y = ci::app::getWindowHeight() * 0.2f;
  ci::gl::color(ci::Color(0.15f, 1.0f, 1.0f));

  ci::gl::drawStrokedCircle(
      _reference_bounce() + ci::vec2(ci::app::getWindowWidth() * 0.08f, y),
      4.0f);
  ci::gl::drawStrokedCircle(_reference_slide() + ci::vec2(0, y), 4.0f);
}

void MyApp::keyDown(KeyEvent event) {
  auto current_volume = song_voice_->getVolume();
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
      if (current_volume < 1.0f) {
        song_voice_->setVolume(current_volume + .01f);
      }
    case KeyEvent::KEY_DOWN:
      if (current_volume > 0) {
        song_voice_->setVolume(current_volume - .01f);
      }
  }
}

void MyApp::mouseDown(ci::app::MouseEvent event) {
  if (event.isLeft() && (event.getX() >= 650 && event.getX() <= 770) &&
      (event.getY() >= 700 && event.getY() <= 750)) {
    on_visualizer_screen_ = true;
  } else if (event.isLeft() && (event.getX() >= 100 && event.getX() <= 262) &&
             (event.getY() >= 600 && event.getY() <= 757)) {
    selected_spiral_pattern_ = true;
    selected_frequency_pattern_ = false;
  } else if (event.isLeft() && (event.getX() >= 400 && event.getX() <= 550) &&
           (event.getY() >= 603 && event.getY() <= 753)) {
    selected_spiral_pattern_ = false;
    selected_frequency_pattern_ = true;
  }
}

void MyApp::mouseUp(ci::app::MouseEvent event) {}

void MyApp::mouseDrag(ci::app::MouseEvent event) {}

void MyApp::mouseMove(ci::app::MouseEvent event) {}

template <typename C>
void PrintText(const std::string& text, const C& color, float font_size,
               const ci::ivec2& size, const ci::vec2& loc) {
  ci::gl::color(color);

  auto box = ci::TextBox()
                 .alignment(ci::TextBox::CENTER)
                 .font(ci::Font("Roboto", font_size))
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const ci::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = ci::gl::Texture::create(surface);
  ci::gl::draw(texture, locp);
}

}  // namespace visualizer
