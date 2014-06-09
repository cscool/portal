#include "sound.h"

const unsigned int SCNT = 12;
int current_track = 0;

FMOD_SYSTEM *sys;
FMOD_SOUND **sounds;
FMOD_CHANNEL *chan = 0;
FMOD_RESULT result;

void ERRCHECK(FMOD_RESULT res)
{
		  if (res != FMOD_OK)
		  {
					 Log("FMOD error! (%d) %s\n", res, FMOD_ErrorString(res));
		  }
}

void initMusic(void)
{
		  unsigned int      version;
		  result = FMOD_System_Create(&sys);
		  ERRCHECK(result);

		  result = FMOD_System_GetVersion(sys, &version);
		  ERRCHECK(result);

		  if (version < FMOD_VERSION)
		  {
					 return;
		  }

		  result = FMOD_System_Init(sys, 1, FMOD_INIT_NORMAL, NULL);
		  ERRCHECK(result);

		  sounds = (FMOD_SOUND **)malloc(SCNT*sizeof(FMOD_SOUND *));
		  result = FMOD_System_CreateSound(sys, "media/scienceisfun.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[0]));
		  ERRCHECK(result);
		  //		  Log("sound 1 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/concentrationenhancingmenuinitialiser.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[1]));
		  ERRCHECK(result);
		  //		  Log("sound 2 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/999999.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[2]));
		  ERRCHECK(result);
		  //		  Log("sound 3 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/thecourtesycall.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[3]));
		  ERRCHECK(result);
		  //		  Log("sound 4 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/technicaldifficulties.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[4]));
		  ERRCHECK(result);
		  //		  Log("sound 5 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/overgrowth.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[5]));
		  ERRCHECK(result);
		  //		  Log("sound 6 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/ghostofrattman.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[5]));
		  ERRCHECK(result);
		  //		  Log("sound 7 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/hauntedpanels.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[7]));
		  ERRCHECK(result);
		  //		  Log("sound 8 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/thefuturestartswithyou.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[8]));
		  ERRCHECK(result);
		  //		  Log("sound 9 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/theresheis.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[9]));
		  ERRCHECK(result);
		  //		  Log("sound 10 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/youknowher.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[10]));
		  ERRCHECK(result);
		  //		  Log("sound 11 of 12 loaded\n");
		  result = FMOD_System_CreateSound(sys, "media/thefriendlyfaithplate.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(sounds[11]));
		  ERRCHECK(result);
		  //		  Log("sound 12 of 12 loaded\n");

		  current_track = (rand() % SCNT);
		  playMusic(current_track);
}

void musicHandler (void)
{
		  int playing = 0;
		  unsigned int ms = 0;
		  unsigned int lenms = 0;

		  if (chan)
		  {

					 result = FMOD_Channel_IsPlaying(chan, &playing);
					 if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
					 {
								ERRCHECK(result);
					 }

					 if (playing)
					 {
								return;
					 }
					 FMOD_SOUND *currentsound = 0;

					 result = FMOD_Channel_GetPosition(chan, &ms, FMOD_TIMEUNIT_MS);
					 if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
					 {
								ERRCHECK(result);
					 }

					 FMOD_Channel_GetCurrentSound(chan, &currentsound);
					 if (currentsound)
					 {
								result = FMOD_Sound_GetLength(currentsound, &lenms, FMOD_TIMEUNIT_MS);
								if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
								{
										  ERRCHECK(result);
								}
					 }
		  }
		  current_track = (current_track + 1) % SCNT;
		  playMusic(current_track);
}

void playMusic(const int & n)
{
		  result = FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sounds[n], 0, &chan);
		  ERRCHECK(result);

		  FMOD_System_Update(sys);

		  return;
}

void stopMusic (void)
{
		  if (sounds)
		  {
					 Log("about to free sounds\n");
					 free(sounds);
		  }
		  if (sys)
		  {
					 Log("releasing fmod system\n");
					 result = FMOD_System_Close(sys);
					 ERRCHECK(result);
					 result = FMOD_System_Release(sys);
					 ERRCHECK(result);
		  }

		  return;
}
