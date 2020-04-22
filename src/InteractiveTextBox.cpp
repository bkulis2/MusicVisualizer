// Copyright (c) 2020 Benjamin Kulis. All rights reserved.

#include "InteractiveTextBox.h"

namespace myapp {

InteractiveTextBox::InteractiveTextBox(const cinder::Rectf& rect)
    : InteractiveObject(rect) {
  mActive = false;
  mText = "Write some text";
  mTextBox.setText(mText);
  mTextBox.setFont(cinder::Font("Arial", 24));
  mTextBox.setPremultiplied(true);
  mTextBox.setSize(cinder::ivec2(rect.getWidth(), rect.getHeight()));
  mTextBox.setBackgroundColor(cinder::Color::white());
  mTextBox.setColor(cinder::Color::black());
  mFirstText = true;
}

void InteractiveTextBox::draw() {
  if (mActive) {
    mTextBox.setBackgroundColor(cinder::Color(0.7f, 0.7f,
                                              1.0f));
  } else {
    mTextBox.setBackgroundColor(cinder::Color::white());
  }
  cinder::gl::color(cinder::Color::white());
  auto texture = cinder::gl::Texture2d::create(mTextBox.render());
  cinder::gl::draw(texture, rect);
}

void InteractiveTextBox::pressed() { mActive = true; }
void InteractiveTextBox::releasedOutside() { mActive = false; }

void InteractiveTextBox::keyDown(cinder::app::KeyEvent& event) {
  if (!mActive) return;
  if (mFirstText) {
    mText = "";
    mFirstText = false;
  }
  if (event.getCode() == cinder::app::KeyEvent::KEY_BACKSPACE) {
    if (mText.size() > 0) {
      mText = mText.substr(0, mText.size() - 1);
    }
  } else {
    const char character = event.getChar();
    mText += std::string(&character, 1);
  }
  mTextBox.setText(mText);
}

}  // namespace myapp
