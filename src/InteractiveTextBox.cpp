// Copyright (c) 2020 Benjamin Kulis. All rights reserved.

#include "InteractiveTextBox.h"

namespace myapp {

InteractiveTextBox::InteractiveTextBox(const cinder::Rectf& rect)
    : InteractiveObject(rect) {
  is_active = false;
  text = "Type in a link or a audio location path.";
  text_box.setText(text);
  text_box.setFont(cinder::Font("Arial", 24));
  text_box.setPremultiplied(true);
  text_box.setSize(cinder::ivec2(rect.getWidth(), rect.getHeight()));
  text_box.setBackgroundColor(cinder::Color::white());
  text_box.setColor(cinder::Color::black());
  default_text = true;
}

void InteractiveTextBox::draw() {
  if (is_active) {
    text_box.setBackgroundColor(cinder::Color(0.7f, 0.7f,
                                              1.0f));
  } else {
    text_box.setBackgroundColor(cinder::Color::white());
  }

  cinder::gl::color(cinder::Color::white());
  auto texture = cinder::gl::Texture2d::create(text_box.render());
  cinder::gl::draw(texture, rect);
}

void InteractiveTextBox::pressed() { is_active = true; }
void InteractiveTextBox::releasedOutside() { is_active = false; }

void InteractiveTextBox::keyDown(cinder::app::KeyEvent& event) {
  if (!is_active) return;
  if (default_text) {
    text = "";
    default_text = false;
  }

  if (event.getCode() == cinder::app::KeyEvent::KEY_BACKSPACE) {
    if (text.size() > 0) {
      text = text.substr(0, text.size() - 1);
    }
  } else {
    const char character = event.getChar();
    text += std::string(&character, 1);
  }

  text_box.setText(text);
}

}  // namespace myapp
