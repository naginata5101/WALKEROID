#include <Mikan.h>
#include "game1'.h"
#include <stdlib.h>
#include <time.h>


void SystemInit( void )
{
 MikanWindow->SetWindowName( "game1" );
}

void Init()
{
    srand((unsigned)time( NULL ));
}

double Sample()
{
    return (double)(rand())/RAND_MAX;
}

int Random()
{
    return rand();
}

int Random(int max)
{
    return (int)(Sample()*max);
}

//MainLoop�J�n�O��1�x�������s
//�e�N�X�`���̓ǂݍ��݂Ȃǂ̃Q�[���J�n�O�̏������s��
void UserInit( void )
{//0�Ԃ̕����Z�b�g���A�T�C�Y=15px,�F=�s���ߓx=255/���ŏ�����
MikanDraw->CreateFont(0,15,MikanDraw->Color(255,255,255,255));

//0�Ԃ̉摜��n_f_stg2.2.png�ɂ���B���ߐF�͐[��
MikanDraw->CreateTexture(0,"n_f_stg2.2.png",TRC_ZERO);

//0�Ԃ̉��y��sky_floor2.wav�Ƃ���B
MikanSound->Load(0,"sky_floor2.wav",false);
//1�Ԃ̉��y��Damage.wav�Ƃ���B
MikanSound->Load(1,"Damage.wav",false);
//2�Ԃ̉��y��Fall.wav�Ƃ���B
MikanSound->Load(2,"Fall.wav",false);
//3�Ԃ̉��y��GAMEOVER.wav�Ƃ���B
MikanSound->Load(3,"GAMEOVER.wav",false);
//4�Ԃ̉��y��title.wav�Ƃ��A�Đ�����B
MikanSound->Load(4,"TITLE.wav",false);
MikanSound->Play(4,true);
//5�Ԃ̉��y��SHOT1.wav�Ƃ���B
MikanSound->Load(5,"SHOT1.wav",false);
//6�Ԃ̉��y��SHOT2.wav�Ƃ���B
MikanSound->Load(6,"SHOT2.wav",false);
//7�Ԃ̉��y��sound1.wav�Ƃ���B
MikanSound->Load(7,"sound1.wav",false);
//8�Ԃ̉��y��GAMECLEAR.wav�Ƃ���B
MikanSound->Load(8,"GAMECLEAR.wav",false);
//9�Ԃ̉��y���s�b�R�s�R�ɂ��Ă���.wav�Ƃ���B
MikanSound->Load(9,"�s�b�R�s�R�ɂ��Ă���.wav",false);

//titleTime��0��
titleTime = 0;
//���[�h�̏�����
mood=0;
Cheat=false;

return;
}

