#ifndef GLIMAC_SOUND
#define GLIMAC_SOUND

#pragma once
#include <SDL.h>
#include <string>
#include <SDL_mixer.h>

namespace glimac {

	///enumaration of sound used
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
			///constructor sound
            Sound();
			///destructor sound
			~Sound() = default;
			///build sound
			int build();
			///play sound
			void play(Sounds s);
			///load sounds
			int loadSounds();
			///set music
			void setEnable(bool isEnabled);
			///get if music enabled
			bool getEnable() const;
			///clean music
			void clean();
	};
}

#endif