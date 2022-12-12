#include <constants.h>


double ratio = pow(2.0, 1.0/12.0);
float getFrequencyFromNote(String note, int octave)
{
    for (int i = 0; i < 13; ++i)
    {
        if (note == MUSIC_NOTES[i])
            return A0_NOTE * pow(ratio, i) * (octave + 1);
    }
}