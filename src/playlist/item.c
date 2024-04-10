/*****************************************************************************
 * playlist/item.c
 *****************************************************************************
 * Copyright (C) 2018 VLC authors and VideoLAN
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "item.h"

#include <vlc_playlist.h>
<<<<<<< HEAD
#include <vlc_input_item.h>
=======
#include <vlc_rand.h>
#include "playlist_internal.h"
#include "libvlc.h"

static void playlist_Preparse( playlist_t *, playlist_item_t * );

static int RecursiveAddIntoParent (
                playlist_t *p_playlist, playlist_item_t *p_parent,
                input_item_node_t *p_node, int i_pos, bool b_flat,
                playlist_item_t **pp_first_leaf );
static int RecursiveInsertCopy (
                playlist_t *p_playlist, playlist_item_t *p_item,
                playlist_item_t *p_parent, int i_pos, bool b_flat );

/*****************************************************************************
 * An input item has gained subitems (Event Callback)
 *****************************************************************************/

static void input_item_add_subitem_tree ( const vlc_event_t * p_event,
                                          void * user_data )
{
    input_item_t *p_input = p_event->p_obj;
    playlist_t *p_playlist = user_data;
    playlist_private_t *p_sys = pl_priv( p_playlist );
    input_item_node_t *p_new_root = p_event->u.input_item_subitem_tree_added.p_root;

    PL_LOCK;

    playlist_item_t *p_item =
        playlist_ItemGetByInput( p_playlist, p_input );

    assert( p_item != NULL );

    bool b_current = get_current_status_item( p_playlist ) == p_item;
    bool b_autostart = var_GetBool( p_playlist, "playlist-autostart" );
    bool b_stop = p_item->i_flags & PLAYLIST_SUBITEM_STOP_FLAG;
    bool b_flat = false;

    p_item->i_flags &= ~PLAYLIST_SUBITEM_STOP_FLAG;

    /* We will have to flatten the tree out if we are in "the playlist" node and
    the user setting demands flat playlist */

    if( !pl_priv(p_playlist)->b_tree ) {
        playlist_item_t *p_up = p_item;
        while( p_up->p_parent )
        {
            if( p_up->p_parent == p_playlist->p_playing )
            {
                b_flat = true;
                break;
            }
            p_up = p_up->p_parent;
        }
    }

    int pos = 0;

    /* If we have to flatten out, then take the item's position in the parent as
    insertion point and delete the item */

    bool b_redirect_request = false;

    if( b_flat )
    {
        playlist_item_t *p_parent = p_item->p_parent;
        assert( p_parent != NULL );

        int i;
        for( i = 0; i < p_parent->i_children; i++ )
        {
            if( p_parent->pp_children[i] == p_item )
            {
                pos = i;
                break;
            }
        }
        assert( i < p_parent->i_children );

        playlist_NodeDeleteExplicit( p_playlist, p_item, 0 );

        /* If there is a pending request referring to the item we just deleted
         * it needs to be updated so that we do not try to play an entity that
         * is no longer part of the playlist. */

        if( p_sys->request.b_request &&
            ( p_sys->request.p_item == p_item ||
              p_sys->request.p_node == p_item ) )
        {
            b_redirect_request = true;
        }

        p_item = p_parent;
    }
    else
    {
        pos = p_item->i_children >= 0 ? p_item->i_children : 0;
    }

    /* At this point:
    "p_item" is the node where sub-items should be inserted,
    "pos" is the insertion position in that node */

    int last_pos = playlist_InsertInputItemTree( p_playlist,
                                                 p_item,
                                                 p_new_root,
                                                 pos,
                                                 b_flat );
    if( b_redirect_request )
    {
        /* a redirect of the pending request is required, as such we update the
         * request to refer to the item that would have been the next in line
         * (if any). */

        assert( b_flat );

        playlist_item_t* p_redirect = NULL;

        if( p_item->i_children > pos )
            p_redirect = p_item->pp_children[pos];

        p_sys->request.p_item = p_redirect;
        p_sys->request.p_node = NULL;
    }

    if( !b_flat ) var_SetInteger( p_playlist, "leaf-to-parent", p_item->i_id );

    //control playback only if it was the current playing item that got subitems
    if( b_current )
    {
        if( ( b_stop && !b_flat ) || !b_autostart )
        {
            playlist_Control( p_playlist, PLAYLIST_STOP, pl_Locked );
        }
        else if( last_pos != pos ) /* any children? */
        {
            /* Continue to play, either random or the first new item */
            playlist_item_t *p_play_item;

            if( var_GetBool( p_playlist, "random" ) )
            {
                p_play_item = NULL;
            }
            else
            {
                p_play_item = p_item->pp_children[pos];
                /* NOTE: this is a work around the general bug:
                if node-to-be-played contains sub-nodes, then second instead
                of first leaf starts playing (only in case the leafs have just
                been instered and playlist has not yet been rebuilt.)
                */
                while( p_play_item->i_children > 0 )
                    p_play_item = p_play_item->pp_children[0];
            }

            playlist_ViewPlay( p_playlist, NULL, p_play_item );
        }
        else if( b_flat && p_playlist->current.i_size > 0 )
        {
            /* If the playlist is flat, empty nodes are automatically deleted;
             * meaning that moving from the current index (the index of a now
             * removed node) to the next would result in a skip of one entry
             * (as the empty node is deleted, the logical next item would be
             * the one that now resides in its place).
             *
             * Imagine [ A, B, C, D ], where B (at index 1) is currently being
             * played and deleted. C is the logically next item, but since the
             * list now looks like [ A, C, D ], advancing to index 2 would mean
             * D is played - and not C.
             *
             * By positioning the playlist-head at index 0 (A), when the
             * playlist advance to the next item, C will correctly be played.
             *
             * Note: Of course, if the deleted item is at index 0, we should
             * play whatever item is at position 0 since we cannot advance to
             * index -1 (as there cannot possibly be any item there).
             **/

            if( last_pos )
                ResetCurrentlyPlaying( p_playlist,
                    ARRAY_VAL( p_playlist->current, last_pos - 1 ) );
            else
                playlist_ViewPlay( p_playlist, NULL,
                    ARRAY_VAL( p_playlist->current, 0 ) );
        }
    }

    PL_UNLOCK;
}
/*****************************************************************************
 * An input item's meta or duration has changed (Event Callback)
 *****************************************************************************/
