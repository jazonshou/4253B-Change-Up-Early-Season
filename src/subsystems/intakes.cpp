#include "main.h"

//HELPER FUNCTIONS
void setIntakes(int left, int right) {
  intakeLeft = left;
  intakeRight = right;
}

void setIndexer(int bottom, int top) {
  indexerBottom = bottom;
  indexerTop = top;
}

//DRIVER CONTROL FUNCTIONS
void autoIndex() {
    setIntakes(127, 127);
    setIndexer(127, 75);

    bool top = false;
    bool middle = false;
    bool bottom = false;

    if(lineSensorTop.get_value() < 2300){
      top = true;
    }
    if(lineSensorMiddle.get_value() < 2300){
      middle = true;
    }
    if(lineSensorBottom.get_value() < 2000){
      bottom = true;
    }

    if(top) {
      setIntakes(127, 127);
      setIndexer(100, 0);

      if(middle) {
        setIntakes(120, 120);
        setIndexer(0, 0);

        if(bottom) {
          setIntakes(0, 0);
          setIndexer(0, 0);
        }
      }
    }
}
