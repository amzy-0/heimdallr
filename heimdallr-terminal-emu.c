/*
 * HEIMDALLR: 
 * you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * this is c/gtk terminal emulator
 * i customize this for heimdallr project and you can run this terminal
 * this terminal is an simple terminal and easy to use when you run heimdallr.
 * 
 * @author(s) : amzy-0 (Mohammad Amin Azimi .K) 
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<sys/unistd.h>
#include<vte/vte.h>
#include<gtk/gtk.h>

GtkWidget *win,
*terminal,
*first_box_terminal,
*second_box_terminal,
*third_box_terminal,
*url_exec_btn_firefox,
*url_exec_btn_chrome,
*url_label,
*url_entry;

static void child_ready(VteTerminal *terminal, GPid pid, GError *error, gpointer user_data)
{
    if (!terminal) return;
    if (pid == -1) gtk_main_quit();
}

/* go to goto firefox */
static void open_url_firefox(void){
    const gchar *entry = gtk_entry_get_text(GTK_ENTRY(url_entry));
    const char *browser = "firefox ";
    const int len_of_browser = strlen(browser); 
    const int  len_of_entry = gtk_entry_get_text_length(GTK_ENTRY(url_entry)); 
    const int finally_length = len_of_entry+len_of_browser+2;
    char *url_merge_with_brw = (char*)malloc(finally_length*sizeof(char)); 
    g_print("%s <->%s\n", entry, browser);
    strcpy(url_merge_with_brw, browser);
    strcat(url_merge_with_brw, entry);
    strcat(url_merge_with_brw, "&");
    if( (system(url_merge_with_brw) )!=0){
        system("notify-send \"firefox command not found !\"&");
    }
    free(url_merge_with_brw);

}
/* go to goto google chrome */
static void open_url_chrome(void){
    const gchar *entry = gtk_entry_get_text(GTK_ENTRY(url_entry));
    const char *browser = "google-chrome ";
    const int len_of_browser = strlen(browser);
    const int  len_of_entry = gtk_entry_get_text_length(GTK_ENTRY(url_entry));
    const int finally_length = len_of_entry+len_of_browser+2;
    char *url_merge_with_brw = (char*)malloc(finally_length*sizeof(char));
    g_print("%s <-> %s \n", entry, browser);
    strcpy(url_merge_with_brw, browser);
    strcat(url_merge_with_brw, entry);
    strcat(url_merge_with_brw, "&");
    if( (system(url_merge_with_brw) )!=0){
        system("notify-send \"google-chrome command not found !\"&");
    }
    free(url_merge_with_brw);

}

// int main initialization


int main(int argc, char *argv[])
{

    // client home address 
    char *home_addr = getenv("HOME");
    char *logo_addr = "/.heimdallr/icon/heimdallr.png";
    
    int home_addr_len = strlen(home_addr);
    int logo_addr_len = strlen(logo_addr);
    int finally_len = home_addr_len + logo_addr_len+1;

    /* icon path  */

    char *path = (char*)malloc(finally_len*sizeof(char));
    strcpy(path, home_addr);
    strcat(path, logo_addr);  

    /* create all widget */



    /* initialize GTK, the window and the terminal */
    gtk_init(&argc, &argv);

    // terminal instance and configuration 
    terminal = vte_terminal_new();
    vte_terminal_set_font_scale(VTE_TERMINAL(terminal), 1.3);

    // window instance 
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title(GTK_WINDOW(win), "Heimdallr");
    
    gtk_window_set_icon_from_file(GTK_WINDOW(win), path, NULL);

    /* go to all standard directories GUI  */
 
    url_exec_btn_firefox = gtk_button_new_with_label("firefox");
    url_exec_btn_chrome = gtk_button_new_with_label("google chrome");


    url_label = gtk_label_new("Enter your URL : ");

    url_entry = gtk_entry_new();

    /* main boxes of terminal  */
    first_box_terminal = gtk_box_new(TRUE, 0);
    second_box_terminal = gtk_box_new(FALSE, 0);
    third_box_terminal = gtk_box_new(TRUE, 0);

    /* Start a new shell */
    gchar **envp = g_get_environ();
    gchar **command = (gchar *[]){g_strdup(g_environ_getenv(envp, "SHELL")), NULL };
    g_strfreev(envp);
    vte_terminal_spawn_async(VTE_TERMINAL(terminal),
        VTE_PTY_DEFAULT,
        home_addr,         /* working directory  */
        command,      /* command */
        NULL,         /* environment */
        2,            /* spawn flags */
        NULL, NULL,   /* child setup */
        NULL,         /* child pid */
        -1,           /* timeout */
        NULL,         /* cancellable */
        child_ready,  /* callback */
        NULL);        /* user_data */


    /* Connect some signals */

    g_signal_connect(win, "destroy", gtk_main_quit, NULL);

    g_signal_connect(terminal, "child-exited", gtk_main_quit, NULL);

    g_signal_connect(G_OBJECT(url_exec_btn_firefox),
                    "clicked",
                    G_CALLBACK(open_url_firefox),
                    (gpointer)win
                  );
                  
    g_signal_connect(G_OBJECT(url_exec_btn_chrome),
                    "clicked",
                    G_CALLBACK(open_url_chrome),
                    (gpointer)win
    );

    /*
     * add  terminal to the first box (Main Box)
     */
    gtk_box_pack_start(GTK_BOX(first_box_terminal), terminal, TRUE, TRUE, 0 );

   /*
    * combine two box (first_box_terminal and second_box_terminal)
    */

    gtk_box_pack_end(GTK_BOX(first_box_terminal), second_box_terminal, FALSE, FALSE, 0);

   /*
    * add third box to the first box (Main Box)
    */

    gtk_box_pack_end(GTK_BOX(first_box_terminal), third_box_terminal, FALSE, FALSE, 0);



    /*
    * url exec button for firefox  (GUI)
    */
    gtk_box_pack_end(GTK_BOX(second_box_terminal), url_exec_btn_firefox, TRUE, TRUE, 4);

    /*
    * url exec button for google chrome  (GUI)
    */
    gtk_box_pack_end(GTK_BOX(second_box_terminal), url_exec_btn_chrome, TRUE, TRUE, 4);


    ////////////////////////////////third box/////////////////////////////////////////
    /*
     * add search label to the third box
     */
    
      gtk_box_pack_start(GTK_BOX(third_box_terminal), url_label, FALSE, FALSE, 4);
    
    /*
     * add search entry to the third box
     */
    gtk_box_pack_start(GTK_BOX(third_box_terminal), url_entry, TRUE, FALSE, 4);

    /*
     * maximize heimdallr terminal
     * you can comment this section
     * if you dont want to maximize your heimdallr terminal
     * and you can modify size or ...
     *  NEXT STEP : Put widgets together and run the main loop
     */

    gtk_container_add(GTK_CONTAINER(win), first_box_terminal);
    const char *text_url = gtk_entry_get_text(GTK_ENTRY(url_entry));
    

    /*
     * render all
     */

    // URL entry get text 
    

    free(path);

    gtk_widget_show_all(win);

    gtk_main();

    return 0;
}
