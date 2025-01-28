#include "controller.h"

int main() {
  Model model(25);
  Controller controller(model);
  controller.begin();
}