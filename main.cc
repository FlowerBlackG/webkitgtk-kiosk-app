#include "kbrowser.h"
#include <gtkmm/application.h>
#include <webkit2/webkit2.h>
#include <fstream>
#include <string>
#include <iostream>

#define PROGRAM_NAME "kbrowser"
#define AUTHORS proper_name("Nikhil Adiga")


static struct {
    const char* title = "fyt A+";
    const char* url = "https://www.baidu.com/";
    bool dev_tool = true;
    bool fullscreen = false;
    int width = 1366;
    int height = 768;
} const config;


extern WebKitWebView *web_view;

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "");

    KBrowser kbrowser;

    //Fullscreen
    if (config.fullscreen)
    {
        kbrowser.fullscreen();
    }
    else
    {
        std::string title = config.title;

        kbrowser.set_default_size(config.width, config.height);
        kbrowser.set_title(title);
    }

    
    
    WebKitAutoplayPolicy autoplay = WEBKIT_AUTOPLAY_ALLOW;
    WebKitWebsitePolicies *wp = webkit_website_policies_new_with_policies("autoplay", autoplay, NULL);
    web_view = WEBKIT_WEB_VIEW(g_object_new(WEBKIT_TYPE_WEB_VIEW, "website-policies", wp, webkit_web_view_new()));
    
    

    //Developer tools
    if (config.dev_tool)
    {
        WebKitSettings *dtsettings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(web_view));
        g_object_set(G_OBJECT(dtsettings), "enable-developer-extras", TRUE, NULL);
    }


    // Other settings.
    {
        WebKitSettings *settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(web_view));
        webkit_settings_set_enable_javascript(settings, TRUE);

        // disable any hardware acceleration.
        webkit_settings_set_hardware_acceleration_policy(settings, WEBKIT_HARDWARE_ACCELERATION_POLICY_NEVER);
        webkit_settings_set_enable_2d_canvas_acceleration(settings, FALSE);
    }



    std::string url = config.url;

    Gtk::Widget *three = Glib::wrap(GTK_WIDGET(web_view));

    kbrowser.add(*three);

    webkit_web_view_load_uri(web_view, &url[0]);

    g_signal_connect(web_view, "load-failed", G_CALLBACK(kbrowser.on_load_failed), NULL);

    kbrowser.show_all();

    app->run(kbrowser);

    return 0;
}
