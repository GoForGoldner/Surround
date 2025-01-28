#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

class Controller {
 public:
  Controller(Model& model);
  void begin();

 private:
  Model& m_model;
};

#endif  // Ends CONTROLLER_H