static void input_item_changed( const vlc_event_t * p_event,
                                void * user_data )
{
    playlist_t *p_playlist = user_data;

    var_SetAddress( p_playlist, "item-change", p_event->p_obj );
}

static int playlist_ItemCmpId( const void *a, const void *b )
{
    const playlist_item_t *pa = a, *pb = b;

    /* ID are between 1 and INT_MAX, this cannot overflow. */
    return pa->i_id - pb->i_id;
}

static int playlist_ItemCmpInput( const void *a, const void *b )
{
    const playlist_item_t *pa = a, *pb = b;

    if( pa->p_input == pb->p_input )
        return 0;
    return (((uintptr_t)pa->p_input) > ((uintptr_t)pb->p_input))
        ? +1 : -1;
}

/*****************************************************************************
 * Playlist item creation
 *****************************************************************************/
playlist_item_t *playlist_ItemNewFromInput( playlist_t *p_playlist,
                                              input_item_t *p_input )
{
    playlist_private_t *p = pl_priv(p_playlist);
    playlist_item_t **pp, *p_item;

    p_item = malloc( sizeof( playlist_item_t ) );
    if( unlikely(p_item == NULL) )
        return NULL;

    assert( p_input );

    p_item->p_input = p_input;
    p_item->i_id = p->i_last_playlist_id;
    p_item->p_parent = NULL;
    p_item->i_children = (p_input->i_type == ITEM_TYPE_NODE) ? 0 : -1;
    p_item->pp_children = NULL;
    p_item->i_nb_played = 0;
    p_item->i_flags = 0;

    PL_ASSERT_LOCKED;

    do  /* Find an unused ID for the item */
    {
        if( unlikely(p_item->i_id == INT_MAX) )
            p_item->i_id = 0;

        p_item->i_id++;

        if( unlikely(p_item->i_id == p->i_last_playlist_id) )
            goto error; /* All IDs taken */

        pp = tsearch( p_item, &p->id_tree, playlist_ItemCmpId );
        if( unlikely(pp == NULL) )
            goto error;

        assert( (*pp)->i_id == p_item->i_id );
        assert( (*pp) == p_item || (*pp)->p_input != p_input );
    }
    while( p_item != *pp );

    pp = tsearch( p_item, &p->input_tree, playlist_ItemCmpInput );
    if( unlikely(pp == NULL) )
    {
        tdelete( p_item, &p->id_tree, playlist_ItemCmpId );
        goto error;
    }
    /* Same input item cannot be inserted twice. */
    assert( p_item == *pp );

    p->i_last_playlist_id = p_item->i_id;
    input_item_Hold( p_item->p_input );

    vlc_event_manager_t *p_em = &p_item->p_input->event_manager;

    vlc_event_attach( p_em, vlc_InputItemSubItemTreeAdded,
                      input_item_add_subitem_tree, p_playlist );
    vlc_event_attach( p_em, vlc_InputItemDurationChanged,
                      input_item_changed, p_playlist );
    vlc_event_attach( p_em, vlc_InputItemMetaChanged,
                      input_item_changed, p_playlist );
    vlc_event_attach( p_em, vlc_InputItemNameChanged,
                      input_item_changed, p_playlist );
    vlc_event_attach( p_em, vlc_InputItemInfoChanged,
                      input_item_changed, p_playlist );
    vlc_event_attach( p_em, vlc_InputItemErrorWhenReadingChanged,
                      input_item_changed, p_playlist );

    return p_item;

error:
    free( p_item );
    return NULL;
}

