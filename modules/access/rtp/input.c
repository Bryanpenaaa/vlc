/**
 * @file input.c
 * @brief RTP packet input
 */
/*****************************************************************************
 * Copyright © 2008 Rémi Denis-Courmont
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <limits.h>
#include <errno.h>
#ifdef HAVE_POLL_H
# include <poll.h>
#endif
#ifdef HAVE_SYS_UIO_H
# include <sys/uio.h>
#endif
#ifdef _WIN32
# include <winsock2.h>
#endif

#include <vlc_common.h>
#include <vlc_demux.h>
#include <vlc_block.h>
#include "vlc_dtls.h"

#include "rtp.h"
#ifdef HAVE_SRTP
# include "srtp.h"
#endif

#define DEFAULT_MRU (1500u - (20 + 8))

/**
 * Processes a packet received from the RTP socket.
 */
static void rtp_process (demux_t *demux, block_t *block)
{
    demux_sys_t *sys = demux->p_sys;

    if (block->i_buffer < 2)
        goto drop;
    const uint8_t ptype = rtp_ptype (block);
    if (ptype >= 72 && ptype <= 76)
        goto drop; /* Muxed RTCP, ignore for now FIXME */

#ifdef HAVE_SRTP
    if (sys->srtp != NULL)
    {
        size_t len = block->i_buffer;
        if (srtp_recv (sys->srtp, block->p_buffer, &len))
        {
            msg_Dbg (demux, "SRTP authentication/decryption failed");
            goto drop;
        }
        block->i_buffer = len;
    }
#endif

    rtp_queue (demux, sys->session, block);
    return;
drop:
    block_Release (block);
}

static int rtp_timeout (vlc_tick_t deadline)
{
    if (deadline == VLC_TICK_INVALID)
        return -1; /* infinite */

<<<<<<< master
    vlc_tick_t t = vlc_tick_now ();
=======
    vlc_tick_t t = mdate ();
>>>>>>> origin/3.0.x
    if (t >= deadline)
        return 0;

    t = (deadline - t) / (CLOCK_FREQ / INT64_C(1000));
    if (unlikely(t > INT_MAX))
        return INT_MAX;
    return t;
}

/**
 * RTP/RTCP session thread for datagram sockets
 */
void *rtp_dgram_thread (void *opaque)
{
    demux_t *demux = opaque;
    demux_sys_t *sys = demux->p_sys;
    vlc_tick_t deadline = VLC_TICK_INVALID;
<<<<<<< master
    struct vlc_dtls *rtp_sock = sys->rtp_sock;
=======
    int rtp_fd = sys->fd;
#ifdef __linux__
    const int trunc_flag = MSG_TRUNC;
#else
    const int trunc_flag = 0;
#endif

    struct iovec iov =
    {
        .iov_len = DEFAULT_MRU,
    };
    struct msghdr msg =
    {
        .msg_iov = &iov,
        .msg_iovlen = 1,
    };
>>>>>>> origin/3.0.x

    vlc_thread_set_name("vlc-rtp");

    for (;;)
    {
        struct pollfd ufd[1];

        ufd[0].events = POLLIN;
        ufd[0].fd = vlc_dtls_GetPollFD(rtp_sock, &ufd[0].events);

        int n = poll (ufd, 1, rtp_timeout (deadline));
        if (n == -1)
            continue;

        int canc = vlc_savecancel ();
        if (n == 0)
            goto dequeue;

        if (ufd[0].revents)
        {
            block_t *block = block_Alloc(DEFAULT_MRU);
            if (unlikely(block == NULL))
<<<<<<< master
                break; /* we are totallly screwed */

            bool truncated;
            ssize_t len = vlc_dtls_Recv(rtp_sock, block->p_buffer,
                                       block->i_buffer, &truncated);
            if (len >= 0) {
                if (truncated) {
                    msg_Err(demux, "packet truncated (MRU was %zu)",
                            block->i_buffer);
=======
            {
                if (iov.iov_len == DEFAULT_MRU)
                    break; /* we are totallly screwed */
                iov.iov_len = DEFAULT_MRU;
                continue; /* retry with shrunk MRU */
            }

            iov.iov_base = block->p_buffer;
            msg.msg_flags = trunc_flag;

            ssize_t len = recvmsg (rtp_fd, &msg, trunc_flag);
            if (len != -1)
            {
                if (msg.msg_flags & trunc_flag)
                {
                    msg_Err(demux, "%zd bytes packet truncated (MRU was %zu)",
                            len, iov.iov_len);
>>>>>>> origin/3.0.x
                    block->i_flags |= BLOCK_FLAG_CORRUPTED;
                }
                else
                    block->i_buffer = len;

                rtp_process (demux, block);
            }
            else
            {
                if (errno == EPIPE)
                    break; /* connection terminated */
                msg_Warn (demux, "RTP network error: %s",
                          vlc_strerror_c(errno));
                block_Release (block);
            }

            n--;
        }

    dequeue:
        if (!rtp_dequeue (demux, sys->session, &deadline))
            deadline = VLC_TICK_INVALID;
<<<<<<< master
=======
        vlc_restorecancel (canc);
    }
    return NULL;
}

/**
 * RTP/RTCP session thread for stream sockets (framed RTP)
 */
void *rtp_stream_thread (void *opaque)
{
#ifndef _WIN32
    demux_t *demux = opaque;
    demux_sys_t *sys = demux->p_sys;
    int fd = sys->fd;

    for (;;)
    {
        /* There is no reordering on stream sockets, so no timeout. */
        ssize_t val;

        uint16_t frame_len;
        if (recv (fd, &frame_len, 2, MSG_WAITALL) != 2)
            break;

        block_t *block = block_Alloc (ntohs (frame_len));
        if (unlikely(block == NULL))
            break;

        block_cleanup_push (block);
        val = recv (fd, block->p_buffer, block->i_buffer, MSG_WAITALL);
        vlc_cleanup_pop ();

        if (val != (ssize_t)block->i_buffer)
        {
            block_Release (block);
            break;
        }

        int canc = vlc_savecancel ();
        rtp_process (demux, block);
        rtp_dequeue_force (demux, sys->session);
>>>>>>> origin/3.0.x
        vlc_restorecancel (canc);
    }
    return NULL;
}
