#include "ephoto.h"

#include <Ecore_Getopt.h>

static const Ecore_Getopt options =
{
   "ephoto",
   "%prog [directory or filename]",
   VERSION,
   "(C) 2026 William L Thomson Jr, see AUTHORS.",
   "MIT, see COPYING",
   "A comprehensive image viewer",
   EINA_TRUE,
   {
      ECORE_GETOPT_HELP ('h', "help"),
      ECORE_GETOPT_VERSION('V', "version"),
      ECORE_GETOPT_COPYRIGHT('R', "copyright"),
      ECORE_GETOPT_LICENSE('L', "license"),
      ECORE_GETOPT_SENTINEL
   }
};

int
main(int argc, char *argv[])
{
    char *real = NULL;
    int return_code = EXIT_SUCCESS;
    unsigned char quit_option = 0;

    Ecore_Getopt_Value values[] =
        {
            ECORE_GETOPT_VALUE_BOOL(quit_option),
            ECORE_GETOPT_VALUE_BOOL(quit_option),
            ECORE_GETOPT_VALUE_BOOL(quit_option),
            ECORE_GETOPT_VALUE_BOOL(quit_option)
        };

    ecore_getopt_parse(&options, values, argc, argv);

    if (quit_option)
        return return_code;

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

    if (argc)
    {
        real = ecore_file_realpath(argv[1]);

        if (!real)
        {
            printf("invalid file or directory: '%s'\n", argv[1]);
            return_code = EXIT_FAILURE;
            goto end;
        }
    }

    Evas_Object *win = ephoto_window_add(real);

    if(real)
        free(real);

    if (!win)
    {
        return_code = EXIT_FAILURE;
        goto end;
    }

   ecore_main_loop_begin();
end:
   e_thumb_shutdown();
   efreet_mime_shutdown();
   eio_shutdown();
   elm_shutdown();

   return return_code;
}
