#ifndef YINXIAO_H
#define YINXIAO_H
#include<QMediaPlayer>

/*enum voiceType{
    settower,
    monsterdie,
    removetower,
    gamewin,
    uplevel,
    shoot,
    buttonclick
};

class Yinxiao{
public:
    Yinxiao();
    void playvoice(voiceType voicetype);

};
*/
inline void settowervoice(){
    static QMediaPlayer     settower; //= new QMediaPlayer;
    settower.setMedia(QUrl("qrc:/sound/settower.wav"));
    settower.setVolume(30);
    settower.play();
}

inline void monsterdievoice(){
    static QMediaPlayer     monsterdie;// = new QMediaPlayer;
    monsterdie.setMedia(QUrl("qrc:/sound/monster1_die.wav"));
    monsterdie.setVolume(30);
    monsterdie.play();
}

inline void removetowervoice(){
    static QMediaPlayer     removetower;//= new QMediaPlayer;
    removetower.setMedia(QUrl("qrc:/sound/remove_tower.wav"));
    removetower.setVolume(30);
    removetower.play();
}

inline void gamewinvoice(){
    static QMediaPlayer     gamewin;//= new QMediaPlayer;
    gamewin.setMedia(QUrl("qrc:/sound/easywin.wav"));
    gamewin.setVolume(30);
    gamewin.play();
}



inline void uplevelvoice(){
    static QMediaPlayer      uplevel;//= new QMediaPlayer;
    uplevel.setMedia(QUrl("qrc:/sound/uplevel.wav"));
    uplevel.setVolume(25);
    uplevel.play();
}

inline void shootvoice(){
    static QMediaPlayer      shoot;//= new QMediaPlayer;
    shoot.setMedia(QUrl("qrc:/sound/shoot.wav"));
    shoot.setVolume(30);
    shoot.play();
}

inline void buttonvoice(){
    static QMediaPlayer pressbutton;//= new QMediaPlayer;
    pressbutton.setMedia(QUrl("qrc:/sound/pressbutton.wav"));
    pressbutton.setVolume(30);
    pressbutton.play();
}











#endif // YINXIAO_H
