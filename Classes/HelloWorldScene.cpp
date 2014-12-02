#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	ss = 0.0f;
	sb = 0.0f;

	maybay = Sprite::create("GameScreen/hero1.png");
	maybay->setPosition(Point(maybay->getContentSize().width, visibleSize.height/2));
	this->addChild( maybay, 1 );


	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2( HelloWorld::onTouchesBegan, this );
	listener->onTouchesMoved = CC_CALLBACK_2( HelloWorld::onTouchesMoved, this );
	listener->onTouchesEnded = CC_CALLBACK_2( HelloWorld::onTouchesEnded, this );

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority( listener, this );

	speed = 300.0f;
	svp = 0.0f;
	Sprite* ht ;

	for (int i = 0; i < 10 ; i++)
	{
		ht = Sprite::create("GameScreen/Asteroid_3.png");
		ht->setPosition(visibleSize.width - 100, visibleSize.height/2);
		addChild(ht, 1);
		hanhtinh.pushBack(ht);
	}

	indexHanhtinh = 0;
	checkAni = false;
	score = 0;
	liveM = 3;

	this->scheduleUpdate();

	String *templateScore = String::createWithFormat("SCORE : %d", score);
	scoreLabel = Label::createWithTTF(templateScore->getCString(), "fonts/UTM Alberta Heavy.ttf", visibleSize.height*0.07f);
	scoreLabel->setPosition( Point(visibleSize.width - scoreLabel->getContentSize().width,
		visibleSize.height - scoreLabel->getContentSize().height)) ;


	templateLive = String::createWithFormat("LIVE : %d", liveM);
	liveLabel = Label::createWithTTF(templateLive->getCString(), "fonts/UTM Alberta Heavy.ttf", visibleSize.height*0.07f);
	liveLabel->setPosition( Point( liveLabel->getContentSize().width , visibleSize.height - liveLabel->getContentSize().height));

	this->addChild( liveLabel, 100 );
	this->addChild( scoreLabel, 100 );

	addBoss();

	return true;
}

Point HelloWorld::indexRandom( int i )
{
	Point p;
	return p;
}

void HelloWorld::randomHanhtinh()
{
	Size size = Director::getInstance()->getWinSize();
	Sprite *ht1 = hanhtinh.at(indexHanhtinh);
	ht1->setVisible(true);
	srand(time(NULL));
	int yRandomPosition = (rand() % (int)(size.height - (ht1->getContentSize().height))) ;
	int XRandomPosition = (rand() % (int)(size.width - (ht1->getContentSize().height))) +1;

	ht1->setPosition(Point( XRandomPosition, yRandomPosition ));
	indexHanhtinh++;
	if (indexHanhtinh >= hanhtinh.size())
	{
		indexHanhtinh = 1;
	}


	Sprite *ht2 = hanhtinh.at(indexHanhtinh);
	ht2->setVisible(true);
	srand(time(NULL));
	int yRandomPosition1 = (rand() % (int)(size.height + (ht1->getContentSize().height))) ;
	ht2->setPosition(Point( size.width - 100, yRandomPosition1 ));
	indexHanhtinh++;
	if (indexHanhtinh >= hanhtinh.size())
	{
		indexHanhtinh = 0;
	}

}


void HelloWorld::addBullet( )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	bullet = Sprite::create("GameScreen/bullet1.png");
	this->addChild(bullet);
	vtbl.pushBack(bullet);

	Point planePosition = maybay->getPosition();
	Point bulletPosition = Point(planePosition.x + maybay->getContentSize().width /2 , planePosition.y);
	bullet->setPosition(bulletPosition);

	float length = Director::getInstance()->getWinSize().height+bullet->getContentSize().height/2-bulletPosition.y;
	float velocity = 350/1;//320pixel/sec
	float realMoveDuration = length/velocity;

	auto actionMove = MoveTo::create(realMoveDuration, Point(visibleSize.width - 100 - 
		bullet->getContentSize().width/2, bulletPosition.y));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(HelloWorld::bulletMoveFinished, this));

	auto sequence = Sequence::create(actionMove, actionDone, NULL);

	bullet->runAction(RepeatForever::create(sequence));


}

void HelloWorld::bulletMoveFinished(Node* pSender)
{
	vtbl.eraseObject((Sprite*)pSender, true);
	this->removeChild( pSender, true );
}

