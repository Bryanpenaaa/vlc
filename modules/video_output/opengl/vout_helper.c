/*****************************************************************************
 * vout_helper.c: OpenGL and OpenGL ES output common code
 *****************************************************************************
 * Copyright (C) 2004-2016 VLC authors and VideoLAN
 * Copyright (C) 2009, 2011 Laurent Aimar
 *
 * Authors: Laurent Aimar <fenrir _AT_ videolan _DOT_ org>
 *          Ilkka Ollakka <ileoo@videolan.org>
 *          Rémi Denis-Courmont
 *          Adrien Maglo <magsoft at videolan dot org>
 *          Felix Paul Kühne <fkuehne at videolan dot org>
 *          Pierre d'Herbemont <pdherbemont at videolan dot org>
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

#include <assert.h>
#include <math.h>

#include <vlc_common.h>
#include <vlc_list.h>
#include <vlc_subpicture.h>
#include <vlc_opengl.h>
#include <vlc_modules.h>
#include <vlc_vout.h>
#include <vlc_viewpoint.h>

<<<<<<< HEAD
#include "filters.h"
#include "gl_api.h"
#include "gl_util.h"
#include "vout_helper.h"
#include "renderer.h"
#include "sub_renderer.h"
=======
#include "vout_helper.h"
#include "internal.h"

#ifndef GL_CLAMP_TO_EDGE
# define GL_CLAMP_TO_EDGE 0x812F
#endif

#define SPHERE_RADIUS 1.f

/* FIXME: GL_ASSERT_NOERROR disabled for now because:
 * Proper GL error handling need to be implemented
 * glClear(GL_COLOR_BUFFER_BIT) throws a GL_INVALID_FRAMEBUFFER_OPERATION on macOS
 * assert fails on vout_display_opengl_Delete on iOS
 */
#if 0
# define HAVE_GL_ASSERT_NOERROR
#endif

#ifdef HAVE_GL_ASSERT_NOERROR
# define GL_ASSERT_NOERROR() do { \
    GLenum glError = vgl->vt.GetError(); \
    switch (glError) \
    { \
        case GL_NO_ERROR: break; \
        case GL_INVALID_ENUM: assert(!"GL_INVALID_ENUM"); \
        case GL_INVALID_VALUE: assert(!"GL_INVALID_VALUE"); \
        case GL_INVALID_OPERATION: assert(!"GL_INVALID_OPERATION"); \
        case GL_INVALID_FRAMEBUFFER_OPERATION: assert(!"GL_INVALID_FRAMEBUFFER_OPERATION"); \
        case GL_OUT_OF_MEMORY: assert(!"GL_OUT_OF_MEMORY"); \
        default: assert(!"GL_UNKNOWN_ERROR"); \
    } \
} while(0)
#else
# define GL_ASSERT_NOERROR()
#endif

typedef struct {
    GLuint   texture;
    GLsizei  width;
    GLsizei  height;

    float    alpha;

    float    top;
    float    left;
    float    bottom;
    float    right;

    float    tex_width;
    float    tex_height;
} gl_region_t;

struct prgm
{
    GLuint id;
    opengl_tex_converter_t *tc;

    struct {
        GLfloat OrientationMatrix[16];
        GLfloat ProjectionMatrix[16];
        GLfloat ZRotMatrix[16];
        GLfloat YRotMatrix[16];
        GLfloat XRotMatrix[16];
        GLfloat ZoomMatrix[16];
    } var;

    struct { /* UniformLocation */
        GLint OrientationMatrix;
        GLint ProjectionMatrix;
        GLint ZRotMatrix;
        GLint YRotMatrix;
        GLint XRotMatrix;
        GLint ZoomMatrix;
    } uloc;
    struct { /* AttribLocation */
        GLint MultiTexCoord[3];
        GLint VertexPosition;
    } aloc;
};
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

struct vout_display_opengl_t {

    vlc_gl_t   *gl;
    struct vlc_gl_api api;

    struct vlc_gl_interop *interop;
    struct vlc_gl_renderer *renderer; /**< weak reference */

    struct vlc_gl_filters *filters;

    struct vlc_gl_interop *sub_interop;
    struct vlc_gl_sub_renderer *sub_renderer;
};

static const vlc_fourcc_t gl_subpicture_chromas[] = {
    VLC_CODEC_RGBA,
    0
};

static void
ResizeFormatToGLMaxTexSize(video_format_t *fmt, unsigned int max_tex_size)
{
    if (fmt->i_width > fmt->i_height)
    {
        unsigned int const  vis_w = fmt->i_visible_width;
        unsigned int const  vis_h = fmt->i_visible_height;
        unsigned int const  nw_w = max_tex_size;
        unsigned int const  nw_vis_w = nw_w * vis_w / fmt->i_width;

        fmt->i_height = nw_w * fmt->i_height / fmt->i_width;
        fmt->i_width = nw_w;
        fmt->i_visible_height = nw_vis_w * vis_h / vis_w;
        fmt->i_visible_width = nw_vis_w;
    }
<<<<<<< HEAD
    else
    {
        unsigned int const  vis_w = fmt->i_visible_width;
        unsigned int const  vis_h = fmt->i_visible_height;
        unsigned int const  nw_h = max_tex_size;
        unsigned int const  nw_vis_h = nw_h * vis_h / fmt->i_height;

        fmt->i_width = nw_h * fmt->i_width / fmt->i_height;
        fmt->i_height = nw_h;
        fmt->i_visible_width = nw_vis_h * vis_w / vis_h;
        fmt->i_visible_height = nw_vis_h;
    }
=======
}

static inline GLsizei GetAlignedSize(unsigned size)
{
    /* Return the smallest larger or equal power of 2 */
    unsigned align = 1 << (8 * sizeof (unsigned) - clz(size));
    return ((align >> 1) == size) ? size : align;
}

