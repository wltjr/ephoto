#include "ephoto.h"

static void _ephoto_display_usage(void);

int
main(int argc, char *argv[])
{
   int return_code = EXIT_SUCCESS;

   elm_init(argc, argv);
   eio_init();
   elm_need_efreet();
   elm_language_set("");
   elm_app_compile_data_dir_set(PACKAGE_DATA_DIR);
   elm_app_info_set(main, "ephoto", "themes/ephoto.edj");
#if HAVE_GETTEXT && ENABLE_NLS
   elm_app_compile_locale_set(LOCALEDIR);
   bindtextdomain(PACKAGE, elm_app_locale_dir_get());
   bind_textdomain_codeset(PACKAGE, "UTF-8");
   textdomain(PACKAGE);
#endif

   if (!efreet_mime_init())
     printf("Could not initialize Efreet_Mime!\n");
   if (!e_ipc_init())
     printf("Could not initialize IPC!\n");
   if (!e_thumb_init())
     printf("Could not initialize Thumbnailer!\n");

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   if (argc > 2)
     {
        printf("Too Many Arguments!\n");
        _ephoto_display_usage();
        return_code = EXIT_FAILURE;
        goto end;
     }
   else if (argc < 2)
     {
        Evas_Object *win = ephoto_window_add(NULL);

        if (!win)
          {
             return_code = EXIT_FAILURE;
             goto end;
          }
     }
   else if (!strncmp(argv[1], "--help", 6))
     {
        _ephoto_display_usage();
        goto end;
     }
   else
     {
        char *real = ecore_file_realpath(argv[1]);

        if (!real)
          {
             printf("invalid file or directory: '%s'\n", argv[1]);
             return_code = EXIT_FAILURE;
             goto end;
          }
        Evas_Object *win = ephoto_window_add(real);

        free(real);
        if (!win)
          {
             return_code = EXIT_FAILURE;
             goto end;
          }
     }

   ecore_main_loop_begin();
end:
   e_thumb_shutdown();
   efreet_mime_shutdown();
   eio_shutdown();
   elm_shutdown();

   return return_code;
}

/* Display useage commands for ephoto */
static void
_ephoto_display_usage(void)
{
    printf("ephoto Usage: \n"
           "ephoto --help   : This page\n"
           "ephoto filename : Specifies a file to open\n"
           "ephoto dirname  : Specifies a directory to open\n");
}
