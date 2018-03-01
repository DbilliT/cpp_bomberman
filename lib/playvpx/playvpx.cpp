#include "bomberman.hpp"
#include "playvpx.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static unsigned int mem_get_le32(const unsigned char *mem) {
  return (mem[3] << 24)|(mem[2] << 16)|(mem[1] << 8)|(mem[0]);
}

static void playvpx_die(Vpxdata *data,const char *fmt, ...) {
  va_list ap;

  (void)data;
  va_start(ap, fmt);
  vprintf(fmt, ap);
  if(fmt[strlen(fmt)-1] != '\n')
    printf("\n");
}

static void playvpx_die_codec(Vpxdata *data, const char *s) {
  const char *detail = vpx_codec_error_detail(&data->codec);
  printf("%s: %s\n", s, vpx_codec_error(&data->codec));
  if(detail)
    printf("    %s\n",detail);
}

void playvpx_convert_to_rgb(Vpxdata *data) {
  if (!data->is_init) { return ; }
  if (data->state == -1) { return ; }
  if (!data->img) { return; }

  vpx_image_t *img = data->img;
  const int w = img->d_w;
  const int w2 = w/2;
  const int pstride = w*3;
  const int h = img->d_h;
  const int h2 = h/2;
  if (!data->pixels) {
    data->pixels = (unsigned char *)malloc(w*h * 3);
  }

  const int strideY = img->stride[0];
  const int strideU = img->stride[1];
  const int strideV = img->stride[2];

  for (int posy = 0; posy < h2; posy++) {
    unsigned char *dst = data->pixels + pstride * (posy * 2);
    unsigned char *dst2 = data->pixels + pstride * (posy * 2 + 1);
    const unsigned char *srcY = img->planes[0] + strideY * posy * 2;
    const unsigned char *srcY2 = img->planes[0] + strideY * (posy * 2 + 1);
    const unsigned char *srcU = img->planes[1] + strideU * posy;
    const unsigned char *srcV = img->planes[2] + strideV * posy;

    for (int posx = 0; posx < w2; posx++) {
      unsigned char Y,U,V;
      short R,G,B;
      short iR,iG,iB;

      U = *(srcU++); V = *(srcV++);
      iR = (351 * (V-128)) / 256;
      iG = - (179 * (V-128)) / 256 - (86 * (U-128)) / 256;
      iB = (444 * (U-128)) / 256;

      Y = *(srcY++);
      R = Y + iR ; G = Y + iG ; B = Y + iB ;
      R = (R<0?0:(R>255?255:R)); G = (G<0?0:(G>255?255:G)); B = (B<0?0:(B>255?255:B));
      *(dst++) = R; *(dst++) = G; *(dst++) = B;

      Y = *(srcY2++);
      R = Y + iR ; G = Y + iG ; B = Y + iB ;
      R = (R<0?0:(R>255?255:R)); G = (G<0?0:(G>255?255:G)); B = (B<0?0:(B>255?255:B));
      *(dst2++) = R; *(dst2++) = G; *(dst2++) = B;

      Y = *(srcY++) ;
      R = Y + iR ; G = Y + iG ; B = Y + iB ;
      R = (R<0?0:(R>255?255:R)); G = (G<0?0:(G>255?255:G)); B = (B<0?0:(B>255?255:B));
      *(dst++) = R; *(dst++) = G; *(dst++) = B;

      Y = *(srcY2++);
      R = Y + iR ; G = Y + iG ; B = Y + iB ;
      R = (R<0?0:(R>255?255:R)); G = (G<0?0:(G>255?255:G)); B = (B<0?0:(B>255?255:B));
      *(dst2++) = R; *(dst2++) = G; *(dst2++) = B;
    }
  }
}

