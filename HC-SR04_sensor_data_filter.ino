long getDistance(long distance, int direct){
  int back = 0;     
  while(distance > 200 || distance < 0){
    if(back > 10){        //go back when always checking distance
      moveBackward(255);
      moveBackward(255);
    }
    
    switch(direct){
    case 1:   //check left distance again
      back++;
      distance = sr04_left.Distance();
      break;
    case 2:   //check front distance again
      back++;
      distance = sr04_front.Distance();
      break;
    case 3:   //check right distance again
      back++;
      distance = sr04_right.Distance();
      break;
    }
  }
  
  return distance;
}

void check_distance(int direct){    
  switch(direct){
    case 1:   //get left distance
      Left_Distance = getDistance(sr04_left.Distance(), 1);
      break;
    case 2:   //get front distance
      Front_Distance = getDistance(sr04_front.Distance(), 2);
      break;
    case 3:   //get right distance
      Right_Distance = getDistance(sr04_right.Distance(), 3);
      break;
  }
}
