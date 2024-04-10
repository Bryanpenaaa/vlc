/*
 * ForgedInitSegment.hpp
 *****************************************************************************
 * Copyright (C) 2015 - VideoLAN Authors
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#ifndef FORGEDINITSEGMENT_HPP
#define FORGEDINITSEGMENT_HPP

#include "../../adaptive/playlist/Segment.h"
<<<<<<< master
#include "CodecParameters.hpp"
=======
>>>>>>> origin/3.0.x

#include <vlc_es.h>
#include <vlc_codecs.h>

namespace smooth
{
    namespace playlist
    {
        using namespace adaptive;
        using namespace adaptive::playlist;
        using namespace adaptive::http;

<<<<<<< master
        class CodecParameters;

=======
>>>>>>> origin/3.0.x
        class ForgedInitSegment : public InitSegment
        {
            public:
                ForgedInitSegment(ICanonicalUrl *parent, const std::string &,
                                  uint64_t, vlc_tick_t);
                virtual ~ForgedInitSegment();
                virtual SegmentChunk* toChunk(SharedResources *, size_t,
                                              BaseRepresentation *) override;
<<<<<<< master
=======
                void setWaveFormatEx(const std::string &);
                void setCodecPrivateData(const std::string &);
                void setChannels(uint16_t);
                void setPacketSize(uint16_t);
                void setSamplingRate(uint32_t);
                void setBitsPerSample(uint16_t);
>>>>>>> origin/3.0.x
                void setVideoSize(unsigned w, unsigned h);
                void setTrackID(unsigned);
                void setLanguage(const std::string &);

            private:
                block_t * buildMoovBox(const CodecParameters &);
                std::string type;
                std::string language;
                unsigned width, height;
                unsigned track_id;
                Timescale timescale;
        };
    }
}

#endif // FORGEDINITSEGMENT_HPP
