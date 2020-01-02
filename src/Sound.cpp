#include <iostream>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include "./Sound.hpp"
#include <SDL.h>
#include <SDL_mixer.h>

namespace glimac {

	int Sound::build() {
		for(int i = 0; i < nbSoundsEffects; i++)
			soundEffects[i] = NULL;

        if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
            std::cout << "SOUND ERROR" << std::endl;
            return -1;
        }
        loadSounds();
            return 0;
	}

    Sound::Sound() {
        build();
    }

	void Sound::play(Sounds s){
		if (!isEnabled){return;}
		if(s == 2){Mix_PlayMusic( backgroundMusic, -1 );}
		else {
			Mix_PlayChannel( -1, soundEffects[s], 0 );
			Mix_Volume(-1,50);
		}
	}

	void Sound::setEnable(bool enabled){

		if(enabled == false && this->isEnabled == true){
			 Mix_HaltMusic();
		}else if (enabled == true && this->isEnabled == false){
			Mix_PlayMusic( backgroundMusic, -1 );
		}
		this->isEnabled = enabled;
	}

	bool Sound::getEnable()const{
		return isEnabled;
	}

	int Sound::loadSounds(){
		backgroundMusic = Mix_LoadMUS("./assets/sounds/main_music.wav");
		if( backgroundMusic == NULL ) {
            std::cout << "./assets/sounds/main_music.wav not found" << std::endl;
            return 0;
        }
        int errorCode = 0;
            for(int i = 0; i < nbSoundsEffects; i++){
                soundEffects[i] = Mix_LoadWAV(soundEffects_path[i].c_str());
                if( soundEffects[i] == NULL ) {
                std::cout << soundEffects_path[i] << "not found" << std::endl;
                errorCode = -1;
            }
            }
            return errorCode;
	}

	void Sound::clean(){

		Mix_HaltMusic();
		 //Free the sound effects
		for(int i = 0; i < nbSoundsEffects; i++){
			if(soundEffects[i]) {
				Mix_FreeChunk(soundEffects[i]);
			}
		}

		if(backgroundMusic) {
			//Free the music
			Mix_FreeMusic( backgroundMusic );
		}
		 
		//Quit SDL_mixer
		 Mix_CloseAudio();
	}

}