// Copyright (c) 2020 Benjamin Kulis. All rights reserved.

#include "InteractiveObject.h"

namespace myapp {
InteractiveObject::InteractiveObject(const cinder::Rectf& rect) {
  this->rect = rect;
  pressedColor = cinder::Color(1.0f, 0.0f, 0.0f);
  idleColor = cinder::Color(0.7f, 0.7f, 0.7f);
  overColor = cinder::Color(1.0f, 1.0f, 1.0f);
  strokeColor = cinder::Color(0.0f, 0.0f, 0.0f);
  mPressed = false;
  mOver = false;
}

InteractiveObject::~InteractiveObject() = default;

void InteractiveObject::draw() {
  if (mPressed) {
    cinder::gl::color(pressedColor);
  } else if (mOver) {
    cinder::gl::color(overColor);
  } else {
    cinder::gl::color(idleColor);
  }
  cinder::gl::drawSolidRect(rect);
  cinder::gl::color(strokeColor);
  cinder::gl::drawStrokedRect(rect);
}

void InteractiveObject::pressed() {
  cinder::app::console() << "pressed" << std::endl;
}

void InteractiveObject::pressedOutside() {
  cinder::app::console() << "pressed outside" << std::endl;
}
void InteractiveObject::released() {
  cinder::app::console() << "released" << std::endl;
}

void InteractiveObject::releasedOutside() {
  cinder::app::console() << "released outside" << std::endl;
}
void InteractiveObject::rolledOver() {
  cinder::app::console() << "rolled over" << std::endl;
}

void InteractiveObject::rolledOut() {
  cinder::app::console() << "rolled out" << std::endl;
}

void InteractiveObject::dragged() {
  cinder::app::console() << "dragged" << std::endl;
}

void InteractiveObject::mouseDown(cinder::app::MouseEvent& event) {
  if (rect.contains(event.getPos())) {
    mPressed = true;
    mOver = false;
    pressed();
  } else {
    pressedOutside();
  }
}

void InteractiveObject::mouseUp(cinder::app::MouseEvent& event) {
  if (rect.contains(event.getPos())) {
    if (mPressed) {
      mPressed = false;
      mOver = true;
      released();
    }
  } else {
    mPressed = false;
    mOver = false;
    releasedOutside();
  }
}

void InteractiveObject::mouseDrag(cinder::app::MouseEvent& event) {
  if (mPressed && rect.contains(event.getPos())) {
    mPressed = true;
    mOver = false;
    dragged();
  }
}

void InteractiveObject::mouseMove(cinder::app::MouseEvent& event) {
  if (rect.contains(event.getPos())) {
    if (!mOver) {
      mPressed = false;
      mOver = true;
      rolledOver();
    }
  } else {
    if (mOver) {
      mPressed = false;
      mOver = false;
      rolledOut();
    }
  }
}

}  // namespace myapp