int playvpx_get_texture(Vpxdata *data) {
  if (!data->is_init) { return 0; }
  if (data->state == -1) { return 0; }
  if (!data->img) { return 0; }

  playvpx_convert_to_rgb(data);

  if (!data->texture) {
    glPixelStorei(GL_UNPACK_ALIGNMENT,4);
    glGenTextures(1, &data->texture);
    glBindTexture(GL_TEXTURE_2D, data->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  }

  glBindTexture(GL_TEXTURE_2D, data->texture);
  int width = data->img->d_w;
  int height = data->img->d_h;
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width,height,0,GL_RGB, GL_UNSIGNED_BYTE,data->pixels);

  return data->texture;
}

void playvpx_init(Vpxdata *data, const char *_fname) {

  memset(data,0,sizeof(*data));
  strcpy(data->fname,_fname);
  data->infile = fopen(data->fname,"rb");
  if (!data->infile) {
    playvpx_die(data,"unable to open file: '%s'",data->fname);
    return;
  }
  if(!(fread(data->file_hdr, 1, IVF_FILE_HDR_SZ, data->infile) == IVF_FILE_HDR_SZ
         && data->file_hdr[0]=='D' && data->file_hdr[1]=='K' && data->file_hdr[2]=='I'
       && data->file_hdr[3]=='F')) {
    playvpx_die(data,"this is not an IVF file: '%s'",data->fname);
    return;
  }
  printf("Using %s\n",vpx_codec_iface_name(vpx_codec_vp8_dx()));
  if(vpx_codec_dec_init(&data->codec, vpx_codec_vp8_dx(), NULL, data->flags)) {
    playvpx_die_codec(data, "Failed to initialize decoder");
    return;
  }
  data->is_init = 1;
}

bool playvpx_loop(Vpxdata *data) {
  if (!data->is_init) { return false; }

  if (data->state == -1) { return false; }

  if (!(fread(data->frame_hdr, 1, IVF_FRAME_HDR_SZ, data->infile) == IVF_FRAME_HDR_SZ)) {
    return false;
  }

  data->frame_sz = mem_get_le32(data->frame_hdr);
  data->iter = NULL;
  data->frame_cnt++;

  if (data->frame_cnt == 950)
    {
      SoundManager& sound=SoundManager::Instance();
      sound.playMusic("data/sound/music.mp3/Pirate.mp3", -1);
    }
  if(data->frame_sz > (int)sizeof(data->frame)) {
    playvpx_die(data,"Frame %d data too big for example code buffer", data->frame_sz);    
    data->state = -1;
    return false;
  }

  if((int)fread(data->frame, 1, data->frame_sz, data->infile) != data->frame_sz) {
    playvpx_die(data,"Frame %d failed to read complete frame", data->frame_cnt);
    data->state = -1;
    return false;
  }
  if(vpx_codec_decode(&data->codec, data->frame, data->frame_sz, NULL, 0)) {
    playvpx_die_codec(data, "Failed to decode frame");
    data->state = -1;
    return false;
  }

  int n = 0;
  vpx_image_t *img;
  while((img = vpx_codec_get_frame(&data->codec, &data->iter))) { 
    data->img = img;
    n += 1;
  }
  if (n>1) { fprintf(stderr,"%d frames in 1\n",n); }

  return true;
}

void playvpx_deinit(Vpxdata *data) {
  if (!data->is_init) { return; }

  printf("Processed %d frames.\n",data->frame_cnt);
  if(vpx_codec_destroy(&data->codec)) {
    playvpx_die_codec(data, "Failed to destroy codec");
  }

  if (data->infile) {
    fclose(data->infile);
  }

  if (data->pixels) {
    free(data->pixels);
  }

  if (data->texture) {
    glDeleteTextures(1,&data->texture);
  }

  memset(data,0,sizeof(*data));
}

void gfx_tex_blit(int tid, float dx, float dy, float dw, float dh) {
  float sx=0,sy=0,sw=1,sh=1;

  float coords[] ={sx,sy, sx+sw,sy, sx,sy+sh, sx+sw,sy+sh};
  float verts[] = {dx,dy, dx+dw,dy, dx,dy+dh, dx+dw,dy+dh};

  glBindTexture(GL_TEXTURE_2D, tid);
  glVertexPointer(2, GL_FLOAT, 0, verts);
  glTexCoordPointer(2, GL_FLOAT, 0, coords);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
