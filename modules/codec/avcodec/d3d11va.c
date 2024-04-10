/*****************************************************************************
 * d3d11va.c: Direct3D11 Video Acceleration decoder
 *****************************************************************************
 * Copyright © 2009 Geoffroy Couprie
 * Copyright © 2009 Laurent Aimar
 * Copyright © 2015 Steve Lhomme
 * Copyright © 2015 VideoLabs
 *
 * Authors: Geoffroy Couprie <geal@videolan.org>
 *          Laurent Aimar <fenrir _AT_ videolan _DOT_ org>
 *          Steve Lhomme <robux4@gmail.com>
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

/**
  * See https://msdn.microsoft.com/en-us/library/windows/desktop/hh162912%28v=vs.85%29.aspx
  **/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

# undef WINAPI_FAMILY
# define WINAPI_FAMILY WINAPI_FAMILY_DESKTOP_APP

#include <assert.h>

#include <vlc_common.h>
#include <vlc_picture.h>
#include <vlc_plugin.h>
#include <vlc_charset.h>
#include <vlc_codec.h>

#define COBJMACROS
#include <initguid.h>
#include <d3d11.h>
#include <libavcodec/d3d11va.h>

#include "../../video_chroma/d3d11_fmt.h"

struct d3d11va_pic_context
{
    struct d3d11_pic_context  ctx;
    struct vlc_va_surface_t   *va_surface;
};

#define D3D11VA_PICCONTEXT_FROM_PICCTX(pic_ctx)  \
    container_of((pic_ctx), struct d3d11va_pic_context, ctx.s)

#include "directx_va.h"

static int Open(vlc_va_t *, AVCodecContext *, enum AVPixelFormat hwfmt, const AVPixFmtDescriptor *,
                const es_format_t *, vlc_decoder_device *, video_format_t *, vlc_video_context **);

vlc_module_begin()
    set_description(N_("Direct3D11 Video Acceleration"))
    set_subcategory(SUBCAT_INPUT_VCODEC)
    set_va_callback(Open, 110)
vlc_module_end()

typedef struct
{
    d3d11_device_t               *d3d_dev;

<<<<<<< master
    vlc_video_context            *vctx;

    const d3d_format_t           *render_fmt;
=======
    /* pool */
    picture_t                    *extern_pics[MAX_SURFACE_COUNT];
>>>>>>> origin/3.0.x

    /* Video decoder */
    D3D11_VIDEO_DECODER_CONFIG   cfg;
    const directx_va_mode_t      *selected_decoder;
    ID3D11VideoDevice            *d3ddec;

    /* avcodec internals */
    struct AVD3D11VAContext      hw;

    /* pool */
    va_pool_t                     *va_pool;
    ID3D11VideoDecoderOutputView  *hw_surface[MAX_SURFACE_COUNT];
    ID3D11ShaderResourceView      *renderSrc[MAX_SURFACE_COUNT * DXGI_MAX_SHADER_VIEW];
} vlc_va_sys_t;

/* */
static int D3dCreateDevice(vlc_va_t *);

static int DxGetInputList(vlc_va_t *, input_list_t *);
static int DxSetupOutput(vlc_va_t *, const directx_va_mode_t *, const video_format_t *);

static int DxCreateDecoderSurfaces(vlc_va_t *, int codec_id,
                                   const video_format_t *fmt, size_t surface_count);
static void DxDestroySurfaces(void *);

static void SetupAVCodecContext(void *opaque, AVCodecContext *avctx)
{
    vlc_va_sys_t *sys = opaque;
    sys->hw.cfg = &sys->cfg;
<<<<<<< master
    sys->hw.surface = sys->hw_surface;
    sys->hw.context_mutex = sys->d3d_dev->context_mutex;
    sys->hw.workaround = sys->selected_decoder->workaround;
    avctx->hwaccel_context = &sys->hw;
=======
    sys->hw.surface_count = dx_sys->va_pool.surface_count;
    sys->hw.surface = dx_sys->hw_surface;
    sys->hw.context_mutex = sys->d3d_dev.context_mutex;

    if (IsEqualGUID(&dx_sys->input, &DXVA_Intel_H264_NoFGT_ClearVideo))
        sys->hw.workaround |= FF_DXVA2_WORKAROUND_INTEL_CLEARVIDEO;
>>>>>>> origin/3.0.x
}

static void d3d11va_pic_context_destroy(picture_context_t *ctx)
{
    struct d3d11va_pic_context *pic_ctx = D3D11VA_PICCONTEXT_FROM_PICCTX(ctx);
    struct vlc_va_surface_t *va_surface = pic_ctx->va_surface;
    static_assert(offsetof(struct d3d11va_pic_context, ctx.s) == 0,
        "Cast assumption failure");
    d3d11_pic_context_destroy(ctx);
    va_surface_Release(va_surface);
}

static picture_context_t *d3d11va_pic_context_copy(picture_context_t *ctx)
{
    struct d3d11va_pic_context *src_ctx = D3D11VA_PICCONTEXT_FROM_PICCTX(ctx);
    struct d3d11va_pic_context *pic_ctx = malloc(sizeof(*pic_ctx));
    if (unlikely(pic_ctx==NULL))
        return NULL;
    *pic_ctx = *src_ctx;
    vlc_video_context_Hold(pic_ctx->ctx.s.vctx);
    va_surface_AddRef(pic_ctx->va_surface);
    for (int i=0;i<DXGI_MAX_SHADER_VIEW; i++)
    {
        pic_ctx->ctx.picsys.resource[i]  = src_ctx->ctx.picsys.resource[i];
        pic_ctx->ctx.picsys.renderSrc[i] = src_ctx->ctx.picsys.renderSrc[i];
    }
    AcquireD3D11PictureSys(&pic_ctx->ctx.picsys);
    return &pic_ctx->ctx.s;
}

