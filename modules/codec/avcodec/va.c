/*****************************************************************************
 * va.c: hardware acceleration plugins for avcodec
 *****************************************************************************
 * Copyright (C) 2009 Laurent Aimar
 * Copyright (C) 2012-2013 Rémi Denis-Courmont
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
# include <config.h>
#endif

#include <vlc_common.h>
#include <vlc_modules.h>
#include <vlc_fourcc.h>
#include <libavutil/pixfmt.h>
#include <libavcodec/avcodec.h>
#include "va.h"

bool vlc_va_MightDecode(enum AVPixelFormat hwfmt, enum AVPixelFormat swfmt)
{
    switch (hwfmt)
    {
        case AV_PIX_FMT_VAAPI:
            switch (swfmt)
            {
                case AV_PIX_FMT_YUVJ420P:
                case AV_PIX_FMT_YUV420P:
                case AV_PIX_FMT_YUV420P10LE:
                    return true;
                default:
                    return false;
            }
        case AV_PIX_FMT_DXVA2_VLD:
            switch (swfmt)
            {
                case AV_PIX_FMT_YUV420P10LE:
                case AV_PIX_FMT_YUVJ420P:
                case AV_PIX_FMT_YUV420P:
                case AV_PIX_FMT_YUV444P:
                case AV_PIX_FMT_YUV420P12:
                case AV_PIX_FMT_YUV444P10:
                case AV_PIX_FMT_YUV444P12:
                case AV_PIX_FMT_YUV422P10:
                case AV_PIX_FMT_YUV422P12:
                    return true;
                default:
                    return false;
            }
            break;

        case AV_PIX_FMT_D3D11VA_VLD:
            switch (swfmt)
            {
                case AV_PIX_FMT_YUV420P10LE:
                case AV_PIX_FMT_YUVJ420P:
                case AV_PIX_FMT_YUV420P:
                case AV_PIX_FMT_YUV444P:
                case AV_PIX_FMT_YUV420P12:
                case AV_PIX_FMT_YUV444P10:
                case AV_PIX_FMT_YUV444P12:
                case AV_PIX_FMT_YUV422P10:
                case AV_PIX_FMT_YUV422P12:
                    return true;
                default:
                    return false;
            }
        break;

        case AV_PIX_FMT_VDPAU:
            switch (swfmt)
            {
                case AV_PIX_FMT_YUVJ444P:
                case AV_PIX_FMT_YUV444P:
                case AV_PIX_FMT_YUVJ422P:
                case AV_PIX_FMT_YUV422P:
                case AV_PIX_FMT_YUVJ420P:
                case AV_PIX_FMT_YUV420P:
                    return true;
                default:
                    return false;
            }
            break;
        default:
            return false;
    }
}

<<<<<<< master
=======
static int vlc_va_Start(void *func, va_list ap)
{
    vlc_va_t *va = va_arg(ap, vlc_va_t *);
    AVCodecContext *ctx = va_arg(ap, AVCodecContext *);
    enum PixelFormat pix_fmt = va_arg(ap, enum PixelFormat);
    const es_format_t *fmt = va_arg(ap, const es_format_t *);
    picture_sys_t *p_sys = va_arg(ap, picture_sys_t *);
    int (*open)(vlc_va_t *, AVCodecContext *, enum PixelFormat,
                const es_format_t *, picture_sys_t *) = func;

    return open(va, ctx, pix_fmt, fmt, p_sys);
}

static void vlc_va_Stop(void *func, va_list ap)
{
    vlc_va_t *va = va_arg(ap, vlc_va_t *);
    void **hwctx = va_arg(ap, void **);
    void (*close)(vlc_va_t *, void *) = func;

    close(va, hwctx);
}

>>>>>>> origin/3.0.x
vlc_va_t *vlc_va_New(vlc_object_t *obj, AVCodecContext *avctx,
                     enum AVPixelFormat hwfmt, const AVPixFmtDescriptor *src_desc,
                     const es_format_t *fmt_in, vlc_decoder_device *device,
                     video_format_t *fmt_out, vlc_video_context **vtcx_out)
{
    struct vlc_va_t *va = vlc_object_create(obj, sizeof (*va));
    if (unlikely(va == NULL))
        return NULL;

<<<<<<< master
    module_t **mods;
    ssize_t total = vlc_module_match("hw decoder", NULL, false, &mods, NULL);

    for (ssize_t i = 0; i < total; i++) {
        vlc_va_open open = vlc_module_map(obj->logger, mods[i]);

        if (open != NULL && open(va, avctx, hwfmt, src_desc, fmt_in, device,
                                 fmt_out, vtcx_out) == VLC_SUCCESS) {
            free(mods);
            return va;
        }
=======
    char *modlist = var_InheritString(obj, "avcodec-hw");

    va->module = vlc_module_load(va, "hw decoder", modlist, true,
                                 vlc_va_Start, va, avctx, pix_fmt, fmt, p_sys);
    free(modlist);
    if (va->module == NULL)
    {
        vlc_object_release(va);
        va = NULL;
>>>>>>> origin/3.0.x
    }

    free(mods);
    vlc_object_delete(va);
    return NULL;
}

void vlc_va_Delete(vlc_va_t *va, AVCodecContext *avctx)
{
    if (va->ops->close != NULL)
        va->ops->close(va, avctx);
    vlc_object_delete(va);
}
