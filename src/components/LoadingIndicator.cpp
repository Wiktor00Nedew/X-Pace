//
// Created by Wiktor on 27.12.2022.
//

#include "LoadingIndicator.h"

LoadingIndicator::LoadingIndicator(QWidget *parent) {
    loadingAnimation = new QMovie("../assets/Spinner-1s-200px.gif");
    loadingAnimation->setScaledSize(QSize(60, 60));
    setMovie(loadingAnimation);
    show();
    loadingAnimation->start();

    // uncomment to make loading indication take place on layout after being hidden
    QSizePolicy sp_retain = sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    setSizePolicy(sp_retain);

    hide();
}

LoadingIndicator::~LoadingIndicator() {
    delete loadingAnimation;
}



