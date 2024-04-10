/*****************************************************************************
 * video.c: transcoding stream output module (video)
 *****************************************************************************
 * Copyright (C) 2003-2009 VLC authors and VideoLAN
 *
 * Authors: Laurent Aimar <fenrir@via.ecp.fr>
 *          Gildas Bazin <gbazin@videolan.org>
 *          Jean-Paul Saman <jpsaman #_at_# m2x dot nl>
 *          Antoine Cellerier <dionoea at videolan dot org>
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
#include "config.h"
#endif

#include <vlc_common.h>
#include <vlc_meta.h>
#include <vlc_spu.h>
#include <vlc_modules.h>
#include <vlc_sout.h>

#include "transcode.h"

#include <math.h>

<<<<<<< HEAD
struct encoder_owner
{
    encoder_t enc;
    sout_stream_id_sys_t *id;
};

static vlc_decoder_device *TranscodeHoldDecoderDevice(vlc_object_t *o, sout_stream_id_sys_t *id)
{
    if (id->dec_dev == NULL)
        id->dec_dev = vlc_decoder_device_Create( o, NULL );
    return id->dec_dev ? vlc_decoder_device_Hold(id->dec_dev) : NULL;
=======
static const video_format_t* video_output_format( sout_stream_id_sys_t *id,
                                                  picture_t *p_pic )
{
    assert( id && p_pic );
    if( id->p_uf_chain )
        return &filter_chain_GetFmtOut( id->p_uf_chain )->video;
    else if( id->p_f_chain )
        return &filter_chain_GetFmtOut( id->p_f_chain )->video;
    else
        return &p_pic->format;
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
}

static inline struct encoder_owner *enc_get_owner( encoder_t *p_enc )
{
    return container_of( p_enc, struct encoder_owner, enc );
}

static vlc_decoder_device *video_get_encoder_device( encoder_t *enc )
{
    struct encoder_owner *p_owner = enc_get_owner( enc );
    if (p_owner->id->dec_dev == NULL)
        p_owner->id->dec_dev = vlc_decoder_device_Create( &enc->obj, NULL );

<<<<<<< HEAD
    return p_owner->id->dec_dev ? vlc_decoder_device_Hold(p_owner->id->dec_dev) : NULL;
=======
    /* will need proper chroma for get_buffer */
    p_dec->fmt_out.video.i_chroma = p_dec->fmt_out.i_codec;

    if( id->p_encoder->fmt_in.i_codec == p_dec->fmt_out.i_codec ||
        video_format_IsSimilar( &id->video_dec_out,
                                &p_dec->fmt_out.video ) )
        return 0;
    id->video_dec_out = p_dec->fmt_out.video;
    id->video_dec_out.p_palette = NULL;

    msg_Dbg( stream, "Checking if filter chain %4.4s -> %4.4s is possible",
                 (char *)&p_dec->fmt_out.i_codec, (char*)&id->p_encoder->fmt_in.i_codec );
    test_chain = filter_chain_NewVideo( stream, false, &filter_owner );
    filter_chain_Reset( test_chain, &p_dec->fmt_out, &p_dec->fmt_out );

    int chain_works = filter_chain_AppendConverter( test_chain, &p_dec->fmt_out,
                                  &id->p_encoder->fmt_in );
    filter_chain_Delete( test_chain );
    msg_Dbg( stream, "Filter chain testing done, input chroma %4.4s seems to be %s for transcode",
                     (char *)&p_dec->fmt_out.video.i_chroma,
                     chain_works == 0 ? "possible" : "not possible");
    return chain_works;
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
}

static const struct encoder_owner_callbacks encoder_video_transcode_cbs = {
    .video.get_device = video_get_encoder_device
};

static vlc_decoder_device * video_get_decoder_device( decoder_t *p_dec )
{
    if( !var_InheritBool( p_dec, "hw-dec" ) )
        return NULL;

    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    return TranscodeHoldDecoderDevice(&p_dec->obj, p_owner->id);
}

static void debug_format( vlc_object_t *p_obj, const es_format_t *fmt )
{
<<<<<<< HEAD
    msg_Dbg( p_obj, "format now %4.4s/%4.4s %dx%d(%dx%d) ø%d",
             (const char *) &fmt->i_codec,
             (const char *) &fmt->video.i_chroma,
             fmt->video.i_visible_width, fmt->video.i_visible_height,
             fmt->video.i_width, fmt->video.i_height,
             fmt->video.orientation );
=======
    return picture_NewFromFormat( &p_enc->fmt_in.video );
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
}

static picture_t *transcode_video_filter_buffer_new( filter_t *p_filter )
{
    assert(p_filter->fmt_out.video.i_chroma == p_filter->fmt_out.i_codec);
    return picture_NewFromFormat( &p_filter->fmt_out.video );
}

static vlc_decoder_device * transcode_video_filter_hold_device(vlc_object_t *o, void *sys)
{
    sout_stream_id_sys_t *id = sys;
    return TranscodeHoldDecoderDevice(o, id);
}

