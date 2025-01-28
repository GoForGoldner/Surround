#include "controller.h"
#include "view.h"

int main() {
  Model model(32);
  View view(32);
  Controller controller(model, view);
  controller.begin();
}