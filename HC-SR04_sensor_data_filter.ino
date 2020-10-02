long getDistance(long distance, int direct){
  int back = 0;     
  while(distance > 200 && distance < 0){
    if(back > 10){        //go back when always checking distance
      moveBackward(50);
    }
    
    switch(direct){
    case 1:   //check left distance
      back++;
      distance = sr04_left.Distance();//读取超声波距离
      break;
    case 2:   //check front distance
      back++;
      distance = sr04_front.Distance();//读取超声波距离
      break;
    case 3:   //check right distance
      back++;
      distance = sr04_right.Distance();//读取超声波距离
      break;
    }
  }
  
  return distance;
}

void check_distance(int direct){    
  switch(direct){
    case 1:   //get left distance
      Left_Distance = getDistance(sr04_left.Distance(), 1);//读取超声波距离
      break;
    case 2:   //get front distance
      Front_Distance = getDistance(sr04_front.Distance(), 2);//读取超声波距离
      break;
    case 3:   //get right distance
      Right_Distance = getDistance(sr04_right.Distance(), 3);//读取超声波距离
      break;
  }
}
