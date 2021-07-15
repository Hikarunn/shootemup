#include<DxLib.h>
#include<cmath>
#include<memory>
#include"Geometry.h"

///�����蔻��֐�
///@param posA A�̍��W
///@param radiusA A�̔��a
///@param posB B�̍��W
///@param radiusB B�̔��a
bool IsHit(const Circle& cA, const Circle& cB) {
	//�����蔻����������Ă�������
	auto totalRadius (cA.radius + cB.radius);
	return(cA.pos - cB.pos).SQMagnitude() <= totalRadius * totalRadius;
	
}

using namespace std;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetMainWindowText("2016008_�����s");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//�w�i�p
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	//�e�̔��a
	constexpr float bullet_radius = 5.0f;

	//���@�̔��a
	constexpr float player_radius = 10.0f;

	struct Bullet {
		Circle circle;//���W
		Vector2 vel;//���x
		bool isActive = false;//�����Ă邩�`�H
	};

	
	//�K����256���炢����Ƃ�
	Bullet bullets[1024];
	

	Position2 enemypos(320,150);//�G���W
	char keystate[256];
	char lastkeystate[256];
	Position2 shotposA(0, 0);
	Position2 shotposB(128, 0);
	Position2 shotposC(256, 0);
	Position2 shotposD(384, 0);
	Position2 shotposE(512, 0);
	
	
	Circle player(Position2(320, 400), player_radius);//���@���W

	unsigned int frame = 0;//�t���[���Ǘ��p

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;

	constexpr int frame_for_bullet_type = 180;
	constexpr int bullet_type_num = 8;

	while (ProcessMessage() == 0) {
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);

		isDebugMode = keystate[KEY_INPUT_P];

		//�w�i
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


		//�v���C���[
		if (keystate[KEY_INPUT_RIGHT]) {
			player.pos.x = min(640, player.pos.x +4);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			player.pos.x = max(0, player.pos.x -4);
		}
		if (keystate[KEY_INPUT_UP]) {
			player.pos.y = max(0,player.pos.y-4);
		}else if (keystate[KEY_INPUT_DOWN]) {
			player.pos.y = min(480,player.pos.y+4);
		}

	if (keystate[KEY_INPUT_Z]&&lastkeystate[KEY_INPUT_Z])
		{

		}
	for (auto& shot : shots)
	{
		if(shot.IsAc)
	}

		int pidx = (frame/4 % 2)*5+3;
		DrawRotaGraph(player.pos.x, player.pos.y, 2.0f, 0.0f, playerH[pidx], true);
		if (isDebugMode) {
			//���@�̖{��(�����蔻��)
			DrawCircle(player.pos.x, player.pos.y, player.radius, 0xffaaaa, false, 3);
		}
		constexpr float base_speed = 5.0f;
		constexpr int blazing_period = 12;
		float speed = base_speed;

		if (frame < frame_for_bullet_type) {


			//�e����
			if (frame % blazing_period == 0) {
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;
						b.vel = Vector2(0, base_speed);
						b.isActive = true;
						break;
					}
				}
			}
		}
		else if(frame<frame_for_bullet_type*2){
			if (frame % blazing_period == 0) {
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;
						b.vel = (player.pos - enemypos). Normalized()* base_speed;
						b.isActive = true;
						break;
					}
				}
			}

		}
		else  if (frame < frame_for_bullet_type * 3) {
			if (frame % blazing_period == 0) {
				int count = 0;
				auto dir = (player.pos - enemypos);
				float bangle = atan2(dir.y, dir.x);
				bangle -= DX_PI_F / 6.0f;
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;
						b.vel = Vector2(cos(bangle), sin(bangle)) * base_speed;
						b.isActive = true;
						bangle += DX_PI_F / 6.0f;
						++count;
					}
					if (count == 3) {
						break;
					}
				}
			
			}
		}
		
		else if (frame < frame_for_bullet_type * 4) {
			if (frame % blazing_period == 0) {
				int count = 0;
				auto dir = (enemypos);
				float bangle = atan2(dir.y, dir.x);
				bangle -= DX_PI_F / 6.0f;
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;
						b.vel = Vector2(cos(bangle), sin(bangle)) * base_speed;
						b.isActive = true;
						bangle += DX_PI_F /6.0f;
						++count;
					}
					if (count == 12) {
						break;
					}
				}

			}
		}
		
		else  if (frame < frame_for_bullet_type * 5) {
			if (frame % blazing_period == 0) {
				int count = 0;
			
				float bangle = (rand() % 15) * DX_PI / 180.0f;
				bangle -= DX_PI_F / 2.0f;
				for (auto& b : bullets) {
					if (!b.isActive) {
						b.circle.pos = enemypos;
						float speed = base_speed / 5 + (rand() % 4);
						b.vel = Vector2(cos(bangle), sin(bangle)) * speed;
						b.isActive = true;
						bangle += DX_PI_F / 6.0f+(float)(rand()%15)*DX_PI_F;

						++count;
					}
					if (count == 12) {
						break;
					}
				}

			}
			
			
		}
		else  {
			if (frame % blazing_period == 0) {
				if (frame % blazing_period == 0) {
					int count = 0;
					auto dir = (player.pos - enemypos);
					float bangle = atan2(dir.y, dir.x);
					bangle -= DX_PI_F / 3.0f;
					for (auto& b : bullets) {
						if (!b.isActive) {
							b.circle.pos = enemypos;
							b.vel = Vector2(cos(bangle), sin(bangle)) * base_speed;
							b.isActive = true;
							bangle += DX_PI_F / 12.0f;
							++count;
						}
						if (count == 7) {
							break;
						}
					}
				}
			}
	
}
	
	
		//�e�̍X�V����ѕ\��
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}
			//�@�e�̌��ݍ��W�ɒe�̌��ݑ��x�����Z���Ă�������
			b.circle.pos += b.vel;
			
			
			//�A
			float angle = atan2(b.vel.y, b.vel.x);
			//�e�̊p�x��atan2�Ōv�Z���Ă��������Bangle�ɒl������񂾂�I�D
			
			DrawRotaGraph(b.circle.pos.x, b.circle.pos.y,1.0f,angle, bulletH, true);
			
			if (isDebugMode) {
				//�e�̖{��(�����蔻��)
				DrawCircle(b.circle.pos.x, b.circle.pos.y, bullet_radius, 0x0000ff, false, 3);
			}
			//�e���E��
			if (b.circle.pos.x + 16 < 0 || b.circle.pos.x - 16 > 640 ||
				b.circle.pos.y + 24 < 0 || b.circle.pos.y - 24 > 480) {
				b.isActive = false;
			}

			//������I
			//����IsHit�͎����������Ă܂���B�����ŏ����Ă��������B

			if(b.isActive &&IsHit(b.circle ,player)) {
				//�������������������Ă��������B
				DrawString(10, 10, "HIT!!", GetColor(0, 0, 0));
				
				b.isActive = false;
			}
			
		}

		//�G�̕\��
		enemypos.x = abs((int)((frame+320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//�G�̖{��(�����蔻��)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		frame=(frame+1)%(frame_for_bullet_type* bullet_type_num);
		ScreenFlip();
		copy(begin(keystate),
			end(keystate),
			begin(lastkeystate));
	}

	DxLib_End();

	return 0;
}