static const struct filter_video_callbacks transcode_filter_video_cbs =
{
    transcode_video_filter_buffer_new, transcode_video_filter_hold_device,
};

static int transcode_video_filters_init( sout_stream_t *p_stream,
                                         const sout_filters_config_t *p_cfg,
                                         const es_format_t *p_src,
                                         vlc_video_context *src_ctx,
                                         const es_format_t *p_dst,
                                         sout_stream_id_sys_t *id );

static int video_update_format_decoder( decoder_t *p_dec, vlc_video_context *vctx )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    sout_stream_id_sys_t *id = p_owner->id;

    vlc_mutex_lock(&id->fifo.lock);
    if( id->encoder != NULL && transcode_encoder_opened( id->encoder ) )
    {
        if( video_format_IsSimilar( &p_dec->fmt_out.video, &id->decoder_out.video ) )
        {
            vlc_mutex_unlock(&id->fifo.lock);
            goto end;
        }

        transcode_remove_filters( &id->p_final_conv_static );
        transcode_remove_filters( &id->p_uf_chain );
        transcode_remove_filters( &id->p_f_chain );
    }
    else if( id->encoder == NULL )
    {
        struct encoder_owner *p_enc_owner =
           (struct encoder_owner *)sout_EncoderCreate( VLC_OBJECT(p_owner->p_stream), sizeof(struct encoder_owner) );
        if ( unlikely(p_enc_owner == NULL))
            return VLC_EGENERIC;

        id->encoder = transcode_encoder_new( &p_enc_owner->enc, &p_dec->fmt_out );
        if( !id->encoder )
        {
            vlc_object_delete( &p_enc_owner->enc );
            return VLC_EGENERIC;
        }

        p_enc_owner->id = id;
        p_enc_owner->enc.cbs = &encoder_video_transcode_cbs;
    }


    es_format_Clean( &id->decoder_out );
    es_format_Copy( &id->decoder_out, &p_dec->fmt_out );
    /* crap, decoders resetting the whole fmtout... */
    es_format_SetMeta( &id->decoder_out, p_dec->fmt_in );

<<<<<<< HEAD
    if( transcode_video_filters_init( p_owner->p_stream,
                  id->p_filterscfg,
                  &id->decoder_out,
                  vctx,
                  &id->decoder_out, id) != VLC_SUCCESS )
=======
    /* Open decoder
     * Initialization of decoder structures
     */
    id->p_decoder->pf_decode = NULL;
    id->p_decoder->pf_queue_video = decoder_queue_video;
    id->p_decoder->p_queue_ctx = id;
    id->p_decoder->pf_get_cc = NULL;
    id->p_decoder->pf_vout_format_update = video_update_format_decoder;
    id->p_decoder->pf_vout_buffer_new = video_new_buffer_decoder;
    id->p_decoder->p_owner = (decoder_owner_sys_t*) p_stream;

    id->p_decoder->p_module =
        module_need( id->p_decoder, "video decoder", "$codec", false );

    if( !id->p_decoder->p_module )
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
    {
        msg_Err(p_dec, "Could not update transcode chain to new format");
        goto error;
    }

    struct vlc_video_context *enc_vctx = NULL;
    const es_format_t *out_fmt;

<<<<<<< HEAD
    if( id->p_uf_chain )
=======
    /* Initialization of encoder format structures */
    es_format_Init( &id->p_encoder->fmt_in, id->p_decoder->fmt_in.i_cat,
                    id->p_decoder->fmt_out.i_codec );

    /* The dimensions will be set properly later on.
     * Just put sensible values so we can test an encoder is available. */
    id->p_encoder->fmt_in.video.i_width =
        id->p_encoder->fmt_out.video.i_width
          ? id->p_encoder->fmt_out.video.i_width
          : id->p_decoder->fmt_in.video.i_width
            ? id->p_decoder->fmt_in.video.i_width : 16;
    id->p_encoder->fmt_in.video.i_height =
        id->p_encoder->fmt_out.video.i_height
          ? id->p_encoder->fmt_out.video.i_height
          : id->p_decoder->fmt_in.video.i_height
            ? id->p_decoder->fmt_in.video.i_height : 16;
    id->p_encoder->fmt_in.video.i_visible_width =
        id->p_encoder->fmt_out.video.i_visible_width
          ? id->p_encoder->fmt_out.video.i_visible_width
          : id->p_decoder->fmt_in.video.i_visible_width
            ? id->p_decoder->fmt_in.video.i_visible_width : id->p_encoder->fmt_in.video.i_width;
    id->p_encoder->fmt_in.video.i_visible_height =
        id->p_encoder->fmt_out.video.i_visible_height
          ? id->p_encoder->fmt_out.video.i_visible_height
          : id->p_decoder->fmt_in.video.i_visible_height
            ? id->p_decoder->fmt_in.video.i_visible_height : id->p_encoder->fmt_in.video.i_height;
    /* The same goes with frame rate. Some encoders need it to be initialized */
    id->p_encoder->fmt_in.video.i_frame_rate = ENC_FRAMERATE;
    id->p_encoder->fmt_in.video.i_frame_rate_base = ENC_FRAMERATE_BASE;

    id->p_encoder->i_threads = p_sys->i_threads;
    id->p_encoder->p_cfg = p_sys->p_video_cfg;

    id->p_encoder->p_module =
        module_need( id->p_encoder, "encoder", p_sys->psz_venc, true );
    if( !id->p_encoder->p_module )
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
    {
        enc_vctx = filter_chain_GetVideoCtxOut( id->p_uf_chain );
        out_fmt = filter_chain_GetFmtOut( id->p_uf_chain );
    }
    else if( id->p_f_chain )
    {
        enc_vctx = filter_chain_GetVideoCtxOut( id->p_f_chain );
        out_fmt = filter_chain_GetFmtOut( id->p_f_chain );
    }