/***************************************************************************
 * Playlist item destruction
 ***************************************************************************/

/**
 * Release an item
 *
 * \param p_item item to delete
*/
void playlist_ItemRelease( playlist_t *p_playlist, playlist_item_t *p_item )
{
    playlist_private_t *p = pl_priv(p_playlist);

    PL_ASSERT_LOCKED;

    vlc_event_manager_t *p_em = &p_item->p_input->event_manager;

    vlc_event_detach( p_em, vlc_InputItemSubItemTreeAdded,
                      input_item_add_subitem_tree, p_playlist );
    vlc_event_detach( p_em, vlc_InputItemMetaChanged,
                      input_item_changed, p_playlist );
    vlc_event_detach( p_em, vlc_InputItemDurationChanged,
                      input_item_changed, p_playlist );
    vlc_event_detach( p_em, vlc_InputItemNameChanged,
                      input_item_changed, p_playlist );
    vlc_event_detach( p_em, vlc_InputItemInfoChanged,
                      input_item_changed, p_playlist );
    vlc_event_detach( p_em, vlc_InputItemErrorWhenReadingChanged,
                      input_item_changed, p_playlist );

    input_item_Release( p_item->p_input );

    tdelete( p_item, &p->input_tree, playlist_ItemCmpInput );
    tdelete( p_item, &p->id_tree, playlist_ItemCmpId );
    free( p_item->pp_children );
    free( p_item );
}

/**
 * Finds a playlist item by ID.
 *
 * Searches for a playlist item with the given ID.
 *
 * \note The playlist must be locked, and the result is only valid until the
 * playlist is unlocked.
 *
 * \warning If an item with the given ID is deleted, it is unlikely but
 * possible that another item will get the same ID. This can result in
 * mismatches.
 * Where holding a reference to an input item is a viable option, then
 * playlist_ItemGetByInput() should be used instead - to avoid this issue.
 *
 * @param p_playlist the playlist
 * @param id ID to look for
 * @return the matching item or NULL if not found
 */
playlist_item_t *playlist_ItemGetById( playlist_t *p_playlist , int id )
{
    playlist_private_t *p = pl_priv(p_playlist);
    playlist_item_t key, **pp;

    PL_ASSERT_LOCKED;
    key.i_id = id;
    pp = tfind( &key, &p->id_tree, playlist_ItemCmpId );
    return (pp != NULL) ? *pp : NULL;
}

/**
 * Finds a playlist item by input item.
 *
 * Searches for a playlist item for the given input item.
 *
 * \note The playlist must be locked, and the result is only valid until the
 * playlist is unlocked.
 *
 * \param p_playlist the playlist
 * \param item input item to look for
 * \return the playlist item or NULL on failure
 */
playlist_item_t *playlist_ItemGetByInput( playlist_t * p_playlist,
                                          const input_item_t *item )
{
    playlist_private_t *p = pl_priv(p_playlist);
    playlist_item_t key, **pp;

    PL_ASSERT_LOCKED;
    key.p_input = (input_item_t *)item;
    pp = tfind( &key, &p->input_tree, playlist_ItemCmpInput );
    return (pp != NULL) ? *pp : NULL;
}

/**
 * Clear the playlist
 *
 * \param p_playlist playlist object
 * \param b_locked TRUE if the playlist is locked
 * \return nothing
 */
void playlist_Clear( playlist_t * p_playlist, bool b_locked )
{
    playlist_item_t *p_root = p_playlist->p_playing;

    PL_LOCK_IF( !b_locked );

    for( int i = p_root->i_children - 1; i >= 0 ;i-- )
        playlist_NodeDelete( p_playlist, p_root->pp_children[i] );

    PL_UNLOCK_IF( !b_locked );
}

