//  







#include "animatorobject.h"


AnimatedObject::AnimatedObject(NeoPixelBus* bus, NeoPixelAnimator* animator, uint8_t n):  
	_bus(bus), 
	_animator(animator),
	_ObjectCount(n)
{

    _objects= new ObjectContext[n];

}

AnimatedObject::~AnimatedObject()
{
    _bus = NULL;
    _animator = NULL; 

    if (_objects)
    {
        delete[] _objects;
        _objects = NULL;
    }
}




uint8_t AnimatedObject::Add(ObjectCallback Objectupdate) {

  uint8_t n; //  = 0; 

  if (_ActiveObjectsCount == _ObjectCount) return false; 

  for (n = 0; n < _ObjectCount; n++ ) {

  	if ( ! _objects[n].isRunning ) break; 
  }

  // do {
  // 	n++; 
  // } while (_objects[n].isRunning == true); 

    _objects[n].fnUpdate = Objectupdate;
    _objects[n].isRunning = true; 
    //Serial.printf("is Running = %u \n", _objects[n].isRunning ) ;
    _ActiveObjectsCount++;
    return n + 1; // returns 0 if failed, 1 = slot 1, 2 = slot 2 etc.....  

}


void AnimatedObject::Stop(uint8_t n) {
  _ActiveObjectsCount--;
  _objects[n].isRunning = false; 

} 

void AnimatedObject::UpdateAll() {
			//Serial.print("Update Called: ");

            ObjectContext* pObject;

			for (uint8_t n = 0; n < _ObjectCount; n++ )  {	
				    pObject = &_objects[n]; 
					if (pObject->isRunning) pObject->fnUpdate();
			}

			
			//Serial.println(); 

}


void AnimatedObject::Begin()
 
 {


}