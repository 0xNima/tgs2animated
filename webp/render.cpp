/*
* Created by uriel on 17/03/21.
* This is licensed under GNU GPL v. 2 or later.
* You should have received a copy of the license in this archive (see LICENSE).
*
* Copyright (c) Uriel Castro, 2021-2021.
*/

#include "render.h"

bool render(const std::string &lottieData, const std::string &outputPath, bool is_tray) {
    std::unique_ptr<rlottie::Animation> animation = rlottie::Animation::loadFromData(lottieData, std::to_string(1), "", false);
    if(!animation) {
        std::cout<<"Could no create animation, is your tgs file valid?"<<std::endl;
        return false;
    }
    auto buffer = std::unique_ptr<uint32_t[]>(new uint32_t[DataHolder::mWidth * DataHolder::mHeight]);
    
    size_t frameCount = animation->totalFrame();
    size_t frameDuration = (animation->duration ()*1000/frameCount);
    

    int index = -1;
    int primes[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53};
    
    while (1) {
        int count = 0;
        for (int i = 0; i < frameCount; i++) {
            for (int j=0; j< index+1; j++) {
                if(i%primes[j] == 0) {
                    count ++;
                }
            }
        } 
        frameDuration = (animation->duration()*1000/frameCount) * (frameCount/(frameCount - count));
        WebpBuilder builder(outputPath, frameDuration);
        for (int i = 0; i < frameCount; i++) {
            bool __is = false;
            for (int j=0; j< index+1; j++) {
                if(i%primes[j] == 0) {
                    __is = true;
                    break;
                }
            }
            if(__is) {
                continue;
            }
            rlottie::Surface surface(buffer.get(), DataHolder::mWidth, DataHolder::mHeight, DataHolder::mWidth*4);
            animation->renderSync(i, surface);
            builder.addFrame(surface);
            
            if(is_tray){
                break;
            }
        }
        if (builder.finilize()) {
            return true;
        };
        index++;
        if (index >= 15) {
            return false;
        }
    }
}
