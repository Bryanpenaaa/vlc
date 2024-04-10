/*****************************************************************************
 * var.c: object variables for input thread
 *****************************************************************************
 * Copyright (C) 2004-2007 VLC authors and VideoLAN
 *
 * Authors: Laurent Aimar <fenrir@via.ecp.fr>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
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

/*****************************************************************************
 * Preamble
 *****************************************************************************/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <vlc_common.h>
#include <assert.h>

#include "input_internal.h"

/*****************************************************************************
<<<<<<< HEAD
=======
 * Callbacks
 *****************************************************************************/
static int StateCallback   ( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int RateCallback    ( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int PositionCallback( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int TimeCallback    ( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int TimeOffsetCallback( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int ProgramCallback ( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int TitleCallback   ( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int SeekpointCallback( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int NavigationCallback( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int EsVideoCallback ( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int EsAudioCallback ( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );
static int EsSpuCallback ( vlc_object_t *p_this, char const *psz_cmd,
                           vlc_value_t oldval, vlc_value_t newval, void * );
static int EsDelayCallback ( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );

static int BookmarkCallback( vlc_object_t *p_this, char const *psz_cmd,
                             vlc_value_t oldval, vlc_value_t newval, void * );

static int RecordCallback( vlc_object_t *p_this, char const *psz_cmd,
                           vlc_value_t oldval, vlc_value_t newval,
                           void *p_data );
static int FrameNextCallback( vlc_object_t *p_this, char const *psz_cmd,
                              vlc_value_t oldval, vlc_value_t newval,
                              void *p_data );

typedef struct
{
    const char *psz_name;
    vlc_callback_t callback;
} vlc_input_callback_t;

static void InputAddCallbacks( input_thread_t *, const vlc_input_callback_t * );
static void InputDelCallbacks( input_thread_t *, const vlc_input_callback_t * );

#ifdef CALLBACK /* For windows */
# undef CALLBACK /* We don't care of this one here */
#endif
/* List all callbacks added by input */
#define CALLBACK(name,cb) { name, cb }
static const vlc_input_callback_t p_input_callbacks[] =
{
    CALLBACK( "state", StateCallback ),
    CALLBACK( "rate", RateCallback ),
    CALLBACK( "position", PositionCallback ),
    CALLBACK( "time", TimeCallback ),
    CALLBACK( "time-offset", TimeOffsetCallback ),
    CALLBACK( "bookmark", BookmarkCallback ),
    CALLBACK( "program", ProgramCallback ),
    CALLBACK( "title", TitleCallback ),
    CALLBACK( "chapter", SeekpointCallback ),
    CALLBACK( "audio-delay", EsDelayCallback ),
    CALLBACK( "spu-delay", EsDelayCallback ),
    CALLBACK( "video-es", EsVideoCallback ),
    CALLBACK( "audio-es", EsAudioCallback ),
    CALLBACK( "spu-es", EsSpuCallback ),
    CALLBACK( "record", RecordCallback ),
    CALLBACK( "frame-next", FrameNextCallback ),

    CALLBACK( NULL, NULL )
};
static const vlc_input_callback_t p_input_title_navigation_callbacks[] =
{
    CALLBACK( "next-title", TitleCallback ),
    CALLBACK( "prev-title", TitleCallback ),
    CALLBACK( "menu-popup", TitleCallback ),
    CALLBACK( "menu-title", TitleCallback ),

    CALLBACK( NULL, NULL )
};
#undef CALLBACK

/*****************************************************************************
 * input_ControlVarInit:
 *  Create all control object variables with their callbacks
 *****************************************************************************/
void input_ControlVarInit ( input_thread_t *p_input )
{
    vlc_value_t val, text;

    /* State */
    var_Create( p_input, "state", VLC_VAR_INTEGER );
    val.i_int = input_priv(p_input)->i_state;
    var_Change( p_input, "state", VLC_VAR_SETVALUE, &val, NULL );

    /* Rate */
    var_Create( p_input, "rate", VLC_VAR_FLOAT | VLC_VAR_DOINHERIT );

    var_Create( p_input, "frame-next", VLC_VAR_VOID );

    /* Position */
    var_Create( p_input, "position",  VLC_VAR_FLOAT );

    /* Time */
    var_Create( p_input, "time", VLC_VAR_INTEGER );
    var_Create( p_input, "time-offset", VLC_VAR_INTEGER );    /* relative */

    /* Bookmark */
    var_Create( p_input, "bookmark", VLC_VAR_INTEGER | VLC_VAR_ISCOMMAND );
    val.psz_string = _("Bookmark");
    var_Change( p_input, "bookmark", VLC_VAR_SETTEXT, &val, NULL );

    /* Program */
    var_Create( p_input, "program", VLC_VAR_INTEGER | VLC_VAR_DOINHERIT );
    var_Get( p_input, "program", &val );
    if( val.i_int <= 0 )
        var_Change( p_input, "program", VLC_VAR_DELCHOICE, &val, NULL );
    text.psz_string = _("Program");
    var_Change( p_input, "program", VLC_VAR_SETTEXT, &text, NULL );

    /* Programs */
    var_Create( p_input, "programs", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
    text.psz_string = _("Programs");
    var_Change( p_input, "programs", VLC_VAR_SETTEXT, &text, NULL );

    /* Title */
    var_Create( p_input, "title", VLC_VAR_INTEGER );
    text.psz_string = _("Title");
    var_Change( p_input, "title", VLC_VAR_SETTEXT, &text, NULL );

    /* Chapter */
    var_Create( p_input, "chapter", VLC_VAR_INTEGER );
    text.psz_string = _("Chapter");
    var_Change( p_input, "chapter", VLC_VAR_SETTEXT, &text, NULL );

    /* Delay */
    var_Create( p_input, "audio-delay", VLC_VAR_INTEGER );
    var_SetInteger( p_input, "audio-delay",
                    1000 * var_GetInteger( p_input, "audio-desync" ) );
    var_Create( p_input, "spu-delay", VLC_VAR_INTEGER );

    val.i_int = -1;
    /* Video ES */
    var_Create( p_input, "video-es", VLC_VAR_INTEGER );
    var_Change( p_input, "video-es", VLC_VAR_SETVALUE, &val, NULL );
    text.psz_string = _("Video Track");
    var_Change( p_input, "video-es", VLC_VAR_SETTEXT, &text, NULL );

    /* Audio ES */
    var_Create( p_input, "audio-es", VLC_VAR_INTEGER );
    var_Change( p_input, "audio-es", VLC_VAR_SETVALUE, &val, NULL );
    text.psz_string = _("Audio Track");
    var_Change( p_input, "audio-es", VLC_VAR_SETTEXT, &text, NULL );

    /* Spu ES */
    var_Create( p_input, "spu-es", VLC_VAR_INTEGER );
    var_Change( p_input, "spu-es", VLC_VAR_SETVALUE, &val, NULL );
    text.psz_string = _("Subtitle Track");
    var_Change( p_input, "spu-es", VLC_VAR_SETTEXT, &text, NULL );

    var_Create( p_input, "spu-choice", VLC_VAR_INTEGER );
    var_SetInteger( p_input, "spu-choice", -1 );

    /* Special read only objects variables for intf */
    var_Create( p_input, "bookmarks", VLC_VAR_STRING | VLC_VAR_DOINHERIT );

    var_Create( p_input, "length", VLC_VAR_INTEGER );

    var_Create( p_input, "bit-rate", VLC_VAR_INTEGER );
    var_Create( p_input, "sample-rate", VLC_VAR_INTEGER );

    /* Special "intf-event" variable. */
    var_Create( p_input, "intf-event", VLC_VAR_INTEGER );

    /* Add all callbacks
     * XXX we put callback only in non preparsing mode. We need to create the variable
     * unless someone want to check all var_Get/var_Change return value ... */
    if( !input_priv(p_input)->b_preparsing )
        InputAddCallbacks( p_input, p_input_callbacks );
}

/*****************************************************************************
 * input_ControlVarStop:
 *****************************************************************************/
void input_ControlVarStop( input_thread_t *p_input )
{
    if( !input_priv(p_input)->b_preparsing )
        InputDelCallbacks( p_input, p_input_callbacks );

    if( input_priv(p_input)->i_title > 1 )
        InputDelCallbacks( p_input, p_input_title_navigation_callbacks );

    for( int i = 0; i < input_priv(p_input)->i_title; i++ )
    {
        char name[sizeof("title ") + 3 * sizeof (int)];

        sprintf( name, "title %2u", i );
        var_DelCallback( p_input, name, NavigationCallback, (void *)(intptr_t)i );
    }

    if( var_Type( p_input, "next-chapter" ) != 0 )
    {
        assert( var_Type( p_input, "prev-chapter" ) != 0 );
        var_Destroy( p_input, "next-chapter" );
        var_Destroy( p_input, "prev-chapter" );
    }
}

/*****************************************************************************
 * input_ControlVarNavigation:
 *  Create all remaining control object variables
 *****************************************************************************/
void input_ControlVarNavigation( input_thread_t *p_input )
{
    vlc_value_t text;

    /* Create more command variables */
    if( input_priv(p_input)->i_title > 1 )
    {
        if( var_Type( p_input, "next-title" ) == 0 ) {
            var_Create( p_input, "next-title", VLC_VAR_VOID );
            text.psz_string = _("Next title");
            var_Change( p_input, "next-title", VLC_VAR_SETTEXT, &text, NULL );
            var_AddCallback( p_input, "next-title", TitleCallback, NULL );
        }

        if( var_Type( p_input, "prev-title" ) == 0 ) {
            var_Create( p_input, "prev-title", VLC_VAR_VOID );
            text.psz_string = _("Previous title");
            var_Change( p_input, "prev-title", VLC_VAR_SETTEXT, &text, NULL );
            var_AddCallback( p_input, "prev-title", TitleCallback, NULL );
        }

        if( var_Type( p_input, "menu-title" ) == 0 ) {
            var_Create( p_input, "menu-title", VLC_VAR_VOID );
            text.psz_string = _("Menu title");
            var_Change( p_input, "menu-title", VLC_VAR_SETTEXT, &text, NULL );
            var_AddCallback( p_input, "menu-title", TitleCallback, NULL );
        }

        if( var_Type( p_input, "menu-popup" ) == 0 ) {
            var_Create( p_input, "menu-popup", VLC_VAR_VOID );
            text.psz_string = _("Menu popup");
            var_Change( p_input, "menu-popup", VLC_VAR_SETTEXT, &text, NULL );
            var_AddCallback( p_input, "menu-popup", TitleCallback, NULL );
        }
    }

    /* Create titles and chapters */
    var_Change( p_input, "title", VLC_VAR_CLEARCHOICES, NULL, NULL );

    for( int i = 0; i < input_priv(p_input)->i_title; i++ )
    {
        vlc_value_t val2, text2;
        char title[sizeof("title ") + 3 * sizeof (int)];

        /* Add Navigation entries */
        sprintf( title, "title %2u", i );
        var_Destroy( p_input, title );
        var_Create( p_input, title, VLC_VAR_INTEGER | VLC_VAR_ISCOMMAND );
        var_AddCallback( p_input, title,
                         NavigationCallback, (void *)(intptr_t)i );

        char psz_length[MSTRTIME_MAX_SIZE + sizeof(" []")];
        if( input_priv(p_input)->title[i]->i_length > 0 )
        {
            strcpy( psz_length, " [" );
            secstotimestr( &psz_length[2], input_priv(p_input)->title[i]->i_length / CLOCK_FREQ );
            strcat( psz_length, "]" );
        }
        else
            psz_length[0] = '\0';

        if( input_priv(p_input)->title[i]->psz_name == NULL ||
            *input_priv(p_input)->title[i]->psz_name == '\0' )
        {
            if( asprintf( &text.psz_string, _("Title %i%s"),
                          i + input_priv(p_input)->i_title_offset, psz_length ) == -1 )
                continue;
        }
        else
        {
            if( asprintf( &text.psz_string, "%s%s",
                          input_priv(p_input)->title[i]->psz_name, psz_length ) == -1 )
                continue;
        }

        /* Add title choice */
        val2.i_int = i;
        var_Change( p_input, "title", VLC_VAR_ADDCHOICE, &val2, &text );

        free( text.psz_string );

        for( int j = 0; j < input_priv(p_input)->title[i]->i_seekpoint; j++ )
        {
            val2.i_int = j;

            if( input_priv(p_input)->title[i]->seekpoint[j]->psz_name == NULL ||
                *input_priv(p_input)->title[i]->seekpoint[j]->psz_name == '\0' )
            {
                /* Default value */
                if( asprintf( &text2.psz_string, _("Chapter %i"),
                          j + input_priv(p_input)->i_seekpoint_offset ) == -1 )
                    continue;
            }
            else
            {
                text2.psz_string =
                    strdup( input_priv(p_input)->title[i]->seekpoint[j]->psz_name );
            }

            var_Change( p_input, title, VLC_VAR_ADDCHOICE, &val2, &text2 );
            free( text2.psz_string );
        }

    }
}

/*****************************************************************************
 * input_ControlVarTitle:
 *  Create all variables for a title
 *****************************************************************************/
void input_ControlVarTitle( input_thread_t *p_input, int i_title )
{
    const input_title_t *t = input_priv(p_input)->title[i_title];
    vlc_value_t text;
    int  i;

    /* Create/Destroy command variables */
    if( t->i_seekpoint <= 1 )
    {
        var_Destroy( p_input, "next-chapter" );
        var_Destroy( p_input, "prev-chapter" );
    }
    else if( var_Type( p_input, "next-chapter" ) == 0 )
    {
        var_Create( p_input, "next-chapter", VLC_VAR_VOID );
        text.psz_string = _("Next chapter");
        var_Change( p_input, "next-chapter", VLC_VAR_SETTEXT, &text, NULL );
        var_AddCallback( p_input, "next-chapter", SeekpointCallback, NULL );

        var_Create( p_input, "prev-chapter", VLC_VAR_VOID );
        text.psz_string = _("Previous chapter");
        var_Change( p_input, "prev-chapter", VLC_VAR_SETTEXT, &text, NULL );
        var_AddCallback( p_input, "prev-chapter", SeekpointCallback, NULL );
    }

    /* Build chapter list */
    var_Change( p_input, "chapter", VLC_VAR_CLEARCHOICES, NULL, NULL );
    for( i = 0; i <  t->i_seekpoint; i++ )
    {
        vlc_value_t val;
        val.i_int = i;

        if( t->seekpoint[i]->psz_name == NULL ||
            *t->seekpoint[i]->psz_name == '\0' )
        {
            /* Default value */
            if( asprintf( &text.psz_string, _("Chapter %i"),
                      i + input_priv(p_input)->i_seekpoint_offset ) == -1 )
                continue;
        }
        else
        {
            text.psz_string = strdup( t->seekpoint[i]->psz_name );
        }

        var_Change( p_input, "chapter", VLC_VAR_ADDCHOICE, &val, &text );
        free( text.psz_string );
    }
}

/*****************************************************************************
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
 * input_ConfigVarInit:
 *  Create all config object variables
 *****************************************************************************/
void input_ConfigVarInit ( input_thread_t *p_input )
{
    /* Create Object Variables for private use only */

    if( input_priv(p_input)->type != INPUT_TYPE_PREPARSING )
    {
        var_Create( p_input, "video", VLC_VAR_BOOL | VLC_VAR_DOINHERIT );
        var_Create( p_input, "audio", VLC_VAR_BOOL | VLC_VAR_DOINHERIT );
        var_Create( p_input, "spu", VLC_VAR_BOOL | VLC_VAR_DOINHERIT );

        var_Create( p_input, "video-track", VLC_VAR_INTEGER|VLC_VAR_DOINHERIT );
        var_Create( p_input, "audio-track", VLC_VAR_INTEGER|VLC_VAR_DOINHERIT );
        var_Create( p_input, "sub-track", VLC_VAR_INTEGER|VLC_VAR_DOINHERIT );

        var_Create( p_input, "audio-language",
                    VLC_VAR_STRING|VLC_VAR_DOINHERIT );
        var_Create( p_input, "sub-language",
                    VLC_VAR_STRING|VLC_VAR_DOINHERIT );
        var_Create( p_input, "menu-language",
                    VLC_VAR_STRING|VLC_VAR_DOINHERIT );

        var_Create( p_input, "video-track-id",
                    VLC_VAR_STRING|VLC_VAR_DOINHERIT );
        var_Create( p_input, "audio-track-id",
                    VLC_VAR_STRING|VLC_VAR_DOINHERIT );
        var_Create( p_input, "sub-track-id",
                    VLC_VAR_STRING|VLC_VAR_DOINHERIT );

        var_Create( p_input, "sub-file", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
        var_Create( p_input, "sub-autodetect-file", VLC_VAR_BOOL |
                    VLC_VAR_DOINHERIT );
        var_Create( p_input, "sub-autodetect-path", VLC_VAR_STRING |
                    VLC_VAR_DOINHERIT );
        var_Create( p_input, "sub-autodetect-fuzzy", VLC_VAR_INTEGER |
                    VLC_VAR_DOINHERIT );

        var_Create( p_input, "sout", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
        var_Create( p_input, "sout-all",   VLC_VAR_BOOL | VLC_VAR_DOINHERIT );
        var_Create( p_input, "sout-audio", VLC_VAR_BOOL | VLC_VAR_DOINHERIT );
        var_Create( p_input, "sout-video", VLC_VAR_BOOL | VLC_VAR_DOINHERIT );
        var_Create( p_input, "sout-spu", VLC_VAR_BOOL | VLC_VAR_DOINHERIT );
        var_Create( p_input, "sout-keep",  VLC_VAR_BOOL | VLC_VAR_DOINHERIT );

        var_Create( p_input, "input-repeat",
                    VLC_VAR_INTEGER|VLC_VAR_DOINHERIT );
        var_Create( p_input, "start-time", VLC_VAR_FLOAT|VLC_VAR_DOINHERIT );
        var_Create( p_input, "stop-time", VLC_VAR_FLOAT|VLC_VAR_DOINHERIT );
        var_Create( p_input, "run-time", VLC_VAR_FLOAT|VLC_VAR_DOINHERIT );
        var_Create( p_input, "input-fast-seek", VLC_VAR_BOOL|VLC_VAR_DOINHERIT );

        var_Create( p_input, "input-slave",
                    VLC_VAR_STRING | VLC_VAR_DOINHERIT );

        var_Create( p_input, "audio-desync",
                    VLC_VAR_INTEGER | VLC_VAR_DOINHERIT );
        var_Create( p_input, "cr-average",
                    VLC_VAR_INTEGER | VLC_VAR_DOINHERIT );
        var_Create( p_input, "clock-synchro",
                    VLC_VAR_INTEGER | VLC_VAR_DOINHERIT);

        var_Create( p_input, "bookmarks", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
        var_Create( p_input, "programs", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
        var_Create( p_input, "program", VLC_VAR_INTEGER | VLC_VAR_DOINHERIT );
        var_Create( p_input, "rate", VLC_VAR_FLOAT | VLC_VAR_DOINHERIT );
    }

    /* */
    var_Create( p_input, "input-record-native", VLC_VAR_BOOL | VLC_VAR_DOINHERIT );

    /* */
    var_Create( p_input, "demux", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
    var_Create( p_input, "demux-filter", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
    var_Create( p_input, "stream-filter", VLC_VAR_STRING | VLC_VAR_DOINHERIT );

    /* Meta */
    var_Create( p_input, "meta-title", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
    var_Create( p_input, "meta-author", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
    var_Create( p_input, "meta-artist", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
    var_Create( p_input, "meta-genre", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
    var_Create( p_input, "meta-copyright", VLC_VAR_STRING | VLC_VAR_DOINHERIT);
    var_Create( p_input, "meta-description", VLC_VAR_STRING|VLC_VAR_DOINHERIT);
    var_Create( p_input, "meta-date", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
    var_Create( p_input, "meta-url", VLC_VAR_STRING | VLC_VAR_DOINHERIT );

    /* Inherited by demux/subtitle.c */
    var_Create( p_input, "sub-original-fps", VLC_VAR_FLOAT );

    /* used by Medialibrary */
    var_Create( p_input, "save-recentplay", VLC_VAR_BOOL | VLC_VAR_DOINHERIT );
}
