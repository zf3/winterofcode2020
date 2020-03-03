function setup() {
  createCanvas(1200,600);
  frameRate(50);
}
var animSpeed = 10;
var animLength = 800/animSpeed;
var LHA = 0;
var RHA = 0;
var tick = 0;
var drawBackground = function(type) {
  switch(type) {
    case 1:
    background(128,128,128);
    break;
  }
}
var drawWeapon = function(h1X,h1Y,h2X,h2Y) {
  strokeWeight(10)
  stroke(0,255,255);
  line(h1X,h1Y,2*h2X-h1X, 2*h2Y-h1Y);
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
var drawPlayerRightArm = function(pX,pY,h2A,h2L) {
    fill(255,255,255)
    strokeWeight(2);
    stroke(0,0,0);
    quad(pX+20+sin(h2A-90)*5,pY-28+cos(h2A-90)*5,pX+20+sin(h2A+90)*5,pY-28+cos(h2A+90)*5,
    pX+20+sin(h2A+90)*5+sin(h2A)*h2L,pY-28+cos(h2A+90)*5+cos(h2A)*h2L,
    pX+20+sin(h2A-90)*5+sin(h2A)*h2L,pY-28+cos(h2A-90)*5+cos(h2A)*h2L);
}
var drawPlayerLeftArm = function(pX,pY,h1A,h1L) {
  fill(255,255,255)
  strokeWeight(2);
  stroke(0,0,0);
  quad(pX-20+sin(h1A-90)*5,pY-28+cos(h1A-90)*5,pX-20+sin(h1A+90)*5,pY-28+cos(h1A+90)*5,
  pX-20+sin(h1A+90)*5+sin(h1A)*h1L,pY-28+cos(h1A+90)*5+cos(h1A)*h1L,
  pX-20+sin(h1A-90)*5+sin(h1A)*h1L,pY-28+cos(h1A-90)*5+cos(h1A)*h1L);
}
function draw() {
  drawBackground(1);
  if(tick <= 90/animSpeed) {
    LHA += animSpeed;
    RHA += animSpeed;
    tick++;
    drawPlayer(600,300);
    drawPlayerRightArm(600,300,RHA/180*PI,50)
    drawPlayerLeftArm(600,300,LHA/180*PI,50)
  }
  if(tick > 90/animSpeed && tick <= 200/animSpeed) {
    LHA -= animSpeed;
    RHA -= animSpeed;
    tick++;
    drawPlayerRightArm(600,300,RHA/180*PI,50)
    drawPlayer(600,300);
    drawPlayerLeftArm(600,300,LHA/180*PI,50)
  }
  if(tick > 200/animSpeed && tick <= 310/animSpeed) {
    LHA += animSpeed;
    RHA += animSpeed;
    tick++;
    drawPlayerRightArm(600,300,RHA/180*PI,50)
    drawPlayer(600,300);
    drawPlayerLeftArm(600,300,LHA/180*PI,50)
  }
  if(tick > 310/animSpeed && tick <= 490/animSpeed) {
    LHA -= animSpeed;
    RHA -= animSpeed;
    tick++;
    drawPlayer(600,300);
    drawPlayerRightArm(600,300,RHA/180*PI,50)
    drawPlayerLeftArm(600,300,LHA/180*PI,50)
  }
  if(tick > 490/animSpeed && tick <= 600/animSpeed) {
    LHA += animSpeed;
    RHA += animSpeed;
    tick++;
    drawPlayerLeftArm(600,300,LHA/180*PI,50)
    drawPlayer(600,300);
    drawPlayerRightArm(600,300,RHA/180*PI,50)
  }
  if(tick > 600/animSpeed && tick <= 710/animSpeed) {
    LHA -= animSpeed;
    RHA -= animSpeed;
    tick++;
    drawPlayerLeftArm(600,300,LHA/180*PI,50)
    drawPlayer(600,300);
    drawPlayerRightArm(600,300,RHA/180*PI,50)
  }
  if(tick > 710/animSpeed && tick <= 800/animSpeed) {
    LHA += animSpeed;
    RHA += animSpeed;
    tick++;
    drawPlayer(600,300);
    drawPlayerRightArm(600,300,RHA/180*PI,50)
    drawPlayerLeftArm(600,300,LHA/180*PI,50)
  }
  if(tick > animLength) {
    tick = 0;
    LHA = 0;
    RHA = 0;
  }
}