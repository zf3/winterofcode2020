function setup() {
  createCanvas(1200,700);
  frameRate(50);
  for(var i = 0; i < 255; i++) {
    pressedKeys.push(false);
  }
}
var pauseGame = false;
var gameScreen = 0;
var shotSize = 20;
var enemyShotSize = 20;
var multiplier = 1;
var enemyMultiplier = 1;
var totalGunAoE;
var totalEnemyGunAoE;
var targetEnemyAngle;
var bestCandidate = 1000;
var amountOfCandidates = 10;
var amountOfMortarCandidates = 10;
var enemyBaseShooting = false;
var enemyTarget;
var weaponType = 0;
var armorUses = 0;
var economy = 5;
var money = 100;
var gunDamage = 10;
var gunAoE = 0;
var baseGunShotXs = [];
var baseGunShotYs = [];
var shotXVelocities = [];
var shotYVelocities = [];
var unitSpeeds = [];
var unitXs = [];
var unitYs = [];
var unitTypes = [];
var unitAngles = [];
var unitHealths = [];
var unitTicks = [];
var unitTargetAngles = [];
var mortarShotXs = [];
var mortarShotYs = [];
var mortarShotXVels = [];
var mortarShotYVels = [];
var baseHealth = 500;
var baseArmor = 0;
var baseGunAngle = 0;
var baseGunPower = 35;
var baseGunSpeed = 2.5;
var maxGunPower = 35;
var enemyEconomy = 5;
var enemyMoney = 100;
var enemyGunDamage = 10;
var enemyGunAoE = 0;
var enemyBaseGunShotXs = [];
var enemyBaseGunShotYs = [];
var enemyShotXVelocities = [];
var enemyShotYVelocities = [];
var enemyWeaponType = 0;
var enemyUnitSpeeds = [];
var enemyUnitXs = [];
var enemyUnitYs = [];
var enemyUnitTypes = [];
var enemyUnitAngles = [];
var enemyUnitHealths = [];
var enemyUnitTicks = [];
var enemyBaseHealth = 500;
var enemyBaseArmor = 0;
var enemyBaseGunAngle = 0;
var enemyBaseGunPower = 35;
var enemyBaseGunSpeed = 2.5;
var enemyMaxGunPower = 35;
var enemyUnitTargetAngles = [];
var enemyMortarShotXs = [];
var enemyMortarShotYs = [];
var enemyMortarShotXVels = [];
var enemyMortarShotYVels = [];
var pressedKeys = [];
var gravity = 0.08;
var firerate = 100;
var enemyFirerate = 100;
var tick = 100;
var tick2 = 0;
var tick3 = 0;
var tick4 = 100;
var enemyClose = false;
var drawUnits = function(a,b,c,d,e) {
  switch(c) {
    //solider
    case 1: {
    strokeWeight(2);
    fill(0,0,255);
    line(a-5,b,a,b-5);
    line(a+5,b,a+10,b-5);
    line(a,b-5,a-5,b-10);
    line(a+10,b-5,a+5,b-10);
    rect(a-5,b-30,10,20);
    line(a-5,b-30,a+5,b-20);
    line(a+5,b-30,a+15,b-20);
    fill(0,0,0);
    rect(a+5,b-20,15,5);
    fill(0,0,255);
    ellipse(a,b-35,10,10);
    rect(a-3,b-37,1,3);
    rect(a+2,b-37,1,3);
    strokeWeight(1);
    fill(255,255,255);
    rect(a-7.5,b-50,15,5,5);
    fill(0,255,0);
    rect(a-7.5,b-50,e*1.5,5,5);
    }
    break;
    //shield
    case 2: {
    strokeWeight(2);
    fill(0,0,255);
    rect(a+16,b-20,10,5);
    rect(a-16,b-25,10,20,5);
    rect(a+6,b-25,10,20,5);
    rect(a-20,b-10,40,10,5);
    fill(255,255,0);
    strokeWeight(1);
    triangle(a,b-35,a,b-30,a-11,b-25);
    triangle(a,b-35,a,b-30,a+11,b-25);
    fill(0,0,255,128);
    arc(a,b,40,70,PI,2*PI);
    strokeWeight(1);
    fill(255,255,255);
    rect(a-25,b-50,50,5,5);
    fill(0,255,0);
    rect(a-25,b-50,e/4,5,5);
    }
    break;
    //mortar
    case 3:
    {
    strokeWeight(5);
    line(a+5*sin(d+PI)+35*sin(d+PI/2),b-8+5*cos(d+PI)+35*cos(d+PI/2),
    a+5*sin(d)+35*sin(d+PI/2),b-8+5*cos(d)+35*cos(d+PI/2));
    strokeWeight(2);
    fill(0,0,255);
    quad(a+5*sin(d),b-8+5*cos(d),a+5*sin(d+PI),b-8+5*cos(d+PI),
    a+5*sin(d+PI)+35*sin(d+PI/2),b-8+5*cos(d+PI)+35*cos(d+PI/2),
    a+5*sin(d)+35*sin(d+PI/2),b-8+5*cos(d)+35*cos(d+PI/2));
    rect(a-20,b-10,40,10,5);
    line(a-5,b,a,b-5);
    line(a+5,b,a+10,b-5);
    line(a,b-5,a-5,b-10);
    line(a+10,b-5,a+5,b-10);
    rect(a-5,b-30,10,20);
    line(a-5,b-30,a+5*sin(d+PI)+10*sin(d+PI/2),b-8+5*cos(d+PI)+10*cos(d+PI/2));
    line(a+5,b-30,a+5*sin(d+PI)+20*sin(d+PI/2),b-8+5*cos(d+PI)+20*cos(d+PI/2));
    fill(0,0,0);
    fill(0,0,255);
    ellipse(a,b-35,10,10);
    rect(a-3,b-37,1,3);
    rect(a+2,b-37,1,3);
    strokeWeight(1);
    fill(255,255,255);
    rect(a-25,b-50,50,5,5);
    fill(0,255,0);
    rect(a-25,b-50,e*5,5,5);
    }
    break;
    //tank
    case 4:
    {
    strokeWeight(2);
    fill(0,0,255,100);
    arc(a,b-28,20,20,PI,PI*2);
    fill(0,0,255,255);
    rect(a-20,b-10,40,10,5);
    quad(a-10,b-28,a+30,b-28,a+30,b-18,a-15,b-18);
    quad(a-10,b-28,a+10,b-28,a+20,b-8,a-20,b-8);
    strokeWeight(1);
    fill(255,255,255);
    rect(a-25,b-50,50,5,5);
    fill(0,255,0);
    rect(a-25,b-50,e,5,5);
    }
    break;
  }
};
var drawEnemyUnits = function(a,b,c,d,e) {
  switch(c) {
    //solider
    case 1: {
    strokeWeight(2);
    fill(255,0,0);
    line(a+5,b,a,b-5);
    line(a-5,b,a-10,b-5);
    line(a,b-5,a+5,b-10);
    line(a-10,b-5,a-5,b-10);
    rect(a-5,b-30,10,20);
    line(a+5,b-30,a-5,b-20);
    line(a-5,b-30,a-15,b-20);
    fill(0,0,0);
    rect(a-20,b-20,15,5);
    fill(255,0,0);
    ellipse(a,b-35,10,10);
    rect(a-3,b-37,1,3);
    rect(a+2,b-37,1,3);
    strokeWeight(1);
    fill(255,255,255);
    rect(a-7.5,b-50,15,5,5);
    fill(255,0,0);
    rect(a-7.5,b-50,e*1.5,5,5);
    }
    break;
    //shield
    case 2: {
    strokeWeight(2);
    fill(255,0,0);
    rect(a-26,b-20,10,5);
    rect(a-16,b-25,10,20,5);
    rect(a+6,b-25,10,20,5);
    rect(a-20,b-10,40,10,5);
    fill(255,255,0);
    strokeWeight(1);
    triangle(a,b-35,a,b-30,a-11,b-25);
    triangle(a,b-35,a,b-30,a+11,b-25);
    fill(255,0,0,128);
    arc(a,b,40,70,PI,2*PI);
    strokeWeight(1);
    fill(255,255,255);
    rect(a-25,b-50,50,5,5);
    fill(255,0,0);
    rect(a-25,b-50,e/4,5,5);
    }
    break;
    //mortar
    case 3:
    {
    strokeWeight(5);
    line(a+5*sin(d+PI)+35*sin(d+PI/2),b-8+5*cos(d+PI)+35*cos(d+PI/2),
    a+5*sin(d)+35*sin(d+PI/2),b-8+5*cos(d)+35*cos(d+PI/2));
    strokeWeight(2);
    fill(255,0,0);
    quad(a+5*sin(d),b-8+5*cos(d),a+5*sin(d+PI),b-8+5*cos(d+PI),
    a+5*sin(d+PI)+35*sin(d+PI/2),b-8+5*cos(d+PI)+35*cos(d+PI/2),
    a+5*sin(d)+35*sin(d+PI/2),b-8+5*cos(d)+35*cos(d+PI/2));
    rect(a-20,b-10,40,10,5);
    line(a-5,b,a,b-5);
    line(a+5,b,a+10,b-5);
    line(a,b-5,a-5,b-10);
    line(a+10,b-5,a+5,b-10);
    rect(a-5,b-30,10,20);
    line(a-5,b-30,a+5*sin(d+PI)+20*sin(d+PI/2),b-18+5*cos(d+PI)+20*cos(d+PI/2));
    line(a+5,b-30,a+5*sin(d+PI)+10*sin(d+PI/2),b-18+5*cos(d+PI)+10*cos(d+PI/2));
    fill(0,0,0);
    fill(255,0,0);
    ellipse(a,b-35,10,10);
    rect(a-3,b-37,1,3);
    rect(a+2,b-37,1,3);
    strokeWeight(1);
    fill(255,255,255);
    rect(a-25,b-50,50,5,5);
    fill(255,0,0);
    rect(a-25,b-50,e*5,5,5);
    }
    break;
    //tank
    case 4:
    {
    strokeWeight(2);
    fill(255,0,0,100);
    arc(a,b-28,20,20,PI,PI*2);
    fill(255,0,0,255);
    rect(a-20,b-10,40,10,5);
    quad(a-10,b-28,a-30,b-28,a-30,b-18,a+10,b-18);
    quad(a-10,b-28,a+10,b-28,a+20,b-8,a-20,b-8);
    strokeWeight(1);
    fill(255,255,255);
    rect(a-25,b-50,50,5,5);
    fill(255,0,0);
    rect(a-25,b-50,e,5,5);
    }
    break;
  }
}
var drawBase = function(a,b,c,d,e,f) {
  switch(d) {
      case 0:
      strokeWeight(5);
      fill(0,0,255);
      quad(a+50+10*sin(c),b+50+10*cos(c),a+50+10*sin(c+PI),b+50+10*cos(c+PI),
      a+50+10*sin(c+PI)+70*sin(c+PI/2),b+50+10*cos(c+PI)+70*cos(c+PI/2),
      a+50+10*sin(c)+70*sin(c+PI/2),b+50+10*cos(c)+70*cos(c+PI/2));
      strokeWeight(1);
      fill(255,255,255);
      rect(a,b-25,100,10,5);
      rect(a,b-50,100,10,5);
      fill(128,128,128);
      rect(a,b-50,f,10,5);
      fill(0,255,0);
      rect(a,b-25,e/5,10,5);
      quad(a+50+10*sin(c),b+50+10*cos(c),a+50+10*sin(c+PI),b+50+10*cos(c+PI),
      a+50+10*sin(c+PI)+baseGunPower*sin(c+PI/2),b+50+10*cos(c+PI)+baseGunPower*cos(c+PI/2),
      a+50+10*sin(c)+baseGunPower*sin(c+PI/2),b+50+10*cos(c)+baseGunPower*cos(c+PI/2));
      strokeWeight(5);
      fill(0,0,255,200);
      arc(a+50,b+50,100,100,90,360);
      fill(0,0,255,255);
      triangle(a+100,b+80,a+100,b+97.5,a+117.5,b+97.5);
      rect(a,b+50,100,100);
      rect(a+100,b+100,20,50);
      strokeWeight(10);
      line(a+50+10*sin(c+PI)+70*sin(c+PI/2),b+50+10*cos(c+PI)+70*cos(c+PI/2),
      a+50+10*sin(c)+70*sin(c+PI/2),b+50+10*cos(c)+70*cos(c+PI/2));
      break;
      case 1:
      strokeWeight(5);
      fill(255,0,0);
      quad(a+50+10*sin(c),b+50+10*cos(c),a+50+10*sin(c+PI),b+50+10*cos(c+PI),
      a+50+10*sin(c+PI)+70*sin(c+PI/2),b+50+10*cos(c+PI)+70*cos(c+PI/2),
      a+50+10*sin(c)+70*sin(c+PI/2),b+50+10*cos(c)+70*cos(c+PI/2));
      strokeWeight(1);
      fill(255,255,255);
      rect(a,b-25,100,10,5);
      rect(a,b-50,100,10,5);
      fill(128,128,128);
      rect(a,b-50,f,10,5);
      fill(255,0,0);
      rect(a,b-25,e/5,10,5);
      fill(0,255,0);
      quad(a+50+10*sin(c),b+50+10*cos(c),a+50+10*sin(c+PI),b+50+10*cos(c+PI),
      a+50+10*sin(c+PI)+enemyBaseGunPower*sin(c+PI/2),b+50+10*cos(c+PI)+enemyBaseGunPower*cos(c+PI/2),
      a+50+10*sin(c)+enemyBaseGunPower*sin(c+PI/2),b+50+10*cos(c)+enemyBaseGunPower*cos(c+PI/2));
      strokeWeight(5);
      fill(255,0,0,200);
      arc(a+50,b+50,100,100,90,360);
      fill(255,0,0,255);
      rect(a,b+50,100,100);
      triangle(a-17.5,b+97.5,a,b+97.5,a,b+80);
      rect(a-20,b+100,20,50);
      strokeWeight(10);
      line(a+50+10*sin(c+PI)+70*sin(c+PI/2),b+50+10*cos(c+PI)+70*cos(c+PI/2),
      a+50+10*sin(c)+70*sin(c+PI/2),b+50+10*cos(c)+70*cos(c+PI/2));
      break;
      }
};
var drawGround = function() {
  strokeWeight(1);
  fill(64,32,0);
  rect(0,660,1200,40);
  fill(0,255,0);
  strokeWeight(1);
  rect(-10,650,1220,10,5);
  stroke(0,0,0);
}
var drawMenu = function() {
  fill(0,0,255)
  strokeWeight(2);
  rect(0,0,600,100);
  fill(0,255,0);
  rect(25,5,40,40);
  rect(75,5,40,40);
  rect(25,55,40,40);
  rect(75,55,40,40);
  if(weaponType === 1) {
    strokeWeight(5);
  }
  rect(150,5,40,40);
  strokeWeight(2);
  if(weaponType === 3) {
    strokeWeight(5);
  }
  rect(200,5,40,40);
  strokeWeight(2);
  if(weaponType === 2) {
    strokeWeight(5);
  }
  rect(150,55,40,40);
  strokeWeight(2);
  if(weaponType === 4) {
    strokeWeight(5);
  }
  rect(200,55,40,40);
  strokeWeight(2);
  rect(275,5,40,40);
  rect(325,5,40,40);
  rect(275,55,40,40);
  rect(325,55,40,40);
  rect(380,5,90,90); 
  rect(480,5,90,90); 
  fill(255,0,0);
  rect(600,0,600,100);
  textSize(8);
  fill(255,255,255);
  text("Max Power",275,62);
  textSize(10);
  fill(255,255,255);
  text("Standard",25,15);
  text("Shield",75,15);
  text("Firerate",275,14);
  text("Damage",325,14);
  text("AoE",330,64);
  text((100-firerate)/10,290,40);
  text((gunDamage-10)/2,340,40);
  text(gunAoE/2,340,90);
  text((maxGunPower-35)/3,290,90);
  textSize(15);
  text("$10",32,35);
  text("$50",82,35);
  text("$50",32,85);
  text("$50",82,85);
  text("$100",155,35);
  text("$100",205,35);
  text("$100",155,85);
  text("$100",205,85);
  text("$50",282,30);
  text("$50",332,30);
  text("$50",282,80);
  text("$50",332,80);
  text("Mortar",25,70);
  text("Tank",80,70);
  textSize(9);
  text("Scattershot",150,15);
  text("Piercing",205,15);
  text("Explosive",150,70);
  text("Slowdown",200,70);
  textSize(20);
  text("Economy",380,35);
  text("Armor",495,35);
  text("$"+economy*20,400,55);
  text("$"+(100+armorUses*20),500,55);
  text(economy-5,420,75)
  textSize(100);
  text("?",875,80);
}
var resetGame = function() {
  shotSize = 20;
  enemyShotSize = 20;
  multiplier = 1;
  enemyMultiplier = 1;
  totalGunAoE;
  totalEnemyGunAoE;
  targetEnemyAngle;
  bestCandidate = 1000;
  amountOfCandidates = 10;
  amountOfMortarCandidates = 10;
  enemyBaseShooting = false;
  enemyTarget;
  weaponType = 0;
  armorUses = 0;
  economy = 5;
  money = 100;
  gunDamage = 10;
  gunAoE = 0;
  baseGunShotXs = [];
  baseGunShotYs = [];
  shotXVelocities = [];
  shotYVelocities = [];
  unitSpeeds = [];
  unitXs = [];
  unitYs = [];
  unitTypes = [];
  unitAngles = [];
  unitHealths = [];
  unitTicks = [];
  unitTargetAngles = [];
  mortarShotXs = [];
  mortarShotYs = [];
  mortarShotXVels = [];
  mortarShotYVels = [];
  baseHealth = 500;
  baseArmor = 0;
  baseGunAngle = 0;
  baseGunPower = 35;
  baseGunSpeed = 2.5;
  maxGunPower = 35;
  enemyEconomy = 5;
  enemyMoney = 100;
  enemyGunDamage = 10;
  enemyGunAoE = 0;
  enemyBaseGunShotXs = [];
  enemyBaseGunShotYs = [];
  enemyShotXVelocities = [];
  enemyShotYVelocities = [];
  enemyWeaponType = 0;
  enemyUnitSpeeds = [];
  enemyUnitXs = [];
  enemyUnitYs = [];
  enemyUnitTypes = [];
  enemyUnitAngles = [];
  enemyUnitHealths = [];
  enemyUnitTicks = [];
  enemyBaseHealth = 500;
  enemyBaseArmor = 0;
  enemyBaseGunAngle = 0;
  enemyBaseGunPower = 35;
  enemyBaseGunSpeed = 2.5;
  enemyMaxGunPower = 35;
  enemyUnitTargetAngles = [];
  enemyMortarShotXs = [];
  enemyMortarShotYs = [];
  enemyMortarShotXVels = [];
  enemyMortarShotYVels = [];
  pressedKeys = [];
  gravity = 0.08;
  firerate = 100;
  enemyFirerate = 100;
  tick = 100;
  tick2 = 0;
  tick3 = 0;
  tick4 = 100;
  enemyClose = false;
}

