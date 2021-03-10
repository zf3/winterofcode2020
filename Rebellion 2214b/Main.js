function setup() {
  createCanvas(1200,600);
  frameRate(50);
  for(var i = 0; i < 255; i++) {
    pressedKeys.push(false);
  }
}
var pressedKeys = [];
var is1H = true;
var playerX = 0;
var playerY = 0;
var LHA = 0;
var LHL = 50;
var RHA = 0;
var RHL = 50;
var playerXVel = 0;
var playerMaxXVel = 5;
var playerXVelAcc = 0.2;
var playerXVelDeAcc = 0.1;
var playerYVel = 0;
var isPointingRight = true;
var playerJumpPower = 8;
var gravity = 0.2;
var prevPX = 0;
var prevPY = 0;
var shotXs = [];
var shotYs = [];
var shotXVels = [];
var shotYVels = [];
var shotAngles = [];
var tick = 0;
var cooldown = 50;
var gunPower = 10;
var touchingPlatform = false;
var touchingPlatform2 = false;
var platformXs = [-250,-750,500];
var platformYs = [70,570,-30];
var platformWidths = [510,2000,500];
var platformHeights = [500,400,600];
var platformTypes = [1,2,1];
var drawBackground = function(type) {
  switch(type) {
    case 1:
    background(192,192,192);
    break;
  }
}
var drawWeapon = function(x,y,angle,type,isPointingRight) {
  switch(type) {
    case 1:
    fill(192,192,192);
    strokeWeight(1);
    if(isPointingRight === true) {
      quad(x+sin(angle+90)*5,y+cos(angle+90)*5,x+sin(angle-90)*5,y+cos(angle-90)*5,
      x+sin(angle-90)*5+sin(angle)*3,y+cos(angle-90)*5+cos(angle)*3,
      x+sin(angle+90)*5+sin(angle)*3,y+cos(angle+90)*5+cos(angle)*3);
      quad(x+sin(angle+90)*5,y+cos(angle+90)*5,x+sin(angle+90)*2,y+cos(angle+90)*2,
      x+sin(angle+90)*2+sin(angle)*20,y+cos(angle+90)*2+cos(angle)*20,
      x+sin(angle+90)*5+sin(angle)*20,y+cos(angle+90)*5+cos(angle)*20);
    }
    if(isPointingRight === false) {
      quad(x+sin(angle+90)*5,y+cos(angle+90)*5,x+sin(angle-90)*5,y+cos(angle-90)*5,
      x+sin(angle-90)*5+sin(angle)*3,y+cos(angle-90)*5+cos(angle)*3,
      x+sin(angle+90)*5+sin(angle)*3,y+cos(angle+90)*5+cos(angle)*3);
      quad(x-sin(angle+90)*5,y-cos(angle+90)*5,x-sin(angle+90)*2,y-cos(angle+90)*2,
      x-sin(angle+90)*2+sin(angle)*20,y-cos(angle+90)*2+cos(angle)*20,
      x-sin(angle+90)*5+sin(angle)*20,y-cos(angle+90)*5+cos(angle)*20);
    }
    break;
  }
}
var drawEnemy = function(pX,pY) {
  fill(255,255,255)
  strokeWeight(2);
  stroke(0,0,0);
  rect(pX-20+600-playerX,pY-30+300-playerY,40,60);
  ellipse(pX+600-playerX,pY-50+300-playerY,40,40);
  rect(pX-15+600-playerX,pY+30+300-playerY,10,40);
  rect(pX+5+600-playerX,pY+30+300-playerY,10,40);
  fill(0,0,0);
  rect(pX-8+600-playerX,pY-56+300-playerY,4,12,2);
  rect(pX+4+600-playerX,pY-56+300-playerY,4,12,2);
  strokeWeight(3);
  line(pX+3+600-playerX,pY-58+300-playerY,pX+9+600-playerX,pY-61+300-playerY);
  line(pX-9+600-playerX,pY-58+300-playerY,pX-3+600-playerX,pY-58+300-playerY);
  strokeWeight(5);
  line(pX-10+600-playerX,pY-70+300-playerY,pX+10+600-playerX,pY-70+300-playerY);
}
var drawEnemyHands = function(pX,pY,h1A,h1L,h2A,h2L,isPointingRight) {
  fill(255,255,255)
  strokeWeight(2);
  stroke(0,0,0);
  if(isPointingRight === false) {
  quad(pX+600-playerX-20+sin(h1A-90)*5,pY+300-playerY-28+cos(h1A-90)*5,
  pX+600-playerX-20+sin(h1A+90)*5,pY+300-playerY-28+cos(h1A+90)*5,
  pX+600-playerX-20+sin(h1A+90)*5+sin(h1A)*h1L,pY+300-playerY-28+cos(h1A+90)*5+cos(h1A)*h1L,
  pX+600-playerX-20+sin(h1A-90)*5+sin(h1A)*h1L,pY+300-playerY-28+cos(h1A-90)*5+cos(h1A)*h1L);
  }
  quad(pX+600-playerX+20+sin(h2A-90)*5,pY+300-playerY-28+cos(h2A-90)*5,
  pX+600-playerX+20+sin(h2A+90)*5,pY+300-playerY-28+cos(h2A+90)*5,
  pX+600-playerX+20+sin(h2A+90)*5+sin(h2A)*h2L,pY+300-playerY-28+cos(h2A+90)*5+cos(h2A)*h2L,
  pX+600-playerX+20+sin(h2A-90)*5+sin(h2A)*h2L,pY+300-playerY-28+cos(h2A-90)*5+cos(h2A)*h2L);
  if(isPointingRight === true) {
    quad(pX+600-playerX-20+sin(h1A-90)*5,pY+300-playerY-28+cos(h1A-90)*5,
    pX+600-playerX-20+sin(h1A+90)*5,pY+300-playerY-28+cos(h1A+90)*5,
    pX+600-playerX-20+sin(h1A+90)*5+sin(h1A)*h1L,pY+300-playerY-28+cos(h1A+90)*5+cos(h1A)*h1L,
    pX+600-playerX-20+sin(h1A-90)*5+sin(h1A)*h1L,pY+300-playerY-28+cos(h1A-90)*5+cos(h1A)*h1L);
  }
}
var drawPlayer = function(pX,pY) {
  fill(255,255,255)
  strokeWeight(2);
  stroke(0,0,0);
  rect(pX-20,pY-30,40,60);
  ellipse(pX,pY-50,40,40);
  rect(pX-15,pY+30,10,40);
  rect(pX+5,pY+30,10,40);
  fill(0,0,0);
  rect(pX-8,pY-56,4,12,2);
  rect(pX+4,pY-56,4,12,2);
  strokeWeight(3);
  line(pX+3,pY-58,pX+9,pY-61);
  line(pX-9,pY-58,pX-3,pY-58);
  strokeWeight(5);
  line(pX-10,pY-70,pX+10,pY-70);
}
var drawPlayerHands = function(pX,pY,h1A,h1L,h2A,h2L,isPointingRight) {
  fill(255,255,255)
  strokeWeight(2);
  stroke(0,0,0);
  if(isPointingRight === false) {
  quad(pX-20+sin(h1A-90)*5,pY-28+cos(h1A-90)*5,pX-20+sin(h1A+90)*5,pY-28+cos(h1A+90)*5,
  pX-20+sin(h1A+90)*5+sin(h1A)*h1L,pY-28+cos(h1A+90)*5+cos(h1A)*h1L,
  pX-20+sin(h1A-90)*5+sin(h1A)*h1L,pY-28+cos(h1A-90)*5+cos(h1A)*h1L);
  }
  quad(pX+20+sin(h2A-90)*5,pY-28+cos(h2A-90)*5,pX+20+sin(h2A+90)*5,pY-28+cos(h2A+90)*5,
  pX+20+sin(h2A+90)*5+sin(h2A)*h2L,pY-28+cos(h2A+90)*5+cos(h2A)*h2L,
  pX+20+sin(h2A-90)*5+sin(h2A)*h2L,pY-28+cos(h2A-90)*5+cos(h2A)*h2L);
  if(isPointingRight === true) {
    quad(pX-20+sin(h1A-90)*5,pY-28+cos(h1A-90)*5,pX-20+sin(h1A+90)*5,pY-28+cos(h1A+90)*5,
    pX-20+sin(h1A+90)*5+sin(h1A)*h1L,pY-28+cos(h1A+90)*5+cos(h1A)*h1L,
    pX-20+sin(h1A-90)*5+sin(h1A)*h1L,pY-28+cos(h1A-90)*5+cos(h1A)*h1L);
  }
}
var defineRectPlatform = function(x,y,width,height,type) {
  strokeWeight(5);
  switch(type) {
  case 1:
  fill(96,0,0);
  rect(x+600-playerX,y+300-playerY,width,height);
  break;
  case 2:
  fill(64,32,32);
  rect(x+600-playerX,y+300-playerY,width,height);
  for(var i = 0; i < (width/30); i++) {
    fill(0,192,0);
    triangle(x-10+i*30+600-playerX,y+300-playerY,x+40+i*30+600-playerX,y+300-playerY,x+15+i*30+600-playerX,y+40+300-playerY);
  }
  break;
  }
  for(var i = 0; i < shotXs.length; i++) {
    if(shotXs[i] >= x && shotXs[i] <= x+width && shotYs[i] >= y && shotYs[i] <= y+height) {
      shotXs.splice(i,1);
      shotYs.splice(i,1);
      shotXVels.splice(i,1);
      shotYVels.splice(i,1);
      shotAngles.splice(i,1);
    }
  }
  if(dist(playerY,0,y+height/2,0) < height/2+70 
  && dist(playerY,0,y+height/2,0) < dist(prevPY,0,y+height/2,0) 
  && dist(playerY,0,y+height/2,0) < height/2+70
  && dist(playerX,0,x+width/2,0) < width/2+20) {
    playerY = prevPY;
    playerYVel = 0;
    touchingPlatform = true;
  }
}
var defineRectPlatform2 = function(x,y,width,height) {
  if(dist(playerX,0,x+width/2,0) < width/2+25 
  && dist(playerX,0,x+width/2,0) < dist(prevPX,0,x+width/2,0) 
  && dist(playerX,0,x+width/2,0) < width/2+25
  && dist(playerY,0,y+height/2,0) < height/2+60) {
    playerX = prevPX;
    playerXVel = 0;
    playerY = prevPY;
    playerYVel = 0;
    touchingPlatform2 = true;
  }
}
keyPressed = function() {
  pressedKeys[keyCode] = true;
}
keyReleased = function() {
  pressedKeys[keyCode] = false;
}
function draw() {
  prevPX = playerX;
  prevPY = playerY;
  drawBackground(1);
  drawPlayer(600,300);
  drawEnemy(550,-100);
  drawEnemyHands(550,-100,0,50,0,50,true);
  if((((LHA+RHA)/2)+360)%360 <= 180) {
    isPointingRight = true;
  }
  if((((LHA+RHA)/2)+360)%360 > 180) {
    isPointingRight = false;
  }
  if(is1H === true) {
    LHA = 90-(atan2((mouseY-270),(mouseX-580)))*180/PI;
    RHA = 90-(atan2((mouseY-270),(mouseX-620)))*180/PI;
    if(isPointingRight === true) {
      drawWeapon(620+sin(RHA/180*PI)*RHL,270+cos(RHA/180*PI)*RHL,RHA/180*PI,1,isPointingRight);
      drawPlayerHands(600,300,LHA/180*PI,LHL,RHA/180*PI,RHL,isPointingRight);
      drawWeapon(580+sin(LHA/180*PI)*LHL,270+cos(LHA/180*PI)*LHL,LHA/180*PI,1,isPointingRight);
    }
    else {
      drawWeapon(580+sin(LHA/180*PI)*LHL,270+cos(LHA/180*PI)*LHL,LHA/180*PI,1,isPointingRight);
      drawPlayerHands(600,300,LHA/180*PI,LHL,RHA/180*PI,RHL,isPointingRight);
      drawWeapon(620+sin(RHA/180*PI)*RHL,270+cos(RHA/180*PI)*RHL,RHA/180*PI,1,isPointingRight);
    }
  }
  if(pressedKeys[68] === true && playerXVel < playerMaxXVel) {
    playerXVel += playerXVelAcc;
  }
  if(playerXVel > 0 && pressedKeys[68] === false) {
    playerXVel -= playerXVelDeAcc;
  }
  if(pressedKeys[65] === true && playerXVel > -playerMaxXVel) {
    playerXVel -= playerXVelAcc;
  }
  if(playerXVel < 0 && pressedKeys[65] === false) {
    playerXVel += playerXVelDeAcc;
  }
  playerYVel += gravity;
  if(pressedKeys[87] === true && touchingPlatform === true) {
    playerYVel -= playerJumpPower;
  }
  for(var i = 0; i < shotXs.length; i++) {
    strokeWeight(3);
    line(shotXs[i]+600-playerX,shotYs[i]+300-playerY,
    shotXs[i]+5*sin(shotAngles[i])+600-playerX,
    shotYs[i]+5*cos(shotAngles[i])+300-playerY);
    shotXs[i] += shotXVels[i];
    shotYs[i] += shotYVels[i];
  }
  if(tick >= cooldown && mouseIsPressed === true) {
    if(is1H = true) {
      shotXs.push(playerX+20+sin(RHA/180*PI)*RHL);
      shotYs.push(playerY-30+cos(RHA/180*PI)*RHL);
      shotAngles.push(RHA/180*PI);
      shotXVels.push(sin(RHA/180*PI)*gunPower);
      shotYVels.push(cos(RHA/180*PI)*gunPower);
      shotXs.push(playerX-20+sin(LHA/180*PI)*LHL);
      shotYs.push(playerY-30+cos(LHA/180*PI)*LHL);
      shotAngles.push(LHA/180*PI);
      shotXVels.push(sin(LHA/180*PI)*gunPower);
      shotYVels.push(cos(LHA/180*PI)*gunPower);
    }
    tick = 0;
  }
  playerX += playerXVel;
  playerY += playerYVel;
  tick++;
  if(playerY > 1000) {
    playerY = 0;
    playerX = 0;
    playerXVel = 0;
    playerYVel = 0;
  }
  touchingPlatform = false;
  touchingPlatform2 = false;
  for(var i = 0; i < platformXs.length; i++) {
    defineRectPlatform2(platformXs[i],platformYs[i],platformWidths[i],platformHeights[i]);
  }
  if(pressedKeys[87] === true && touchingPlatform2 === true && touchingPlatform === false) {
    playerY -= 2;
  }
  if(pressedKeys[83] === true && touchingPlatform2 === true && touchingPlatform === false) {
    playerY += 2;
  }
  for(var i = 0; i < platformXs.length; i++) {
    defineRectPlatform(platformXs[i],platformYs[i],platformWidths[i],platformHeights[i],platformTypes[i]);
  }
}