static struct d3d11va_pic_context *CreatePicContext(
                                                  UINT slice,
                                                  ID3D11ShaderResourceView *renderSrc[DXGI_MAX_SHADER_VIEW],
                                                  vlc_video_context *vctx)
{
    struct d3d11va_pic_context *pic_ctx = calloc(1, sizeof(*pic_ctx));
    if (unlikely(pic_ctx==NULL))
        return NULL;
    pic_ctx->ctx.s = (picture_context_t) {
        d3d11va_pic_context_destroy, d3d11va_pic_context_copy,
        vlc_video_context_Hold(vctx),
    };

    ID3D11Resource *p_resource;
    ID3D11ShaderResourceView_GetResource(renderSrc[0], &p_resource);

    pic_ctx->ctx.picsys.slice_index = slice;
    pic_ctx->ctx.picsys.sharedHandle = INVALID_HANDLE_VALUE;
    for (int i=0;i<DXGI_MAX_SHADER_VIEW; i++)
    {
        pic_ctx->ctx.picsys.resource[i] = p_resource;
        pic_ctx->ctx.picsys.renderSrc[i] = renderSrc[i];
    }
    AcquireD3D11PictureSys(&pic_ctx->ctx.picsys);
    ID3D11Resource_Release(p_resource);
    return pic_ctx;
}

static picture_context_t* NewSurfacePicContext(vlc_va_t *va, vlc_va_surface_t *va_surface)
{
    vlc_va_sys_t *sys = va->sys;
    ID3D11VideoDecoderOutputView *surface = sys->hw_surface[va_surface_GetIndex(va_surface)];
    ID3D11ShaderResourceView *resourceView[DXGI_MAX_SHADER_VIEW];

    D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC viewDesc;
    ID3D11VideoDecoderOutputView_GetDesc(surface, &viewDesc);

    for (size_t i=0; i<DXGI_MAX_SHADER_VIEW; i++)
        resourceView[i] = sys->renderSrc[viewDesc.Texture2D.ArraySlice*DXGI_MAX_SHADER_VIEW + i];

    struct d3d11va_pic_context *pic_ctx = CreatePicContext(
                                                  viewDesc.Texture2D.ArraySlice,
                                                  resourceView, sys->vctx);
    if (unlikely(pic_ctx==NULL))
        return NULL;
    pic_ctx->va_surface = va_surface;
    return &pic_ctx->ctx.s;
}

static int Get(vlc_va_t *va, picture_t *pic, AVCodecContext *ctx, AVFrame *frame)
{
    (void) ctx;

    vlc_va_sys_t *sys = va->sys;
    vlc_va_surface_t *va_surface = va_pool_Get(sys->va_pool);
    if (unlikely(va_surface == NULL))
        return VLC_ENOENT;
    pic->context = NewSurfacePicContext(va, va_surface);
    if (unlikely(pic->context == NULL))
    {
        va_surface_Release(va_surface);
        return VLC_ENOMEM;
    }
    frame->data[3] = (uint8_t*)sys->hw_surface[va_surface_GetIndex(va_surface)];
    return VLC_SUCCESS;
}

static void Close(vlc_va_t *va, AVCodecContext* ctx)
{
    vlc_va_sys_t *sys = va->sys;

    if (sys->vctx)
        vlc_video_context_Release(sys->vctx);

    if (sys->va_pool)
        va_pool_Close(sys->va_pool);

    if (ctx)
        ctx->hwaccel_context = NULL;
}

static const struct vlc_va_operations ops = { Get, Close, };

