// #qo pkg-config: gstreamer-1.0 gstreamer-app-1.0 gdk-pixbuf-2.0
// apt install libgdk-pixbuf2.0-dev

#include <gst/gst.h>
#include <gst/app/gstappsrc.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

GST_DEBUG_CATEGORY (appsrc_pipeline_debug);
#define GST_CAT_DEFAULT appsrc_pipeline_debug

typedef struct _App App;

struct _App
{
  GstElement *pipeline;
  GstElement *appsrc;

  GMainLoop *loop;
  guint sourceid;

  GTimer *timer;

};

App s_app = {};

static gboolean
read_data (App * app)
{
    printf("@@@@ [%s] START\n", __func__);
    guint len;
    GstFlowReturn ret;
    gdouble ms;

        GstBuffer *buffer;
        GdkPixbuf *pb;
        gboolean ok = TRUE;

	buffer = gst_buffer_new_allocate(NULL, 640*480*3, NULL);

        pb = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, 640, 480);
        gdk_pixbuf_fill(pb, 0xff0000ff);

 	GstMapInfo map;
	gst_buffer_map(buffer, &map, GST_MAP_WRITE);
	memcpy(map.data, gdk_pixbuf_get_pixels(pb), 640*480*3*sizeof(guchar));

	static int dump = 0;
	if (dump) {
               int flags = O_WRONLY | O_CREAT | O_TRUNC;
		int fd = open("/tmp/hoge", flags, 0644);
		write(fd, map.data, 640*480*3*sizeof(guchar));
		dump = 0;
	}

        printf ("feed buffer\n");
        g_signal_emit_by_name (app->appsrc, "push-buffer", buffer, &ret);
        gst_buffer_unref (buffer);

        if (ret != GST_FLOW_OK) {
            /* some error, stop sending data */
            printf ("some error\n");
            ok = FALSE;
        }

        g_timer_start(app->timer);

        return ok;

    printf("@@@@ [%s]   END\n", __func__);

        //g_signal_emit_by_name (app->appsrc, "end-of-stream", &ret);
    return FALSE;
}

/* This signal callback is called when appsrc needs data, we add an idle handler
 * to the mainloop to start pushing data into the appsrc */
static void
start_feed (GstElement * pipeline, guint size, App * app)
{
  printf("@@@@ [%s] START source id=%d\n", __func__, app->sourceid);
  if (app->sourceid == 0) {
    printf ("start feeding\n");
    app->sourceid = g_idle_add ((GSourceFunc) read_data, app);
  }
}

/* This callback is called when appsrc has enough data and we can stop sending.
 * We remove the idle handler from the mainloop */
static void
stop_feed (GstElement * pipeline, App * app)
{
  printf("@@@@ [%s] START source id=%d\n", __func__, app->sourceid);
  if (app->sourceid != 0) {
    printf ("stop feeding\n");
    g_source_remove (app->sourceid);
    app->sourceid = 0;
  }
}

static gboolean
bus_message (GstBus * bus, GstMessage * message, App * app)
{
  printf ("got message %s\n",
      gst_message_type_get_name (GST_MESSAGE_TYPE (message)));

  switch (GST_MESSAGE_TYPE (message)) {
    case GST_MESSAGE_ERROR: {
        GError *err = NULL;
        gchar *dbg_info = NULL;

        gst_message_parse_error (message, &err, &dbg_info);
        g_printerr ("ERROR from element %s: %s\n",
            GST_OBJECT_NAME (message->src), err->message);
        g_printerr ("Debugging info: %s\n", (dbg_info) ? dbg_info : "none");
        g_error_free (err);
        g_free (dbg_info);
        g_main_loop_quit (app->loop);
        break;
    }
    case GST_MESSAGE_EOS:
      g_main_loop_quit (app->loop);
      break;
    default:
      break;
  }
  return TRUE;
}

int
main (int argc, char *argv[])
{
  App *app = &s_app;
  GError *error = NULL;
  GstBus *bus;
  GstCaps *caps;

  gst_init (&argc, &argv);

  GST_DEBUG_CATEGORY_INIT (appsrc_pipeline_debug, "appsrc-pipeline", 0,
      "appsrc pipeline example");

  /* create a mainloop to get messages and to handle the idle handler that will
   * feed data to appsrc. */
  app->loop = g_main_loop_new (NULL, TRUE);
  app->timer = g_timer_new();

  //app->pipeline = gst_parse_launch("appsrc name=mysource ! videoconvert ! videoscale method=1 ! theoraenc bitrate=150 ! udpsink host=192.168.20.209 port=5005", NULL);
  app->pipeline = gst_parse_launch(
  "appsrc name=mysource do-timestamp=true is-live=true ! "
  "video/x-raw,format=NV12,width=320,height=240,framerate=60/1 ! "
  "videoconvert ! "
  "vaapiencode_h264 ! "
  "rtph264pay ! "
  "queue ! "
  "udpsink host=192.168.20.209 port=5005",
  NULL);
  g_assert (app->pipeline);

  bus = gst_pipeline_get_bus (GST_PIPELINE (app->pipeline));
  g_assert(bus);

  /* add watch for messages */
  gst_bus_add_watch (bus, (GstBusFunc) bus_message, app);

  /* get the appsrc */
    app->appsrc = gst_bin_get_by_name (GST_BIN(app->pipeline), "mysource");
    g_assert(app->appsrc);
    g_signal_connect (app->appsrc, "need-data", G_CALLBACK (start_feed), app);
    g_signal_connect (app->appsrc, "enough-data", G_CALLBACK (stop_feed), app);

  /* go to playing and wait in a mainloop. */
  gst_element_set_state (app->pipeline, GST_STATE_PLAYING);

  /* this mainloop is stopped when we receive an error or EOS */
  g_main_loop_run (app->loop);

  printf ("stopping\n");

  gst_element_set_state (app->pipeline, GST_STATE_NULL);

  gst_object_unref (bus);
  g_main_loop_unref (app->loop);

  return 0;
}
