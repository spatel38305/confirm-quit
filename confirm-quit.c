#include <yed/plugin.h>

void test( int nargs, char **args );

int yed_plugin_boot( yed_plugin *self )
{
    YED_PLUG_VERSION_CHECK();

    yed_plugin_set_command( self, "test", test );

    return 0;
}

void test( int nargs, char **args )
{
    yed_cprint( "Hello World!" );
}
