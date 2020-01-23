
var baseGunShotXs = [];
var baseGunShotYs = [];

function setup() {
  createCanvas(1200,700);
  frameRate(50);

  baseGunShotXs = [0];
  baseGunShotYs = [0];
  baseGunShotXs.push(60);
  console.log(baseGunShotXs);
}
var shotXVelocities = [];
var shotYVelocities = [];
var baseHealth = 100;
var baseGunAngle = 0;
var baseGunPower = 10;
var baseGunSpeed = 5;
var maxGunPower = 25;
var pressedKeys = [];
var gravity = 10;
for(var i = 0; i < 255; i++) {
  pressedKeys.push(false);
}
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
  if(pressedKeys[32]) {
    console.log(baseGunShotXs);
      baseGunShotXs.push(60+70*Math.sin(baseGunAngle+90));
      baseGunShotYs.push(600+70*Math.cos(baseGunAngle+90));
      shotXVelocities.push(baseGunPower*Math.sin(baseGunAngle+90));
      shotYVelocities.push(baseGunPower*Math.cos(baseGunAngle+90));
  }
  for(var i = 0; i < baseGunShotXs.length; i++) {
      fill(64,64,64);
      strokeWeight(5);
      ellipse(baseGunShotXs[i],baseGunShotYs[i],20,20);
      baseGunShotXs[i]+=shotXVelocities;
      baseGunShotXs[i]-=shotYVelocities;
      shotYVelocities+=gravity;
      if(shotYVelocities >= 700) {
          baseGunShotXs.splice(i,1);
          baseGunShotYs.splice(i,1); 
          shotXVelocities.splice(i,1);
          shotYVelocities.splice(i,1);
      }
  }
}
