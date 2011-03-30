#include "vibratoevent.h"

#include <rtmidiwrapper.h>
#include <QSettings>

VibratoEvent::VibratoEvent(uint8_t channel, double startTime, uint32_t positionIndex,
                           EventType eventType, VibratoType vibratoType) :
    MidiEvent(channel, startTime, 0, positionIndex),
    eventType(eventType),
    vibratoType(vibratoType)
{
}

void VibratoEvent::performEvent(RtMidiWrapper& sequencer)
{
    if (eventType == VIBRATO_ON)
    {
        QSettings settings;
        uint8_t vibratoWidth = 0;

        if (vibratoType == NORMAL_VIBRATO)
        {
            vibratoWidth = settings.value("midi/vibrato", 85).toUInt();
        }
        else if (vibratoType == WIDE_VIBRATO)
        {
            vibratoWidth = settings.value("midi/wide_vibrato", 127).toUInt();
        }

        sequencer.setVibrato(channel, vibratoWidth);
    }
    else // VIBRATO_OFF
    {
        sequencer.setVibrato(channel, 0);
    }

}