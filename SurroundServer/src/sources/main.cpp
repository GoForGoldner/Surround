#include "controller.h"

int main() {
  Model model(32);
  Controller controller(model);
  controller.begin();
}