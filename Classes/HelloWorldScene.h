#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    Sprite *maybay;
	Sprite *bullet;
	Sprite *bullet_boss;
	Sprite *vatPham;
	Sprite *boss;
	Point touchTopoint( Touch* touch );
	bool touchingSprite ( Touch* touch );
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
	void randomHanhtinh();
	void update( float dt );
	Point indexRandom( int i);
	void addBullet();
	void bulletMoveFinished(Node* pSender);
	void Animationht();
	void addVatpham();
	void vatphamMoveFinished( Node *pSender );
	void addBoss();
	void bulletBoss();
	void removebulletBoss( Node *pSender );

	
  private:
	float speed , ss, sb, svp;
	Point touchOffset;
	Vector<Sprite*> hanhtinh;
	Vector<Sprite*> vtbl;
	Vector< Sprite*> vatpham;
	Vector<SpriteFrame*> animFrames;
	Vector<Sprite*> bt;
	int indexHanhtinh;
	bool checkAni;
	unsigned int score;
	unsigned int liveM;
	Label *scoreLabel;
	Label *liveLabel;
	String *templateLive;


    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