<<<<<<< HEAD
    else
=======
    id->p_encoder->fmt_in.video.i_chroma = id->p_encoder->fmt_in.i_codec;
    id->p_encoder->p_module = NULL;

    if( p_sys->i_threads <= 0 )
        return VLC_SUCCESS;

    int i_priority = p_sys->b_high_priority ? VLC_THREAD_PRIORITY_OUTPUT :
                       VLC_THREAD_PRIORITY_VIDEO;
    p_sys->id_video = id;
    p_sys->pp_pics = picture_fifo_New();
    if( p_sys->pp_pics == NULL )
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
    {
        enc_vctx = vctx; /* Decoder video context */
        out_fmt = &id->decoder_out;
    }

    if( !transcode_encoder_opened( id->encoder ) )
    {
        transcode_encoder_video_configure( VLC_OBJECT(p_owner->p_stream),
                   &id->p_decoder->fmt_out.video,
                   id->p_enccfg,
                   &out_fmt->video,
                   enc_vctx,
                   id->encoder);

        if( transcode_encoder_open( id->encoder, id->p_enccfg ) != VLC_SUCCESS )
            goto error;
    }

    const es_format_t *encoder_fmt = transcode_encoder_format_in( id->encoder );

    if( !video_format_IsSimilar(&encoder_fmt->video, &out_fmt->video) )
    {
        filter_owner_t chain_owner = {
           .video = &transcode_filter_video_cbs,
           .sys = id,
        };

        if ( !id->p_final_conv_static )
            id->p_final_conv_static =
               filter_chain_NewVideo( p_owner->p_stream, false, &chain_owner );
         filter_chain_Reset( id->p_final_conv_static,
               out_fmt,
               enc_vctx,
               encoder_fmt);
         if( filter_chain_AppendConverter( id->p_final_conv_static, NULL ) != VLC_SUCCESS )
             goto error;
    }
    vlc_mutex_unlock(&id->fifo.lock);

    if( !id->downstream_id )
        id->downstream_id =
            id->pf_transcode_downstream_add( p_owner->p_stream,
                                             id->p_decoder->fmt_in,
                                             transcode_encoder_format_out( id->encoder ) );
    msg_Info( p_dec, "video format update succeed" );

end:
    return VLC_SUCCESS;

<<<<<<< HEAD
error:
    transcode_remove_filters( &id->p_final_conv_static );

    if( transcode_encoder_opened( id->encoder ) )
        transcode_encoder_close( id->encoder );

    transcode_remove_filters( &id->p_uf_chain );
    transcode_remove_filters( &id->p_f_chain );

    vlc_mutex_unlock( &id->fifo.lock );

    return VLC_EGENERIC;
}

static picture_t *video_new_buffer_encoder( transcode_encoder_t *p_enc )
{
    return picture_NewFromFormat( &transcode_encoder_format_in( p_enc )->video );
}

static int transcode_process_picture( sout_stream_id_sys_t *id,
                                      picture_t *p_pic, block_t **out);
=======
/* Take care of the scaling and chroma conversions. */
static int conversion_video_filter_append( sout_stream_id_sys_t *id,
                                           picture_t *p_pic )
{
    const video_format_t *p_vid_out = video_output_format( id, p_pic );

    if( ( p_vid_out->i_chroma != id->p_encoder->fmt_in.video.i_chroma ) ||
        ( p_vid_out->i_width != id->p_encoder->fmt_in.video.i_width ) ||
        ( p_vid_out->i_height != id->p_encoder->fmt_in.video.i_height ) )
    {
        es_format_t fmt_out;
        es_format_Init( &fmt_out, VIDEO_ES, p_vid_out->i_chroma );
        fmt_out.video = *p_vid_out;
        return filter_chain_AppendConverter( id->p_uf_chain ? id->p_uf_chain : id->p_f_chain,
                                             &fmt_out, &id->p_encoder->fmt_in );
    }
    return VLC_SUCCESS;
}

