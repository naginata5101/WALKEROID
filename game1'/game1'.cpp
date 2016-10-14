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

//MainLoop開始前に1度だけ実行
//テクスチャの読み込みなどのゲーム開始前の準備を行う
void UserInit( void )
{//0番の文字セットを、サイズ=15px,色=不透過度=255/白で初期化
MikanDraw->CreateFont(0,15,MikanDraw->Color(255,255,255,255));

//0番の画像をn_f_stg2.2.pngにする。透過色は深緑
MikanDraw->CreateTexture(0,"n_f_stg2.2.png",TRC_ZERO);

//0番の音楽をsky_floor2.wavとする。
MikanSound->Load(0,"sky_floor2.wav",false);
//1番の音楽をDamage.wavとする。
MikanSound->Load(1,"Damage.wav",false);
//2番の音楽をFall.wavとする。
MikanSound->Load(2,"Fall.wav",false);
//3番の音楽をGAMEOVER.wavとする。
MikanSound->Load(3,"GAMEOVER.wav",false);
//4番の音楽をtitle.wavとし、再生する。
MikanSound->Load(4,"TITLE.wav",false);
MikanSound->Play(4,true);
//5番の音楽をSHOT1.wavとする。
MikanSound->Load(5,"SHOT1.wav",false);
//6番の音楽をSHOT2.wavとする。
MikanSound->Load(6,"SHOT2.wav",false);
//7番の音楽をsound1.wavとする。
MikanSound->Load(7,"sound1.wav",false);
//8番の音楽をGAMECLEAR.wavとする。
MikanSound->Load(8,"GAMECLEAR.wav",false);
//9番の音楽をピッコピコにしてやんよ.wavとする。
MikanSound->Load(9,"ピッコピコにしてやんよ.wav",false);

//titleTimeを0に
titleTime = 0;
//モードの初期化
mood=0;
Cheat=false;

return;
}

