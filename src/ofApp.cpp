#include "ofApp.h"
#include <math.h>
using namespace std;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    cam.setOrientation(ofPoint(-20,0,0));
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    leap.open();
    
    
    mode = 0;
    
    change = false;
    
    
    cam.setOrientation(ofPoint(-20,0,0));
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    leap.open();
    
    
    //    心拍数的演出
    sound.loadSound("pikumin.mp3");
    sound.setLoop(true);
    sound.setVolume(0.5);
    
    sound.play();
    
    
    //    ofSetFrameRate(100);
    //    elapsedTime=0;
    //
    //    int bufferSize =256;
    //    left.assign(bufferSize, 0.0);
    //    soundstream.setup(this, 0, 2, 44100, bufferSize,4);
    //
    //画像など
    
    manbo.loadImage("manboo.png");
    end.loadImage("end.png");
    same.loadImage("same.png");
    neko.loadImage("neko.png");
    mode  = 0;
    
    ofSetFrameRate(100);
    
    a =0;
    b =0;
    
    aa=5;
    bb=5;
    
    n =0;
    nn= 10;
    
    
    
   
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    simpleHands = leap.getSimpleHands();
    if (leap.isFrameNew() && simpleHands.size() ) {
        fingerPos.clear();
        
        handPos.clear();
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2
                         , ofGetHeight()/2);
        leap.setMappingZ(-150,150,-200,200);
        
        fingerType fingerTypes[] = {THUMB, INDEX,MIDDLE,RING,PINKY};
        
        for (int i = 0; i < simpleHands.size(); i++) {
            
            handPos.push_back(simpleHands[i].handPos);
            
            for (int f = 0; f<5 ; f++ ) {
                
                
                
                ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp;
                fingerPos.push_back(mcp);
                
                ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip;
                fingerPos.push_back(pip);
                
                ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip;
                fingerPos.push_back(dip);
                
                ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip;
                fingerPos.push_back(tip);
                
            }
            imgX = fingerPos.at(7).x;
            imgY = fingerPos.at(7).y;
        }
        
    }
    leap.markFrameAsOld();
    