static void transcode_video_framerate_init( sout_stream_t *p_stream,
                                            sout_stream_id_sys_t *id,
                                            const video_format_t *p_vid_out )
{
    /* Handle frame rate conversion */
    if( !id->p_encoder->fmt_out.video.i_frame_rate ||
        !id->p_encoder->fmt_out.video.i_frame_rate_base )
    {
        if( p_vid_out->i_frame_rate &&
            p_vid_out->i_frame_rate_base )
        {
            id->p_encoder->fmt_out.video.i_frame_rate =
                p_vid_out->i_frame_rate;
            id->p_encoder->fmt_out.video.i_frame_rate_base =
                p_vid_out->i_frame_rate_base;
        }
        else
        {
            /* Pick a sensible default value */
            id->p_encoder->fmt_out.video.i_frame_rate = ENC_FRAMERATE;
            id->p_encoder->fmt_out.video.i_frame_rate_base = ENC_FRAMERATE_BASE;
        }
    }

    id->p_encoder->fmt_in.video.i_frame_rate =
        id->p_encoder->fmt_out.video.i_frame_rate;
    id->p_encoder->fmt_in.video.i_frame_rate_base =
        id->p_encoder->fmt_out.video.i_frame_rate_base;

    vlc_ureduce( &id->p_encoder->fmt_in.video.i_frame_rate,
        &id->p_encoder->fmt_in.video.i_frame_rate_base,
        id->p_encoder->fmt_in.video.i_frame_rate,
        id->p_encoder->fmt_in.video.i_frame_rate_base,
        0 );
     msg_Dbg( p_stream, "source fps %u/%u, destination %u/%u",
        id->p_decoder->fmt_out.video.i_frame_rate,
        id->p_decoder->fmt_out.video.i_frame_rate_base,
        id->p_encoder->fmt_in.video.i_frame_rate,
        id->p_encoder->fmt_in.video.i_frame_rate_base );
}

static void transcode_video_size_init( sout_stream_t *p_stream,
                                     sout_stream_id_sys_t *id,
                                     const video_format_t *p_vid_out )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;

    /* Calculate scaling
     * width/height of source */
    int i_src_visible_width = p_vid_out->i_visible_width;
    int i_src_visible_height = p_vid_out->i_visible_height;

    if (i_src_visible_width == 0)
        i_src_visible_width = p_vid_out->i_width;
    if (i_src_visible_height == 0)
        i_src_visible_height = p_vid_out->i_height;
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

static void decoder_queue_video( decoder_t *p_dec, picture_t *p_pic )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    sout_stream_id_sys_t *id = p_owner->id;

    block_t *p_block = NULL;
    int ret = transcode_process_picture( id, p_pic, &p_block );

<<<<<<< HEAD
    if( p_block == NULL )
        return;
=======
    /* aspect ratio */
    float f_aspect = (double)p_vid_out->i_sar_num *
                     p_vid_out->i_width /
                     p_vid_out->i_sar_den /
                     p_vid_out->i_height;
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

    vlc_fifo_Lock( id->output_fifo );
    id->b_error |= ret != VLC_SUCCESS;
    if( id->b_error )
    {
        vlc_fifo_Unlock( id->output_fifo );
        block_ChainRelease( p_block );
        return;
    }

    vlc_fifo_QueueUnlocked( id->output_fifo, p_block );
    vlc_fifo_Unlock( id->output_fifo );
}

