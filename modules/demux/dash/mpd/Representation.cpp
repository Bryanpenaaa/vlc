/*
 * Representation.cpp
 *****************************************************************************
 * Copyright (C) 2010 - 2011 Klagenfurt University
 *
 * Created on: Aug 10, 2010
 * Authors: Christopher Mueller <christopher.mueller@itec.uni-klu.ac.at>
 *          Christian Timmerer  <christian.timmerer@itec.uni-klu.ac.at>
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
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <cstdlib>

#include "Representation.h"
#include "AdaptationSet.h"
#include "MPD.h"
<<<<<<< master
=======
#include "TrickModeType.h"
>>>>>>> origin/3.0.x
#include "../../adaptive/playlist/SegmentTemplate.h"
#include "../../adaptive/playlist/SegmentTimeline.h"
#include "TemplatedUri.hpp"

using namespace dash::mpd;

Representation::Representation  ( AdaptationSet *set ) :
                BaseRepresentation( set )
{
}

Representation::~Representation ()
{
}

StreamFormat Representation::getStreamFormat() const
{
    return StreamFormat(getMimeType());
<<<<<<< master
=======
}

TrickModeType*      Representation::getTrickModeType        () const
{
    return this->trickModeType;
}

void                Representation::setTrickMode        (TrickModeType *trickModeType)
{
    this->trickModeType = trickModeType;
}

int Representation::getQualityRanking() const
{
    return this->qualityRanking;
}

void Representation::setQualityRanking( int qualityRanking )
{
    if ( qualityRanking > 0 )
        this->qualityRanking = qualityRanking;
}

const std::list<const Representation*>&     Representation::getDependencies() const
{
    return this->dependencies;
}

void Representation::addDependency(const Representation *dep)
{
    if ( dep != NULL )
        this->dependencies.push_back( dep );
>>>>>>> origin/3.0.x
}

std::string Representation::contextualize(size_t number, const std::string &component,
                                          const SegmentTemplate *templ) const
{
<<<<<<< master
    std::string str(component);
    if(!templ)
        return str;

=======
    if(!templ)
        return component;

    std::string str(component);

>>>>>>> origin/3.0.x
    std::string::size_type pos = 0;
    while(pos < str.length())
    {
        TemplatedUri::Token token;
        if(str[pos] == '$' && TemplatedUri::IsDASHToken(str, pos, token))
        {
            TemplatedUri::TokenReplacement replparam;
            switch(token.type)
            {
                case TemplatedUri::Token::TOKEN_TIME:
                    replparam.value = templ ? getScaledTimeBySegmentNumber(number, templ) : 0;
                    break;
                case TemplatedUri::Token::TOKEN_BANDWIDTH:
                    replparam.value = getBandwidth();
                    break;
                case TemplatedUri::Token::TOKEN_NUMBER:
                    replparam.value = number;
                    break;
                case TemplatedUri::Token::TOKEN_REPRESENTATION:
                    replparam.str = id.str();
                    break;
                case TemplatedUri::Token::TOKEN_ESCAPE:
                    break;

                default:
                    pos += token.fulllength;
                    continue;
            }
            /* Replace with newvalue */
            std::string::size_type newlen = TemplatedUri::ReplaceDASHToken(
                                                    str, pos, token, replparam);
            if(newlen == std::string::npos)
                newlen = token.fulllength;
            pos += newlen;
        }
        else pos++;
    }

    return str;
}

stime_t Representation::getScaledTimeBySegmentNumber(uint64_t index, const SegmentTemplate *templ) const
{
<<<<<<< master
    stime_t time = 0;
=======
    vlc_tick_t time = 0;
>>>>>>> origin/3.0.x
    const SegmentTimeline *tl = templ->inheritSegmentTimeline();
    if(tl)
    {
        time = tl->getScaledPlaybackTimeByElementNumber(index);
    }
    else if(templ->inheritDuration())
    {
        time = templ->inheritDuration() * index;
    }
    return time;
}

