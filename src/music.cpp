#include <constants.h>
#include <Adafruit_CircuitPlayground.h>


double ratio = pow(2.0, 1.0/12.0);
float getFrequencyFromNote(String note)
{
    int index;
    for (int i = 0; i < 13; ++i)
    {
        if (note == MUSIC_NOTES[i])
        {
            index = i;
            break;
        }
    }

    return 220 * pow(ratio, index);
}


int playSongIndex = 0;
const int playSongNumNotes = 8;
const String playSongNotes[playSongNumNotes] = {"C", "C", "C", "D#", "G", "G", "G", "A#"};
void playSong()
{
    String note = playSongNotes[playSongIndex];
    float frequency = getFrequencyFromNote(note);
    CircuitPlayground.playTone(frequency, MUSIC_NOTE_DURATION);
    ++playSongIndex;
    playSongIndex %= playSongNumNotes;
}


const int playStartupTuneNumNotes = 5;
const String playStartupTuneNotes[playStartupTuneNumNotes] = {"E", "C", "G", "G", "A"};
void playStartupTune()
{
    for (int i = 0; i < playStartupTuneNumNotes; ++i)
    {
        int frequency = getFrequencyFromNote(playStartupTuneNotes[i]);
        int duration = (i == playStartupTuneNumNotes - 1) ? MUSIC_NOTE_DURATION * 2 : MUSIC_NOTE_DURATION;
        CircuitPlayground.playTone(frequency, duration);
    }
}