function keyPressed () {
  pressedKeys[keyCode] = true;
}

function keyReleased () {
  pressedKeys[keyCode] = false;
}

function mousePressed () {
  switch(gameScreen) {
  case 0:{
    if(dist(600,400,mouseX,mouseY) <= 100) {
      gameScreen = 1;
    }
    if(dist(300,400,mouseX,mouseY) <= 100) {
      gameScreen = 2;
    }
    if(dist(900,400,mouseX,mouseY) <= 100) {
      gameScreen = 3;
    }
  }
  break;
  case 1: {
    if(baseHealth > 0 && pauseGame === false) {
      if(mouseX >= 25 && mouseX <= 65 && mouseY >= 5 && mouseY <= 45 && money >= 10) {
        unitXs.push(140);
        unitYs.push(650);
        unitTypes.push(1);
        unitAngles.push(0);
        unitHealths.push(10);
        unitTicks.push(0);
        unitTargetAngles.push(0);
        unitSpeeds.push(1);
        //3.5 DPS
        money-=10;
      }
      if(mouseX >= 75 && mouseX <= 115 && mouseY >= 5 && mouseY <= 45 && money >= 50) {
        unitXs.push(150);
        unitYs.push(650);
        unitTypes.push(2);
        unitAngles.push(0);
        unitHealths.push(200);
        unitTicks.push(0);
        unitTargetAngles.push(0);
        unitSpeeds.push(1);
        //2 DPS
        money-=50;
      }
      if(mouseX >= 75 && mouseX <= 115 && mouseY >= 55 && mouseY <= 95 && money >= 50) {
        unitXs.push(150);
        unitYs.push(650);
        unitTypes.push(4);
        unitAngles.push(0);
        unitHealths.push(50);
        unitTicks.push(0);
        unitTargetAngles.push(0);
        unitSpeeds.push(1);
        //10 DPS
        money-=50;
      }
      if(mouseX >= 25 && mouseX <= 65 && mouseY >= 55 && mouseY <= 95 && money >= 50) {
        unitXs.push(150);
        unitYs.push(650);
        unitTypes.push(3);
        unitAngles.push(0);
        unitHealths.push(10);
        unitTicks.push(0);
        unitTargetAngles.push(0);
        unitSpeeds.push(1);
        //50 DPS
        money-=50;
      }
      if(mouseX >= 275 && mouseX <= 315 && mouseY >= 5 && mouseY <= 45 && firerate > 50 && money >= 50) {
        firerate -= 10;
        money-=50;
      }
      if(mouseX >= 325 && mouseX <= 365 && mouseY >= 5 && mouseY <= 45 && gunDamage < 20 && money >= 50) {
        gunDamage += 2;
        money-=50;
      }
      if(mouseX >= 325 && mouseX <= 365 && mouseY >= 55 && mouseY <= 95 && gunAoE < 10 && money >= 50) {
        gunAoE += 2;
        money-=50;
      }
      if(mouseX >= 275 && mouseX <= 315 && mouseY >= 55 && mouseY <= 95 && maxGunPower < 50 && money >= 50) {
        maxGunPower += 3;
        money-=50;
      }
      if(mouseX >= 150 && mouseX <= 190 && mouseY >= 5 && mouseY <= 45 && weaponType!==1 && money >= 100) {
        weaponType = 1;
        money-=100;
      }
      if(mouseX >= 150 && mouseX <= 190 && mouseY >= 55 && mouseY <= 95 && weaponType!==2 && money >= 100) {
        weaponType = 2;
        money-=100;
      }  
      if(mouseX >= 200 && mouseX <= 240 && mouseY >= 5 && mouseY <= 45 && weaponType!==3 && money >= 100) {
        weaponType = 3;
        money-=100;
      }  
      if(mouseX >= 200 && mouseX <= 240 && mouseY >= 55 && mouseY <= 95 && weaponType!==4 && money >= 100) {
        weaponType = 4;
        money-=100;
      }
      if(mouseX >= 380 && mouseX <= 470 && mouseY >= 5 && mouseY <= 95 && economy < 10 && money >= economy*20) {
        money-=economy*20;
        economy++;
      }
      if(mouseX >= 480 && mouseX <= 570 && mouseY >= 5 && mouseY <= 95 && money >= armorUses*20+100 && baseArmor < 100) {
        baseArmor+=20;
        money-=100+armorUses*20;
        armorUses++;
      }
    }
    if(dist(1150,150,mouseX,mouseY) <= 50 && pauseGame === false) {
      gameScreen = 0;
    }
    if(dist(1040,150,mouseX,mouseY) <= 50 && pauseGame === false) {
      resetGame();
    }
    if(dist(930,150,mouseX,mouseY) <= 50) {
      if(pauseGame === false) {
        pauseGame = true;
      }
      else {
        pauseGame = false;
      }
    }
  }
  break;
  case 2: {
    if(dist(1150,50,mouseX,mouseY) <= 50) {
      gameScreen = 0;
    }
  }
  break;
  case 3: {
    if(dist(1150,50,mouseX,mouseY) <= 50) {
      gameScreen = 0;
    }
  }
  break;
  }
}

