﻿#include "TitleState.h"
#include "cocos-ext.h"
#include "Utility/Audio/ADX2Player.h"

USING_NS_CC;
using namespace cocos2d::extension;

TitleState* TitleState::create(Layer* layer){

	auto obj = new TitleState();

	if (obj && obj->init(layer)){
		obj->retain();
		obj->autorelease();
		return obj;
	}

	CC_SAFE_DELETE(obj);
	return nullptr;
}

bool TitleState::init(Layer* layer){
	mSceneState = FADEIN;
	mUpdateState = UPDATESTART;
	parentLayer = layer;
	mTestTouch = false;
    
    mADX2Player = ADX2Player::create( "Sound/ADX2/WorkUnit_0/Mode.acb" );
    mADX2Player->retain();

	auto debugLabel = Label::createWithTTF("TitleScreen", "Font/MarkerFelt.ttf", 64);
	debugLabel->setName("ラベル");
    debugLabel->setColor(Color3B::WHITE);
	debugLabel->setPosition(Vec2(100, 100));
	parentLayer->addChild(debugLabel);
    
    mSlide->slideBarCreate("p1",
                           parentLayer,
                           "Texture/GamePlay/slider/sliderTrack.png",
                           "Texture/GamePlay/slider/sliderTrack.png",
                           "Texture/GamePlay/slider/sliderThumb.png",
                           "Texture/GamePlay/slider/switch-thumb.png",
                           Vec2(300,300));
    
    mBG->BackGraundCreate(parentLayer);
    
	return true;
}

void TitleState::update(float at){
	
    (this->*updateFunc[mSceneState])(at);
    
 }

void TitleState::fadeIn(float at){
	if (mTestTouch){
		mTestTouch = false;
		mSceneState = MAIN;
	}
	auto obj = (Label*)parentLayer->getChildByName("ラベル");

	obj->setString("fadeIN");
    
    CCLOG("%f",mSlide->getValue("p1", parentLayer));
}

void TitleState::sceneMain(float at){
	(this->*mainFunc[mUpdateState])(at);
}

void TitleState::fadeOut(float at){
	if (mTestTouch){
		mTestTouch = false;
		mSceneState = FADEIN;
	}
	auto obj = (Label*)parentLayer->getChildByName("ラベル");

	obj->setString("fadeOut");
    
    
}

void TitleState::mainStart(float at){
	mUpdateState = UPDATELOOP;
}

void TitleState::mainLoop(float at){
	if (mTestTouch){
		mTestTouch = false;
		mUpdateState = UPDATEEND;
	}
	auto obj = (Label*)parentLayer->getChildByName("ラベル");

	obj->setString("Loop");
}

void TitleState::mainEnd(float at){
	mUpdateState =UPDATESTART;
	mSceneState = FADEOUT;
}

bool TitleState::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	mTestTouch = true;
    
    mADX2Player->play( 0 );

	return true;
}


void TitleState::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){

}
