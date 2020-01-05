#ifndef GLIMAC_SOUND
#define GLIMAC_SOUND

#pragma once
#include <SDL.h>
#include <string>
#include <SDL_mixer.h>

namespace glimac {
    enum Sounds {BUILD,DESTROY,BACKGROUND}; //  0 1 2
	class Sound {
		private:
			bool isEnabled = true;
			int nbSoundsEffects = 2;
			Mix_Music *backgroundMusic = NULL;
            Mix_Chunk *soundEffects[2];

		  std::string soundEffects_path[2] = {
		                   "./assets/sounds/put_cube.wav",
		                   "./assets/sounds/destroy_cube.wav"
		   };

		public:
			int build();
            Sound();
			~Sound() = default;
			void play(Sounds s);
			int  loadSounds();
			void setEnable(bool isEnabled);
			bool getEnable() const;
			void clean();
	};
}

#endif