static GLuint BuildVertexShader(const opengl_tex_converter_t *tc,
                                unsigned plane_count)
{
    /* Basic vertex shader */
    static const char *template =
        "#version %u\n"
        "varying vec2 TexCoord0;\n"
        "attribute vec4 MultiTexCoord0;\n"
        "%s%s"
        "attribute vec3 VertexPosition;\n"
        "uniform mat4 OrientationMatrix;\n"
        "uniform mat4 ProjectionMatrix;\n"
        "uniform mat4 XRotMatrix;\n"
        "uniform mat4 YRotMatrix;\n"
        "uniform mat4 ZRotMatrix;\n"
        "uniform mat4 ZoomMatrix;\n"
        "void main() {\n"
        " TexCoord0 = vec4(OrientationMatrix * MultiTexCoord0).st;\n"
        "%s%s"
        " gl_Position = ProjectionMatrix * ZoomMatrix * ZRotMatrix * XRotMatrix * YRotMatrix * vec4(VertexPosition, 1.0);\n"
        "}";

    const char *coord1_header = plane_count > 1 ?
        "varying vec2 TexCoord1;\nattribute vec4 MultiTexCoord1;\n" : "";
    const char *coord1_code = plane_count > 1 ?
        " TexCoord1 = vec4(OrientationMatrix * MultiTexCoord1).st;\n" : "";
    const char *coord2_header = plane_count > 2 ?
        "varying vec2 TexCoord2;\nattribute vec4 MultiTexCoord2;\n" : "";
    const char *coord2_code = plane_count > 2 ?
        " TexCoord2 = vec4(OrientationMatrix * MultiTexCoord2).st;\n" : "";

    char *code;
    if (asprintf(&code, template, tc->glsl_version, coord1_header, coord2_header,
                 coord1_code, coord2_code) < 0)
        return 0;

    GLuint shader = tc->vt->CreateShader(GL_VERTEX_SHADER);
    tc->vt->ShaderSource(shader, 1, (const char **) &code, NULL);
    if (tc->b_dump_shaders)
        msg_Dbg(tc->gl, "\n=== Vertex shader for fourcc: %4.4s ===\n%s\n",
                (const char *)&tc->fmt.i_chroma, code);
    tc->vt->CompileShader(shader);
    free(code);
    return shader;
}