static int Open(vlc_va_t *va, AVCodecContext *ctx, enum AVPixelFormat hwfmt, const AVPixFmtDescriptor *desc,
                const es_format_t *fmt_in, vlc_decoder_device *dec_device,
                video_format_t *fmt_out, vlc_video_context **vtcx_out)
{
    int err = VLC_EGENERIC;

    ctx->hwaccel_context = NULL;

    if ( hwfmt != AV_PIX_FMT_D3D11VA_VLD )
        return VLC_EGENERIC;

    d3d11_decoder_device_t *devsys = GetD3D11OpaqueDevice( dec_device );
    if ( devsys == NULL )
        return VLC_EGENERIC;

<<<<<<< master
    if (!(ID3D11Device_GetCreationFlags(devsys->d3d_dev.d3ddevice) & D3D11_CREATE_DEVICE_VIDEO_SUPPORT))
    {
        msg_Err(va, "Missing D3D11_CREATE_DEVICE_VIDEO_SUPPORT");
        return VLC_EGENERIC;
    }
=======
#if !VLC_WINSTORE_APP
    /* Allow using D3D11VA automatically starting from Windows 8.1 */
    if (!va->obj.force)
    {
        bool isWin81OrGreater = false;
        HMODULE hKernel32 = GetModuleHandle(TEXT("kernel32.dll"));
        if (likely(hKernel32 != NULL))
            isWin81OrGreater = GetProcAddress(hKernel32, "IsProcessCritical") != NULL;
        if (!isWin81OrGreater)
            return VLC_EGENERIC;
    }
#endif
>>>>>>> origin/3.0.x

    vlc_va_sys_t *sys = calloc(1, sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    va->sys = sys;

<<<<<<< master
    sys->render_fmt = NULL;
    sys->d3d_dev = &devsys->d3d_dev;
    if (sys->d3d_dev->context_mutex == INVALID_HANDLE_VALUE)
        msg_Warn(va, "No mutex found to lock the decoder");

    struct va_pool_cfg pool_cfg = {
        D3dCreateDevice,
        DxDestroySurfaces,
        DxCreateDecoderSurfaces,
        SetupAVCodecContext,
        sys,
    };

    sys->va_pool = va_pool_Create(va, &pool_cfg);
    if (sys->va_pool == NULL)
    {
        err = VLC_EGENERIC;
=======
    sys->d3d_dev.d3ddevice = NULL;
    va->sys->render = DXGI_FORMAT_UNKNOWN;
    if ( p_sys != NULL && p_sys->context != NULL ) {
        void *d3dvidctx = NULL;
        HRESULT hr = ID3D11DeviceContext_QueryInterface(p_sys->context, &IID_ID3D11VideoContext, &d3dvidctx);
        if (FAILED(hr)) {
           msg_Err(va, "Could not Query ID3D11VideoContext Interface from the picture. (hr=0x%lX)", hr);
        } else {
            ID3D11DeviceContext_GetDevice( p_sys->context, &sys->d3d_dev.d3ddevice );
            HANDLE context_lock = INVALID_HANDLE_VALUE;
            UINT dataSize = sizeof(context_lock);
            hr = ID3D11DeviceContext_GetPrivateData(p_sys->context, &GUID_CONTEXT_MUTEX, &dataSize, &context_lock);
            if (FAILED(hr))
                msg_Warn(va, "No mutex found to lock the decoder");
            sys->d3d_dev.context_mutex = context_lock;

            sys->d3d_dev.d3dcontext = p_sys->context;
            sys->d3d_dev.owner = false;
            D3D11_GetDriverVersion(va, &sys->d3d_dev);
            sys->d3dvidctx = d3dvidctx;

            assert(p_sys->texture[KNOWN_DXGI_INDEX] != NULL);
            D3D11_TEXTURE2D_DESC dstDesc;
            ID3D11Texture2D_GetDesc( p_sys->texture[KNOWN_DXGI_INDEX], &dstDesc);
            sys->render = dstDesc.Format;
            if (dstDesc.BindFlags & D3D11_BIND_DECODER)
            {
                va->sys->textureWidth = dstDesc.Width;
                va->sys->textureHeight = dstDesc.Height;
                va->sys->totalTextureSlices = dstDesc.ArraySize;
            }
        }
    }

    err = D3D11_Create( va, &sys->hd3d, false );
    if (err != VLC_SUCCESS)
>>>>>>> origin/3.0.x
        goto error;
    }

    video_format_t final_fmt = *fmt_out;
    static const directx_sys_t dx_sys = { DxGetInputList, DxSetupOutput };
    sys->selected_decoder = directx_va_Setup(va, &dx_sys, ctx, desc, fmt_in, isXboxHardware(sys->d3d_dev),
                                             &final_fmt, &sys->hw.surface_count);
    if (sys->selected_decoder == NULL)
    {
        err = VLC_EGENERIC;
        goto error;
    }

<<<<<<< master
    final_fmt.i_chroma = sys->render_fmt->fourcc;
    err = va_pool_SetupDecoder(va, sys->va_pool, ctx, &final_fmt, sys->hw.surface_count);
=======
    err = directx_va_Setup(va, &sys->dx_sys, ctx, fmt, isXboxHardware(sys->d3d_dev.d3ddevice));
>>>>>>> origin/3.0.x
    if (err != VLC_SUCCESS)
        goto error;

    msg_Info(va, "Using D3D11VA (%ls, vendor %x(%s), device %x, revision %x)",
                sys->d3d_dev->adapterDesc.Description,
                sys->d3d_dev->adapterDesc.VendorId, DxgiVendorStr(sys->d3d_dev->adapterDesc.VendorId),
                sys->d3d_dev->adapterDesc.DeviceId, sys->d3d_dev->adapterDesc.Revision);

    sys->vctx = D3D11CreateVideoContext(dec_device, sys->render_fmt->formatTexture);
    if (sys->vctx == NULL)
    {
        msg_Dbg(va, "no video context");
        err = VLC_EGENERIC;
        goto error;
    }

    va->ops = &ops;
    *fmt_out = final_fmt;
    *vtcx_out = sys->vctx;
    return VLC_SUCCESS;

error:
    Close(va, ctx);
    return err;
}

/**
 * It creates a Direct3D device usable for decoding
 */
static int D3dCreateDevice(vlc_va_t *va)
{
    vlc_va_sys_t *sys = va->sys;
    HRESULT hr;

<<<<<<< master
    assert(sys->d3d_dev->d3ddevice && sys->d3d_dev->d3dcontext);
=======
    if (sys->d3d_dev.d3ddevice && sys->d3d_dev.d3dcontext) {
        msg_Dbg(va, "Reusing Direct3D11 device");
        ID3D11DeviceContext_AddRef(sys->d3d_dev.d3dcontext);
        return VLC_SUCCESS;
    }

    sys->d3d_dev.d3dcontext = (void*)var_InheritInteger(va, "winrt-d3dcontext");
    if (unlikely(sys->d3d_dev.d3dcontext))
    {
        ID3D11DeviceContext_GetDevice(sys->d3d_dev.d3dcontext, &sys->d3d_dev.d3ddevice);
        ID3D11DeviceContext_AddRef(sys->d3d_dev.d3dcontext);
        ID3D11Device_Release(sys->d3d_dev.d3ddevice);
    }

    /* */
    if (likely(!sys->d3d_dev.d3ddevice))
    {
        hr = D3D11_CreateDevice(va, &sys->hd3d, true, &sys->d3d_dev);
        if (FAILED(hr)) {
            msg_Err(va, "D3D11CreateDevice failed. (hr=0x%lX)", hr);
            return VLC_EGENERIC;
        }
    }

>>>>>>> origin/3.0.x
    void *d3dvidctx = NULL;
    hr = ID3D11DeviceContext_QueryInterface(sys->d3d_dev->d3dcontext, &IID_ID3D11VideoContext, &d3dvidctx);
    if (FAILED(hr)) {
       msg_Err(va, "Could not Query ID3D11VideoContext Interface. (hr=0x%lX)", hr);
       ID3D11DeviceContext_Release(sys->d3d_dev.d3dcontext);
       ID3D11Device_Release(sys->d3d_dev.d3ddevice);
       return VLC_EGENERIC;
    }
<<<<<<< master
    sys->hw.video_context = d3dvidctx;
=======
    sys->d3dvidctx = d3dvidctx;

    return VLC_SUCCESS;
}

/**
 * It releases a Direct3D device and its resources.
 */
static void D3dDestroyDevice(vlc_va_t *va)
{
    vlc_va_sys_t *sys = va->sys;
    if (sys->d3dvidctx)
        ID3D11VideoContext_Release(sys->d3dvidctx);
    D3D11_ReleaseDevice( &sys->d3d_dev );
}

/**
 * It describes our Direct3D object
 */
static char *DxDescribe(vlc_va_sys_t *sys)
{

    IDXGIAdapter *p_adapter = D3D11DeviceAdapter(sys->d3d_dev.d3ddevice);
    if (!p_adapter) {
       return NULL;
    }

    char *description = NULL;
    DXGI_ADAPTER_DESC adapterDesc;
    if (SUCCEEDED(IDXGIAdapter_GetDesc(p_adapter, &adapterDesc))) {
        char *utfdesc = FromWide(adapterDesc.Description);
        if (likely(utfdesc!=NULL))
        {
            if (asprintf(&description, "D3D11VA (%s, vendor %x(%s), device %x, revision %x)",
                         utfdesc,
                         adapterDesc.VendorId, DxgiVendorStr(adapterDesc.VendorId), adapterDesc.DeviceId, adapterDesc.Revision) < 0)
                description = NULL;
            free(utfdesc);
        }
    }

    IDXGIAdapter_Release(p_adapter);
    return description;
}

/**
 * It creates a DirectX video service
 */
static int DxCreateVideoService(vlc_va_t *va)
{
    directx_sys_t *dx_sys = &va->sys->dx_sys;
>>>>>>> origin/3.0.x

    void *d3dviddev = NULL;
    hr = ID3D11Device_QueryInterface(sys->d3d_dev->d3ddevice, &IID_ID3D11VideoDevice, &d3dviddev);
    if (FAILED(hr)) {
       msg_Err(va, "Could not Query ID3D11VideoDevice Interface. (hr=0x%lX)", hr);
       ID3D11VideoContext_Release(sys->hw.video_context);
       return VLC_EGENERIC;
    }
    sys->d3ddec = d3dviddev;

    return VLC_SUCCESS;
}

static void ReleaseInputList(input_list_t *p_list)
{
    free(p_list->list);
}

static int DxGetInputList(vlc_va_t *va, input_list_t *p_list)
{
    vlc_va_sys_t *sys = va->sys;
    HRESULT hr;

    UINT input_count = ID3D11VideoDevice_GetVideoDecoderProfileCount(sys->d3ddec);

    p_list->count = input_count;
    p_list->list = calloc(input_count, sizeof(*p_list->list));
    if (unlikely(p_list->list == NULL)) {
        return VLC_ENOMEM;
    }
    p_list->pf_release = ReleaseInputList;

    for (unsigned i = 0; i < input_count; i++) {
        hr = ID3D11VideoDevice_GetVideoDecoderProfile(sys->d3ddec, i, &p_list->list[i]);
        if (FAILED(hr))
        {
            msg_Err(va, "GetVideoDecoderProfile %d failed. (hr=0x%lX)", i, hr);
            ReleaseInputList(p_list);
            return VLC_EGENERIC;
        }
    }

    return VLC_SUCCESS;
}

<<<<<<< master
static const d3d_format_t *D3D11_FindDXGIFormat(DXGI_FORMAT dxgi)
{
    for (const d3d_format_t *output_format = DxgiGetRenderFormatList();
         output_format->name != NULL; ++output_format)
    {
        if (output_format->formatTexture == dxgi &&
                is_d3d11_opaque(output_format->fourcc))
        {
            return output_format;
        }
    }
    return NULL;
}

static int DxSetupOutput(vlc_va_t *va, const directx_va_mode_t *mode, const video_format_t *fmt)
=======
extern const GUID DXVA_ModeHEVC_VLD_Main10;
extern const GUID DXVA_ModeVP9_VLD_10bit_Profile2;

static int DxSetupOutput(vlc_va_t *va, const GUID *input, const video_format_t *fmt)
>>>>>>> origin/3.0.x
{
    vlc_va_sys_t *sys = va->sys;
    HRESULT hr;

#ifndef NDEBUG
    BOOL bSupported = false;
    for (int format = 0; format < 188; format++) {
        hr = ID3D11VideoDevice_CheckVideoDecoderFormat(sys->d3ddec, mode->guid, format, &bSupported);
        if (SUCCEEDED(hr) && bSupported)
            msg_Dbg(va, "format %s is supported for output", DxgiFormatToStr(format));
    }
#endif

<<<<<<< master
    if (!directx_va_canUseDecoder(va, sys->d3d_dev->adapterDesc.VendorId, sys->d3d_dev->adapterDesc.DeviceId,
                                  mode->guid, sys->d3d_dev->WDDM.build))
    {
        msg_Warn(va, "GPU blocklisted for %s codec", mode->name);
        return VLC_EGENERIC;
    }

    const d3d_format_t *processorInput[4];
    int idx = 0;
    const d3d_format_t *decoder_format;
    UINT supportFlags = D3D11_FORMAT_SUPPORT_DECODER_OUTPUT | D3D11_FORMAT_SUPPORT_SHADER_LOAD;
    decoder_format = FindD3D11Format( va, sys->d3d_dev, 0, DXGI_RGB_FORMAT|DXGI_YUV_FORMAT,
                                      mode->bit_depth, mode->log2_chroma_h+1, mode->log2_chroma_w+1,
                                      DXGI_CHROMA_GPU, supportFlags );
    if (decoder_format == NULL)
        decoder_format = FindD3D11Format( va, sys->d3d_dev, 0, DXGI_RGB_FORMAT|DXGI_YUV_FORMAT,
                                        mode->bit_depth, 0, 0, DXGI_CHROMA_GPU, supportFlags );
    if (decoder_format == NULL && mode->bit_depth > 10)
        decoder_format = FindD3D11Format( va, sys->d3d_dev, 0, DXGI_RGB_FORMAT|DXGI_YUV_FORMAT,
                                        10, 0, 0, DXGI_CHROMA_GPU, supportFlags );
    if (decoder_format == NULL)
        decoder_format = FindD3D11Format( va, sys->d3d_dev, 0, DXGI_RGB_FORMAT|DXGI_YUV_FORMAT,
                                        0, 0, 0, DXGI_CHROMA_GPU, supportFlags );
    if (decoder_format != NULL)
    {
        msg_Dbg(va, "favor decoder format %s", decoder_format->name);
        processorInput[idx++] = decoder_format;
    }

    if (decoder_format == NULL || decoder_format->formatTexture != DXGI_FORMAT_NV12)
        processorInput[idx++] = D3D11_FindDXGIFormat(DXGI_FORMAT_NV12);
    processorInput[idx++] = D3D11_FindDXGIFormat(DXGI_FORMAT_420_OPAQUE);
    processorInput[idx++] = NULL;

=======
    IDXGIAdapter *pAdapter = D3D11DeviceAdapter(sys->d3d_dev.d3ddevice);
    if (!pAdapter)
        return VLC_EGENERIC;

    DXGI_ADAPTER_DESC adapterDesc;
    hr = IDXGIAdapter_GetDesc(pAdapter, &adapterDesc);
    IDXGIAdapter_Release(pAdapter);
    if (FAILED(hr))
        return VLC_EGENERIC;

    char *psz_decoder_name = directx_va_GetDecoderName(input);

    if (!directx_va_canUseDecoder(va, adapterDesc.VendorId, adapterDesc.DeviceId,
                                  input, sys->d3d_dev.WDDM.build))
    {
        msg_Warn(va, "GPU blacklisted for %s codec", psz_decoder_name);
        free(psz_decoder_name);
        return VLC_EGENERIC;
    }

    DXGI_FORMAT processorInput[5];
    int idx = 0;
    if ( sys->render != DXGI_FORMAT_UNKNOWN )
        processorInput[idx++] = sys->render;
    if (IsEqualGUID(input, &DXVA_ModeHEVC_VLD_Main10) || IsEqualGUID(input, &DXVA_ModeVP9_VLD_10bit_Profile2))
        processorInput[idx++] = DXGI_FORMAT_P010;
    processorInput[idx++] = DXGI_FORMAT_NV12;
    processorInput[idx++] = DXGI_FORMAT_420_OPAQUE;
    processorInput[idx++] = DXGI_FORMAT_UNKNOWN;

>>>>>>> origin/3.0.x
    /* */
    for (idx = 0; processorInput[idx] != NULL; ++idx)
    {
        BOOL is_supported = false;
        hr = ID3D11VideoDevice_CheckVideoDecoderFormat(sys->d3ddec, mode->guid, processorInput[idx]->formatTexture, &is_supported);
        if (SUCCEEDED(hr) && is_supported)
            msg_Dbg(va, "%s output is supported for decoder %s.", DxgiFormatToStr(processorInput[idx]->formatTexture), mode->name);
        else
        {
            msg_Dbg(va, "Can't get a decoder output format %s for decoder %s.", DxgiFormatToStr(processorInput[idx]->formatTexture), mode->name);
            continue;
        }

       // check if we can create render texture of that format
       // check the decoder can output to that format
       if ( !D3D11_DeviceSupportsFormat(sys->d3d_dev, processorInput[idx]->formatTexture,
                                  D3D11_FORMAT_SUPPORT_SHADER_LOAD) )
       {
#ifndef ID3D11VideoContext_VideoProcessorBlt
           msg_Dbg(va, "Format %s needs a processor but is not supported",
                   DxgiFormatToStr(processorInput[idx]->formatTexture));
#else
           if ( !D3D11_DeviceSupportsFormat(sys->d3d_dev, processorInput[idx]->formatTexture,
                                      D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_INPUT) )
           {
               msg_Dbg(va, "Format %s needs a processor but is not available",
                       DxgiFormatToStr(processorInput[idx]->formatTexture));
               continue;
           }
#endif
        }

        D3D11_VIDEO_DECODER_DESC decoderDesc;
        ZeroMemory(&decoderDesc, sizeof(decoderDesc));
        decoderDesc.Guid = *mode->guid;
        decoderDesc.SampleWidth = fmt->i_width;
        decoderDesc.SampleHeight = fmt->i_height;
        decoderDesc.OutputFormat = processorInput[idx]->formatTexture;

        UINT cfg_count = 0;
        hr = ID3D11VideoDevice_GetVideoDecoderConfigCount( sys->d3ddec, &decoderDesc, &cfg_count );
        if (FAILED(hr))
        {
            msg_Err( va, "Failed to get configuration for decoder %s. (hr=0x%lX)", mode->name, hr );
            continue;
        }
        if (cfg_count == 0) {
            msg_Err( va, "No decoder configuration possible for %s %dx%d",
                     DxgiFormatToStr(decoderDesc.OutputFormat),
                     decoderDesc.SampleWidth, decoderDesc.SampleHeight );
            continue;
        }

<<<<<<< master
        msg_Dbg(va, "Using output format %s for decoder %s", DxgiFormatToStr(processorInput[idx]->formatTexture), mode->name);
        sys->render_fmt = processorInput[idx];
=======
        msg_Dbg(va, "Using output format %s for decoder %s", DxgiFormatToStr(processorInput[idx]), psz_decoder_name);
        if ( sys->render == processorInput[idx] && sys->totalTextureSlices > 4)
        {
            if (CanUseVoutPool(&sys->d3d_dev, sys->totalTextureSlices))
                dx_sys->can_extern_pool = true;
            else
                msg_Warn( va, "use internal pool" );
        }
        sys->render = processorInput[idx];
        free(psz_decoder_name);
>>>>>>> origin/3.0.x
        return VLC_SUCCESS;
    }

    msg_Dbg(va, "Output format from picture source not supported.");
    return VLC_EGENERIC;
}

static bool CanUseDecoderPadding(const vlc_va_sys_t *sys)
{
    /* Qualcomm hardware has issues with textures and pixels that should not be
    * part of the decoded area */
<<<<<<< master
    return sys->d3d_dev->adapterDesc.VendorId != GPU_MANUFACTURER_QUALCOMM;
=======
    return adapterDesc.VendorId != GPU_MANUFACTURER_QUALCOMM;
>>>>>>> origin/3.0.x
}

/**
 * It creates a Direct3D11 decoder using the given video format
 */
static int DxCreateDecoderSurfaces(vlc_va_t *va, int codec_id,
                                   const video_format_t *fmt, size_t surface_count)
{
    vlc_va_sys_t *sys = va->sys;
    HRESULT hr;

    void *pv;
    hr = ID3D11Device_QueryInterface( sys->d3d_dev->d3ddevice, &IID_ID3D10Multithread, &pv);
    if (SUCCEEDED(hr)) {
        ID3D10Multithread *pMultithread = pv;
        ID3D10Multithread_SetMultithreadProtected(pMultithread, TRUE);
        ID3D10Multithread_Release(pMultithread);
    }

<<<<<<< master
#ifdef VLC_WINSTORE_APP
    /* On the Xbox 1/S, any decoding of H264 with one dimension over 2304
     * crashes totally the device */
    if (codec_id == AV_CODEC_ID_H264 &&
        (fmt->i_width > 2304 || fmt->i_height > 2304) &&
        isXboxHardware(sys->d3d_dev))
=======
    if (!sys->textureWidth || !sys->textureHeight)
    {
        sys->textureWidth  = fmt->i_width;
        sys->textureHeight = fmt->i_height;
    }

    if ((sys->textureWidth != fmt->i_width || sys->textureHeight != fmt->i_height) &&
        !CanUseDecoderPadding(sys))
    {
        msg_Dbg(va, "mismatching external pool sizes use the internal one %dx%d vs %dx%d",
                sys->textureWidth, sys->textureHeight, fmt->i_width, fmt->i_height);
        dx_sys->can_extern_pool = false;
        sys->textureWidth  = fmt->i_width;
        sys->textureHeight = fmt->i_height;
    }
    if (sys->totalTextureSlices && sys->totalTextureSlices < surface_count)
    {
        msg_Warn(va, "not enough decoding slices in the texture (%d/%d)",
                 sys->totalTextureSlices, surface_count);
        dx_sys->can_extern_pool = false;
    }
#if VLC_WINSTORE_APP
    /* On the Xbox 1/S, any decoding of H264 with one dimension over 2304
     * crashes totally the device */
    if (codec_id == AV_CODEC_ID_H264 &&
        (sys->textureWidth > 2304 || sys->textureHeight > 2304) &&
        isXboxHardware(sys->d3d_dev.d3ddevice))
>>>>>>> origin/3.0.x
    {
        msg_Warn(va, "%dx%d resolution not supported by your hardware", fmt->i_width, fmt->i_height);
        return VLC_EGENERIC;
    }
#endif

    D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC viewDesc;
    ZeroMemory(&viewDesc, sizeof(viewDesc));
    viewDesc.DecodeProfile = *sys->selected_decoder->guid;
    viewDesc.ViewDimension = D3D11_VDOV_DIMENSION_TEXTURE2D;

    D3D11_TEXTURE2D_DESC texDesc;
    ZeroMemory(&texDesc, sizeof(texDesc));
    texDesc.Width = fmt->i_width;
    texDesc.Height = fmt->i_height;
    texDesc.MipLevels = 1;
    texDesc.Format = sys->render_fmt->formatTexture;
    texDesc.SampleDesc.Count = 1;
    texDesc.MiscFlags = 0;
    texDesc.ArraySize = surface_count;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_DECODER;
    texDesc.CPUAccessFlags = 0;

    if (D3D11_DeviceSupportsFormat(sys->d3d_dev, texDesc.Format, D3D11_FORMAT_SUPPORT_SHADER_LOAD))
        texDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    ID3D11Texture2D *p_texture;
    hr = ID3D11Device_CreateTexture2D( sys->d3d_dev->d3ddevice, &texDesc, NULL, &p_texture );
    if (FAILED(hr)) {
        msg_Err(va, "CreateTexture2D %zu failed. (hr=0x%lX)", surface_count, hr);
        return VLC_EGENERIC;
    }

<<<<<<< master
    unsigned surface_idx;
    for (surface_idx = 0; surface_idx < surface_count; surface_idx++) {
        viewDesc.Texture2D.ArraySlice = surface_idx;
=======
    if (dx_sys->can_extern_pool)
    {
#if !D3D11_DIRECT_DECODE
        size_t surface_idx;
        for (surface_idx = 0; surface_idx < surface_count; surface_idx++) {
            picture_t *pic = decoder_NewPicture( (decoder_t*) va->obj.parent );
            sys->extern_pics[surface_idx] = pic;
            dx_sys->hw_surface[surface_idx] = NULL;
            if (pic==NULL)
            {
                msg_Warn(va, "not enough decoder pictures %d out of %d", surface_idx, surface_count);
                dx_sys->can_extern_pool = false;
                break;
            }

            D3D11_TEXTURE2D_DESC texDesc;
            ID3D11Texture2D_GetDesc(pic->p_sys->texture[KNOWN_DXGI_INDEX], &texDesc);
            assert(texDesc.Format == sys->render);
            assert(texDesc.BindFlags & D3D11_BIND_DECODER);

#if !LIBAVCODEC_VERSION_CHECK( 57, 27, 2, 61, 102 )
            if (pic->p_sys->slice_index != surface_idx)
            {
                msg_Warn(va, "d3d11va requires decoding slices to be the first in the texture (%d/%d)",
                         pic->p_sys->slice_index, surface_idx);
                dx_sys->can_extern_pool = false;
                break;
            }
#endif

            viewDesc.Texture2D.ArraySlice = pic->p_sys->slice_index;
            hr = ID3D11VideoDevice_CreateVideoDecoderOutputView( dx_sys->d3ddec,
                                                                 pic->p_sys->resource[KNOWN_DXGI_INDEX],
                                                                 &viewDesc,
                                                                 &pic->p_sys->decoder );
            if (FAILED(hr)) {
                msg_Warn(va, "CreateVideoDecoderOutputView %d failed. (hr=0x%0lx)", surface_idx, hr);
                dx_sys->can_extern_pool = false;
                break;
            }

            D3D11_AllocateShaderView(va, sys->d3d_dev.d3ddevice, textureFmt, pic->p_sys->texture, pic->p_sys->slice_index, pic->p_sys->resourceView);

            dx_sys->hw_surface[surface_idx] = pic->p_sys->decoder;
        }

        if (!dx_sys->can_extern_pool)
        {
            for (size_t i = 0; i < surface_idx; ++i)
            {
                if (dx_sys->hw_surface[i])
                {
                    ID3D11VideoDecoderOutputView_Release(dx_sys->hw_surface[i]);
                    dx_sys->hw_surface[i] = NULL;
                }
                if (sys->extern_pics[i])
                {
                    sys->extern_pics[i]->p_sys->decoder = NULL;
                    picture_Release(sys->extern_pics[i]);
                    sys->extern_pics[i] = NULL;
                }
            }
        }
        else
#endif
            msg_Dbg(va, "using external surface pool");
    }
>>>>>>> origin/3.0.x

        hr = ID3D11VideoDevice_CreateVideoDecoderOutputView( sys->d3ddec,
                                                                (ID3D11Resource*) p_texture,
                                                                &viewDesc,
                                                                &sys->hw_surface[surface_idx] );
        if (FAILED(hr)) {
            msg_Err(va, "CreateVideoDecoderOutputView %d failed. (hr=0x%lX)", surface_idx, hr);
            ID3D11Texture2D_Release(p_texture);
            return VLC_EGENERIC;
        }

<<<<<<< master
        if (texDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
        {
            ID3D11Texture2D *textures[DXGI_MAX_SHADER_VIEW] = {p_texture, p_texture, p_texture};
            D3D11_AllocateResourceView(vlc_object_logger(va), sys->d3d_dev->d3ddevice, sys->render_fmt, textures, surface_idx,
                                &sys->renderSrc[surface_idx * DXGI_MAX_SHADER_VIEW]);
=======
        unsigned surface_idx;
        for (surface_idx = 0; surface_idx < surface_count; surface_idx++) {
            sys->extern_pics[surface_idx] = NULL;
            viewDesc.Texture2D.ArraySlice = surface_idx;

            hr = ID3D11VideoDevice_CreateVideoDecoderOutputView( dx_sys->d3ddec,
                                                                 (ID3D11Resource*) p_texture,
                                                                 &viewDesc,
                                                                 &dx_sys->hw_surface[surface_idx] );
            if (FAILED(hr)) {
                msg_Err(va, "CreateVideoDecoderOutputView %d failed. (hr=0x%0lx)", surface_idx, hr);
                ID3D11Texture2D_Release(p_texture);
                return VLC_EGENERIC;
            }

            if (texDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
            {
                ID3D11Texture2D *textures[D3D11_MAX_SHADER_VIEW] = {p_texture, p_texture, p_texture};
                D3D11_AllocateShaderView(va, sys->d3d_dev.d3ddevice, textureFmt, textures, surface_idx,
                                   &sys->resourceView[surface_idx * D3D11_MAX_SHADER_VIEW]);
            }
>>>>>>> origin/3.0.x
        }
    }
    ID3D11Texture2D_Release(p_texture);
    msg_Dbg(va, "ID3D11VideoDecoderOutputView succeed with %zu surfaces (%dx%d)",
            surface_count, fmt->i_width, fmt->i_height);

    D3D11_VIDEO_DECODER_DESC decoderDesc;
    ZeroMemory(&decoderDesc, sizeof(decoderDesc));
    decoderDesc.Guid = *sys->selected_decoder->guid;
    decoderDesc.SampleWidth = fmt->i_width;
    decoderDesc.SampleHeight = fmt->i_height;
    decoderDesc.OutputFormat = sys->render_fmt->formatTexture;

    UINT cfg_count;
    hr = ID3D11VideoDevice_GetVideoDecoderConfigCount( sys->d3ddec, &decoderDesc, &cfg_count );
    if (FAILED(hr)) {
        msg_Err(va, "GetVideoDecoderConfigCount failed. (hr=0x%lX)", hr);
        return VLC_EGENERIC;
    }

    /* List all configurations available for the decoder */
    D3D11_VIDEO_DECODER_CONFIG cfg_list[cfg_count];
    for (unsigned i = 0; i < cfg_count; i++) {
        hr = ID3D11VideoDevice_GetVideoDecoderConfig( sys->d3ddec, &decoderDesc, i, &cfg_list[i] );
        if (FAILED(hr)) {
            msg_Err(va, "GetVideoDecoderConfig failed. (hr=0x%lX)", hr);
            return VLC_EGENERIC;
        }
    }

    msg_Dbg(va, "we got %d decoder configurations", cfg_count);

    /* Select the best decoder configuration */
    int cfg_score = 0;
    for (unsigned i = 0; i < cfg_count; i++) {
        const D3D11_VIDEO_DECODER_CONFIG *cfg = &cfg_list[i];

        /* */
        msg_Dbg(va, "configuration[%d] ConfigBitstreamRaw %d",
                i, cfg->ConfigBitstreamRaw);

        /* */
        int score;
        if (cfg->ConfigBitstreamRaw == 1)
            score = 1;
        else if (codec_id == AV_CODEC_ID_H264 && cfg->ConfigBitstreamRaw == 2)
            score = 2;
        else
            continue;
        if (IsEqualGUID(&cfg->guidConfigBitstreamEncryption, &DXVA_NoEncrypt))
            score += 16;

        if (cfg_score < score) {
            sys->cfg = *cfg;
            cfg_score = score;
        }
    }
    if (cfg_score <= 0) {
        msg_Err(va, "Failed to find a supported decoder configuration");
        return VLC_EGENERIC;
    }

    /* Create the decoder */
    ID3D11VideoDecoder *decoder;
    hr = ID3D11VideoDevice_CreateVideoDecoder( sys->d3ddec, &decoderDesc, &sys->cfg, &decoder );
    if (FAILED(hr)) {
        msg_Err(va, "ID3D11VideoDevice_CreateVideoDecoder failed. (hr=0x%lX)", hr);
        sys->hw.decoder = NULL;
        return VLC_EGENERIC;
    }
    sys->hw.decoder = decoder;

    msg_Dbg(va, "DxCreateDecoderSurfaces succeed");
    return VLC_SUCCESS;
}

static void DxDestroySurfaces(void *opaque)
{
    vlc_va_sys_t *sys = opaque;
    if (sys->hw.decoder)
        ID3D11VideoDecoder_Release(sys->hw.decoder);
    if (sys->hw_surface[0]) {
        for (unsigned i = 0; i < sys->hw.surface_count; i++)
        {
            for (int j = 0; j < DXGI_MAX_SHADER_VIEW; j++)
            {
                if (sys->renderSrc[i*DXGI_MAX_SHADER_VIEW + j])
                    ID3D11ShaderResourceView_Release(sys->renderSrc[i*DXGI_MAX_SHADER_VIEW + j]);
            }
            ID3D11VideoDecoderOutputView_Release( sys->hw_surface[i] );
        }
    }

    if (sys->d3ddec)
        ID3D11VideoDevice_Release(sys->d3ddec);
    if (sys->hw.video_context)
        ID3D11VideoContext_Release(sys->hw.video_context);

    free(sys);
}
