#ifndef _PROGRAM_SOUND_H_
#define _PROGRAM_SOUND_H_

#define SOUND_INVALID_ID 0

// SoundPlay (..., type, ...)
#define SOUND_WAV_3D     1
#define SOUND_MP3_STEREO 2
#define SOUND_MP3_3D     3
#define SOUND_WAV_STEREO 4

// SoundPlay (..., volume_type, ...)
#define VOLUME_FX        1
#define VOLUME_MUSIC     2
#define VOLUME_SPEECH    3

//SoundSet3DParam(..., type, ...)
#define SOUND_PARAM_MAX_DISTANCE 1
#define SOUND_PARAM_MIN_DISTANCE 2
#define SOUND_PARAM_POSITION     3

//#20180815-03
#define RVB_I_MUSIC 0
#define RVB_I_EFFECTS 1

#define RVB_ENVIRON_SEA 0
#define RVB_ENVIRON_LOC 1
#define RVB_ENVIRON_WM 2

#define RVB_OFF 0
#define RVB_GENERIC 1
#define RVB_ROOM 2
#define RVB_LIVINGROOM 3
#define RVB_STONEROOM 4
#define RVB_AUDITORIUM 5
#define RVB_CONCERTHALL 6
#define RVB_CAVE 7
#define RVB_ARENA 8
#define RVB_HANGAR 9
#define RVB_CARPETTEDHALLWAY 10
#define RVB_HALLWAY 11
#define RVB_STONECORRIDOR 12
#define RVB_ALLEY 13
#define RVB_FOREST 14
#define RVB_CITY 15
#define RVB_MOUNTAINS 16
#define RVB_QUARRY 17
#define RVB_PLAIN 18
#define RVB_PARKINGLOT 19
#define RVB_SEWERPIPE 20
#define RVB_UNDERWATER 21

#endif