int transcode_video_init( sout_stream_t *p_stream, const es_format_t *p_fmt,
                          sout_stream_id_sys_t *id )
{
    msg_Dbg( p_stream,
             "creating video transcoding from fcc=`%4.4s' to fcc=`%4.4s'",
             (char*)&p_fmt->i_codec, (char*)&id->p_enccfg->i_codec );

    vlc_picture_chain_Init( &id->fifo.pic );
    id->output_fifo = block_FifoNew();
    if( id->output_fifo == NULL )
        return VLC_ENOMEM;

    id->b_transcode = true;
    es_format_Init( &id->decoder_out, VIDEO_ES, 0 );

    /* Open decoder
     */
    dec_get_owner( id->p_decoder )->id = id;

    static const struct decoder_owner_callbacks dec_cbs =
    {
<<<<<<< HEAD
        .video = {
            .get_device = video_get_decoder_device,
            .format_update = video_update_format_decoder,
            .queue = decoder_queue_video,
        },
    };
    id->p_decoder->cbs = &dec_cbs;

    id->p_decoder->pf_decode = NULL;
    id->p_decoder->pf_get_cc = NULL;

    id->p_decoder->p_module =
        module_need_var( id->p_decoder, "video decoder", "codec" );
=======
        /* Only width specified */
        f_scale_width = (float)id->p_encoder->fmt_out.video.i_visible_width/i_src_visible_width;
        f_scale_height = f_scale_width;
    }
    else if( id->p_encoder->fmt_out.video.i_visible_width <= 0 &&
             id->p_encoder->fmt_out.video.i_visible_height > 0 )
    {
         /* Only height specified */
         f_scale_height = (float)id->p_encoder->fmt_out.video.i_visible_height/i_src_visible_height;
         f_scale_width = f_scale_height;
     }
     else if( id->p_encoder->fmt_out.video.i_visible_width > 0 &&
              id->p_encoder->fmt_out.video.i_visible_height > 0 )
     {
         /* Width and height specified */
         f_scale_width = (float)id->p_encoder->fmt_out.video.i_visible_width/i_src_visible_width;
         f_scale_height = (float)id->p_encoder->fmt_out.video.i_visible_height/i_src_visible_height;
     }

     /* check maxwidth and maxheight */
     if( p_sys->i_maxwidth && f_scale_width > (float)p_sys->i_maxwidth /
                                                     i_src_visible_width )
     {
         f_scale_width = (float)p_sys->i_maxwidth / i_src_visible_width;
     }

     if( p_sys->i_maxheight && f_scale_height > (float)p_sys->i_maxheight /
                                                       i_src_visible_height )
     {
         f_scale_height = (float)p_sys->i_maxheight / i_src_visible_height;
     }


     /* Change aspect ratio from source pixel to scaled pixel */
     f_aspect = f_aspect * f_scale_height / f_scale_width;
     msg_Dbg( p_stream, "scaled pixel aspect is %f:1", f_aspect );

     /* f_scale_width and f_scale_height are now final */
     /* Calculate width, height from scaling
      * Make sure its multiple of 2
      */
     /* width/height of output stream */
     int i_dst_visible_width =  lroundf(f_scale_width*i_src_visible_width);
     int i_dst_visible_height = lroundf(f_scale_height*i_src_visible_height);
     int i_dst_width =  lroundf(f_scale_width*p_vid_out->i_width);
     int i_dst_height = lroundf(f_scale_height*p_vid_out->i_height);

     if( i_dst_visible_width & 1 ) ++i_dst_visible_width;
     if( i_dst_visible_height & 1 ) ++i_dst_visible_height;
     if( i_dst_width & 1 ) ++i_dst_width;
     if( i_dst_height & 1 ) ++i_dst_height;

     /* Store calculated values */
     id->p_encoder->fmt_out.video.i_width = i_dst_width;
     id->p_encoder->fmt_out.video.i_visible_width = i_dst_visible_width;
     id->p_encoder->fmt_out.video.i_height = i_dst_height;
     id->p_encoder->fmt_out.video.i_visible_height = i_dst_visible_height;

     id->p_encoder->fmt_in.video.i_width = i_dst_width;
     id->p_encoder->fmt_in.video.i_visible_width = i_dst_visible_width;
     id->p_encoder->fmt_in.video.i_height = i_dst_height;
     id->p_encoder->fmt_in.video.i_visible_height = i_dst_visible_height;

     msg_Dbg( p_stream, "source %ix%i, destination %ix%i",
         i_src_visible_width, i_src_visible_height,
         i_dst_visible_width, i_dst_visible_height
     );
}

static void transcode_video_sar_init( sout_stream_t *p_stream,
                                     sout_stream_id_sys_t *id,
                                     const video_format_t *p_vid_out )
{
    int i_src_visible_width = p_vid_out->i_visible_width;
    int i_src_visible_height = p_vid_out->i_visible_height;

    if (i_src_visible_width == 0)
        i_src_visible_width = p_vid_out->i_width;
    if (i_src_visible_height == 0)
        i_src_visible_height = p_vid_out->i_height;
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

    if( !id->p_decoder->p_module )
    {
<<<<<<< HEAD
        msg_Err( p_stream, "cannot find video decoder" );
        es_format_Clean( &id->decoder_out );
        return VLC_EGENERIC;
=======
        vlc_ureduce( &id->p_encoder->fmt_out.video.i_sar_num,
                     &id->p_encoder->fmt_out.video.i_sar_den,
                     (uint64_t)p_vid_out->i_sar_num * id->p_encoder->fmt_out.video.i_width * p_vid_out->i_height,
                     (uint64_t)p_vid_out->i_sar_den * id->p_encoder->fmt_out.video.i_height * p_vid_out->i_width,
                     0 );
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
    }
    if( id->decoder_out.i_codec == 0 ) /* format_update can happen on open() */
    {
        es_format_Clean( &id->decoder_out );
        es_format_Copy( &id->decoder_out, &id->p_decoder->fmt_out );
    }

<<<<<<< HEAD
    return VLC_SUCCESS;
=======
    id->p_encoder->fmt_in.video.i_sar_num =
        id->p_encoder->fmt_out.video.i_sar_num;
    id->p_encoder->fmt_in.video.i_sar_den =
        id->p_encoder->fmt_out.video.i_sar_den;

    msg_Dbg( p_stream, "encoder aspect is %i:%i",
             id->p_encoder->fmt_out.video.i_sar_num * id->p_encoder->fmt_out.video.i_width,
             id->p_encoder->fmt_out.video.i_sar_den * id->p_encoder->fmt_out.video.i_height );

}