//1秒間に60回実行
//0を返している間は何度でも実行される
int MainLoop( void )
{
//画面の初期化 
	MikanDraw->ClearScreen();

//タイトル画面
if(mood==0){
if((titleTime /10) %9 <=6){
	MikanDraw->DrawTexture(0,(640-32*7.5)/2,48,32*0,(((titleTime / 10)  %9)+8)*32,32*7.5,32);
}else{
	MikanDraw->DrawTexture(0,(640-32*7.5)/2,48,32*7.5,((((titleTime / 10)  %9)-7)+8)*32,32*7.5,32);
}
MikanDraw->Printf(0,(640-5*16-3*(16-1))/2,90,"Push S to play !",PlayerX,PlayerY);
//ミク
MikanDraw->DrawTexture(0,(640-5*4*2-3*(4-1)-32)/2,150,32 * ((titleTime / 5)  % 8),0,32,32);
MikanDraw->Printf(0,(640-5*4*2-3*(4-1)-32)/2+32,150,"初音ミク");
MikanDraw->Printf(0,(640-5*4*2-3*(4-1)-32)/2+32,168,"自機");
//壁
MikanDraw->DrawTexture(0,50,200,32*0,32*4,32,32);
MikanDraw->Printf(0,92,200,"壁　当たると痛い");
MikanDraw->Printf(0,92,218,"　　撃つと10点");
//敵
MikanDraw->DrawTexture(0,50,250,32 * (((titleTime / 5)  % 3)+6),32*1,32,32);
MikanDraw->Printf(0,92,250,"敵　当たると痛い");
MikanDraw->Printf(0,92,268,"　　撃つと20点");
//穴
MikanDraw->DrawTexture(0,50,300,32*0,32*6,32,32);
MikanDraw->Printf(0,92,300,"ｴﾀｰﾅﾙ･ﾌｫｰｽ･穴");
MikanDraw->Printf(0,92,318,"　落ちると死ぬ");
//弾
MikanDraw->DrawTexture(0,50,350,32*5,32*3,32,32);
MikanDraw->Printf(0,92,350,"自機の弾");
MikanDraw->Printf(0,92,368,"　あらゆる物を破壊する");
MikanDraw->DrawTexture(0,50,400,32*5,32*4,32,32);
MikanDraw->Printf(0,92,400,"敵の弾");
MikanDraw->Printf(0,92,418,"　当たると痛い");
//アイテム
MikanDraw->DrawTexture(0,640/2+50,200,32*4,32*3,32,32);
MikanDraw->Printf(0,640/2+50+32,200,"葱（少）");
MikanDraw->Printf(0,640/2+50+32,218,"　取ると50点");
MikanDraw->DrawTexture(0,640/2+50,250,32*4,32*4,32,32);
MikanDraw->Printf(0,640/2+50+32,250,"葱（多）");
MikanDraw->Printf(0,640/2+50+32,268,"　取ると500点");
MikanDraw->DrawTexture(0,640/2+50,300,32*0,32*3,32,32);
MikanDraw->Printf(0,640/2+50+32,300,"はちゅねミク");
MikanDraw->Printf(0,640/2+50+32,318,"　取るとLifeが1増える！");


//Cheatモード!!
if(Cheat ==false){
	MikanDraw->Printf(0,(640-5*22-3*(22-1))/2,105,"Push C to Cheat mood !",PlayerX,PlayerY);
}else{
		MikanDraw->Printf(0,(640-5*13-3*(13-1))/2,105,"Cheat Mood !!",PlayerX,PlayerY);
}
if(MikanInput->GetKeyNum(K_C) >0){
	Cheat = true;
}

//titleTimeを増やす
titleTime = titleTime +1;

	
//以下、初期化作業
//自機の初期化
PlayersLife=3;
Score=0;
PlayerX=640/2-32;
PlayerY=480-32;

//弾を初期化
for(count1=0;count1<count_MAX;count1=count1+1){
    PlayerShotIsAlive[count1]=false;
	EnemyShot1IsAlive[count1]=false;
	EnemyShot2IsAlive[count1]=false;
	EnemyShot3IsAlive[count1]=false;
}

//壁の初期化
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
//敵の初期化
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


//アイテムの初期化
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




//時間の初期化
FrameTime=0;
//開始直後にミスモーションをしないようにする
MissTime=-1000;
//開始直後に落下モーションをしないようにする
FallTime=-1000;
//開始直後に弾を撃てるようにする
PlayerLastShotTime=-1000;
//開始直後に慣性が働かないようにする。
LastLeftTime = -100;
LastRightTime = -100;
LastUpTime = -100;
LastDownTime = -100;





if(MikanInput->GetKeyNum(K_S) >0){
	mood=1;
	//titleTimeを0に
	titleTime = 0;
	if(Cheat ==false){
		MikanSound->Play(0,true);
	}else{
		MikanSound->Play(9,true);
	}
	MikanSound->Stop(4);
}
}


//プレイ画面
if(mood==1){
//自機の移動の入力（慣性あり）
 //左
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
	 //右
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
	 //上
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
	 //下
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
//ミス・落下後、スクロールに合わせて動く
else{
	PlayerY = PlayerY + ScrollSpeed;
	twiceLeftSpeed = 0;
	twiceRightSpeed = 0;
	twiceUpSpeed = 0;
	twiceDownSpeed = 0;
}

//自機を枠外に出さない
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



//自機が弾を撃つ関数
if(MikanInput->GetKeyNum(K_Z) > 0 &&
	FrameTime-PlayerLastShotTime > 15 &&
	PlayersLife > 0 &&
	FrameTime - MissTime >= 130 &&
	FrameTime - FallTime >= 130){
    for(count1=0;count1<count_MAX;count1++){
        //弾が存在していない枠を探して、見つかれば
        if(PlayerShotIsAlive[count1]==false){
            //弾を作って
            PlayerShotIsAlive[count1]=true;
            PlayerShotX[count1]=PlayerX;
            PlayerShotY[count1]=PlayerY-32/2;
			MikanSound->Play(5,false);
			//撃った時間を記録
			PlayerLastShotTime=FrameTime;
            //ループから抜ける
            break;
        }
    }
}
//敵が弾を撃つ関数
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

//弾の座標を更新する関数
for(count1=0;count1<count_MAX;count1++){
    //弾が存在している枠を探して、見つかれば
    if(PlayerShotIsAlive[count1]==true){
        //座標を更新する
         PlayerShotY[count1]=PlayerShotY[count1]-10;
        //もしも画面外へ弾が飛び出ていたら
        if(PlayerShotY[count1]<-32){
            //弾を削除する
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


//敵撃破数に応じてボーナスアイテム出現！
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

//壁,敵,アイテムの移動
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


//自機の壁,敵,弾との当たり判定
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
//自機とアイテムの当たり判定
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



//弾と壁との当たり判定
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
//弾と敵との当たり判定
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

//穴との当たり判定
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





//画面内に入った壁を出現させる
for(count1=0;count1<count_MAX;count1++){
	if(WallY[count1] == -32){
		WallIsAlive[count1] = true;
	}
}
//画面内に入った敵を出現させる
for(count1=0;count1<count_MAX;count1++){
	if(EnemyY[count1] == -32){
		EnemyIsAlive[count1] = true;
		EnemyTime[count1] = FrameTime;
	}
}


//デバッグモード
if(Cheat ==true){
		//ミクは死なない！
	if(PlayersLife ==0){
		PlayersLife =3;
	}
	//「X」を押すと自機が自爆!!
	if(MikanInput->GetKeyNum(K_X) > 1 &&
		PlayersLife > 0){
		PlayersLife =0;
	}
	//「R」でやり直し
	if(MikanInput->GetKeyNum(K_R) > 1){
	FrameTime = FrameTime-10;
	}
}




//以下描画

//背景を表示
for(i=0;i<Y_length;i++){
    for(j=0;j<20;j++){
		MikanDraw->DrawTexture(0,j*mWIDTH,FrameTime * ScrollSpeed + (i-Y_adjust)*mHEIGHT,(map[i][j] % 9) * mWIDTH,(7- (map[i][j] /9))* mHEIGHT,mWIDTH,mHEIGHT);
	}
}
//ギミックを表示
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
	





//自機画像を表示
//0番の画像を、描画先の座標(100,100)を左上の頂点とし、画像内の座標(0,0)から、サイズ(32,32)の大きさで
if(PlayersLife > 0){
	//ミス後
	if(FrameTime - MissTime >= 70 &&
		FrameTime - MissTime < 85){
		MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 * ((FrameTime / 5)  %8),0,32,32);
	}
	else{
		if(FrameTime - MissTime > 100 &&
		FrameTime - MissTime < 115){
		MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 * ((FrameTime / 5)  % 8),0,32,32);
	}
		//落下後
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
				//通常時
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
//各モーション
if(PlayersLife >= 0){	
	//ミス
	if(FrameTime - MissTime < 70){
		if(FrameTime - MissTime < 60){
			MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 *((FrameTime - MissTime)/ 10),32*2,32,32);
		};
	};
	//落下
	if(FrameTime - FallTime < 70){
		if(FrameTime - FallTime <50){
		MikanDraw->DrawTexture(0,PlayerX,PlayerY,32 *((FrameTime - FallTime)/ 10),32,32,32);
		};
	};
}


//弾の画像を表示
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
//アイテムの表示
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



//自機の座標と残りライフと経過時間（秒）を表示
MikanDraw->Printf(0,0,0,"YourLife = %d",PlayersLife);
MikanDraw->Printf(0,0,15,"YourScore = %d",Score);
MikanDraw->Printf(0,0,45,"経過時間 = %d s",FrameTime/60);


//1フレーム経過
FrameTime=FrameTime+1;

//残機0でリザルトへ
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
//リザルト画面
if(mood==2){
if(PlayersLife >0){
	MikanDraw->Printf(0,(640-5*9*2-3*(9-1))/2,60,"げ～むくりあ～♪♪");
}else{
	MikanDraw->Printf(0,(640-5*9*2-3*(9-1))/2,60,"げ～む～お～ば～♪");
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

//MainLoop終了後に1度だけ実行
//後片付けなどを行う
void CleanUp( void )
{

	
	
}
