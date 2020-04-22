// Copyright (c) 2020 Benjamin Kulis. All rights reserved.

#ifndef FINALPROJECT_INTERACTIVEOBJECT_H
#define FINALPROJECT_INTERACTIVEOBJECT_H

#include "InteractiveObject.h"

#pragma once
#include <cinder/Color.h>
#include <cinder/Rect.h>
#include <cinder/app/App.h>
#include <cinder/app/MouseEvent.h>
#include <cinder/gl/gl.h>

namespace myapp {
class InteractiveObject {
 public:
  InteractiveObject(const cinder::Rectf& rect);
  virtual ~InteractiveObject();
  virtual void draw();
  virtual void pressed();
  virtual void pressedOutside();
  virtual void released();
  virtual void releasedOutside();
  virtual void rolledOver();
  virtual void rolledOut();
  virtual void dragged();
  void mouseDown(cinder::app::MouseEvent& event);
  void mouseUp(cinder::app::MouseEvent& event);
  void mouseDrag(cinder::app::MouseEvent& event);
  void mouseMove(cinder::app::MouseEvent& event);
  cinder::Rectf rect;
  cinder::Color pressedColor, idleColor, overColor, strokeColor;

 protected:
  bool mPressed, mOver;
};

}  // namespace myapp

#endif  // FINALPROJECT_INTERACTIVEOBJECT_H
