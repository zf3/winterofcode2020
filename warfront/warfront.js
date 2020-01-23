function setup() {
  createCanvas(1200,700);
  frameRate(50);
  for(var i = 0; i < 255; i++) {
    pressedKeys.push(false);
  }
}
var baseGunShotXs = [];
var baseGunShotYs = [];
var shotXVelocities = [];
var shotYVelocities = [];
var baseHealth = 100;
var baseGunAngle = 0;
var baseGunPower = 10;
var baseGunSpeed = 5;
var maxGunPower = 25;
var pressedKeys = [];
var gravity = 0.08;
var firerate = 100;
var tick = 0;
var drawBase = function(a,b,c,d) {
  switch(d) {
      case 0:
      strokeWeight(5);
      fill(0,0,255);
      quad(a+50+10*sin(c),b+50+10*cos(c),a+50+10*sin(c+180),b+50+10*cos(c+180),
      a+50+10*sin(c+180)+70*sin(c+90),b+50+10*cos(c+180)+70*cos(c+90),
      a+50+10*sin(c)+70*sin(c+90),b+50+10*cos(c)+70*cos(c+90));
      strokeWeight(1);
      fill(0,255,0);
      quad(a+50+10*sin(c),b+50+10*cos(c),a+50+10*sin(c+180),b+50+10*cos(c+180),
      a+50+10*sin(c+180)+baseGunPower*sin(c+90),b+50+10*cos(c+180)+baseGunPower*cos(c+90),
      a+50+10*sin(c)+baseGunPower*sin(c+90),b+50+10*cos(c)+baseGunPower*cos(c+90));
      strokeWeight(5);
      fill(0,0,255,200);
      arc(a+50,b+50,100,100,90,360);
      fill(0,0,255,255);
      rect(a,b+50,100,100);
      strokeWeight(10);
      line(a+50+10*sin(c+180)+70*sin(c+90),b+50+10*cos(c+180)+70*cos(c+90),
      a+50+10*sin(c)+70*sin(c+90),b+50+10*cos(c)+70*cos(c+90));
      break;
      }
};
function keyPressed () {
  pressedKeys[keyCode] = true;
}

function keyReleased () {
  pressedKeys[keyCode] = false;
}

function draw() {
  tick++;
  background(128,128,255);
  drawBase(10,550,(baseGunAngle-30)/180*PI,0);
  if(pressedKeys[87] && baseGunAngle <= 180) {
      baseGunAngle+=1/baseGunSpeed;
  }
  if(pressedKeys[83] && baseGunAngle >= 0) {
      baseGunAngle-=1/baseGunSpeed;
  }
  if(pressedKeys[68] && baseGunPower <= maxGunPower) {
      baseGunPower+=1/baseGunSpeed;
  }
  if(pressedKeys[65] && baseGunPower >= 0 ) {
      baseGunPower-=1/baseGunSpeed;
  }
  if(pressedKeys[32] && tick % firerate === 0) {
      print(baseGunShotXs.length);
      baseGunShotXs.push(60+70*sin((baseGunAngle-270)/180*PI));
      baseGunShotYs.push(600+70*cos((baseGunAngle-270)/180*PI));
      shotXVelocities.push(baseGunPower/10*sin((baseGunAngle-270)/180*PI));
      shotYVelocities.push(-baseGunPower/10*cos((baseGunAngle-270)/180*PI));
  }
  for(var i = 0; i < baseGunShotXs.length; i++) {
      fill(64,64,64);
      strokeWeight(5);
      ellipse(baseGunShotXs[i],baseGunShotYs[i],20,20);
      baseGunShotXs[i]+=shotXVelocities[i];
      baseGunShotYs[i]-=shotYVelocities[i];
      shotYVelocities[i]-=gravity;
      if(baseGunShotYs[i] >= 700) {
          baseGunShotXs.splice(i,1);
          baseGunShotYs.splice(i,1); 
          shotXVelocities.splice(i,1);
          shotYVelocities.splice(i,1);
      }
  }
}
