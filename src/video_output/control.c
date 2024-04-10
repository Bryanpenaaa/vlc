/*****************************************************************************
 * control.c : vout internal control
 *****************************************************************************
 * Copyright (C) 2009 Laurent Aimar
 *
 * Authors: Laurent Aimar <fenrir _AT_ videolan _DOT_ org>
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

#include <vlc_common.h>
#include <vlc_vout.h>
#include "vout_internal.h"
#include "control.h"

/* */
void vout_control_Init(vout_control_t *ctrl)
{
    vlc_mutex_init(&ctrl->lock);
    vlc_cond_init(&ctrl->wait_request);
    vlc_cond_init(&ctrl->wait_available);

    ctrl->is_held = false;
    ctrl->yielding = false;
    ctrl->forced_awake = false;
    ctrl->pending_count = 0;
}

void vout_control_Wake(vout_control_t *ctrl)
{
    vlc_mutex_lock(&ctrl->lock);
    ctrl->forced_awake = true;
    vlc_cond_signal(&ctrl->wait_request);
    vlc_mutex_unlock(&ctrl->lock);
}

void vout_control_Hold(vout_control_t *ctrl)
{
    vlc_mutex_lock(&ctrl->lock);
    ++ctrl->pending_count;
    vlc_cond_signal(&ctrl->wait_request);
    while (ctrl->is_held || !ctrl->yielding)
        vlc_cond_wait(&ctrl->wait_available, &ctrl->lock);
    ctrl->is_held = true;
    --ctrl->pending_count;
    if (ctrl->pending_count == 0)
        vlc_cond_signal(&ctrl->wait_request);
    vlc_mutex_unlock(&ctrl->lock);
}

static void vout_control_ReleaseUnlocked(vout_control_t *ctrl)
{
    assert(ctrl->is_held);
    ctrl->is_held = false;
    vlc_cond_signal(&ctrl->wait_available);
}

void vout_control_Release(vout_control_t *ctrl)
{
    vlc_mutex_lock(&ctrl->lock);
    vout_control_ReleaseUnlocked(ctrl);
    vlc_mutex_unlock(&ctrl->lock);
}

void vout_control_ReleaseAndWake(vout_control_t *ctrl)
{
    vlc_mutex_lock(&ctrl->lock);
    vout_control_ReleaseUnlocked(ctrl);
    ctrl->forced_awake = true;
    vlc_cond_signal(&ctrl->wait_request);
    vlc_mutex_unlock(&ctrl->lock);
}

<<<<<<< HEAD
void vout_control_Wait(vout_control_t *ctrl, vlc_tick_t deadline)
=======
void vout_control_PushVoid(vout_control_t *ctrl, int type)
{
    vout_control_cmd_t cmd;

    vout_control_cmd_Init(&cmd, type);
    vout_control_Push(ctrl, &cmd);
}
void vout_control_PushBool(vout_control_t *ctrl, int type, bool boolean)
{
    vout_control_cmd_t cmd;

    vout_control_cmd_Init(&cmd, type);
    cmd.u.boolean = boolean;
    vout_control_Push(ctrl, &cmd);
}
void vout_control_PushInteger(vout_control_t *ctrl, int type, int integer)
{
    vout_control_cmd_t cmd;

    vout_control_cmd_Init(&cmd, type);
    cmd.u.integer = integer;
    vout_control_Push(ctrl, &cmd);
}
void vout_control_PushTime(vout_control_t *ctrl, int type, vlc_tick_t time)
{
    vout_control_cmd_t cmd;

    vout_control_cmd_Init(&cmd, type);
    cmd.u.time = time;
    vout_control_Push(ctrl, &cmd);
}
void vout_control_PushMessage(vout_control_t *ctrl, int type, int channel, const char *string)
{
    vout_control_cmd_t cmd;

    vout_control_cmd_Init(&cmd, type);
    cmd.u.message.channel = channel;
    cmd.u.message.string = strdup(string);
    vout_control_Push(ctrl, &cmd);
}
void vout_control_PushPair(vout_control_t *ctrl, int type, int a, int b)
{
    vout_control_cmd_t cmd;

    vout_control_cmd_Init(&cmd, type);
    cmd.u.pair.a = a;
    cmd.u.pair.b = b;
    vout_control_Push(ctrl, &cmd);
}
void vout_control_PushString(vout_control_t *ctrl, int type, const char *string)
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
{
    vlc_mutex_lock(&ctrl->lock);

    ctrl->yielding = true;

<<<<<<< HEAD
    while (ctrl->pending_count != 0)
    {
        /* Let vout_control_Hold() callers pass */
        vlc_cond_signal(&ctrl->wait_available);
        vlc_cond_wait(&ctrl->wait_request, &ctrl->lock);
    }

    if (deadline != VLC_TICK_INVALID)
    {
        do
        {
            if (ctrl->forced_awake)
                break;

            vlc_cond_signal(&ctrl->wait_available);
        }
        while (vlc_cond_timedwait(&ctrl->wait_request, &ctrl->lock,
                                  deadline) == 0);
=======
int vout_control_Pop(vout_control_t *ctrl, vout_control_cmd_t *cmd,
                     vlc_tick_t deadline)
{
    vlc_mutex_lock(&ctrl->lock);
    if (ctrl->cmd.i_size <= 0) {
        ctrl->is_processing = false;
        vlc_cond_broadcast(&ctrl->wait_acknowledge);

        /* Spurious wakeups are perfectly fine */
        if (deadline > VLC_TICK_INVALID && ctrl->can_sleep)
            vlc_cond_timedwait(&ctrl->wait_request, &ctrl->lock, deadline);
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
    }

    ctrl->yielding = false;

    while (ctrl->is_held)
        vlc_cond_wait(&ctrl->wait_available, &ctrl->lock);

    ctrl->forced_awake = false;
    vlc_mutex_unlock(&ctrl->lock);
}