/***************************************************************************
 * Playlist item addition
 ***************************************************************************/
/**
 * Playlist add
 *
 * Add an item to the playlist
 * \param p_playlist the playlist to add into
 * \param psz_uri the mrl to add to the playlist
 * \param play_now whether to start playing immediately or not
 * \return VLC_SUCCESS or a VLC error code
 */
int playlist_Add( playlist_t *p_playlist, const char *psz_uri, bool play_now )
{
    return playlist_AddExt( p_playlist, psz_uri, NULL, play_now,
                            0, NULL, 0, true );
}

/**
 * Add a MRL into the playlist or the media library, duration and options given
 *
 * \param p_playlist the playlist to add into
 * \param psz_uri the mrl to add to the playlist
 * \param psz_name a text giving a name or description of this item
 * \param play_now whether to start playing immediately or not
 * \param i_options the number of options
 * \param ppsz_options an array of options
 * \param i_option_flags options flags
 * \param b_playlist TRUE for playlist, FALSE for media library
 * \return VLC_SUCCESS or a VLC error code
*/
int playlist_AddExt( playlist_t *p_playlist, const char * psz_uri,
                     const char *psz_name, bool play_now,
                     int i_options, const char *const *ppsz_options,
                     unsigned i_option_flags,
                     bool b_playlist )
{
    input_item_t *p_input = input_item_New( psz_uri, psz_name );
    if( !p_input )
        return VLC_ENOMEM;
    input_item_AddOptions( p_input, i_options, ppsz_options, i_option_flags );
    int i_ret = playlist_AddInput( p_playlist, p_input, play_now, b_playlist );
    input_item_Release( p_input );
    return i_ret;
}
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

vlc_playlist_item_t *
vlc_playlist_item_New(input_item_t *media, uint64_t id)
{
    vlc_playlist_item_t *item = malloc(sizeof(*item));
    if (unlikely(!item))
        return NULL;

<<<<<<< HEAD
    vlc_atomic_rc_init(&item->rc);
    item->id = id;
    item->media = media;
    input_item_Hold(media);
    return item;
=======
    if( p_input->i_type != ITEM_TYPE_NODE )
        ARRAY_APPEND(p_playlist->items, p_item);

    playlist_NodeInsert( p_parent, p_item, i_pos );
    playlist_SendAddNotify( p_playlist, p_item );
    playlist_Preparse( p_playlist, p_item );

    return p_item;
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
}

void
vlc_playlist_item_Hold(vlc_playlist_item_t *item)
{
    vlc_atomic_rc_inc(&item->rc);
}

void
vlc_playlist_item_Release(vlc_playlist_item_t *item)
{
    if (vlc_atomic_rc_dec(&item->rc))
    {
        input_item_Release(item->media);
        free(item);
    }
}

<<<<<<< HEAD
input_item_t *
vlc_playlist_item_GetMedia(vlc_playlist_item_t *item)
{
    return item->media;
=======
/**
 * Get the duration of all items in a node.
 */
vlc_tick_t playlist_GetNodeDuration( playlist_item_t* node )
{
    vlc_tick_t duration = input_item_GetDuration( node->p_input );
    if( duration == -1 )
        duration = 0;

    for( int i = 0; i < node->i_children; i++ )
        duration += playlist_GetNodeDuration( node->pp_children[i] );

    return duration;
}

/***************************************************************************
 * The following functions are local
 ***************************************************************************/

/* Enqueue an item for preparsing */
static void playlist_Preparse( playlist_t *p_playlist,
                               playlist_item_t *p_item )
{
    playlist_private_t *sys = pl_priv(p_playlist);
    input_item_t *input = p_item->p_input;

    PL_ASSERT_LOCKED;
    /* Preparse if no artist/album info, and hasn't been preparsed already
       and if user has some preparsing option (auto-preparse variable)
       enabled*/
    char *psz_artist = input_item_GetArtist( input );
    char *psz_album = input_item_GetAlbum( input );

    if( sys->b_preparse && !input_item_IsPreparsed( input )
     && (EMPTY_STR(psz_artist) || EMPTY_STR(psz_album)) )
        vlc_MetadataRequest( p_playlist->obj.libvlc, input, 0, -1, p_item );
    free( psz_artist );
    free( psz_album );
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
}

uint64_t
vlc_playlist_item_GetId(vlc_playlist_item_t *item)
{
    return item->id;
}