//        if(imgX > 1024  || imgX < 0){
//            mode=1;
//        }else if(imgY>768 || imgY<0){
//            mode=1;
//        }
    
    
    a = a +aa;
    
    b = b + bb;
    
    n = n+nn;
    
    if(a<-500 || a>500){
        aa= -aa;
        
    }
    
    if(b<-350 || b>350){
        bb = -bb;
        
    }
    
    if(n<0 || n>ofGetWidth()){
        nn= -nn;
        
    }
    
    
    
    
    volume = ofSoundGetSpectrum(GetPrecision);
    
    //    elapsedTime++;
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
     cam.begin();
    
    
    for (int i = 0; i <simpleHands.size(); i++) {
        for (int f =0; f<5; f++) {
            
            
            if(mode == 0){
                for (int i = 0; i <simpleHands.size(); i++) {
                    for (int f =0; f<5; f++) {
                        
                        if(((fingerPos.at(7).x >-130)&&(fingerPos.at(7).x <-110)) && ((fingerPos.at(7).y>-70)&&(fingerPos.at(7).y>-50))){
                            
                            
                            manbo.draw(ofPoint( fingerPos.at(7)) , manbo.getWidth()/2, manbo.getHeight()/2);
                            ofSetColor(30,60,255);
                            
                           
                            //                   はじめに画像の中心にfinger7がきたらスタートにしたい
                            cout << "finger6:"<<fingerPos.at(7).x<<endl;
                            change =true;
                            
                        }
                        cout << "getwidth :"<<ofGetWidth()/2-100<<endl;
                        cout << "finger7-x:"<<fingerPos.at(7).x<<endl;
                        cout << "finger7-y:"<<fingerPos.at(7).y<<endl;
                        if (change == true) {
                            
                            
                            manbo.draw(ofPoint( fingerPos.at(7) ) , manbo.getWidth()/2, manbo.getHeight()/2);
                            
                            ofSetCircleResolution(255);
                            same.draw(a,b , same.getWidth()*1.5, same.getHeight()*1.5);
                            
                                ofSetCircleResolution(255);
                            neko.draw(n, a, neko.getWidth()*2, neko.getHeight()*2);
                            rectangle1.set(a,b , same.getWidth()*1.5, same.getHeight()*1.5);//座標、幅、高さをセット
                            rectangle2.set(n,a , neko.getWidth()*2, neko.getHeight()*2);
                            if(imgX > 500  || imgX < -500){
                                mode=1;
                            }else if(imgY>350 || imgY<-350){
                                mode=1;
                            }

                            

                        }
                        //                        else{
                        //                            manbo.draw(0,0,manbo.getWidth(), manbo.getHeight());
                        //                        }
                        
                        ofSetColor(0, 255, 0);
                        ofDrawSphere(handPos.at(i), 20);
                        
                        
                        ofSetColor(255);
                        ofDrawSphere(fingerPos.at(20*i+4*f+0),10);
                        //                        cout << " 中心から０ : " << fingerPos.at(20*i+4*f+0) << endl;
                        
                        
                        ofSetColor(200);
                        ofDrawSphere(fingerPos.at(20*i+4*f+1),10);
                        //                        cout << " 中心から１: " << fingerPos.at(20*i+4*f+1) << endl;
                        
                        
                        ofSetColor(155);
                        ofDrawSphere(fingerPos.at(20*i+4*f+2),10);
                        //                        cout << " 中心から２ : " << fingerPos.at(20*i+4*f+2) << endl;
                        
                        
                        ofSetColor(100);
                        ofDrawSphere(fingerPos.at(20*i+4*f+3),10);
                        
                        ofLine(fingerPos.at(20*i+4*f+0), fingerPos.at(20*i+4*f+1));
                        ofLine(fingerPos.at(20*i+4*f+1), fingerPos.at(20*i+4*f+2));
                        ofLine(fingerPos.at(20*i+4*f+2), fingerPos.at(20*i+4*f+3));
                    }
                }
                //                cout << "finger7 :"<<fingerPos.at(7).x<<endl;
                //                cout << "wide : :"<<ofGetHeight()/2<<endl;
                
            }
            if (mode == 1){
                end.draw(0,-300,ofGetWidth()/2, ofGetHeight()/2);
                
            }
            if (rectangle1.inside(fingerPos.at(7).x, fingerPos.at(7).y)) {//もし、manboの画像がrectangleの中だったら
                cout << "画像の中"<< endl;
                mode = 1;
            }
            if (rectangle2.inside(fingerPos.at(7).x, fingerPos.at(7).y)) {//もし、マウスがrectangleの中だったら
                cout << "画像の中"<< endl;
                mode = 1;
            }
            
            
        }
    }
    cam.end();
    
    //    same.draw(rectangle);
    //
    //    // ----------音の波形を描画-----------
    //    ofSetColor(245, 58, 135);//波形の色を指定
    //    ofSetLineWidth(3);//線の幅を指定
    //    slide++;//波形をずらしていく変数をインクリメント if(slide==130)slide=0;//130ずれたらリセット
    //    ofBeginShape();//点を結んだ集合を以下で描画
    //    for (unsigned int i = 0; i < left.size(); i++){//左チャンネルの配列が終わるまで描画
    //        //第一引数はx座標,第二引数はy座標(leftの配列の値を表現)
    //        ofVertex(i*10, 500 -left[i+slide]*3000.0f);
    //    }
    //    ofEndShape(false);//点の集合の終わり
    
}

void ofApp::exit(){
    
    
    
    
}
///---------------------------以下音の入力イベント----------------------------
//void ofApp::audioIn(float * input, int bufferSize, int nChannels){
//    if(elapsedTime%8==0){
//        for(int i = 0; i< bufferSize; i++){
//            left[i]   = input[i*2]*0.5;
//        }
//    }
//
//
//
//}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'a'){
        aa = aa+20;
    }
    
    if(key == 'b'){
        bb++;
    }
    
    if(key == 'n'){
        nn = nn+40;
    }
    
   
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
