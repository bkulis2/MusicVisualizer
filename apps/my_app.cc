// Copyright (c) 2020 Benjamin Kulis. All rights reserved.

#include "my_app.h"

#include <choreograph/Choreograph.h>
#include <cinder/Rand.h>

namespace myapp {

using ci::Color;
using ci::ColorA;
using ci::Rectf;
using ci::TextBox;
using ci::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() {
  Rectf rect(100.0f, 400.0f, 650.0f, 450.0f);
  text_box_ = std::make_shared<InteractiveTextBox>(rect);
  go_to_visualizer_ = false;
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load(cinder::app::loadAsset("lofi.mp3"));
  song_voice_ = cinder::audio::Voice::create(sourceFile);

  ch::PhraseRef<ci::vec2> bounce =
      ch::makeProcedure<ci::vec2>(2.0, [](ch::Time t, ch::Time duration) {
        return ci::vec2(0, sin(ch::easeInOutQuad(t) * 6 * M_PI) * 100.0f);
      });

  // ramp phrase
  float w = (float)ci::app::getWindowWidth();
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

void MyApp::update() {
  ch::Time t = (ch::Time)timer_.getSeconds();
  timer_.start();
  ch::Timeline().step(t);
}

void MyApp::draw() {
  if (!go_to_visualizer_) {
    ci::gl::enableAlphaBlending();
    ci::gl::clear(Color(0, 0, 0));
    text_box_->draw();
    PrintTitle();
    PrintChoose();
    DrawPlayButton();
    DisplayPicture();
  } else {
    ci::gl::clear(Color(0, 0, 0));
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
    song_voice_->start();
  }
}

void MyApp::PrintTitle() const {
  ci::gl::color(ci::Rand::randFloat(), ci::Rand::randFloat(),
                ci::Rand::randFloat());
  ci::gl::drawStrokedRect(Rectf(getWindowWidth() / 2 - 200.0f, 50,
                                getWindowWidth() / 2 + 200.0f, 250));
  PrintText("Music\nVisualizer", Color::white(), 80, ci::ivec2{500, 150},
            ci::vec2{getWindowWidth() / 2, 150});
}

void MyApp::PrintChoose() const {
  ci::gl::color(0, 0, 0);
  float font_size = 40;
  PrintText("Choose Your Song: ", Color::white(), font_size,
            ci::ivec2{1000, 150}, ci::vec2{170, getWindowHeight() / 2 - 50});
  PrintText("Choose Your Pattern: ", Color::white(), font_size,
            ci::ivec2{1000, 150}, ci::vec2{180, getWindowHeight() / 2 + 150});
}

void MyApp::DrawPlayButton() const {
  ci::gl::color(0, 1, 0);
  Rectf rect(650.0f, 700.0f, 770.0f, 750.0f);
  ci::gl::drawSolidRect(rect);
  PrintText("Play Pattern", Color::white(), 20, ci::ivec2{100, 150},
            ci::vec2{710, 725});
}

void MyApp::DisplayPicture() {
  ci::gl::Texture2dRef texture =
      ci::gl::Texture2d::create(loadImage(loadAsset("spiral.jpg")));
  const ci::vec2 locp = {100, 600};
  ci::gl::draw(texture, locp);
}

void MyApp::keyDown(KeyEvent event) { text_box_->keyDown(event); }

void MyApp::mouseDown(ci::app::MouseEvent event) {
  if (event.isLeft() && (event.getX() >= 650 && event.getX() <= 770) &&
      (event.getY() >= 700 && event.getY() <= 750)) {
    go_to_visualizer_ = true;
  } else if (!go_to_visualizer_) {
    text_box_->mouseDown(event);
  }

  // draw rect around selected pattern
  //  if (event.isLeft()) {
  //    cinder::gl::color(cinder::Color::white());
  //    cinder::gl::drawStrokedRect()
  //  }
}

void MyApp::mouseUp(ci::app::MouseEvent event) { text_box_->mouseUp(event); }

void MyApp::mouseDrag(ci::app::MouseEvent event) {
  text_box_->mouseDrag(event);
}

void MyApp::mouseMove(ci::app::MouseEvent event) {
  text_box_->mouseMove(event);
}

template <typename C>
void PrintText(const std::string& text, const C& color, float font_size,
               const ci::ivec2& size, const ci::vec2& loc) {
  ci::gl::color(color);

  auto box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(ci::Font("Arial", font_size))
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
}  // namespace myapp