static int
GenTextures(const opengl_tex_converter_t *tc,
            const GLsizei *tex_width, const GLsizei *tex_height,
            GLuint *textures)
{
    tc->vt->GenTextures(tc->tex_count, textures);

    for (unsigned i = 0; i < tc->tex_count; i++)
    {
        tc->vt->BindTexture(tc->tex_target, textures[i]);

#if !defined(USE_OPENGL_ES2)
        /* Set the texture parameters */
        tc->vt->TexParameterf(tc->tex_target, GL_TEXTURE_PRIORITY, 1.0);
        tc->vt->TexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
#endif

        tc->vt->TexParameteri(tc->tex_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        tc->vt->TexParameteri(tc->tex_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        tc->vt->TexParameteri(tc->tex_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        tc->vt->TexParameteri(tc->tex_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    if (tc->pf_allocate_textures != NULL)
    {
        int ret = tc->pf_allocate_textures(tc, textures, tex_width, tex_height);
        if (ret != VLC_SUCCESS)
        {
            tc->vt->DeleteTextures(tc->tex_count, textures);
            memset(textures, 0, tc->tex_count * sizeof(GLuint));
            return ret;
        }
    }
    return VLC_SUCCESS;
}

static void
DelTextures(const opengl_tex_converter_t *tc, GLuint *textures)
{
    tc->vt->DeleteTextures(tc->tex_count, textures);
    memset(textures, 0, tc->tex_count * sizeof(GLuint));
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
}

static struct vlc_gl_filters *
CreateFilters(vlc_gl_t *gl, const struct vlc_gl_api *api,
              struct vlc_gl_interop *interop,
              struct vlc_gl_renderer **out_renderer)
{
    struct vlc_gl_filters *filters = vlc_gl_filters_New(gl, api, interop);
    if (!filters)
    {
        msg_Err(gl, "Could not create filters");
        return NULL;
    }

    const opengl_vtable_t *vt = &api->vt;
    const video_format_t *fmt_in = &interop->fmt_in;

    int upscaler = var_InheritInteger(gl, "gl-upscaler");
    int downscaler = var_InheritInteger(gl, "gl-downscaler");
    int has_dovi = fmt_in->dovi.rpu_present && !fmt_in->dovi.el_present; /* can't handle EL yet */

    if (upscaler || downscaler || has_dovi)
    {
<<<<<<< HEAD
        char upscaler_value[12];
        char downscaler_value[12];
=======
        tc->pl_ctx = pl_context_create(PL_API_VER, &(struct pl_context_params) {
            .log_cb    = log_cb,
            .log_priv  = tc,
            .log_level = PL_LOG_INFO,
        });
        if (tc->pl_ctx) {
#   if PL_API_VER >= 20
            tc->pl_sh = pl_shader_alloc(tc->pl_ctx, &(struct pl_shader_params) {
                .glsl.version = tc->glsl_version,
                .glsl.gles = tc->is_gles,
            });
#   elif PL_API_VER >= 6
            tc->pl_sh = pl_shader_alloc(tc->pl_ctx, NULL, 0);
#   else
            tc->pl_sh = pl_shader_alloc(tc->pl_ctx, NULL, 0, 0);
#   endif
        }
    }
#endif
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

        snprintf(upscaler_value, sizeof(upscaler_value), "%d", upscaler);
        snprintf(downscaler_value, sizeof(downscaler_value), "%d", downscaler);
        upscaler_value[sizeof(upscaler_value) - 1] = '\0';
        downscaler_value[sizeof(downscaler_value) - 1] = '\0';

<<<<<<< HEAD
        config_chain_t cfg = {
            .psz_name = (char *) "upscaler",
            .psz_value = upscaler_value,
            .p_next = &(config_chain_t) {
                .psz_name = (char *) "downscaler",
                .psz_value = downscaler_value,
            },
        };
=======
        if (desc == NULL)
        {
            vlc_object_release(tc);
            return VLC_EGENERIC;
        }
        if (desc->plane_count == 0)
        {
            /* Opaque chroma: load a module to handle it */
            tc->p_module = module_need(tc, "glconv", "$glconv", true);
        }
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

        struct vlc_gl_filter *scale_filter =
            vlc_gl_filters_Append(filters, "pl_scale", &cfg);
        if (!scale_filter)
        {
            if (upscaler)
                msg_Err(gl, "Could not apply upscaler filter, "
                            "ignoring --gl-upscaler=%d", upscaler);
            if (downscaler)
                msg_Err(gl, "Could not apply downscaler filter, "
                            "ignoring --gl-downscaler=%d", downscaler);
        }
    }

    struct vlc_gl_filter *renderer_filter =
        vlc_gl_filters_Append(filters, "renderer", NULL);
    if (!renderer_filter)
    {
        msg_Warn(gl, "Could not create renderer for %4.4s",
                 (const char *) &fmt_in->i_chroma);
        goto error;
    }
    GL_ASSERT_NOERROR(vt);

    int ret = vlc_gl_filters_InitFramebuffers(filters);
    if (ret != VLC_SUCCESS)
    {
        msg_Err(gl, "Could not init filters framebuffers");
        goto error;
    }

    /* The renderer is a special filter: we need its concrete instance to
     * forward SetViewpoint() */
    *out_renderer = renderer_filter->sys;

    return filters;

error:
    vlc_gl_filters_Delete(filters);
    return NULL;
}

vout_display_opengl_t *vout_display_opengl_New(video_format_t *fmt,
                                               const vlc_fourcc_t **subpicture_chromas,
                                               vlc_gl_t *gl,
                                               const vlc_viewpoint_t *viewpoint,
                                               vlc_video_context *context)
{
<<<<<<< HEAD
    vout_display_opengl_t *vgl = calloc(1, sizeof(*vgl));
    if (!vgl)
        return NULL;

    vgl->gl = gl;

    int ret = vlc_gl_api_Init(&vgl->api, gl);
    if (ret != VLC_SUCCESS)
        goto free_vgl;

    const struct vlc_gl_api *api = &vgl->api;
    const opengl_vtable_t *vt = &api->vt;

#if !defined(USE_OPENGL_ES2)
    const unsigned char *ogl_version = vt->GetString(GL_VERSION);
    bool supports_shaders = strverscmp((const char *)ogl_version, "2.0") >= 0;
    if (!supports_shaders)
    {
        msg_Err(gl, "shaders not supported, bailing out");
        goto free_vgl;
    }
#endif

    /* Resize the format if it is greater than the maximum texture size
     * supported by the hardware */
    GLint       max_tex_size;
    vt->GetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);
=======
    if (gl->getProcAddress == NULL) {
        msg_Err(gl, "getProcAddress not implemented, bailing out\n");
        return NULL;
    }

    vout_display_opengl_t *vgl = calloc(1, sizeof(*vgl));
    if (!vgl)
        return NULL;

    vgl->gl = gl;

#if defined(USE_OPENGL_ES2) || defined(HAVE_GL_CORE_SYMBOLS)
#define GET_PROC_ADDR_CORE(name) vgl->vt.name = gl##name
#else
#define GET_PROC_ADDR_CORE(name) GET_PROC_ADDR_EXT(name, true)
#endif
#define GET_PROC_ADDR_EXT(name, critical) do { \
    vgl->vt.name = vlc_gl_GetProcAddress(gl, "gl"#name); \
    if (vgl->vt.name == NULL && critical) { \
        msg_Err(gl, "gl"#name" symbol not found, bailing out\n"); \
        free(vgl); \
        return NULL; \
    } \
} while(0)
#if defined(USE_OPENGL_ES2)
#define GET_PROC_ADDR(name) GET_PROC_ADDR_CORE(name)
#define GET_PROC_ADDR_CORE_GL(name) GET_PROC_ADDR_EXT(name, false) /* optional for GLES */
#else
#define GET_PROC_ADDR(name) GET_PROC_ADDR_EXT(name, true)
#define GET_PROC_ADDR_CORE_GL(name) GET_PROC_ADDR_CORE(name)
#endif
#define GET_PROC_ADDR_OPTIONAL(name) GET_PROC_ADDR_EXT(name, false) /* GL 3 or more */

    GET_PROC_ADDR_CORE(BindTexture);
    GET_PROC_ADDR_CORE(BlendFunc);
    GET_PROC_ADDR_CORE(Clear);
    GET_PROC_ADDR_CORE(ClearColor);
    GET_PROC_ADDR_CORE(DeleteTextures);
    GET_PROC_ADDR_CORE(DepthMask);
    GET_PROC_ADDR_CORE(Disable);
    GET_PROC_ADDR_CORE(DrawArrays);
    GET_PROC_ADDR_CORE(DrawElements);
    GET_PROC_ADDR_CORE(Enable);
    GET_PROC_ADDR_CORE(Finish);
    GET_PROC_ADDR_CORE(Flush);
    GET_PROC_ADDR_CORE(GenTextures);
    GET_PROC_ADDR_CORE(GetError);
    GET_PROC_ADDR_CORE(GetIntegerv);
    GET_PROC_ADDR_CORE(GetString);
    GET_PROC_ADDR_CORE(PixelStorei);
    GET_PROC_ADDR_CORE(TexImage2D);
    GET_PROC_ADDR_CORE(TexParameterf);
    GET_PROC_ADDR_CORE(TexParameteri);
    GET_PROC_ADDR_CORE(TexSubImage2D);
    GET_PROC_ADDR_CORE(Viewport);

    GET_PROC_ADDR_CORE_GL(GetTexLevelParameteriv);
    GET_PROC_ADDR_CORE_GL(TexEnvf);

    GET_PROC_ADDR(CreateShader);
    GET_PROC_ADDR(ShaderSource);
    GET_PROC_ADDR(CompileShader);
    GET_PROC_ADDR(AttachShader);
    GET_PROC_ADDR(DeleteShader);

    GET_PROC_ADDR(GetProgramiv);
    GET_PROC_ADDR(GetShaderiv);
    GET_PROC_ADDR(GetProgramInfoLog);
    GET_PROC_ADDR(GetShaderInfoLog);

    GET_PROC_ADDR(GetUniformLocation);
    GET_PROC_ADDR(GetAttribLocation);
    GET_PROC_ADDR(VertexAttribPointer);
    GET_PROC_ADDR(EnableVertexAttribArray);
    GET_PROC_ADDR(UniformMatrix4fv);
    GET_PROC_ADDR(UniformMatrix3fv);
    GET_PROC_ADDR(UniformMatrix2fv);
    GET_PROC_ADDR(Uniform4fv);
    GET_PROC_ADDR(Uniform4f);
    GET_PROC_ADDR(Uniform3f);
    GET_PROC_ADDR(Uniform2f);
    GET_PROC_ADDR(Uniform1f);
    GET_PROC_ADDR(Uniform1i);

    GET_PROC_ADDR(CreateProgram);
    GET_PROC_ADDR(LinkProgram);
    GET_PROC_ADDR(UseProgram);
    GET_PROC_ADDR(DeleteProgram);

    GET_PROC_ADDR(ActiveTexture);

    GET_PROC_ADDR(GenBuffers);
    GET_PROC_ADDR(BindBuffer);
    GET_PROC_ADDR(BufferData);
    GET_PROC_ADDR(DeleteBuffers);

    GET_PROC_ADDR_OPTIONAL(GetFramebufferAttachmentParameteriv);

    GET_PROC_ADDR_OPTIONAL(BufferSubData);
    GET_PROC_ADDR_OPTIONAL(BufferStorage);
    GET_PROC_ADDR_OPTIONAL(MapBufferRange);
    GET_PROC_ADDR_OPTIONAL(FlushMappedBufferRange);
    GET_PROC_ADDR_OPTIONAL(UnmapBuffer);
    GET_PROC_ADDR_OPTIONAL(FenceSync);
    GET_PROC_ADDR_OPTIONAL(DeleteSync);
    GET_PROC_ADDR_OPTIONAL(ClientWaitSync);
#undef GET_PROC_ADDR

    GL_ASSERT_NOERROR();

    const char *extensions = (const char *)vgl->vt.GetString(GL_EXTENSIONS);
    assert(extensions);
    if (!extensions)
    {
        msg_Err(gl, "glGetString returned NULL\n");
        free(vgl);
        return NULL;
    }
#if !defined(USE_OPENGL_ES2)
    // Check for OpenGL < 2.0
    const unsigned char *ogl_version = vgl->vt.GetString(GL_VERSION);
    if (strverscmp((const char *)ogl_version, "2.0") < 0) {
        // Even with OpenGL < 2.0 we might have GLSL support,
        // so check the GLSL version before finally giving up:
        const unsigned char *glsl_version = vgl->vt.GetString(GL_SHADING_LANGUAGE_VERSION);
        if (!glsl_version || strverscmp((const char *)glsl_version, "1.10") < 0) {
            msg_Err(gl, "shaders not supported, bailing out\n");
            free(vgl);
            return NULL;
        }
    }
#endif

    /* Resize the format if it is greater than the maximum texture size
     * supported by the hardware */
    GLint       max_tex_size;
    vgl->vt.GetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

    if ((GLint)fmt->i_width > max_tex_size ||
        (GLint)fmt->i_height > max_tex_size)
        ResizeFormatToGLMaxTexSize(fmt, max_tex_size);

    vgl->interop = vlc_gl_interop_New(gl, context, fmt);
    if (!vgl->interop)
    {
        msg_Err(gl, "Could not create interop");
        goto free_vgl;
    }
    GL_ASSERT_NOERROR(vt);

    vgl->filters = CreateFilters(gl, api, vgl->interop, &vgl->renderer);
    if (!vgl->filters)
    {
        msg_Err(gl, "Could not create filters");
        goto delete_interop;
    }
    GL_ASSERT_NOERROR(vt);

    vgl->sub_interop = vlc_gl_interop_NewForSubpictures(gl);
    if (!vgl->sub_interop)
    {
        msg_Err(gl, "Could not create sub interop");
        goto delete_filters;
    }
    GL_ASSERT_NOERROR(vt);

<<<<<<< HEAD
    vgl->sub_renderer =
        vlc_gl_sub_renderer_New(gl, api, vgl->sub_interop);
    if (!vgl->sub_renderer)
    {
        msg_Err(gl, "Could not create sub renderer");
        goto delete_sub_interop;
=======
    /* */
    vgl->vt.Disable(GL_BLEND);
    vgl->vt.Disable(GL_DEPTH_TEST);
    vgl->vt.DepthMask(GL_FALSE);
    vgl->vt.Enable(GL_CULL_FACE);
    vgl->vt.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    vgl->vt.Clear(GL_COLOR_BUFFER_BIT);

    vgl->vt.GenBuffers(1, &vgl->vertex_buffer_object);
    vgl->vt.GenBuffers(1, &vgl->index_buffer_object);
    vgl->vt.GenBuffers(vgl->prgm->tc->tex_count, vgl->texture_buffer_object);

    /* Initial number of allocated buffer objects for subpictures, will grow dynamically. */
    int subpicture_buffer_object_count = 8;
    vgl->subpicture_buffer_object = vlc_alloc(subpicture_buffer_object_count, sizeof(GLuint));
    if (!vgl->subpicture_buffer_object) {
        vout_display_opengl_Delete(vgl);
        return NULL;
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
    }

    GL_ASSERT_NOERROR(vt);

    if (fmt->projection_mode != PROJECTION_MODE_RECTANGULAR
     && vout_display_opengl_SetViewpoint(vgl, viewpoint) != VLC_SUCCESS)
        msg_Err(gl, "Could not set viewpoint");

    /* Forward to the core the changes to the input format requested by the
     * interop */
    *fmt = vgl->interop->fmt_in;

    if (subpicture_chromas) {
        *subpicture_chromas = gl_subpicture_chromas;
    }

    GL_ASSERT_NOERROR(vt);
    return vgl;
<<<<<<< HEAD

delete_sub_renderer:
    vlc_gl_sub_renderer_Delete(vgl->sub_renderer);
delete_sub_interop:
    vlc_gl_interop_Delete(vgl->sub_interop);
delete_filters:
    vlc_gl_filters_Delete(vgl->filters);
delete_interop:
    vlc_gl_interop_Delete(vgl->interop);
free_vgl:
    free(vgl);

=======
}

void vout_display_opengl_Delete(vout_display_opengl_t *vgl)
{
    GL_ASSERT_NOERROR();

    /* */
    vgl->vt.Finish();
    vgl->vt.Flush();

    const size_t main_tex_count = vgl->prgm->tc->tex_count;
    const bool main_del_texs = !vgl->prgm->tc->handle_texs_gen;

    if (vgl->pool)
        picture_pool_Release(vgl->pool);
    opengl_deinit_program(vgl, vgl->prgm);
    opengl_deinit_program(vgl, vgl->sub_prgm);

    vgl->vt.DeleteBuffers(1, &vgl->vertex_buffer_object);
    vgl->vt.DeleteBuffers(1, &vgl->index_buffer_object);
    vgl->vt.DeleteBuffers(main_tex_count, vgl->texture_buffer_object);

    if (vgl->subpicture_buffer_object_count > 0)
        vgl->vt.DeleteBuffers(vgl->subpicture_buffer_object_count,
                              vgl->subpicture_buffer_object);
    free(vgl->subpicture_buffer_object);

    if (main_del_texs)
        vgl->vt.DeleteTextures(main_tex_count, vgl->texture);

    for (int i = 0; i < vgl->region_count; i++)
    {
        if (vgl->region[i].texture)
            vgl->vt.DeleteTextures(1, &vgl->region[i].texture);
    }
    free(vgl->region);
    GL_ASSERT_NOERROR();

    free(vgl);
}

static void UpdateZ(vout_display_opengl_t *vgl)
{
    /* Do trigonometry to calculate the minimal z value
     * that will allow us to zoom out without seeing the outside of the
     * sphere (black borders). */
    float tan_fovx_2 = tanf(vgl->f_fovx / 2);
    float tan_fovy_2 = tanf(vgl->f_fovy / 2);
    float z_min = - SPHERE_RADIUS / sinf(atanf(sqrtf(
                    tan_fovx_2 * tan_fovx_2 + tan_fovy_2 * tan_fovy_2)));

    /* The FOV value above which z is dynamically calculated. */
    const float z_thresh = 90.f;

    if (vgl->f_fovx <= z_thresh * M_PI / 180)
        vgl->f_z = 0;
    else
    {
        float f = z_min / ((FIELD_OF_VIEW_DEGREES_MAX - z_thresh) * M_PI / 180);
        vgl->f_z = f * vgl->f_fovx - f * z_thresh * M_PI / 180;
        if (vgl->f_z < z_min)
            vgl->f_z = z_min;
    }
}

static void UpdateFOVy(vout_display_opengl_t *vgl)
{
    vgl->f_fovy = 2 * atanf(tanf(vgl->f_fovx / 2) / vgl->f_sar);
}

int vout_display_opengl_SetViewpoint(vout_display_opengl_t *vgl,
                                     const vlc_viewpoint_t *p_vp)
{
#define RAD(d) ((float) ((d) * M_PI / 180.f))
    float f_fovx = RAD(p_vp->fov);
    if (f_fovx > FIELD_OF_VIEW_DEGREES_MAX * M_PI / 180 + 0.001f
        || f_fovx < -0.001f)
        return VLC_EBADVAR;

    vgl->f_teta = RAD(p_vp->yaw) - (float) M_PI_2;
    vgl->f_phi  = RAD(p_vp->pitch);
    vgl->f_roll = RAD(p_vp->roll);


    if (fabsf(f_fovx - vgl->f_fovx) >= 0.001f)
    {
        /* FOVx has changed. */
        vgl->f_fovx = f_fovx;
        UpdateFOVy(vgl);
        UpdateZ(vgl);
    }
    getViewpointMatrixes(vgl, vgl->fmt.projection_mode, vgl->prgm);

    return VLC_SUCCESS;
#undef RAD
}


void vout_display_opengl_SetWindowAspectRatio(vout_display_opengl_t *vgl,
                                              float f_sar)
{
    /* Each time the window size changes, we must recompute the minimum zoom
     * since the aspect ration changes.
     * We must also set the new current zoom value. */
    vgl->f_sar = f_sar;
    UpdateFOVy(vgl);
    UpdateZ(vgl);
    getViewpointMatrixes(vgl, vgl->fmt.projection_mode, vgl->prgm);
}

void vout_display_opengl_Viewport(vout_display_opengl_t *vgl, int x, int y,
                                  unsigned width, unsigned height)
{
    vgl->vt.Viewport(x, y, width, height);
}

picture_pool_t *vout_display_opengl_GetPool(vout_display_opengl_t *vgl, unsigned requested_count)
{
    GL_ASSERT_NOERROR();

    if (vgl->pool)
        return vgl->pool;

    opengl_tex_converter_t *tc = vgl->prgm->tc;
    requested_count = __MIN(VLCGL_PICTURE_MAX, requested_count);
    /* Allocate with tex converter pool callback if it exists */
    if (tc->pf_get_pool != NULL)
    {
        vgl->pool = tc->pf_get_pool(tc, requested_count);
        if (!vgl->pool)
            goto error;
        return vgl->pool;
    }

    /* Allocate our pictures */
    picture_t *picture[VLCGL_PICTURE_MAX] = {NULL, };
    unsigned count;
    for (count = 0; count < requested_count; count++)
    {
        picture[count] = picture_NewFromFormat(&vgl->fmt);
        if (!picture[count])
            break;
    }
    if (count <= 0)
        goto error;

    /* Wrap the pictures into a pool */
    vgl->pool = picture_pool_New(count, picture);
    if (!vgl->pool)
    {
        for (unsigned i = 0; i < count; i++)
            picture_Release(picture[i]);
        goto error;
    }

    GL_ASSERT_NOERROR();
    return vgl->pool;

error:
    DelTextures(tc, vgl->texture);
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
    return NULL;
}

int vout_display_opengl_UpdateFormat(vout_display_opengl_t *vgl,
                                     const video_format_t *fmt,
                                     vlc_video_context *vctx)
{
    /* If the format can't be changed, the state must remain valid to accept the
     * initial format. */

    vlc_gl_t *gl = vgl->gl;
    const struct vlc_gl_api *api = &vgl->api;

    assert(!fmt->p_palette);
    video_format_t in_fmt = *fmt;

<<<<<<< HEAD
    struct vlc_gl_interop *interop = vlc_gl_interop_New(gl, vctx, &in_fmt);
    if (!interop)
=======
    int         last_count = vgl->region_count;
    gl_region_t *last = vgl->region;

    vgl->region_count = 0;
    vgl->region       = NULL;

    tc = vgl->sub_prgm->tc;
    if (subpicture) {

        int count = 0;
        for (subpicture_region_t *r = subpicture->p_region; r; r = r->p_next)
            count++;

        vgl->region_count = count;
        vgl->region       = calloc(count, sizeof(*vgl->region));

        int i = 0;
        for (subpicture_region_t *r = subpicture->p_region;
             r && ret == VLC_SUCCESS; r = r->p_next, i++) {
            gl_region_t *glr = &vgl->region[i];

            glr->width  = r->fmt.i_visible_width;
            glr->height = r->fmt.i_visible_height;
            if (!vgl->supports_npot) {
                glr->width  = GetAlignedSize(glr->width);
                glr->height = GetAlignedSize(glr->height);
                glr->tex_width  = (float) r->fmt.i_visible_width  / glr->width;
                glr->tex_height = (float) r->fmt.i_visible_height / glr->height;
            } else {
                glr->tex_width  = 1.0;
                glr->tex_height = 1.0;
            }
            glr->alpha  = (float)subpicture->i_alpha * r->i_alpha / 255 / 255;
            glr->left   =  2.0 * (r->i_x                          ) / subpicture->i_original_picture_width  - 1.0;
            glr->top    = -2.0 * (r->i_y                          ) / subpicture->i_original_picture_height + 1.0;
            glr->right  =  2.0 * (r->i_x + r->fmt.i_visible_width ) / subpicture->i_original_picture_width  - 1.0;
            glr->bottom = -2.0 * (r->i_y + r->fmt.i_visible_height) / subpicture->i_original_picture_height + 1.0;

            glr->texture = 0;
            /* Try to recycle the textures allocated by the previous
               call to this function. */
            for (int j = 0; j < last_count; j++) {
                if (last[j].texture &&
                    last[j].width  == glr->width &&
                    last[j].height == glr->height) {
                    glr->texture = last[j].texture;
                    memset(&last[j], 0, sizeof(last[j]));
                    break;
                }
            }

            const size_t pixels_offset =
                r->fmt.i_y_offset * r->p_picture->p->i_pitch +
                r->fmt.i_x_offset * r->p_picture->p->i_pixel_pitch;
            if (!glr->texture)
            {
                /* Could not recycle a previous texture, generate a new one. */
                ret = GenTextures(tc, &glr->width, &glr->height, &glr->texture);
                if (ret != VLC_SUCCESS)
                    continue;
            }
            /* Use the visible pitch of the region */
            r->p_picture->p[0].i_visible_pitch = r->fmt.i_visible_width
                                               * r->p_picture->p[0].i_pixel_pitch;
            ret = tc->pf_update(tc, &glr->texture, &glr->width, &glr->height,
                                r->p_picture, &pixels_offset);
        }
    }
    for (int i = 0; i < last_count; i++) {
        if (last[i].texture)
            DelTextures(tc, &last[i].texture);
    }
    free(last);

    VLC_UNUSED(subpicture);

    GL_ASSERT_NOERROR();
    return ret;
}

static int BuildSphere(unsigned nbPlanes,
                        GLfloat **vertexCoord, GLfloat **textureCoord, unsigned *nbVertices,
                        GLushort **indices, unsigned *nbIndices,
                        const float *left, const float *top,
                        const float *right, const float *bottom)
{
    unsigned nbLatBands = 128;
    unsigned nbLonBands = 128;

    *nbVertices = (nbLatBands + 1) * (nbLonBands + 1);
    *nbIndices = nbLatBands * nbLonBands * 3 * 2;

    *vertexCoord = vlc_alloc(*nbVertices * 3, sizeof(GLfloat));
    if (*vertexCoord == NULL)
        return VLC_ENOMEM;
    *textureCoord = vlc_alloc(nbPlanes * *nbVertices * 2, sizeof(GLfloat));
    if (*textureCoord == NULL)
    {
        free(*vertexCoord);
        return VLC_ENOMEM;
    }
    *indices = vlc_alloc(*nbIndices, sizeof(GLushort));
    if (*indices == NULL)
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
    {
        msg_Err(gl, "Could not create interop");
        return VLC_EGENERIC;
    }

    if (in_fmt.i_chroma != fmt->i_chroma)
    {
        msg_Warn(gl, "Could not update format, the interop changed the "
                     "requested chroma from %4.4s to %4.4s\n",
                     (char *) &fmt->i_chroma, (char *) &in_fmt.i_chroma);
        vlc_gl_interop_Delete(interop);
        return VLC_EGENERIC;
    }

    struct vlc_gl_renderer *renderer;
    struct vlc_gl_filters *filters = CreateFilters(gl, api, interop, &renderer);
    if (!filters)
    {
        vlc_gl_interop_Delete(interop);
        return VLC_EGENERIC;
    }

    /* We created everything necessary, it worked, now the old ones could be
     * replaced. */
    vlc_gl_filters_Delete(vgl->filters);
    vlc_gl_interop_Delete(vgl->interop);

    vgl->interop = interop;
    vgl->filters = filters;
    vgl->renderer = renderer;

    return VLC_SUCCESS;
}

void vout_display_opengl_Delete(vout_display_opengl_t *vgl)
{
    const opengl_vtable_t *vt = &vgl->api.vt;

    GL_ASSERT_NOERROR(vt);

    /* */
    vt->Finish();
    vt->Flush();

    vlc_gl_sub_renderer_Delete(vgl->sub_renderer);
    vlc_gl_interop_Delete(vgl->sub_interop);

    vlc_gl_filters_Delete(vgl->filters);
    vlc_gl_interop_Delete(vgl->interop);

    GL_ASSERT_NOERROR(vt);

    free(vgl);
}

int vout_display_opengl_SetViewpoint(vout_display_opengl_t *vgl,
                                     const vlc_viewpoint_t *p_vp)
{
    return vlc_gl_renderer_SetViewpoint(vgl->renderer, p_vp);
}

void vout_display_opengl_SetOutputSize(vout_display_opengl_t *vgl,
                                       unsigned width, unsigned height)
{
<<<<<<< HEAD
    int ret = vlc_gl_filters_SetOutputSize(vgl->filters, width, height);
    /* The renderer, last filter in the chain, necessarily accepts the new
     * output size */
    assert(ret == VLC_SUCCESS);
    (void) ret;
=======
    opengl_tex_converter_t *tc = prgm->tc;
    tc->pf_prepare_shader(tc, vgl->tex_width, vgl->tex_height, 1.0f);

    for (unsigned j = 0; j < vgl->prgm->tc->tex_count; j++) {
        assert(vgl->texture[j] != 0);
        vgl->vt.ActiveTexture(GL_TEXTURE0+j);
        vgl->vt.BindTexture(tc->tex_target, vgl->texture[j]);

        vgl->vt.BindBuffer(GL_ARRAY_BUFFER, vgl->texture_buffer_object[j]);

        assert(prgm->aloc.MultiTexCoord[j] != -1);
        vgl->vt.EnableVertexAttribArray(prgm->aloc.MultiTexCoord[j]);
        vgl->vt.VertexAttribPointer(prgm->aloc.MultiTexCoord[j], 2, GL_FLOAT,
                                     0, 0, 0);
    }

    vgl->vt.BindBuffer(GL_ARRAY_BUFFER, vgl->vertex_buffer_object);
    vgl->vt.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, vgl->index_buffer_object);
    vgl->vt.EnableVertexAttribArray(prgm->aloc.VertexPosition);
    vgl->vt.VertexAttribPointer(prgm->aloc.VertexPosition, 3, GL_FLOAT, 0, 0, 0);

    vgl->vt.UniformMatrix4fv(prgm->uloc.OrientationMatrix, 1, GL_FALSE,
                             prgm->var.OrientationMatrix);
    vgl->vt.UniformMatrix4fv(prgm->uloc.ProjectionMatrix, 1, GL_FALSE,
                             prgm->var.ProjectionMatrix);
    vgl->vt.UniformMatrix4fv(prgm->uloc.ZRotMatrix, 1, GL_FALSE,
                             prgm->var.ZRotMatrix);
    vgl->vt.UniformMatrix4fv(prgm->uloc.YRotMatrix, 1, GL_FALSE,
                             prgm->var.YRotMatrix);
    vgl->vt.UniformMatrix4fv(prgm->uloc.XRotMatrix, 1, GL_FALSE,
                             prgm->var.XRotMatrix);
    vgl->vt.UniformMatrix4fv(prgm->uloc.ZoomMatrix, 1, GL_FALSE,
                             prgm->var.ZoomMatrix);

    vgl->vt.DrawElements(GL_TRIANGLES, vgl->nb_indices, GL_UNSIGNED_SHORT, 0);
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
}

void vout_display_opengl_Viewport(vout_display_opengl_t *vgl, int x, int y,
                                  unsigned width, unsigned height)
{
    vlc_gl_filters_SetViewport(vgl->filters, x, y, width, height);
}

int vout_display_opengl_Prepare(vout_display_opengl_t *vgl,
                                picture_t *picture, subpicture_t *subpicture)
{
    GL_ASSERT_NOERROR(&vgl->api.vt);

    int ret = vlc_gl_filters_UpdatePicture(vgl->filters, picture);
    if (ret != VLC_SUCCESS)
        return ret;

    ret = vlc_gl_sub_renderer_Prepare(vgl->sub_renderer, subpicture);
    GL_ASSERT_NOERROR(&vgl->api.vt);
    return ret;
}
int vout_display_opengl_Display(vout_display_opengl_t *vgl)
{
<<<<<<< HEAD
    GL_ASSERT_NOERROR(&vgl->api.vt);

    int ret = vlc_gl_filters_Draw(vgl->filters);
    if (ret != VLC_SUCCESS)
        return ret;
=======
    GL_ASSERT_NOERROR();

    /* Why drawing here and not in Render()? Because this way, the
       OpenGL providers can call vout_display_opengl_Display to force redraw.
       Currently, the OS X provider uses it to get a smooth window resizing */
    vgl->vt.Clear(GL_COLOR_BUFFER_BIT);

    vgl->vt.UseProgram(vgl->prgm->id);

    if (source->i_x_offset != vgl->last_source.i_x_offset
     || source->i_y_offset != vgl->last_source.i_y_offset
     || source->i_visible_width != vgl->last_source.i_visible_width
     || source->i_visible_height != vgl->last_source.i_visible_height)
    {
        float left[PICTURE_PLANE_MAX];
        float top[PICTURE_PLANE_MAX];
        float right[PICTURE_PLANE_MAX];
        float bottom[PICTURE_PLANE_MAX];
        const opengl_tex_converter_t *tc = vgl->prgm->tc;
        for (unsigned j = 0; j < tc->tex_count; j++)
        {
            float scale_w = (float)tc->texs[j].w.num / tc->texs[j].w.den
                          / vgl->tex_width[j];
            float scale_h = (float)tc->texs[j].h.num / tc->texs[j].h.den
                          / vgl->tex_height[j];

            /* Warning: if NPOT is not supported a larger texture is
               allocated. This will cause right and bottom coordinates to
               land on the edge of two texels with the texels to the
               right/bottom uninitialized by the call to
               glTexSubImage2D. This might cause a green line to appear on
               the right/bottom of the display.
               There are two possible solutions:
               - Manually mirror the edges of the texture.
               - Add a "-1" when computing right and bottom, however the
               last row/column might not be displayed at all.
            */
            left[j]   = (source->i_x_offset +                       0 ) * scale_w;
            top[j]    = (source->i_y_offset +                       0 ) * scale_h;
            right[j]  = (source->i_x_offset + source->i_visible_width ) * scale_w;
            bottom[j] = (source->i_y_offset + source->i_visible_height) * scale_h;
        }

        TextureCropForStereo(vgl, left, top, right, bottom);
        int ret = SetupCoords(vgl, left, top, right, bottom);
        if (ret != VLC_SUCCESS)
            return ret;

        vgl->last_source.i_x_offset = source->i_x_offset;
        vgl->last_source.i_y_offset = source->i_y_offset;
        vgl->last_source.i_visible_width = source->i_visible_width;
        vgl->last_source.i_visible_height = source->i_visible_height;
    }
    DrawWithShaders(vgl, vgl->prgm);

    /* Draw the subpictures */
    // Change the program for overlays
    struct prgm *prgm = vgl->sub_prgm;
    GLuint program = prgm->id;
    opengl_tex_converter_t *tc = prgm->tc;
    vgl->vt.UseProgram(program);

    vgl->vt.Enable(GL_BLEND);
    vgl->vt.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* We need two buffer objects for each region: for vertex and texture coordinates. */
    if (2 * vgl->region_count > vgl->subpicture_buffer_object_count) {
        if (vgl->subpicture_buffer_object_count > 0)
            vgl->vt.DeleteBuffers(vgl->subpicture_buffer_object_count,
                                  vgl->subpicture_buffer_object);
        vgl->subpicture_buffer_object_count = 0;

        int new_count = 2 * vgl->region_count;
        vgl->subpicture_buffer_object = realloc_or_free(vgl->subpicture_buffer_object, new_count * sizeof(GLuint));
        if (!vgl->subpicture_buffer_object)
            return VLC_ENOMEM;

        vgl->subpicture_buffer_object_count = new_count;
        vgl->vt.GenBuffers(vgl->subpicture_buffer_object_count,
                           vgl->subpicture_buffer_object);
    }

    vgl->vt.ActiveTexture(GL_TEXTURE0 + 0);
    for (int i = 0; i < vgl->region_count; i++) {
        gl_region_t *glr = &vgl->region[i];
        const GLfloat vertexCoord[] = {
            glr->left,  glr->top,
            glr->left,  glr->bottom,
            glr->right, glr->top,
            glr->right, glr->bottom,
        };
        const GLfloat textureCoord[] = {
            0.0, 0.0,
            0.0, glr->tex_height,
            glr->tex_width, 0.0,
            glr->tex_width, glr->tex_height,
        };

        assert(glr->texture != 0);
        vgl->vt.BindTexture(tc->tex_target, glr->texture);

        tc->pf_prepare_shader(tc, &glr->width, &glr->height, glr->alpha);

        vgl->vt.BindBuffer(GL_ARRAY_BUFFER, vgl->subpicture_buffer_object[2 * i]);
        vgl->vt.BufferData(GL_ARRAY_BUFFER, sizeof(textureCoord), textureCoord, GL_STATIC_DRAW);
        vgl->vt.EnableVertexAttribArray(prgm->aloc.MultiTexCoord[0]);
        vgl->vt.VertexAttribPointer(prgm->aloc.MultiTexCoord[0], 2, GL_FLOAT,
                                    0, 0, 0);

        vgl->vt.BindBuffer(GL_ARRAY_BUFFER, vgl->subpicture_buffer_object[2 * i + 1]);
        vgl->vt.BufferData(GL_ARRAY_BUFFER, sizeof(vertexCoord), vertexCoord, GL_STATIC_DRAW);
        vgl->vt.EnableVertexAttribArray(prgm->aloc.VertexPosition);
        vgl->vt.VertexAttribPointer(prgm->aloc.VertexPosition, 2, GL_FLOAT,
                                    0, 0, 0);

        vgl->vt.UniformMatrix4fv(prgm->uloc.OrientationMatrix, 1, GL_FALSE,
                                 prgm->var.OrientationMatrix);
        vgl->vt.UniformMatrix4fv(prgm->uloc.ProjectionMatrix, 1, GL_FALSE,
                                 prgm->var.ProjectionMatrix);
        vgl->vt.UniformMatrix4fv(prgm->uloc.ZRotMatrix, 1, GL_FALSE,
                                 prgm->var.ZRotMatrix);
        vgl->vt.UniformMatrix4fv(prgm->uloc.YRotMatrix, 1, GL_FALSE,
                                 prgm->var.YRotMatrix);
        vgl->vt.UniformMatrix4fv(prgm->uloc.XRotMatrix, 1, GL_FALSE,
                                 prgm->var.XRotMatrix);
        vgl->vt.UniformMatrix4fv(prgm->uloc.ZoomMatrix, 1, GL_FALSE,
                                 prgm->var.ZoomMatrix);

        vgl->vt.DrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    vgl->vt.Disable(GL_BLEND);
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

    ret = vlc_gl_sub_renderer_Draw(vgl->sub_renderer);
    if (ret != VLC_SUCCESS)
        return ret;

    GL_ASSERT_NOERROR(&vgl->api.vt);

    return VLC_SUCCESS;
}