static void transcode_video_encoder_init( sout_stream_t *p_stream,
                                          sout_stream_id_sys_t *id,
                                          picture_t *p_pic )
{
    const video_format_t *p_vid_out = video_output_format( id, p_pic );

    id->p_encoder->fmt_in.video.orientation =
        id->p_encoder->fmt_out.video.orientation =
        id->p_decoder->fmt_in.video.orientation;

    transcode_video_framerate_init( p_stream, id, p_vid_out );

    transcode_video_size_init( p_stream, id, p_vid_out );
    transcode_video_sar_init( p_stream, id, p_vid_out );

    msg_Dbg( p_stream, "source chroma: %4.4s, destination %4.4s",
             (const char *)&id->p_decoder->fmt_out.video.i_chroma,
             (const char *)&id->p_encoder->fmt_in.video.i_chroma);
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
}

static int transcode_video_filters_init( sout_stream_t *p_stream,
                                         const sout_filters_config_t *p_cfg,
                                         const es_format_t *p_src,
                                         vlc_video_context *src_ctx,
                                         const es_format_t *p_dst,
                                         sout_stream_id_sys_t *id )
{
    /* Build chain */
    filter_owner_t owner = {
        .video = &transcode_filter_video_cbs,
        .sys = id,
    };
    id->p_f_chain = filter_chain_NewVideo( p_stream, false, &owner );
    if( !id->p_f_chain )
        return VLC_EGENERIC;
    filter_chain_Reset( id->p_f_chain, p_src, src_ctx, p_src );

    /* Deinterlace */
    if( p_cfg->video.psz_deinterlace != NULL )
    {
        filter_chain_AppendFilter( id->p_f_chain,
                                   p_cfg->video.psz_deinterlace,
                                   p_cfg->video.p_deinterlace_cfg,
                                   p_src );
        p_src = filter_chain_GetFmtOut( id->p_f_chain );
        src_ctx = filter_chain_GetVideoCtxOut( id->p_f_chain );
    }

    if( id->p_enccfg->video.fps.num > 0 &&
        id->p_enccfg->video.fps.den > 0 &&
      ( id->p_enccfg->video.fps.num != p_src->video.i_frame_rate ||
        id->p_enccfg->video.fps.den != p_src->video.i_frame_rate_base ) )
    {
        es_format_t dst;
        es_format_Copy(&dst, p_src);
        dst.video.i_frame_rate = id->p_enccfg->video.fps.num;
        dst.video.i_frame_rate_base = id->p_enccfg->video.fps.den;
        filter_chain_AppendFilter( id->p_f_chain, "fps", NULL, &dst );
        p_src = filter_chain_GetFmtOut( id->p_f_chain );
        src_ctx = filter_chain_GetVideoCtxOut( id->p_f_chain );
        es_format_Clean(&dst);
    }

    /* User filters */
    if( p_cfg->psz_filters )
    {
        msg_Dbg( p_stream, "adding user filters" );
        id->p_uf_chain = filter_chain_NewVideo( p_stream, true, &owner );
        if(!id->p_uf_chain)
            return VLC_EGENERIC;
        filter_chain_Reset( id->p_uf_chain, p_src, src_ctx, p_dst );
        filter_chain_AppendFromString( id->p_uf_chain, p_cfg->psz_filters );
        p_src = filter_chain_GetFmtOut( id->p_uf_chain );
        debug_format( VLC_OBJECT(p_stream), p_src );
   }

    /* Update encoder so it matches filters output */
    transcode_encoder_update_format_in( id->encoder, p_src, id->p_enccfg );

    /* SPU Sources */
    if( p_cfg->video.psz_spu_sources )
    {
        if( id->p_spu || (id->p_spu = spu_Create( p_stream, NULL )) )
            spu_ChangeSources( id->p_spu, p_cfg->video.psz_spu_sources );
    }

    return VLC_SUCCESS;
}

void transcode_video_clean( sout_stream_id_sys_t *id )
{
    /* Close encoder, but only if one was opened. */
    if ( id->encoder )
        transcode_encoder_delete( id->encoder );

    es_format_Clean( &id->decoder_out );

    /* Close filters */
    transcode_remove_filters( &id->p_f_chain );
    transcode_remove_filters( &id->p_uf_chain );
    transcode_remove_filters( &id->p_final_conv_static );
    if( id->p_spu_blender )
        filter_DeleteBlend( id->p_spu_blender );
    if( id->p_spu )
        spu_Destroy( id->p_spu );
    if ( id->dec_dev )
        vlc_decoder_device_Release( id->dec_dev );

    block_FifoRelease(id->output_fifo);
}

void transcode_video_push_spu( sout_stream_t *p_stream, sout_stream_id_sys_t *id,
                               subpicture_t *p_subpicture )
{
    if( !id->p_spu )
        id->p_spu = spu_Create( p_stream, NULL );
    if( !id->p_spu )
        subpicture_Delete( p_subpicture );
    else
        spu_PutSubpicture( id->p_spu, p_subpicture );
}