void HelloWorld::addVatpham()
{
	vatPham = Sprite::create("GameScreen/ufo1.png");
	this->addChild( vatPham );
	vatpham.pushBack(vatPham);
	auto vatPhamSize = vatPham->getContentSize();
	auto winSize = Director::getInstance()->getWinSize();
	int minX = vatPhamSize.width/2;
	int maxX = winSize.width - vatPhamSize.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX) + minX;
	vatPham->setPosition(Point(actualX, winSize.height +  vatPhamSize.height/2));

}

void HelloWorld::vatphamMoveFinished( Node *pSender )
{

}

void HelloWorld::addBoss()
{
	Size size = Director::getInstance()->getWinSize();
	boss = Sprite::create("GameScreen/Space_Pod.png");
	boss->setPosition(Point( size.width - 100, size.height/2));
	this->addChild( boss);
	bulletBoss();
}

void HelloWorld::bulletBoss()
{
	bullet_boss = Sprite::create("GameScreen/bullet2.png");
	this->addChild( bullet_boss );
	bt.pushBack(bullet_boss);

	Point bossPositon = boss->getPosition();
	Point btPosition = Point( bossPositon.x - boss->getContentSize().width, bossPositon.y );
	bullet_boss->setPosition(btPosition);
}

void HelloWorld::removebulletBoss( Node *pSender )
{

}
void HelloWorld::update( float dt )
{

	ss += speed*dt;
	sb += speed*dt;
	svp += speed*dt;
	if (ss> 500.0f)
	{

		randomHanhtinh();
		addVatpham();

		ss = 0.0f;
	}


	if (sb > 150.0f)
	{
		addBullet();
		sb=0.0f;
	}





	for (auto ht : hanhtinh)
	{

		ht->setPositionX( ht->getPositionX() - speed*dt );

		//Va cham hanh tinh va may bay
		if (ht->getBoundingBox().intersectsRect(maybay->getBoundingBox()))
		{
			if (ht->isVisible())
			{
				liveM--;
				templateLive = String::createWithFormat("LIVE : %d", liveM);
				liveLabel->setString( templateLive->getCString() );
				log("live : %d", liveM);
				if( liveM <=0 )
				{
					Director::getInstance()->pause();

				}
				ht->setVisible( false );
			}

						
		}

		//va cham dan va hanh tinh
		for (auto bl : vtbl)
		{
			if (ht->getBoundingBox().intersectsRect(bl->getBoundingBox()))
			{
				if (ht->isVisible())
				{
					score++;
					String *templeScore = String::createWithFormat(" SCORE : %i ", score);
					scoreLabel->setString( templeScore->getCString() );
					log("score : %d", score);
					ht->setVisible(false);
				}


			}

		}

		for ( auto vp : vatpham)
		{
			
			if (score > 0 && score % 10 ==0)
			{
				vp->setPositionY( vp->getPositionY() - speed*dt );
			}
			
		}

	}
}

void HelloWorld::Animationht()
{
	checkAni = true;
	//animFrames.reserve(2);
	animFrames.pushBack( SpriteFrame::create("enemy2_down4.png", Rect(0,0,69,95)) );

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);
	bullet->runAction( RepeatForever::create(animate) );

}

Point HelloWorld::touchTopoint( Touch* touch )
{
	// convert the touch object to a position in our cocos2d space
	return Director::getInstance()->convertToGL( touch->getLocationInView() );
}

bool HelloWorld::touchingSprite( Touch* touch )
{
	return (this->maybay->getPosition().getDistance(this->touchTopoint(touch)) < 70.0f);
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	touchOffset = Point::ZERO;

	for (auto touch : touches)
	{
		if (touch && this->touchingSprite(touch))
		{
			touchOffset = maybay->getPosition() - touchTopoint(touch);
		}
	}
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{

	for (auto touch : touches)
	{
		if (touch && touchOffset.x && touchOffset.y)
		{
			this->maybay->setPosition( this->touchTopoint(touch) + this->touchOffset );
		}
	}


}

void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	for (auto touch : touches)
	{
		if (touch && touchOffset.x && touchOffset.y)
		{
			this->maybay->setPosition( this->touchTopoint(touch) + this->touchOffset );
		}
	}

}