//1�b�Ԃ�60����s
//0��Ԃ��Ă���Ԃ͉��x�ł����s�����
int MainLoop( void )
{
//��ʂ̏����� 
	MikanDraw->ClearScreen();

//�^�C�g�����
if(mood==0){
if((titleTime /10) %9 <=6){
	MikanDraw->DrawTexture(0,(640-32*7.5)/2,48,32*0,(((titleTime / 10)  %9)+8)*32,32*7.5,32);
}else{
	MikanDraw->DrawTexture(0,(640-32*7.5)/2,48,32*7.5,((((titleTime / 10)  %9)-7)+8)*32,32*7.5,32);
}
MikanDraw->Printf(0,(640-5*16-3*(16-1))/2,90,"Push S to play !",PlayerX,PlayerY);
//�~�N
MikanDraw->DrawTexture(0,(640-5*4*2-3*(4-1)-32)/2,150,32 * ((titleTime / 5)  % 8),0,32,32);
MikanDraw->Printf(0,(640-5*4*2-3*(4-1)-32)/2+32,150,"�����~�N");
MikanDraw->Printf(0,(640-5*4*2-3*(4-1)-32)/2+32,168,"���@");
//��
MikanDraw->DrawTexture(0,50,200,32*0,32*4,32,32);
MikanDraw->Printf(0,92,200,"�ǁ@������ƒɂ�");
MikanDraw->Printf(0,92,218,"�@�@����10�_");
//�G
MikanDraw->DrawTexture(0,50,250,32 * (((titleTime / 5)  % 3)+6),32*1,32,32);
MikanDraw->Printf(0,92,250,"�G�@������ƒɂ�");
MikanDraw->Printf(0,92,268,"�@�@����20�_");
//��
MikanDraw->DrawTexture(0,50,300,32*0,32*6,32,32);
MikanDraw->Printf(0,92,300,"����٥̫�����");
MikanDraw->Printf(0,92,318,"�@������Ǝ���");
//�e
MikanDraw->DrawTexture(0,50,350,32*5,32*3,32,32);
MikanDraw->Printf(0,92,350,"���@�̒e");
MikanDraw->Printf(0,92,368,"�@�����镨��j�󂷂�");
MikanDraw->DrawTexture(0,50,400,32*5,32*4,32,32);
MikanDraw->Printf(0,92,400,"�G�̒e");
MikanDraw->Printf(0,92,418,"�@������ƒɂ�");
//�A�C�e��
MikanDraw->DrawTexture(0,640/2+50,200,32*4,32*3,32,32);
MikanDraw->Printf(0,640/2+50+32,200,"�K�i���j");
MikanDraw->Printf(0,640/2+50+32,218,"�@����50�_");
MikanDraw->DrawTexture(0,640/2+50,250,32*4,32*4,32,32);
MikanDraw->Printf(0,640/2+50+32,250,"�K�i���j");
MikanDraw->Printf(0,640/2+50+32,268,"�@����500�_");
MikanDraw->DrawTexture(0,640/2+50,300,32*0,32*3,32,32);
MikanDraw->Printf(0,640/2+50+32,300,"�͂���˃~�N");
MikanDraw->Printf(0,640/2+50+32,318,"�@����Life��1������I");


//Cheat���[�h!!
if(Cheat ==false){
	MikanDraw->Printf(0,(640-5*22-3*(22-1))/2,105,"Push C to Cheat mood !",PlayerX,PlayerY);
}else{
		MikanDraw->Printf(0,(640-5*13-3*(13-1))/2,105,"Cheat Mood !!",PlayerX,PlayerY);
}
if(MikanInput->GetKeyNum(K_C) >0){
	Cheat = true;
}

//titleTime�𑝂₷
titleTime = titleTime +1;

	
//�ȉ��A���������
//���@�̏�����
PlayersLife=3;
Score=0;
PlayerX=640/2-32;
PlayerY=480-32;

//�e��������
for(count1=0;count1<count_MAX;count1=count1+1){
    PlayerShotIsAlive[count1]=false;
	EnemyShot1IsAlive[count1]=false;
	EnemyShot2IsAlive[count1]=false;
	EnemyShot3IsAlive[count1]=false;
}

//�ǂ̏�����
for(count1=0;count1<count_MAX;count1=count1+1){
	WallIsAlive[count1]=false;
	WallX[count1] =0;
	WallY[count1] =0;
}
for(i=0;i<Y_length;i++){
    for(j=0;j<20;j++){
		for(count1=0;count1<count_MAX;count1=count1+1){
			if(gimmck[i][j] ==2){
				if(WallX[count1] ==0 && WallY[count1] ==0){
					WallX[count1] = j * mWIDTH;
					WallY[count1] = FrameTime * ScrollSpeed +(i-Y_adjust)* mHEIGHT;
					break;
				}
			}
		}
	}
}
//�G�̏�����
for(count1=0;count1<count_MAX;count1=count1+1){
	EnemyIsAlive[count1]=false;
	EnemyX[count1] =0;
	EnemyY[count1] =0;
}
for(i=0;i<Y_length;i++){
    for(j=0;j<20;j++){
		for(count1=0;count1<count_MAX;count1=count1+1){
			if(gimmck[i][j] ==3){
				if(EnemyX[count1] ==0 && EnemyY[count1] ==0){
					EnemyX[count1] = j * mWIDTH;
					EnemyY[count1] = FrameTime * ScrollSpeed +(i-Y_adjust)* mHEIGHT;
					break;
				}
			}
		}
	}
}
for(count1=0;count1<count_MAX;count1=count1+1){
	EnemyIsAlive[count1]=false;
}


//�A�C�e���̏�����
ShotEnemy1 =0;
ShotEnemy2 =0;
for(count1=0;count1<count_MAX;count1=count1+1){
	item3IsAlive[count1]=false;
	item3X[count1] =0;
	item3Y[count1] =0;
}
for(i=0;i<Y_length;i++){
    for(j=0;j<20;j++){
		for(count1=0;count1<count_MAX;count1=count1+1){
			if(gimmck[i][j] ==4){
				if(item3IsAlive[count1] == false){
					item3X[count1] = j * mWIDTH;
					item3Y[count1] = FrameTime * ScrollSpeed +(i-Y_adjust)* mHEIGHT;
					item3IsAlive[count1] = true;
					break;
				}
			}
		}
	}
}




//���Ԃ̏�����
FrameTime=0;
//�J�n����Ƀ~�X���[�V���������Ȃ��悤�ɂ���
MissTime=-1000;
//�J�n����ɗ������[�V���������Ȃ��悤�ɂ���
FallTime=-1000;
//�J�n����ɒe�����Ă�悤�ɂ���
PlayerLastShotTime=-1000;
//�J�n����Ɋ����������Ȃ��悤�ɂ���B
LastLeftTime = -100;
LastRightTime = -100;
LastUpTime = -100;
LastDownTime = -100;





if(MikanInput->GetKeyNum(K_S) >0){
	mood=1;
	//titleTime��0��
	titleTime = 0;
	if(Cheat ==false){
		MikanSound->Play(0,true);
	}else{
		MikanSound->Play(9,true);
	}
	MikanSound->Stop(4);
}
}


//�v���C���
if(mood==1){
//���@�̈ړ��̓��́i��������j
 //��
if(FrameTime - MissTime > 70 &&
	FrameTime - FallTime > 70){
	if(twiceLeftSpeed > 0){
		twiceLeftSpeed = twiceLeftSpeed - 1;
		}
	if(MikanInput->GetKeyNum(K_LEFT) > 0 && 
		MikanInput->GetKeyNum(K_LEFT) <= 16){
		twiceLeftSpeed = MikanInput->GetKeyNum(K_LEFT);
		}
	if(MikanInput->GetKeyNum(K_LEFT) > 16){
		twiceLeftSpeed = 16;
		}
	PlayerX = PlayerX - twiceLeftSpeed / 2;
	 //�E
	if(twiceRightSpeed > 0){
		twiceRightSpeed = twiceRightSpeed - 1;
		}
	if(MikanInput->GetKeyNum(K_RIGHT) > 0 && 
		MikanInput->GetKeyNum(K_RIGHT) <= 16){
		twiceRightSpeed = MikanInput->GetKeyNum(K_RIGHT);
		}
	if(MikanInput->GetKeyNum(K_RIGHT) > 16){
		twiceRightSpeed = 16;
		}
	PlayerX = PlayerX + twiceRightSpeed / 2;
	 //��
	if(twiceUpSpeed > 0){
		twiceUpSpeed = twiceUpSpeed - 1;
		}
	if(MikanInput->GetKeyNum(K_UP) > 0 && 
		MikanInput->GetKeyNum(K_UP) <= 16){
		twiceUpSpeed = MikanInput->GetKeyNum(K_UP);
		}
	if(MikanInput->GetKeyNum(K_UP) > 16){
		twiceUpSpeed = 16;
		}
	PlayerY = PlayerY - twiceUpSpeed / 2;
	 //��
	if(twiceDownSpeed > 0){
		twiceDownSpeed = twiceDownSpeed - 1;
		}
	if(MikanInput->GetKeyNum(K_DOWN) > 0 && 
		MikanInput->GetKeyNum(K_DOWN) <= 16){
		twiceDownSpeed = MikanInput->GetKeyNum(K_DOWN);
		}
	if(MikanInput->GetKeyNum(K_DOWN) > 16){
		twiceDownSpeed = 16;
		}
	PlayerY = PlayerY + twiceDownSpeed / 2;
}
//�~�X�E������A�X�N���[���ɍ��킹�ē���
else{
	PlayerY = PlayerY + ScrollSpeed;
	twiceLeftSpeed = 0;
	twiceRightSpeed = 0;
	twiceUpSpeed = 0;
	twiceDownSpeed = 0;
}

//���@��g�O�ɏo���Ȃ�
if(PlayerX>=640-32){
PlayerX=640-32;
}
if(PlayerX<=0){
PlayerX=0;
}
if(PlayerY>=480-32){
PlayerY=480-32;
}
if(PlayerY<=0){
PlayerY=0;
}



//���@���e�����֐�
if(MikanInput->GetKeyNum(K_Z) > 0 &&
	FrameTime-PlayerLastShotTime > 15 &&
	PlayersLife > 0 &&
	FrameTime - MissTime >= 130 &&
	FrameTime - FallTime >= 130){
    for(count1=0;count1<count_MAX;count1++){
        //�e�����݂��Ă��Ȃ��g��T���āA�������
        if(PlayerShotIsAlive[count1]==false){
            //�e�������
            PlayerShotIsAlive[count1]=true;
            PlayerShotX[count1]=PlayerX;
            PlayerShotY[count1]=PlayerY-32/2;
			MikanSound->Play(5,false);
			//���������Ԃ��L�^
			PlayerLastShotTime=FrameTime;
            //���[�v���甲����
            break;
        }
    }
}
//�G���e�����֐�
for(count1=0;count1<count_MAX;count1++){
	if((FrameTime - EnemyTime[count1])%60 ==0 &&
		EnemyIsAlive[count1] == true){
		for(count2=0;count2<count_MAX;count2++){
			if(EnemyShot1IsAlive[count2] == false &&
				EnemyShot2IsAlive[count2] == false &&
				EnemyShot3IsAlive[count2] == false){
				EnemyShot1IsAlive[count2] = true;
				EnemyShot2IsAlive[count2] = true;
				EnemyShot3IsAlive[count2] = true;
				EnemyShot1X[count2] = EnemyX[count1];
				EnemyShot2X[count2] = EnemyX[count1];
				EnemyShot3X[count2] = EnemyX[count1];
				EnemyShot1Y[count2] = EnemyY[count1] +32/2;
				EnemyShot2Y[count2] = EnemyY[count1] +32/2;
				EnemyShot3Y[count2] = EnemyY[count1] +32/2;
				MikanSound->Play(6,false);
				break;
			}
		}
	}
}

//�e�̍��W���X�V����֐�
for(count1=0;count1<count_MAX;count1++){
    //�e�����݂��Ă���g��T���āA�������
    if(PlayerShotIsAlive[count1]==true){
        //���W���X�V����
         PlayerShotY[count1]=PlayerShotY[count1]-10;
        //��������ʊO�֒e����яo�Ă�����
        if(PlayerShotY[count1]<-32){
            //�e���폜����
            PlayerShotIsAlive[count1]=false;
		}
	}
	if(EnemyShot1IsAlive[count1] == true){
		EnemyShot1X[count1] = EnemyShot1X[count1] -5;
		EnemyShot1Y[count1] = EnemyShot1Y[count1] +5;
		if(EnemyShot1X[count1] <-32 || EnemyShot1Y[count1] >480){
			EnemyShot1IsAlive[count1] = false;
		}
	}
	if(EnemyShot2IsAlive[count1] == true){
		EnemyShot2Y[count1] = EnemyShot2Y[count1] +5;
		if(EnemyShot2Y[count1] >480){
			EnemyShot2IsAlive[count1] = false;
		}
	}
	if(EnemyShot3IsAlive[count1] == true){
		EnemyShot3X[count1] = EnemyShot3X[count1] +5;
		EnemyShot3Y[count1] = EnemyShot3Y[count1] +5;
		if(EnemyShot3X[count1] >640 || EnemyShot3Y[count1] >480){
			EnemyShot3IsAlive[count1] = false;
		}
	}
}


//�G���j���ɉ����ă{�[�i�X�A�C�e���o���I
if(ShotEnemy2 ==20){
	item2IsAlive = true;
	item2X =640/2-32;
	item2Y =-32;
	ShotEnemy2 =0;
}else{
	if(ShotEnemy1 ==5){
		item1IsAlive = true;
		item1X =640/2-32;
		item1Y =-32;
		ShotEnemy1 =0;
	}
}

//��,�G,�A�C�e���̈ړ�
for(count1=0;count1<count_MAX;count1++){
	WallY[count1] = WallY[count1] + ScrollSpeed;
	if(WallY[count1] >640){
		WallIsAlive[count1] = false;
	}
	EnemyY[count1] = EnemyY[count1] + ScrollSpeed;
	if(EnemyY[count1] >640){
		EnemyIsAlive[count1] = false;
	}
	item3Y[count1] = item3Y[count1] + ScrollSpeed;
	if(item3Y[count1] >640){
		item3IsAlive[count1] = false;
	}
}
item1Y = item1Y + ScrollSpeed;
if(item1Y >640){
	item1IsAlive = false;
}
item2Y = item2Y + ScrollSpeed;
if(item2Y >640){
	item2IsAlive = false;
}


//���@�̕�,�G,�e�Ƃ̓����蔻��
for(count1=0;count1<count_MAX;count1++){
	if(PlayerX > WallX[count1] -32 &&
		PlayerX < WallX[count1] +32 &&
		PlayerY > WallY[count1] -32 &&
		PlayerY < WallY[count1] +32 &&
		WallIsAlive[count1] == true &&
		FrameTime - MissTime >= 130 &&
		FrameTime - FallTime >= 130){
		PlayersLife = PlayersLife -1;
		MissTime = FrameTime;
		MikanSound->Play(1,false);
	}
	if(PlayerX > EnemyX[count1] -32 &&
		PlayerX < EnemyX[count1] +32 &&
		PlayerY > EnemyY[count1] -32 &&
		PlayerY < EnemyY[count1] +32 &&
		EnemyIsAlive[count1] == true &&
		FrameTime - MissTime >= 130 &&
		FrameTime - FallTime >= 130){
		PlayersLife = PlayersLife -1;
		MissTime = FrameTime;
		MikanSound->Play(1,false);
	}
	if((PlayerX-EnemyShot1X[count1])*(PlayerX-EnemyShot1X[count1])+
		(PlayerY-EnemyShot1Y[count1])*(PlayerY-EnemyShot1Y[count1]) < 32*32	&&
		PlayersLife >0 && EnemyShot1IsAlive[count1] == true &&
		FrameTime - MissTime >= 130 && FrameTime - FallTime >= 130){
		PlayersLife = PlayersLife -1;
		EnemyShot1IsAlive[count1] = false;
		MissTime = FrameTime;
		MikanSound->Play(1,false);
	}
	if((PlayerX-EnemyShot2X[count1])*(PlayerX-EnemyShot2X[count1])+
		(PlayerY-EnemyShot2Y[count1])*(PlayerY-EnemyShot2Y[count1]) < 32*32	&&
		PlayersLife >0 && EnemyShot2IsAlive[count1] == true &&
		FrameTime - MissTime >= 130 && FrameTime - FallTime >= 130){
		PlayersLife = PlayersLife -1;
		EnemyShot2IsAlive[count1] = false;
		MissTime = FrameTime;
		MikanSound->Play(1,false);
	}
	if((PlayerX-EnemyShot3X[count1])*(PlayerX-EnemyShot3X[count1])+
		(PlayerY-EnemyShot3Y[count1])*(PlayerY-EnemyShot3Y[count1]) < 32*32	&&
		PlayersLife >0 && EnemyShot3IsAlive[count1] == true &&
		FrameTime - MissTime >= 130 && FrameTime - FallTime >= 130){
		PlayersLife = PlayersLife -1;
		EnemyShot3IsAlive[count1] = false;
		MissTime = FrameTime;
		MikanSound->Play(1,false);
	}
}
//���@�ƃA�C�e���̓����蔻��
if(PlayerX > item1X -32 &&
	PlayerX < item1X +32 &&
	PlayerY > item1Y -32 &&
	PlayerY < item1Y +32 &&
	item1IsAlive == true){
	Score = Score +50;
	item1IsAlive = false;
}
if(PlayerX > item2X -32 &&
	PlayerX < item2X +32 &&
	PlayerY > item2Y -32 &&
	PlayerY < item2Y +32 &&
	item2IsAlive == true){
	Score = Score +500;
	item2IsAlive = false;
}
for(count1=0;count1<count_MAX;count1++){
	if(PlayerX > item3X[count1] -32 &&
		PlayerX < item3X[count1] +32 &&
		PlayerY > item3Y[count1] -32 &&
		PlayerY < item3Y[count1] +32 &&
		item3IsAlive[count1] == true){
		PlayersLife = PlayersLife +1;
		item3IsAlive[count1] = false;
	}
}



//�e�ƕǂƂ̓����蔻��
for(count1=0;count1<count_MAX;count1++){
	for(count2=0;count2<count_MAX;count2++){
		if((PlayerShotX[count1]-WallX[count2])*(PlayerShotX[count1]-WallX[count2])+
			(PlayerShotY[count1]-WallY[count2])*(PlayerShotY[count1]-WallY[count2]) < 32*32	&&
			WallIsAlive[count2] == true	&& PlayerShotIsAlive[count1] == true){
			PlayerShotIsAlive[count1] = false;
			WallIsAlive[count2] = false;
			Score = Score +10;
			MikanSound->Play(7,false);
			break;
		}
	}
}
//�e�ƓG�Ƃ̓����蔻��
for(count1=0;count1<count_MAX;count1++){
	for(count2=0;count2<count_MAX;count2++){
		if((PlayerShotX[count1]-EnemyX[count2])*(PlayerShotX[count1]-EnemyX[count2])+
			(PlayerShotY[count1]-EnemyY[count2])*(PlayerShotY[count1]-EnemyY[count2]) < 32*32	&&
			EnemyIsAlive[count2] == true && PlayerShotIsAlive[count1] == true){
			PlayerShotIsAlive[count1] = false;
			EnemyIsAlive[count2] = false;
			Score = Score +20;
			ShotEnemy1 = ShotEnemy1 +1;
			ShotEnemy2 = ShotEnemy2 +1;
			MikanSound->Play(7,false);
			break;
		}
	}
}

//���Ƃ̓����蔻��
for(i=0;i<Y_length;i++){
    for(j=0;j<20;j++){
		if(gimmck[i][j] ==1){
			if(PlayerX > j*mWIDTH -16 &&
				PlayerX < j*mWIDTH +16 &&
				PlayerY > FrameTime * ScrollSpeed +(i-Y_adjust)* mHEIGHT -16 &&
				PlayerY < FrameTime * ScrollSpeed +(i-Y_adjust)* mHEIGHT +16 &&
				FrameTime - FallTime >= 130){
				PlayersLife = 0;
				PlayerX = j*mWIDTH;
				PlayerY = FrameTime * ScrollSpeed + (i-Y_adjust)*mHEIGHT;
				FallTime = FrameTime;
				MikanSound->Play(2,false);
			};
		};
	}
}





//��ʓ��ɓ������ǂ��o��������
for(count1=0;count1<count_MAX;count1++){
	if(WallY[count1] == -32){
		WallIsAlive[count1] = true;
	}
}
//��ʓ��ɓ������G���o��������
for(count1=0;count1<count_MAX;count1++){
	if(EnemyY[count1] == -32){
		EnemyIsAlive[count1] = true;
		EnemyTime[count1] = FrameTime;
	}
}


//�f�o�b�O���[�h
if(Cheat ==true){
		//�~�N�͎��ȂȂ��I
	if(PlayersLife ==0){
		PlayersLife =3;
	}
	//�uX�v�������Ǝ��@������!!
	if(MikanInput->GetKeyNum(K_X) > 1 &&
		PlayersLife > 0){
		PlayersLife =0;
	}
	//�uR�v�ł�蒼��
	if(MikanInput->GetKeyNum(K_R) > 1){
	FrameTime = FrameTime-10;
	}
}




//�ȉ��`��

//�w�i��\��
for(i=0;i<Y_length;i++){
    for(j=0;j<20;j++){
		MikanDraw->DrawTexture(0,j*mWIDTH,FrameTime * ScrollSpeed + (i-Y_adjust)*mHEIGHT,(map[i][j] % 9) * mWIDTH,(7- (map[i][j] /9))* mHEIGHT,mWIDTH,mHEIGHT);
	}
}
//�M�~�b�N��\��
for(i=0;i<Y_length;i++){
    for(j=0;j<20;j++){
		if(gimmck[i][j] ==1){
			MikanDraw->DrawTexture(0,j*mWIDTH,FrameTime * ScrollSpeed + (i-Y_adjust)*mHEIGHT,6* mWIDTH,5* mHEIGHT,mWIDTH,mHEIGHT);
		}
		for(count1=0;count1<count_MAX;count1++){
			if(gimmck[i][j] ==2 && WallIsAlive[count1] ==true){
				MikanDraw->DrawTexture(0,WallX[count1],WallY[count1],0* mWIDTH,4* mHEIGHT,mWIDTH,mHEIGHT);
			}
		}
		for(count2=0;count2<count_MAX;count2++){
			if(gimmck[i][j] ==3 && EnemyIsAlive[count2] ==true){
				MikanDraw->DrawTexture(0,EnemyX[count2],EnemyY[count2],(6+((FrameTime /5) %3))* mWIDTH,1* mHEIGHT,mWIDTH,mHEIGHT);
			}
		}
	}
}
	





//���@�摜��\��
//0�Ԃ̉摜���A�`���̍��W(100,100)������̒��_�Ƃ��A�摜���̍��W(0,0)����A�T�C�Y(32,32)�̑傫����
if(PlayersLife > 0){
	//�~�X��
	if(FrameTime - MissTime >= 70 &&
		FrameTime - MissTime < 85){
		MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 * ((FrameTime / 5)  %8),0,32,32);
	}
	else{
		if(FrameTime - MissTime > 100 &&
		FrameTime - MissTime < 115){
		MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 * ((FrameTime / 5)  % 8),0,32,32);
	}
		//������
		else{
			if(FrameTime - FallTime >= 70 &&
				FrameTime - FallTime < 85){
				MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 * ((FrameTime / 5)  % 8),0,32,32);
			}
			else{
				if(FrameTime - FallTime >= 100 &&
					FrameTime - FallTime < 115){
					MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 * ((FrameTime / 5)  % 8),0,32,32);
				}
				//�ʏ펞
				else{
					if(FrameTime - MissTime > 130 &&
					FrameTime - FallTime > 130){
					MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 * ((FrameTime / 5)  % 8),0,32,32);
					}
				}
			}
		}
	}
}
//�e���[�V����
if(PlayersLife >= 0){	
	//�~�X
	if(FrameTime - MissTime < 70){
		if(FrameTime - MissTime < 60){
			MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 *((FrameTime - MissTime)/ 10),32*2,32,32);
		};
	};
	//����
	if(FrameTime - FallTime < 70){
		if(FrameTime - FallTime <50){
		MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 *((FrameTime - FallTime)/ 10),32,32,32);
		};
	};
}