int transcode_video_get_output_dimensions( sout_stream_id_sys_t *id,
                                           unsigned *w, unsigned *h )
{
    vlc_mutex_lock( &id->fifo.lock );
    *w = id->decoder_out.video.i_visible_width;
    *h = id->decoder_out.video.i_visible_height;
    vlc_mutex_unlock( &id->fifo.lock );
    return (*w && *h) ? VLC_SUCCESS : VLC_EGENERIC;
}

static picture_t * RenderSubpictures( sout_stream_id_sys_t *id, picture_t *p_pic )
{
    if( !id->p_spu )
        return p_pic;

    /* Check if we have a subpicture to overlay */
    video_format_t fmt, outfmt;
    vlc_mutex_lock( &id->fifo.lock );
    video_format_Copy( &outfmt, &id->decoder_out.video );
    vlc_mutex_unlock( &id->fifo.lock );
    video_format_Copy( &fmt, &p_pic->format );
    if( fmt.i_visible_width <= 0 || fmt.i_visible_height <= 0 )
    {
        fmt.i_visible_width  = fmt.i_width;
        fmt.i_visible_height = fmt.i_height;
        fmt.i_x_offset       = 0;
        fmt.i_y_offset       = 0;
    }

    subpicture_t *p_subpic = spu_Render( id->p_spu, NULL, &fmt,
                                         &outfmt, vlc_tick_now(), p_pic->date,
                                         false, false );

    /* Overlay subpicture */
    if( p_subpic )
    {
        if( filter_chain_IsEmpty( id->p_f_chain ) )
        {
            /* We can't modify the picture, we need to duplicate it,
                 * in this point the picture is already p_encoder->fmt.in format*/
            picture_t *p_tmp = video_new_buffer_encoder( id->encoder );
            if( likely( p_tmp ) )
            {
                picture_Copy( p_tmp, p_pic );
                picture_Release( p_pic );
                p_pic = p_tmp;
            }
        }
        if( unlikely( !id->p_spu_blender ) )
            id->p_spu_blender = filter_NewBlend( VLC_OBJECT( id->p_spu ), &fmt );
        if( likely( id->p_spu_blender ) )
            picture_BlendSubpicture( p_pic, id->p_spu_blender, p_subpic );
        subpicture_Delete( p_subpic );
    }
    video_format_Clean( &fmt );
    video_format_Clean( &outfmt );

    return p_pic;
}

static void tag_last_block_with_flag( block_t **out, int i_flag )
{
    block_t *p_last = *out;
    if( p_last )
    {
        while( p_last->p_next )
            p_last = p_last->p_next;
        p_last->i_flags |= i_flag;
    }
}

