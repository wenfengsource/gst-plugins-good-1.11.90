/* GStreamer
 * Copyright (C) <1999> Erik Walthinsen <omega@cse.ogi.edu>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */


#ifndef __GST_UDPSRC_H__
#define __GST_UDPSRC_H__

#include <gst/gst.h>
#include <gst/base/gstpushsrc.h>
#include <gio/gio.h>

G_BEGIN_DECLS

#include "gstudpnetutils.h"

#define GST_TYPE_UDPSRC \
  (gst_udpsrc_get_type())
#define GST_UDPSRC(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_UDPSRC,GstUDPSrc))
#define GST_UDPSRC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_UDPSRC,GstUDPSrcClass))
#define GST_IS_UDPSRC(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_UDPSRC))
#define GST_IS_UDPSRC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_UDPSRC))
#define GST_UDPSRC_CAST(obj) ((GstUDPSrc *)(obj))

typedef struct _GstUDPSrc GstUDPSrc;
typedef struct _GstUDPSrcClass GstUDPSrcClass;

struct _GstUDPSrc {
  GstPushSrc parent;

  /* properties */
  gchar     *address;
  gint       port;
  gchar     *multi_iface;
  gint       ttl;
  GstCaps   *caps;
  gint       buffer_size;
  guint64    timeout;
  gint       skip_first_bytes;
  GSocket   *socket;
  gboolean   close_socket;
  gboolean   auto_multicast;
  gboolean   reuse;
  gboolean   loop;
  gboolean   retrieve_sender_address;

  /* stats */
  guint      max_size;

  /* our sockets */
  GSocket   *used_socket;
  GInetSocketAddress *addr;
  gboolean   external_socket;

  gboolean   made_cancel_fd;
  GCancellable *cancellable;

  /* memory management */
  GstAllocator *allocator;
  GstAllocationParams params;

  GstMemory   *mem;
  GstMapInfo   map;
  GstMemory   *mem_max;
  GstMapInfo   map_max;
  GInputVector vec[2];

// vvv wenfeng
  GSocketAddress *saddr ; 
  guint   keep_alive_time;
  guint   keep_alive_len;
  gchar    keep_alive_str[50];
  gboolean  nat_flag;
  gchar     *nat_address;
  gint       nat_port;
  gint    time_id;
// ^^^ wenfeng

  gchar     *uri;
};

struct _GstUDPSrcClass {
  GstPushSrcClass parent_class;
};

GType gst_udpsrc_get_type(void);

G_END_DECLS


#endif /* __GST_UDPSRC_H__ */
