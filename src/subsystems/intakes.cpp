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

void resetLineSensors(){
  lineSensorTop.calibrate();
  lineSensorMiddle.calibrate();
  lineSensorBottom.calibrate();
}

//DRIVER CONTROL FUNCTIONS
void autoIndex() {
  setIntakes(127, 127);
  setIndexer(127, 50);

  bool top = false;
  bool middle = false;
  bool bottom = false;

  if(topLimitSwitch.get_value() || lineSensorTop.get_value() < 2500){
    top = true;
  }
  if(lineSensorMiddle.get_value() < 2300){
    middle = true;
  }
  if(lineSensorBottom.get_value() < 2400){
    bottom = true;
  }

  if(top) {
    setIntakes(127, 127);
    setIndexer(100, 0);

    if(middle) {
      setIntakes(127, 127);
      setIndexer(0, 0);

      if(bottom) {
        setIntakes(0, 0);
        setIndexer(0, 0);
      }
    }
  }
}

void cycle(){
  bool ballEjected = false;
  bool prevsensor = true;
  bool sensor = true;

  setIndexer(127, 127);
  while(1){
    sensor = (topLimitSwitch.get_value() || lineSensorTop.get_value() < 2500);
    if(!sensor && prevsensor){
      ballEjected = true;
    }
    if(ballEjected && sensor){
      setIndexer(0, 0);
      break;
    }
    prevsensor = sensor;
    delay(15);
    lcd::print(1, "ryan no pp %d", ballEjected);
  }
}

void intakeOne(){
  setIntakes(100, 100); setIndexer(127, 127);
  if(lineSensorBottom.get_value() < 2200){
    setIntakes(0, 0);
  }
  if(topLimitSwitch.get_value() || lineSensorTop.get_value() < 2500){
    setIndexer(0, 0);
  }
}