static int transcode_process_picture( sout_stream_id_sys_t *id,
                                      picture_t *p_pic, block_t **out)
{
<<<<<<< HEAD
    /* Run the filter and output chains; first with the picture,
     * and then with NULL as many times as we need until they
     * stop outputting frames.
     */
    for ( picture_t *p_in = p_pic ;; p_in = NULL /* drain second time */ )
    {
        /* Run filter chain */
        if( id->p_f_chain )
            p_in = filter_chain_VideoFilter( id->p_f_chain, p_in );
=======
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    *out = NULL;

    int ret = id->p_decoder->pf_decode( id->p_decoder, in );
    if( ret != VLCDEC_SUCCESS )
        return VLC_EGENERIC;

    picture_t *p_pics = transcode_dequeue_all_pics( id );
    if( p_pics == NULL )
        goto end;

    do
    {
        picture_t *p_pic = p_pics;
        p_pics = p_pics->p_next;
        p_pic->p_next = NULL;

        if( id->b_error )
        {
            picture_Release( p_pic );
            continue;
        }

        if( unlikely (
             id->p_encoder->p_module && p_pic &&
             !video_format_IsSimilar( &id->fmt_input_video, &p_pic->format )
            )
          )
        {
            msg_Info( p_stream, "aspect-ratio changed, reiniting. %i -> %i : %i -> %i.",
                        id->fmt_input_video.i_sar_num, p_pic->format.i_sar_num,
                        id->fmt_input_video.i_sar_den, p_pic->format.i_sar_den
                    );
            /* Close filters */
            if( id->p_f_chain )
                filter_chain_Delete( id->p_f_chain );
            id->p_f_chain = NULL;
            if( id->p_uf_chain )
                filter_chain_Delete( id->p_uf_chain );
            id->p_uf_chain = NULL;

            /* Reinitialize filters */
            id->p_encoder->fmt_out.video.i_visible_width  = p_sys->i_width & ~1;
            id->p_encoder->fmt_out.video.i_visible_height = p_sys->i_height & ~1;
            id->p_encoder->fmt_out.video.i_sar_num = id->p_encoder->fmt_out.video.i_sar_den = 0;

            transcode_video_encoder_init( p_stream, id, p_pic );
            transcode_video_filter_init( p_stream, id );
            if( conversion_video_filter_append( id, p_pic ) != VLC_SUCCESS )
                goto error;
            memcpy( &id->fmt_input_video, &p_pic->format, sizeof(video_format_t));
        }
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

        if( !p_in )
            break;

<<<<<<< HEAD
        for( ;; p_in = NULL /* drain second time */ )
        {
            /* Run user specified filter chain */
            filter_chain_t * secondary_chains[] = { id->p_uf_chain,
                                                    id->p_final_conv_static };
            for( size_t i=0; i<ARRAY_SIZE(secondary_chains); i++ )
            {
                if( !secondary_chains[i] )
                    continue;
                p_in = filter_chain_VideoFilter( secondary_chains[i], p_in );
            }
=======
        if( unlikely( !id->p_encoder->p_module && p_pic ) )
        {
            if( id->p_f_chain )
                filter_chain_Delete( id->p_f_chain );
            if( id->p_uf_chain )
                filter_chain_Delete( id->p_uf_chain );
            id->p_f_chain = id->p_uf_chain = NULL;

            transcode_video_encoder_init( p_stream, id, p_pic );
            transcode_video_filter_init( p_stream, id );
            if( conversion_video_filter_append( id, p_pic ) != VLC_SUCCESS )
                goto error;
            memcpy( &id->fmt_input_video, &p_pic->format, sizeof(video_format_t));

            if( transcode_video_encoder_open( p_stream, id ) != VLC_SUCCESS )
                goto error;
        }
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

            if( !p_in )
                break;

<<<<<<< HEAD
            /* Blend subpictures */
            p_in = RenderSubpictures( id, p_in );

            if( p_in )
=======
            for ( ;; ) {
                picture_t *p_user_filtered_pic = p_filtered_pic;

                /* Run user specified filter chain */
                if( id->p_uf_chain )
                    p_user_filtered_pic = filter_chain_VideoFilter( id->p_uf_chain, p_user_filtered_pic );
                if( !p_user_filtered_pic )
                    break;

                OutputFrame( p_stream, p_user_filtered_pic, id, out );

                p_filtered_pic = NULL;
            }

            p_pic = NULL;
        }
        continue;
error:
        if( p_pic )
            picture_Release( p_pic );
        id->b_error = true;
    } while( p_pics );

    if( p_sys->i_threads >= 1 )
    {
        /* Pick up any return data the encoder thread wants to output. */
        vlc_mutex_lock( &p_sys->lock_out );
        *out = p_sys->p_buffers;
        p_sys->p_buffers = NULL;
        vlc_mutex_unlock( &p_sys->lock_out );
    }

end:
    /* Drain encoder */
    if( unlikely( !id->b_error && in == NULL ) )
    {
        if( p_sys->i_threads == 0 )
        {
            if( id->p_encoder->p_module )
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
            {
                /* If a packetizer is used, multiple blocks might be returned, in w */
                block_t *p_encoded = transcode_encoder_encode( id->encoder, p_in );
                picture_Release( p_in );
                block_ChainAppend( out, p_encoded );
            }
        }
    }

<<<<<<< HEAD
    return VLC_SUCCESS;
=======
    return id->b_error ? VLC_EGENERIC : VLC_SUCCESS;
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
}

int transcode_video_process( sout_stream_t *p_stream, sout_stream_id_sys_t *id,
                                    block_t *in, block_t **out )
{
    *out = NULL;

    bool b_eos = in && (in->i_flags & BLOCK_FLAG_END_OF_SEQUENCE);

<<<<<<< HEAD
    int ret = id->p_decoder->pf_decode( id->p_decoder, in );
    if( ret != VLCDEC_SUCCESS )
        return VLC_EGENERIC;
=======
    id->fifo.pic.first = NULL;
    id->fifo.pic.last = &id->fifo.pic.first;
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

    /*
     * Encoder creation depends on decoder's update_format which is only
     * created once a few frames have been passed to the decoder.
     */
    if( id->encoder == NULL )
        return VLC_SUCCESS;

    vlc_fifo_Lock( id->output_fifo );
    if( unlikely( !id->b_error && in == NULL ) && transcode_encoder_opened( id->encoder ) )
    {
        msg_Dbg( p_stream, "Flushing thread and waiting that");
        if( transcode_encoder_drain( id->encoder, out ) == VLC_SUCCESS )
            msg_Dbg( p_stream, "Flushing done");
        else
            msg_Warn( p_stream, "Flushing failed");
    }
    bool has_error = id->b_error;
    if( !has_error )
    {
        vlc_frame_t *pendings = vlc_fifo_DequeueAllUnlocked( id->output_fifo );
        block_ChainAppend(out, pendings);
    }
    vlc_fifo_Unlock( id->output_fifo );

    if( b_eos )
        tag_last_block_with_flag( out, BLOCK_FLAG_END_OF_SEQUENCE );

    return has_error ? VLC_EGENERIC : VLC_SUCCESS;
}
