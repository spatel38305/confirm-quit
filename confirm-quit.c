#include <yed/plugin.h>

void confirm_quit( int nargs, char **args );

int yed_plugin_boot( yed_plugin *self )
{
    YED_PLUG_VERSION_CHECK();

    yed_plugin_set_command( self, "quit", confirm_quit );

    return 0;
}

void confirm_quit( int nargs, char **args )
{
    if ( ys->interactive_command )
    {
        int y_or_n;
        sscanf( args[0], "%d", &y_or_n );

        if ( ( y_or_n == 'y' ) || ( y_or_n == 'Y' ) )
        {
            ys->interactive_command = NULL;
            ys->status = YED_QUIT;
        }
        else if ( ( y_or_n == 'n' ) || ( y_or_n == 'N' ) )
        {
            ys->interactive_command = NULL;
        }
    }
    else
    {
        yed_buffer *buff;
        tree_it( yed_buffer_name_t, yed_buffer_ptr_t ) bit;

        tree_traverse( ys->buffers, bit )
        {
            buff = tree_it_val( bit );

            if ( !( buff->flags & BUFF_SPECIAL ) )
            {
                if ( buff->flags & BUFF_MODIFIED )
                {
                    ys->interactive_command = "quit";
                    ys->cmd_prompt = "(confirm-quit) You have unsaved buffers! Do you want to really quit? y or n";
                    yed_clear_cmd_buff();
                    break;
                }
            }
        }

        if ( !ys->interactive_command )
        {
            ys->status = YED_QUIT;
        }
    }
}
