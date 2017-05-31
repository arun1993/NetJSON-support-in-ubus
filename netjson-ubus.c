#include <libubox/uloop.h>
#include <libubus.h>
#include <unistd.h>
#include <libubox/blobmsg_json.h>


static void ubus_netjson_device_monitor(struct ubus_context *ctx, struct ubus_object_data *obj, void *priv)
{
  // Function to print device_monitor
}

static void ubus_netjson_device_config(struct ubus_context *ctx, struct ubus_object_data *obj, void *priv)
{
  // Function to print device_monitor
}

static int ubus_netjson_device_config(struct ubus_context *ctx, int argc, char **argv)
{
        const char *path = NULL;

        if (argc > 1)
                return -2;

        if (argc == 1)
                path = argv[0];

        return ubus_lookup(ctx, path, get_device_config, NULL);
}


static int ubus_netjson_device_monitor(struct ubus_context *ctx, int argc, char **argv)
{
        const char *path = NULL;

        if (argc > 1)
                return -2;

        if (argc == 1)
                path = argv[0];

        return ubus_lookup(ctx, path, get_device_monitoring, NULL);
}

static int usage(const char *prog)
{
        fprintf(stderr,
                "Usage: ubus netjson <Objects> <Interface> <parameter>\n"
                "NetJSON Objects:\n"
                " -config :   To display the DeviceConfiguration NetJSON\n"
                " -monitor:   To display the DeviceMonitoring NetJSON\n"
                "\n"
                "Interface:\n"
                " - all                        List objects\n"
                " - eth0     Call an object method\n"
                " - wireless                   Listen for events\n"
                "\n"
                "Parameters:\n"
                " - all        List all parameters associated\n"
                " - Status     List the status alone\n"
                " - ip_addr    List the Ip address alone\n"
				" - ....  etc as per NetJSON Object parameter\n"
                "\n", prog);
        return 1;
}

static struct {
        const char *name;
        int (*cb)(struct ubus_context *ctx, int argc, char **argv);
} commands[] = {
        { "config", ubus_netjson_device_config },
        { "monitor", ubus_netjson_device_monitor },
};

int main(int argc, char** argv)
{
        static struct ubus_context      *ctx;
        const char                      *ubus_socket = NULL;
        int ret = 0;
`
        uloop_init();

        ctx = ubus_connect(ubus_socket);
        if (!ctx) {
                fprintf(stderr, "Failed to connect to ubus\n");
                return -1;
        }

        ret == -2;

        for (i = 0; i < ARRAY_SIZE(commands); i++) {
            if (strcmp(commands[i].name, cmd) != 0)
                continue;

            ret = commands[i].cb(ctx, argc, argv);
            break;
        }

        if (ret == -2) 
           usage(progname);

        ubus_add_uloop(ctx);

        uloop_run();
        ubus_free(ctx);
        uloop_done();

        return 0;
}

