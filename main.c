
#include <glib.h>
#include <gnet.h>
#include <stdint.h>
#include <netinet/in.h>

#include "iscsi.h"
#include "target.h"
#include "parameters.h"

uint32_t iscsi_debug_level = 0;

static GServer *tcp_srv;

int device_init(globals_t * a, targv_t * b, disc_target_t * c)
{
	return -1;
}

int device_command(target_session_t * e, target_cmd_t * d)
{
	return -1;
}

int device_shutdown(target_session_t * f)
{
	return -1;
}

static void tcp_event(GConn * conn, GConnEvent * evt, gpointer user_data)
{
	switch (evt->type) {
	case GNET_CONN_ERROR:
	case GNET_CONN_CONNECT:
	case GNET_CONN_CLOSE:
	case GNET_CONN_TIMEOUT:
	case GNET_CONN_READ:
	case GNET_CONN_WRITE:
	case GNET_CONN_READABLE:
	case GNET_CONN_WRITABLE:
		/* do nothing */
		break;
	}
}

static void tcp_srv_event(GServer * srv, GConn * conn, gpointer user_data)
{
	gnet_conn_set_callback(conn, tcp_event, NULL);
}

static int net_init(void)
{
	tcp_srv = gnet_server_new(NULL, 3260, tcp_srv_event, NULL);
	if (!tcp_srv)
		return -1;

	return 0;
}

static void net_exit(void)
{
	gnet_server_unref(tcp_srv);
}

static globals_t gbls;
static targv_t tv_all[4];

static int master_iscsi_init(void)
{
	return target_init(&gbls, tv_all, "MyFirstTarget");
}

static void master_iscsi_exit(void)
{
	target_shutdown(&gbls);
}

int main(int argc, char *argv[])
{
	GMainLoop *ml;

	ml = g_main_loop_new(NULL, FALSE);
	if (!ml)
		return 1;

	if (net_init())
		return 1;
	if (master_iscsi_init())
		return 1;

	g_main_loop_run(ml);

	master_iscsi_exit();
	net_exit();

	g_main_loop_unref(ml);

	return 0;
}
