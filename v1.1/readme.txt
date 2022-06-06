
if you want to play Bang! with music please make sure you install sox

sudo apt update
sudo apt install sox
sudo apt-get install libsox-fmt-all

and  then run
sox --Version make sure you successfully install sox

instead of run ./main
run ./music to enjoy your game

BUG
if you die in your turn, bad thing happen



card ID list

101) Bang!
102) Miss
103) Beer
104) Cat_Balou --? not done yet
105) Panic
106) Duel
107) General_Store
108) Indians
109) Gatling
110) Salon
111) Wells_Fargo
112) Stagecoach

TODO:
charater
role
winnig
blue_card

charater ID name role

401 -> 4 means bullets
      01 is ID


void Last_Call(){
    heal();
}

void Tornado(){
    while(travel){
        discard();
        draw();
        draw();
    }
}

void Punch(){
    if(1 >= distance()){
        Bang();
    }
}

