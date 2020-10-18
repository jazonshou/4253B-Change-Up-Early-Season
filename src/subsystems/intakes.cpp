#include "main.h"

//HELPER FUNCTIONS
//Function: sets left and right intakes
void setIntakes(int left, int right) {
  intakeLeft = left;
  intakeRight = right;
}
//Function: sets bottom and top rollers/indexers
void setIndexer(int bottom, int top) {
  indexerBottom = bottom;
  indexerTop = top;
}

//DRIVER CONTROL FUNCTIONS
void autoIndex() {
    //in the beginning, sets all intakes/rollers to max speed
    //except for the very top roller to prevent the ball from overshooting
    setIntakes(127, 127);
    setIndexer(127, 75);

    bool top = false;
    bool middle = false;
    bool bottom = false;

    //if the top sensor detects a ball...
    //stop the top roller and slow down the bottom roller
    if(lineSensorTop.get_value() < 2300){
      top = true;
    }
    //if the top & the bottom seonsors detect a ball...
    //stop both rollers and slow down intakes
    if(lineSensorMiddle.get_value() < 2300){
      middle = true;
    }
    //if all sensors detect a ball...
    //stop all motors
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