function draw() {
  switch(gameScreen) {
  case 1: {
  if(pauseGame === false) {
  tick++;
  tick2++;
  tick3++;
  tick4++;
  background(128,128,255);
  textSize(35);
  strokeWeight(5);
  fill(64,64,64);
  ellipse(1150,150,100,100);
  ellipse(1040,150,100,100);
  if(dist(mouseX,mouseY,930,150) <= 50) {
    strokeWeight(15);
  }
  ellipse(930,150,100,100);
  strokeWeight(5);
  fill(255,255,255);
  text("Back",1110,160);
  textSize(25);
  text("Restart",1000,155);
  text("Pause",895,155);
  textSize(20);
  strokeWeight(2);
  text("Money: $"+money,5,130);
  drawGround();
  drawMenu();
  drawBase(10,500,(baseGunAngle)/180*PI,0,baseHealth,baseArmor);
  drawBase(1090,500,(180-(enemyBaseGunAngle))/180*PI,1,enemyBaseHealth,enemyBaseArmor);
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
  if(pressedKeys[32] && tick >= firerate && baseHealth > 0) {
    if(weaponType !== 1) {
      baseGunShotXs.push(60+70*sin((baseGunAngle-270)/180*PI));
      baseGunShotYs.push(550+70*cos((baseGunAngle-270)/180*PI));
      shotXVelocities.push(baseGunPower/10*sin((baseGunAngle-270)/180*PI));
      shotYVelocities.push(-baseGunPower/10*cos((baseGunAngle-270)/180*PI));
      tick = 0;
    }
    if(weaponType === 1) {
      baseGunShotXs.push(60+70*sin((baseGunAngle-270)/180*PI));
      baseGunShotYs.push(550+70*cos((baseGunAngle-270)/180*PI));
      shotXVelocities.push(baseGunPower/10*sin((baseGunAngle-265)/180*PI));
      shotYVelocities.push(-baseGunPower/10*cos((baseGunAngle-265)/180*PI));
      baseGunShotXs.push(60+70*sin((baseGunAngle-270)/180*PI));
      baseGunShotYs.push(550+70*cos((baseGunAngle-270)/180*PI));
      shotXVelocities.push(baseGunPower/10*sin((baseGunAngle-270)/180*PI));
      shotYVelocities.push(-baseGunPower/10*cos((baseGunAngle-270)/180*PI));
      baseGunShotXs.push(60+70*sin((baseGunAngle-270)/180*PI));
      baseGunShotYs.push(550+70*cos((baseGunAngle-270)/180*PI));
      shotXVelocities.push(baseGunPower/10*sin((baseGunAngle-275)/180*PI));
      shotYVelocities.push(-baseGunPower/10*cos((baseGunAngle-275)/180*PI));
      tick = 0;
    }
  }
  if(enemyMoney >= 10 && enemyBaseHealth > 0) {
    enemyUnitXs.push(1090);
    enemyUnitYs.push(650);
    enemyUnitTypes.push(1);
    enemyUnitAngles.push(0);
    enemyUnitHealths.push(10);
    enemyUnitTicks.push(0);
    enemyUnitSpeeds.push(1);
    enemyMoney -= 10;
  }
  for(var i = 0; i < baseGunShotXs.length; i++) {
      fill(64,64,64);
      if(weaponType === 1) {
        shotSize = 10;
        strokeWeight(2);
        ellipse(baseGunShotXs[i],baseGunShotYs[i],10,10);
      }
      else {
        shotSize = 20;
        strokeWeight(5);
        ellipse(baseGunShotXs[i],baseGunShotYs[i],20,20);
      }
      baseGunShotXs[i]+=shotXVelocities[i];
      baseGunShotYs[i]-=shotYVelocities[i];
      shotYVelocities[i]-=gravity;
      if(weaponType!==2) {
        totalGunAoE = gunAoE;
      }
      else {
        totalGunAoE = gunAoE + 50;
      }
      if(weaponType === 3) {
        multiplier = 2;
      }
      if(weaponType === 1) {
        multiplier = 0.7;
      }
      if(weaponType === 2 || weaponType === 4) {
        multiplier = 1;
      }
      if(baseGunShotYs[i] >= 650) {
        for(var j = 0; j < enemyUnitXs.length; j++) {
            if(dist(enemyUnitXs[j],0,baseGunShotXs[i],0) <= 40+shotSize/2 && enemyUnitTypes[j] !== 1) {
              if(enemyUnitHealths[j]- (abs(shotXVelocities[i])+abs(shotYVelocities[i]))*gunDamage/2 >= 0) {
                enemyUnitHealths[j] -= (abs(shotXVelocities[i])+abs(shotYVelocities[i]))*gunDamage/2*multiplier;
              }
              else {
                enemyUnitHealths[j] = 0;
              }
              if(weaponType === 4) {
                enemyUnitSpeeds[j] = 0;
              }
            }
            if(dist(enemyUnitXs[j],0,baseGunShotXs[i],0) <= 10+shotSize/2 && enemyUnitTypes[j] === 1) {
              if(enemyUnitHealths[j]- (abs(shotXVelocities[i])+abs(shotYVelocities[i]))*gunDamage/2 >= 0) {
                enemyUnitHealths[j] -= (abs(shotXVelocities[i])+abs(shotYVelocities[i]))*gunDamage/2*multiplier;
              }
              else {
                enemyUnitHealths[j] = 0;
              }
              if(weaponType === 4) {
                enemyUnitSpeeds[j] = 0;
              }
            }
            if(dist(enemyUnitXs[j],0,baseGunShotXs[i],0) <= 10+shotSize/2+totalGunAoE && enemyUnitTypes[j] === 1) {
              if(dist(enemyUnitXs[j],0,baseGunShotXs[i],0) <= 10+shotSize/2) {
                if(enemyUnitHealths[j] - totalGunAoE >= 0) {
                  enemyUnitHealths[j] -= totalGunAoE;
                }
                else {
                  enemyUnitHealths[j] = 0;
                }
              }
              else {
                if(enemyUnitHealths[j] - ((totalGunAoE)-(dist(enemyUnitXs[j],0,baseGunShotXs[i],0)-10-shotSize/2)) >= 0) {
                  enemyUnitHealths[j] -= ((totalGunAoE)-(dist(enemyUnitXs[j],0,baseGunShotXs[i],0)-10-shotSize/2));
                }
                else {
                  enemyUnitHealths[j] = 0;
                }
              }
              if(weaponType === 4) {
                enemyUnitSpeeds[j] = 0;
              }
            }
            if(dist(enemyUnitXs[j],0,baseGunShotXs[i],0) <= 40+shotSize/2+totalGunAoE && enemyUnitTypes[j] !== 1) {
              if(dist(enemyUnitXs[j],0,baseGunShotXs[i],0) <= 40+shotSize/2) {
                if(enemyUnitHealths[j] - totalGunAoE >= 0) {
                  enemyUnitHealths[j] -= totalGunAoE;
                }
                else {
                  enemyUnitHealths[j] = 0;
                }
              }
              else {
                if(enemyUnitHealths[j] - ((totalGunAoE)-(dist(enemyUnitXs[j],0,baseGunShotXs[i],0)-40-shotSize/2)) >= 0) {
                  enemyUnitHealths[j] -= ((totalGunAoE)-(dist(enemyUnitXs[j],0,baseGunShotXs[i],0)-40-shotSize/2));
                }
                else {
                  enemyUnitHealths[j] = 0;
                }
              }
              if(weaponType === 4) {
                enemyUnitSpeeds[j] = 0.5;
              }
          }
        }
        baseGunShotXs.splice(i,1);
        baseGunShotYs.splice(i,1); 
        shotXVelocities.splice(i,1);
        shotYVelocities.splice(i,1);
      }
  }
  for(var i = 0; i < mortarShotXs.length; i++) {
    fill(64,64,64);
    strokeWeight(2);
    ellipse(mortarShotXs[i],mortarShotYs[i],10,10);
    mortarShotXs[i]+=mortarShotXVels[i];
    mortarShotYs[i]-=mortarShotYVels[i];
    mortarShotYVels[i]-=gravity;
    if(mortarShotYs[i] >= 650) {
      for(var j = 0; j < enemyUnitXs.length; j++) {
          if(dist(enemyUnitXs[j],0,mortarShotXs[i],0) <= 45 && enemyUnitTypes[j] !== 1) {
            if(enemyUnitHealths[j]- (abs(mortarShotXVels[i])+abs(mortarShotYVels[i]))*5 >= 0) {
              enemyUnitHealths[j] -= (abs(mortarShotXVels[i])+abs(mortarShotYVels[i]))*5;
            }
            else {
              enemyUnitHealths[j] = 0;
            }
          }
          if(dist(enemyUnitXs[j],0,mortarShotXs[i],0) <= 25 && enemyUnitTypes[j] === 1) {
            if(enemyUnitHealths[j]- (abs(mortarShotXVels[i])+abs(mortarShotYVels[i]))*5 >= 0) {
              enemyUnitHealths[j] -= (abs(mortarShotXVels[i])+abs(mortarShotYVels[i]))*5;
            }
            else {
              enemyUnitHealths[j] = 0;
            }
          }
      }
      if(dist(mortarShotXs[i],0,1140,0) <= 65 && enemyBaseHealth > 0) {
        if(enemyBaseArmor <= 0) {
          if(enemyBaseHealth- (abs(mortarShotXVels[i])+abs(mortarShotYVels[i]))*5 >= 0) {
            enemyBaseHealth -= (abs(mortarShotXVels[i])+abs(mortarShotYVels[i]))*5;
          }
          else {
            enemyBaseHealth = 0;
          }
        }
        else {
          if(enemyBaseArmor- (abs(mortarShotXVels[i])+abs(mortarShotYVels[i]))*5 >= 0) {
            enemyBaseArmor -= (abs(mortarShotXVels[i])+abs(mortarShotYVels[i]))*5;
          }
          else {
            enemyUnitArmor = 0;
          }
        }
      }
      mortarShotXs.splice(i,1);
      mortarShotYs.splice(i,1); 
      mortarShotXVels.splice(i,1);
      mortarShotYVels.splice(i,1);
    }
}
  for(var i = 0; i < enemyMortarShotXs.length; i++) {
    fill(64,64,64);
    strokeWeight(2);
    ellipse(enemyMortarShotXs[i],enemyMortarShotYs[i],10,10);
    enemyMortarShotXs[i]+=enemyMortarShotXVels[i];
    enemyMortarShotYs[i]-=enemyMortarShotYVels[i];
    enemyMortarShotYVels[i]-=gravity;
    if(enemyMortarShotYs[i] >= 650) {
      for(var j = 0; j < unitXs.length; j++) {
          if(dist(unitXs[j],0,enemyMortarShotXs[i],0) <= 45 && unitTypes[j] !== 1) {
            if(unitHealths[j]- (abs(enemyMortarShotXVels[i])+abs(enemyMortarShotYVels[i]))*5 >= 0) {
              unitHealths[j] -= (abs(enemyMortarShotXVels[i])+abs(enemyMortarShotYVels[i]))*5;
            }
            else {
              unitHealths[j] = 0;
            }
          }
          if(dist(unitXs[j],0,enemyMortarShotXs[i],0) <= 25 && unitTypes[j] === 1) {
            if(unitHealths[j]- (abs(enemyMortarShotXVels[i])+abs(enemyMortarShotYVels[i]))*5 >= 0) {
              unitHealths[j] -= (abs(enemyMortarShotXVels[i])+abs(enemyMortarShotYVels[i]))*5;
            }
            else {
              unitHealths[j] = 0;
            }
          }
      }
      if(dist(enemyMortarShotXs[i],0,130,0) <= 65 && baseHealth > 0) {
        if(baseArmor <= 0) {
          if(baseHealth- (abs(enemyMortarShotXVels[i])+abs(enemyMortarShotYVels[i]))*5 >= 0) {
            baseHealth -= (abs(enemyMortarShotXVels[i])+abs(enemyMortarShotYVels[i]))*5;
          }
          else {
            baseHealth = 0;
          }
        }
        else {
          if(baseArmor- (abs(enemyMortarShotXVels[i])+abs(enemyMortarShotYVels[i]))*5 >= 0) {
            baseArmor -= (abs(enemyMortarShotXVels[i])+abs(enemyMortarShotYVels[i]))*5;
          }
          else {
            unitArmor = 0;
          }
        }
      }
      enemyMortarShotXs.splice(i,1);
      enemyMortarShotYs.splice(i,1); 
      enemyMortarShotXVels.splice(i,1);
      enemyMortarShotYVels.splice(i,1);
    }
  }
  for(var i = 0; i < enemyBaseGunShotXs.length; i++) {
    fill(64,64,64);
    strokeWeight(5);
    if(enemyWeaponType!==2) {
      enemyTotalGunAoE = enemyGunAoE;
    }
    else {
      enemyTotalGunAoE = enemyGunAoE + 50;
    }
    if(enemyWeaponType === 3) {
      enemyMultiplier = 2;
    }
    if(enemyWeaponType === 1) {
      multiplier = 0.7;
    }
    if(enemyWeaponType === 2 || enemyWeaponType === 4) {
      enemyMultiplier = 1;
    }
    if(enemyWeaponType === 1) {
      enemyShotSize = 10;
      ellipse(enemyBaseGunShotXs[i],enemyBaseGunShotYs[i],10,10);
    }
    else {
      enemyShotSize = 20;
      ellipse(enemyBaseGunShotXs[i],enemyBaseGunShotYs[i],20,20);
    }
    enemyBaseGunShotXs[i]+=enemyShotXVelocities[i];
    enemyBaseGunShotYs[i]-=enemyShotYVelocities[i];
    enemyShotYVelocities[i]-=gravity;
    if(enemyBaseGunShotYs[i] >= 650) {
      for(var j = 0; j < unitXs.length; j++) {
        if(dist(unitXs[j],0,enemyBaseGunShotXs[i],0) <= 40+enemyShotSize/2 && unitTypes[j] !== 1) {
            if(unitHealths[j]- (abs(enemyShotXVelocities[i])+abs(enemyShotYVelocities[i]))*enemyGunDamage/2 >= 0) {
              unitHealths[j] -= (abs(enemyShotXVelocities[i])+abs(enemyShotYVelocities[i]))*enemyGunDamage/2*enemyMultiplier;
            }
            else {
              unitHealths[j] = 0;
            }
            if(enemyWeaponType === 4) {
              unitSpeeds[j] = 0;
            }
        }
        if(dist(unitXs[j],0,enemyBaseGunShotXs[i],0) <= 10+enemyShotSize/2 && unitTypes[j] === 1) {
            if(unitHealths[j]- (abs(enemyShotXVelocities[i])+abs(enemyShotYVelocities[i]))*enemyGunDamage/2 >= 0) {
              unitHealths[j] -= (abs(enemyShotXVelocities[i])+abs(enemyShotYVelocities[i]))*enemyGunDamage/2*enemyMultiplier;
            }
            else {
              unitHealths[j] = 0;
            }
            if(enemyWeaponType === 4) {
              unitSpeeds[j] = 0;
            }
        }
        if(dist(unitXs[j],0,enemyBaseGunShotXs[i],0) <= 10+enemyShotSize/2+enemyTotalGunAoE && unitTypes[j] === 1) {
            if(dist(unitXs[j],0,enemyBaseGunShotXs[i],0) <= 10+enemyShotSize/2) {
              if(unitHealths[j] - enemyTotalGunAoE >= 0) {
                unitHealths[j] -= enemyTotalGunAoE;
              }
              else {
                unitHealths[j] = 0;
              }
            }
            else {
              if(unitHealths[j] - (enemyTotalGunAoE-dist(unitXs[j],0,enemyBaseGunShotXs[i],0)-10+enemyShotSize/2) >= 0) {
                unitHealths[j] -= (enemyTotalGunAoE-dist(unitXs[j],0,enemyBaseGunShotXs[i],0)-10+enemyShotSize/2);
              }
              else {
                unitHealths[j] = 0;
              }
            }
            if(enemyWeaponType === 4) {
              unitSpeeds[j] = 0;
            }
        }
        if(dist(unitXs[j],0,enemyBaseGunShotXs[i],0) <= 40+enemyShotSize/2+enemyTotalGunAoE && unitTypes[j] !== 1) {
            if(dist(unitXs[j],0,enemyBaseGunShotXs[i],0) <= 40+enemyShotSize/2) {
              if(unitHealths[j] - enemyTotalGunAoE >= 0) {
                unitHealths[j] -= enemyTotalGunAoE;
              }
              else {
                unitHealths[j] = 0;
              }
            }
            else {
              if(unitHealths[j] - (enemyTotalGunAoE-dist(unitXs[j],0,enemyBaseGunShotXs[i],0)-40+enemyShotSize/2) >= 0) {
                unitHealths[j] -= (enemyTotalGunAoE-dist(unitXs[j],0,enemyBaseGunShotXs[i],0)-40+enemyShotSize/2);
              }
              else {
                unitHealths[j] = 0;
              }
            }
            if(enemyWeaponType === 4) {
              unitSpeeds[j] = 0;
            }
        }
      }
      enemyBaseGunShotXs.splice(i,1);
      enemyBaseGunShotYs.splice(i,1); 
      enemyShotXVelocities.splice(i,1);
      enemyShotYVelocities.splice(i,1);
    }
}
  if(tick2 >= 60) {
    money+=economy;
    enemyMoney+=enemyEconomy;
    tick2 = 0;
  }
  for(var i = 0; i < unitXs.length; i++) {
    if(dist(unitXs[i],0,1090,0) <= enemyMaxGunPower*12) {
      enemyBaseShooting = true;
      enemyTarget = i;
    }
    unitTicks[i]++;
    enemyClose = false;
    drawUnits(unitXs[i],unitYs[i],unitTypes[i],unitAngles[i]/180*PI,unitHealths[i]);
    for(var j = 0; j < enemyUnitXs.length; j++) {
      if(unitTypes[i] !== 3 && dist(0,unitXs[i],0,enemyUnitXs[j]) <= 100 && enemyClose === false) {
        enemyClose = true;
        if(unitTypes[i] === 1 && unitTicks[i] >= 5) {
          enemyUnitHealths[j] -= 0.35;
          unitTicks[i] = 0;
        }
        if(unitTypes[i] === 2 && unitTicks[i] >= 10) {
          enemyUnitHealths[j] -= 0.4;
          unitTicks[i] = 0;
        }
        if(unitTypes[i] === 4 && unitTicks[i] >= 60) {
          if(enemyUnitHealths[j] > 10) {
          enemyUnitHealths[j] -= 10;
          }
          else{
            enemyUnitHealths[j] = 0;
          }
          unitTicks[i] = 0;
        }
      }
      if(unitTypes[i] === 3 && dist(0,unitXs[i],0,enemyUnitXs[j]+5) <= 210 && enemyClose === false) {
        enemyClose = true;
        bestCandidate = 1000;
        for(var l = 0; l < amountOfMortarCandidates; l++) {
          var testX = unitXs[i]+40*sin(((l*90/amountOfMortarCandidates)-270)/180*PI);
          var testY = unitYs[i]+40*cos(((l*90/amountOfMortarCandidates)-270)/180*PI);
          var testXVel = 35/10*sin(((l*90/amountOfMortarCandidates)-270)/180*PI);
          var testYVel = -35/10*cos(((l*90/amountOfMortarCandidates)-270)/180*PI);
          var endPoint = testX+testXVel*((testYVel/gravity)*2+(Math.sqrt((650-testY)*2/gravity)));
          if(dist(endPoint,0,enemyUnitXs[j],0) < bestCandidate) {
            unitTargetAngles[i] = l*90/amountOfMortarCandidates;
            bestCandidate = dist(endPoint,0,enemyUnitXs[j],0);
          }
        }
        if(unitTargetAngles[i] > unitAngles[i]) {
          unitAngles[i] += 1/2.5;
        }
        if(unitTargetAngles[i] < unitAngles[i]) {
          unitAngles[i] -= 1/2.5;
        }
        if(unitTicks[i] >= 100) {
          unitTicks[i] = 0;
          mortarShotXs.push(unitXs[i]+40*sin((unitAngles[i]-270)/180*PI));
          mortarShotYs.push(unitYs[i]+40*cos((unitAngles[i]-270)/180*PI));
          mortarShotXVels.push(35/10*sin((unitAngles[i]-270)/180*PI));
          mortarShotYVels.push(-35/10*cos((unitAngles[i]-270)/180*PI));
        }
      }
    }
    if(unitTypes[i] !== 3 && dist(0,unitXs[i],0,1090) <= 100 && enemyBaseHealth > 0 && enemyClose === false) {
      enemyClose = true;
      if(unitTypes[i] === 1 && unitTicks[i] >= 5) {
        if(enemyBaseArmor <= 0) {
          enemyBaseHealth -= 0.35;
        }
        else{
          enemyBaseArmor -= 0.35;
        }
        unitTicks[i] = 0;
      }
      if(unitTypes[i] === 2 && unitTicks[i] >= 10) {
        if(enemyBaseArmor <= 0) {
          enemyBaseHealth -= 0.4;
        }
        else{
          enemyBaseArmor -= 0.4;
        }
        unitTicks[i] = 0;
      }
      if(unitTypes[i] === 4 && unitTicks[i] >= 60) {
        if(enemyBaseArmor <= 0) {
          enemyBaseHealth -= 10;
        }
        else{
          enemyBaseArmor -= 10;
        }
        unitTicks[i] = 0;
      }
    }
    if(unitTypes[i] === 3 && dist(0,unitXs[i],0,1140) <= 210 && enemyClose === false) {
      enemyClose = true;
      bestCandidate = 1000;
      for(var l = 0; l < amountOfMortarCandidates; l++) {
        var testX = unitXs[i]+40*sin(((l*90/amountOfMortarCandidates)-270)/180*PI);
        var testY = unitYs[i]+40*cos(((l*90/amountOfMortarCandidates)-270)/180*PI);
        var testXVel = 35/10*sin(((l*90/amountOfMortarCandidates)-270)/180*PI);
        var testYVel = -35/10*cos(((l*90/amountOfMortarCandidates)-270)/180*PI);
        var endPoint = testX+testXVel*((testYVel/gravity)*2+(Math.sqrt((650-testY)*2/gravity)));
        if(dist(endPoint,0,1140,0) < bestCandidate) {
          unitTargetAngles[i] = l*90/amountOfMortarCandidates;
          bestCandidate = dist(endPoint,0,1140,0);
        }
      }
      if(unitTargetAngles[i] > unitAngles[i]) {
        unitAngles[i] += 1/2.5;
      }
      if(unitTargetAngles[i] < unitAngles[i]) {
        unitAngles[i] -= 1/2.5;
      }
      if(unitTicks[i] >= 100) {
        unitTicks[i] = 0;
        mortarShotXs.push(unitXs[i]+40*sin((unitAngles[i]-270)/180*PI));
        mortarShotYs.push(unitYs[i]+40*cos((unitAngles[i]-270)/180*PI));
        mortarShotXVels.push(35/10*sin((unitAngles[i]-270)/180*PI));
        mortarShotYVels.push(-35/10*cos((unitAngles[i]-270)/180*PI));
      }
    }
    if(enemyClose === false) {
      unitXs[i] += unitSpeeds[i];
    }
    if(unitSpeeds[i] < 1) {
      unitSpeeds[i] += 0.004;
    }
    if(unitHealths[i] <= 0 || unitXs[i] >= 1200) {
      unitXs.splice(i,1);
      unitYs.splice(i,1);
      unitTypes.splice(i,1);
      unitAngles.splice(i,1);
      unitHealths.splice(i,1);
      unitTicks.splice(i,1);
      unitSpeeds.splice(i,1);
      unitTargetAngles.splice(i,1);
      if(enemyTarget === i) {
        enemyBaseShooting = false;
      }
    }
  }
  for(var i = 0; i < enemyUnitXs.length; i++) {
    enemyUnitTicks[i]++;
    enemyClose = false;
    drawEnemyUnits(enemyUnitXs[i],enemyUnitYs[i],enemyUnitTypes[i],(180-enemyUnitAngles[i])/180*PI,enemyUnitHealths[i]);
    for(var j = 0; j < unitXs.length; j++) {
      if(enemyUnitTypes[i] !== 3 && dist(0,unitXs[j],0,enemyUnitXs[i]) <= 100 && enemyClose === false) {
        enemyClose = true;
        if(enemyUnitTypes[i] === 1 && enemyUnitTicks[i] >= 5) {
          unitHealths[j] -= 0.35;
          enemyUnitTicks[i] = 0;
        }
        if(enemyUnitTypes[i] === 2 && enemyUnitTicks[i] >= 10) {
          unitHealths[j] -= 0.4;
          enemyUnitTicks[i] = 0;
        }
        if(enemyUnitTypes[i] === 4 && enemyUnitTicks[i] >= 60) {
          if(unitHealths[j] > 10) {
            unitHealths[j] -= 10;
          }
          else {
            unitHealths[j] = 0;
          }
          enemyUnitTicks[i] = 0;
        }
      }
      if(enemyUnitTypes[i] === 3 && dist(0,unitXs[j],0,enemyUnitXs[i]) <= 210 && enemyClose === false) {
          enemyClose = true;
          bestCandidate = 1000;
          //This part(960 to 984)
          for(var l = 0; l < amountOfMortarCandidates; l++) {
            var testX = (unitXs[i]+40*sin((-(l*90/amountOfMortarCandidates)-90)/180*PI));
            var testY = (unitYs[i]+40*cos((-(l*90/amountOfMortarCandidates)-90)/180*PI));
            var testXVel = (35/10*sin((-(l*90/amountOfMortarCandidates)-90)/180*PI));
            var testYVel = (-35/10*cos((-(l*90/amountOfMortarCandidates))-90)/180*PI);
            var endPoint = testX+testXVel*((testYVel/gravity)*2+Math.sqrt(testY*2/gravity));
            if(dist(endPoint,0,unitXs[j]+10,0) < bestCandidate) {
              enemyUnitTargetAngles[i] = l*90/amountOfMortarCandidates;
              bestCandidate = dist(endPoint,0,unitXs[j]+10,0);
            }
          }
          if(enemyUnitTargetAngles[i] > enemyUnitAngles[i]) {
            enemyUnitAngles[i] += 1/2.5;
          }
          if(enemyUnitTargetAngles[i] < enemyUnitAngles[i]) {
            enemyUnitAngles[i] -= 1/2.5;
          }
          if(enemyUnitTicks[i] >= 100) {
            enemyUnitTicks[i] = 0;
            enemyMortarShotXs.push(enemyUnitXs[i]+40*sin((-(enemyUnitAngles[i])-90)/180*PI));
            enemyMortarShotYs.push(enemyUnitYs[i]+40*cos((-(enemyUnitAngles[i])-90)/180*PI));
            enemyMortarShotXVels.push(35/10*sin((-(enemyUnitAngles[i])-90)/180*PI));
            enemyMortarShotYVels.push(-35/10*cos((-(enemyUnitAngles[i])-90)/180*PI));
          }
      }
    }
    if(enemyUnitTypes[i] !== 3 && dist(0,enemyUnitXs[i],0,130) <= 100 && baseHealth > 0 && enemyClose === false) {
      enemyClose = true;
      if(enemyUnitTypes[i] === 1 && enemyUnitTicks[i] >= 5) {
        if(baseArmor <= 0) {
          baseHealth -= 0.35;
        }
        else{
          baseArmor -= 0.35;
        }
        enemyUnitTicks[i] = 0;
      }
      if(enemyUnitTypes[i] === 2 && enemyUnitTicks[i] >= 10) {
        if(baseArmor <= 0) {
          baseHealth -= 0.4;
        }
        else{
          baseArmor -= 0.4;
        }
        enemyUnitTicks[i] = 0;
      }
      if(enemyUnitTypes[i] === 4 && enemyUnitTicks[i] >= 60) {
        if(baseArmor <= 0) {
          baseHealth -= 10;
        }
        else{
          baseArmor -= 10;
        }
        enemyUnitTicks[i] = 0;
      }
    }
    if(enemyUnitTypes[i] === 3 && dist(0,enemyUnitXs[i],0,60) <= 210 && enemyClose === false && baseHealth > 0) {
      enemyClose = true;
      bestCandidate = 1000;
      for(var l = 0; l < amountOfMortarCandidates; l++) {
        var testX = enemyUnitXs[i]+40*sin((-(l*90/amountOfMortarCandidates)-90)/180*PI);
        var testY = enemyUnitYs[i]+40*cos((-(l*90/amountOfMortarCandidates)-90)/180*PI);
        var testXVel = 35/10*sin((-(l*90/amountOfMortarCandidates)-90)/180*PI);
        var testYVel = -35/10*cos((-(l*90/amountOfMortarCandidates)-90)/180*PI);
        var endPoint = testX+testXVel*((testYVel/gravity)*2+(Math.sqrt((650-testY)*2/gravity)));
        if(dist(endPoint,0,60,0) < bestCandidate) {
          enemyUnitTargetAngles[i] = l*90/amountOfMortarCandidates;
          bestCandidate = dist(endPoint,0,60,0);
        }
      }
      if(enemyUnitTargetAngles[i] > enemyUnitAngles[i]) {
        enemyUnitAngles[i] += 1/2.5;
      }
      if(enemyUnitTargetAngles[i] < enemyUnitAngles[i]) {
        enemyUnitAngles[i] -= 1/2.5;
      }
      if(enemyUnitTicks[i] >= 100) {
        enemyUnitTicks[i] = 0;
        enemyMortarShotXs.push(enemyUnitXs[i]+40*sin((-(enemyUnitAngles[i])-90)/180*PI));
        enemyMortarShotYs.push(enemyUnitYs[i]+40*cos((-(enemyUnitAngles[i])-90)/180*PI));
        enemyMortarShotXVels.push(35/10*sin((-(enemyUnitAngles[i])-90)/180*PI));
        enemyMortarShotYVels.push(-35/10*cos((-(enemyUnitAngles[i])-90)/180*PI));
      }
    }
    if(enemyClose === false) {
      enemyUnitXs[i] -= enemyUnitSpeeds[i];
    }
    if(enemyUnitSpeeds[i] < 1) {
      enemyUnitSpeeds[i] += 0.004;
    }
    if(enemyUnitHealths[i] <= 0 || enemyUnitXs[i] <= 0) {
      enemyUnitXs.splice(i,1);
      enemyUnitYs.splice(i,1);
      enemyUnitTypes.splice(i,1);
      enemyUnitAngles.splice(i,1);
      enemyUnitHealths.splice(i,1);
      enemyUnitTicks.splice(i,1);
      enemyUnitSpeeds.splice(i,1);
      if(enemyTarget === i) {
        enemyBaseShooting = false;
      }
    }
  }
  if(enemyBaseShooting === true && enemyBaseHealth > 0) {
    bestCandidate = 1000;
    for(var i = 0; i < amountOfCandidates; i++) {
      var testX = (1140+70*sin((-(i*90/amountOfCandidates)-90)/180*PI));
      var testY = (550+70*cos((-(i*90/amountOfCandidates)-90)/180*PI));
      var testXVel = (enemyBaseGunPower/10*sin((-(i*90/amountOfCandidates)-90)/180*PI));
      var testYVel = (-enemyBaseGunPower/10*cos((-(i*90/amountOfCandidates))-90)/180*PI);
      var endPoint = testX+testXVel*((testYVel/gravity)*2+Math.sqrt(testY*2/gravity));
      if(dist(endPoint,0,unitXs[enemyTarget],0) < bestCandidate) {
        targetEnemyAngle = i*90/amountOfCandidates;
        bestCandidate = dist(endPoint,0,unitXs[enemyTarget],0);
      }
    }
    if(targetEnemyAngle > enemyBaseGunAngle) {
      enemyBaseGunAngle+=1/enemyBaseGunSpeed;
    }
    if(targetEnemyAngle < enemyBaseGunAngle) {
      enemyBaseGunAngle-=1/enemyBaseGunSpeed;
    }
    if(tick4 >= enemyFirerate) {
      tick4 = 0;
      enemyBaseGunShotXs.push(1140+70*sin((-enemyBaseGunAngle-90)/180*PI));
      enemyBaseGunShotYs.push(550+70*cos((-enemyBaseGunAngle-90)/180*PI));
      enemyShotXVelocities.push(enemyBaseGunPower/10*sin((-enemyBaseGunAngle-90)/180*PI));
      enemyShotYVelocities.push(-enemyBaseGunPower/10*cos((-enemyBaseGunAngle-90)/180*PI));
    }
  }
  if(enemyBaseShooting === false) {
    bestCandidate = 1000;
  }
}
  break;
  }
  break;
  case 0: {
  background(128,128,255);
  drawGround();
  drawBase(10,500,(45)/180*PI,0,500,100);
  drawBase(1090,500,(180-(45))/180*PI,1,500,100);
  textSize(200);
  fill(64,64,64);
  text("Warfront",200,200);
  strokeWeight(20);
  ellipse(600,400,200,200);
  ellipse(300,400,200,200);
  ellipse(900,400,200,200);
  fill(255,255,255);
  strokeWeight(10);
  triangle(575,410,635,445,575,480)
  textSize(75);
  text("Play",525,400);
  textSize(50);
  text("Settings",815,410)
  textSize(35);
  text("Instructions",215,410);
  }
  break;
  case 2: {
    textSize(150);
    background(128,128,255);
    drawBase(10,500,(45)/180*PI,0,500,100);
    drawBase(1090,500,(180-(45))/180*PI,1,500,100);
    drawGround();
    fill(64,64,64);
    strokeWeight(10);
    text("Instructions",200,125);
    strokeWeight(5);
    ellipse(1150,50,100,100);
    textSize(20);
    fill(255,255,255);
    text("Back",1125,55);
    {
    text("\n    Welcome to Warfront! Warfront is a strategy game where you control a base and\n try to destroy the AI-controlled enemy base. You have a menu, which you can use\n to buy the Economy upgrade, which increases money earning so you can buy more\n stuff, you can buy troops, of which there are four types - Soliders (Basic soliders,\n cheap), Mortars (High-damage, but require setup time and are easily destroyed),\n Tanks (Ok at everything, can one-shot soliders and mortars), and Shielders \n(Extremely tough, but have the lowest DPS. Other than troops, you can upgrade\n your base's cannon, which you can use to shoot enemies, though even maxed out\n it cannot hit the enemy base. There are two ways to upgrade the cannon. There \nare the normal upgrades, which are Damage (increases damage), Max Power \n(increases max range), Firerate (increases firerate, obviously), and AoE (adds \nexplosives - explosives deal extra damage and have a larger area of effect compared \nto the cannonball). There are also the cannon types - your cannon can be turned into \na type, which has special attributes as follows: Piercing - doubled damage! Scattershot\n - fires three lower-damage shots, Slowdown - Slows down enemies if they are hit, \nand Explosive - Extra explosives! Finally, you can also buy base Armor, which \nincreases in cost as you keep buying it and basically adds a second health bar with a\n max HP of 100 - the first has a HP of 500. Have fun!",210,150);
    }
  }
  break;
  case 3: {
    textSize(150);
    background(128,128,255);
    drawBase(10,500,(45)/180*PI,0,500,100);
    drawBase(1090,500,(180-(45))/180*PI,1,500,100);
    drawGround();
    fill(64,64,64);
    strokeWeight(10);
    text("Settings",300,125);
    strokeWeight(5);
    ellipse(1150,50,100,100);
    textSize(20);
    fill(255,255,255);
    text("Back",1125,55);
  }
  break;
  }
}