//�e�̉摜��\��
for(count1=0;count1<count_MAX;count1++){
	if(PlayerShotIsAlive[count1]==true){
		MikanDraw->DrawTexture(0,PlayerShotX[count1],PlayerShotY[count1],32*5,32*3,32,32);
	}
	if(EnemyShot1IsAlive[count1] == true){
		MikanDraw->DrawTexture(0,EnemyShot1X[count1],EnemyShot1Y[count1],32*5,32*4,32,32);
	}
	if(EnemyShot2IsAlive[count1] == true){
		MikanDraw->DrawTexture(0,EnemyShot2X[count1],EnemyShot2Y[count1],32*5,32*4,32,32);
	}
	if(EnemyShot3IsAlive[count1] == true){
		MikanDraw->DrawTexture(0,EnemyShot3X[count1],EnemyShot3Y[count1],32*5,32*4,32,32);
	}
}
//�A�C�e���̕\��
if(item1IsAlive == true){
	MikanDraw->DrawTexture(0,item1X,item1Y,32*4,32*3,32,32);
}
if(item2IsAlive == true){
	MikanDraw->DrawTexture(0,item2X,item2Y,32*4,32*4,32,32);
}
for(count1=0;count1<count_MAX;count1++){
	if(item3IsAlive[count1] == true){
		MikanDraw->DrawTexture(0,item3X[count1],item3Y[count1],32*0,32*3,32,32);
	}
}



//���@�̍��W�Ǝc�胉�C�t�ƌo�ߎ��ԁi�b�j��\��
MikanDraw->Printf(0,0,0,"YourLife = %d",PlayersLife);
MikanDraw->Printf(0,0,15,"YourScore = %d",Score);
MikanDraw->Printf(0,0,45,"�o�ߎ��� = %d s",FrameTime/60);


//1�t���[���o��
FrameTime=FrameTime+1;

//�c�@0�Ń��U���g��
if(PlayersLife <=0 || FrameTime >= 4200){
	if(FrameTime - MissTime >= 70 && FrameTime - FallTime >= 70){
		mood=2;
		MikanSound->Stop(0);
		MikanSound->Stop(9);
		if(PlayersLife >0){
			MikanSound->Play(8,false);
		}else{
			MikanSound->Play(3,false);
		}
	}
}



}
//���U���g���
if(mood==2){
if(PlayersLife >0){
	MikanDraw->Printf(0,(640-5*9*2-3*(9-1))/2,60,"���`�ނ��肠�`���");
}else{
	MikanDraw->Printf(0,(640-5*9*2-3*(9-1))/2,60,"���`�ށ`���`�΁`��");
}
MikanDraw->Printf(0,(640-5*9-3*(9-1))/2,120,"Score=%d",Score);
MikanDraw->Printf(0,(640-5*13-3*(13-1))/2,135,"TimeBonus=%d",FrameTime/6);
if(PlayersLife >0){
	MikanDraw->Printf(0,(640-5*13-3*(13-1))/2,150,"LifeBonus=%d",PlayersLife*200);
}
MikanDraw->Printf(0,(640-5*18-3*(18-1))/2,180,"YourTotalScore=%d",Score + FrameTime/6 + PlayersLife*200);
MikanDraw->Printf(0,(640-5*23-3*(23-1))/2,225,"Push R to play again!!");

if(MikanInput->GetKeyNum(K_R) >0){
	mood=0;
	Cheat=false;
	MikanSound->Stop(3);
	MikanSound->Play(4,true);

}

}

return 0;
}

//MainLoop�I�����1�x�������s
//��Еt���Ȃǂ��s��
void CleanUp( void )
{

	
	
}
