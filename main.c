/*#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <regex.h>

#define KEY "1A5"
char UP_CASE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char LOW_CASE[] = "abcdefghijklmnopqrstuvwxyz";
char DIGITS[] = "0123456789";

typedef struct {
    char *email;
    char *password;
} User;
void show_error_message(GtkWindow *parent, const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(parent, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", message);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_close), NULL);
    gtk_widget_show(dialog);
}
char check_first_name(const char *first_name,const char *last_name) {
    GtkWidget *button = NULL;
    while (*first_name) {
        if (isdigit(*first_name)) {
            GtkWidget *button = gtk_button_new();
            GtkCssProvider *css_provider = gtk_css_provider_new();
            gtk_css_provider_load_from_data(css_provider,"button {"
        "  min-width: 100px;"
        "  min-height: 100px;"
        "  border-radius: 50%;"
        "  background-color: #4CAF50;"
        "}", -1);

        }
        }


}
void check_password(const gchar *password,const gchar *confirm_password, const gchar *first_name, const gchar *last_name, GtkWindow *parent) {
    const int is_Same =strncmp(password ,confirm_password,strlen(password));
    char message[1024] = "";
    if(!is_Same){

        char content[1000];

        FILE* file;
        file = fopen("C:\\Users\\PC\\CLionProjects\\C_UI\\Most_Used_Password.txt", "r");
        if (file != NULL) {
            while (fgets(content, sizeof(content), file) != NULL) {
                content[strcspn(content, "\n")] = '\0';  // Remove newline character strncmp(content ,password,strlen(content)-1)
                if (strcmp(content, password) == 0) {
                    strcat(message, "Weak password: easy to guess.\n");
                    break; // Exit loop if we find a match
                }
            }
            fclose(file);
        } else {
            strcat(message, "Could not open password file.\n");
        }

        if (strstr(password, first_name) != NULL || strstr(password, last_name) != NULL) {
            strcat(message, "Your password contains part of your name.\n");
        }

        int result[3] = {0, 0, 0}; // [uppercase, lowercase, digit]
        for (int i = 0; i < strlen(password); i++) {
            if (strchr(UP_CASE, password[i])) {
                result[0] = 1; // Uppercase found
            }
            if (strchr(LOW_CASE, password[i])) {
                result[1] = 1; // Lowercase found
            }
            if (strchr(DIGITS, password[i])) {
                result[2] = 1; // Digit found
            }
        }

        // Short messages for missing criteria
        if (!result[0]) strcat(message, "Add at least one uppercase letter.\n");
        if (!result[1]) strcat(message, "Add at least one lowercase letter.\n");
        if (!result[2]) strcat(message, "Add at least one digit.\n");

        // Show the error message if there are issues
        if (strlen(message) > 0) {
            show_error_message(parent, message);
        } else {
            printf("Password is acceptable.\n");
        }
    }else {
        strcat(message,"The Password and The Confirmation should be the Same");
        show_error_message(parent,message);
    }
}
void check_SignUp(GtkWidget *widget, gpointer user_data) {
    // Retrieve the signup window from user_data
    GtkWidget *signup_window=GTK_WIDGET(user_data);
    int is_feild_empty = 0;

    //Retrieve the first_name information
    GtkWidget *First_Name = g_object_get_data(G_OBJECT(signup_window),"First Name");
    GtkEntryBuffer *first_name_buffer = gtk_entry_get_buffer(GTK_ENTRY(First_Name));
    const gchar *first_name_text = gtk_entry_buffer_get_text(first_name_buffer);
    if(strlen(first_name_text) == 0)
        is_feild_empty = 1;


    //Retrieve the Last_name information
    GtkWidget *Last_Name = g_object_get_data(G_OBJECT(signup_window),"Last Name");
    GtkEntryBuffer *Last_Name_buffer = gtk_entry_get_buffer(GTK_ENTRY(Last_Name));
    const gchar *Last_Name_text = gtk_entry_buffer_get_text(Last_Name_buffer);
    if(strlen(Last_Name_text) == 0)
        is_feild_empty =1;

    //Retrieve the Last_name information
    GtkWidget *CIN = g_object_get_data(G_OBJECT(signup_window),"CIN");
    GtkEntryBuffer *CIN_buffer = gtk_entry_get_buffer(GTK_ENTRY(CIN));
    const gchar *CIN_text = gtk_entry_buffer_get_text(CIN_buffer);
    if(strlen(CIN_text) == 0)
        is_feild_empty =1;

    //Retrieve the Last_name information
    GtkWidget *Email = g_object_get_data(G_OBJECT(signup_window),"Email");
    GtkEntryBuffer *Email_buffer = gtk_entry_get_buffer(GTK_ENTRY(Email));
    const gchar *Email_text = gtk_entry_buffer_get_text(Email_buffer);
    if(strlen(Email_text) == 0)
        is_feild_empty =1;

    //Retrieve the Last_name information
    GtkWidget *Birthday = g_object_get_data(G_OBJECT(signup_window),"Birthday DD//MM//YYY");
    GtkEntryBuffer *Birthday_buffer = gtk_entry_get_buffer(GTK_ENTRY(Birthday));
    const gchar *Birthday_text = gtk_entry_buffer_get_text(Birthday_buffer);
    if(strlen(Birthday_text) == 0)
        is_feild_empty =1;

    //Retrieve the Last_name information
    GtkWidget *Password = g_object_get_data(G_OBJECT(signup_window),"Password");
    GtkEntryBuffer *Password_buffer = gtk_entry_get_buffer(GTK_ENTRY(Password));
    const gchar *Password_text = gtk_entry_buffer_get_text(Password_buffer);
    if(strlen(Password_text) == 0)
        is_feild_empty =1;

    //Retrieve the Last_name information
    GtkWidget *Confirm_Password = g_object_get_data(G_OBJECT(signup_window),"Confirm Password");
    GtkEntryBuffer *Confirm_Password_buffer = gtk_entry_get_buffer(GTK_ENTRY(Confirm_Password));
    const gchar *Confirm_Password_text = gtk_entry_buffer_get_text(Confirm_Password_buffer);

    if(strlen(Confirm_Password_text) == 0)
        is_feild_empty =1;
    if (is_feild_empty) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(signup_window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", "ALL Fields Required");
        g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_close), NULL);
        gtk_widget_show(dialog);

    }else {

        check_password(Password_text,Confirm_Password_text,first_name_text,Last_Name_text,(GtkWindow *)user_data);

    }

    g_print("first_name: %s\n",first_name_text);
    g_print("last_name: %s\n",Last_Name_text);
    g_print("cin: %s\n",CIN_text);
    g_print("Email: %s\n",Email_text);
    g_print("Birthday: %s\n",Birthday_text);
    g_print("Password: %s\n",Password_text);
    g_print("Confirm Password : %s\n",Confirm_Password_text);





}

static void signup_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *main_window = GTK_WIDGET(user_data);

    // Create a new Signup window
    GtkWidget *signup_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(signup_window), "SignUp");
    gtk_window_set_default_size(GTK_WINDOW(signup_window), 350, 600);
    gtk_window_set_resizable(GTK_WINDOW(signup_window), FALSE);


    // Create a fixed layout for the login window
    GtkWidget *signup_fix = gtk_fixed_new();

    //First name entry
    GtkWidget *first_name =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(first_name), "First Name");
    gtk_fixed_put(GTK_FIXED(signup_fix), first_name, 50, 100);
    gtk_widget_set_size_request(first_name, 250, 25);

    ///Crete first name image
    GtkWidget *first_name_button = gtk_button_new();


    GtkWidget *first_name_image = gtk_image_new_from_file("../info_red.png");
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(hbox), first_name_image);
    gtk_button_set_child(GTK_BUTTON(first_name_button), hbox);

    gtk_fixed_put(GTK_FIXED(signup_fix), first_name_button, 310, 100);
    gtk_widget_set_size_request(first_name_button, 20, 20);

    //Last name entry
    GtkWidget *Last_name =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Last_name), "Last Name");
    gtk_fixed_put(GTK_FIXED(signup_fix), Last_name, 50, 140);
    gtk_widget_set_size_request(Last_name, 250, 25);
    //Last name image
    GtkWidget *last_name_image = gtk_image_new_from_file("../info_red.png");
    GtkWidget *last_name_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(last_name_hbox), first_name_image);
    gtk_button_set_child(GTK_BUTTON(first_name_button), last_name_hbox);

    gtk_fixed_put(GTK_FIXED(signup_fix), first_name_button, 310, 140);
    gtk_widget_set_size_request(first_name_button, 20, 20);

    //CIN Entry
    GtkWidget *cin =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(cin), "CIN");
    gtk_fixed_put(GTK_FIXED(signup_fix), cin, 50, 180);
    gtk_widget_set_size_request(cin, 250, 25);

    //CIN image
    GtkWidget *CIN_image = gtk_image_new_from_file("../info_red.png");
    GtkWidget *CIN_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(CIN_hbox), first_name_image);
    gtk_button_set_child(GTK_BUTTON(first_name_button), CIN_hbox);

    gtk_fixed_put(GTK_FIXED(signup_fix), first_name_button, 310, 180);
    gtk_widget_set_size_request(first_name_button, 20, 20);

    //Email Entry
    GtkWidget *Email =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Email), "Email");
    gtk_fixed_put(GTK_FIXED(signup_fix), Email, 50, 220);
    gtk_widget_set_size_request(Email, 250, 25);

    //Birthday Entry
    GtkWidget *Birthday =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Birthday), "Birthday DD//MM//YYY");
    gtk_fixed_put(GTK_FIXED(signup_fix), Birthday, 50, 260);
    gtk_widget_set_size_request(Birthday, 250, 25);

    //Password
    GtkWidget *Password =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password), "Password");
    gtk_fixed_put(GTK_FIXED(signup_fix), Password, 50, 300);
    gtk_widget_set_size_request(Password, 250, 25);
    gtk_entry_set_visibility(GTK_ENTRY(Password),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(Password),'*');

    //Password_Confirmation
    GtkWidget *Password_Confirmation =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password_Confirmation), "Confirm Password");
    gtk_fixed_put(GTK_FIXED(signup_fix), Password_Confirmation, 50, 340);
    gtk_widget_set_size_request(Password_Confirmation, 250, 25);
    gtk_entry_set_visibility(GTK_ENTRY(Password_Confirmation),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(Password_Confirmation),'*');

    // Store the entry widgets in the login window using g_object_set_data
    g_object_set_data(G_OBJECT(signup_window), "First Name", first_name);
    g_object_set_data(G_OBJECT(signup_window), "Last Name", Last_name);
    g_object_set_data(G_OBJECT(signup_window), "CIN", cin);
    g_object_set_data(G_OBJECT(signup_window), "Email", Email);
    g_object_set_data(G_OBJECT(signup_window), "Birthday DD//MM//YYY", Birthday);
    g_object_set_data(G_OBJECT(signup_window), "Password", Password);
    g_object_set_data(G_OBJECT(signup_window), "Confirm Password", Password_Confirmation);




    // Create Submit Button
    GtkWidget *Submit = gtk_button_new_with_label("Submit");
    gtk_fixed_put(GTK_FIXED(signup_fix), Submit, 50, 380);
    gtk_widget_set_size_request(Submit, 250, 20);

    g_signal_connect(Submit, "clicked", G_CALLBACK(check_SignUp), signup_window);





    // Set the fixed layout as the child of the login window
    gtk_window_set_child(GTK_WINDOW(signup_window), signup_fix);




    // Show the login window
    gtk_widget_show(signup_window);

    // Close the main window
    gtk_widget_hide(main_window);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                   //
//                                                                                                   //
//                                                                                                   //
//                                                                                                   //
//                                                                                                   //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////

void check_login_infoemation(GtkWidget *widget, gpointer user_data) {
    // Retrieve the login window from user_data
    GtkWidget *login_window = GTK_WIDGET(user_data);

    // Retrieve the entries using g_object_get_data
    GtkWidget *email_entry = g_object_get_data(G_OBJECT(login_window), "email_entry");
    GtkEntryBuffer *login_buffer = gtk_entry_get_buffer(GTK_ENTRY(email_entry));
    const gchar *email = gtk_entry_buffer_get_text(login_buffer);

    // Print email and password (for testing purposes)
    g_print("Email: %s\n", email);




}




static void login_button_clicked(GtkWidget *widget, gpointer user_data) {
    // Get the main window from user data
    GtkWidget *main_window = GTK_WIDGET(user_data);

    // Create a new login window
    GtkWidget *login_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(login_window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(login_window), 350, 600);
    gtk_window_set_resizable(GTK_WINDOW(login_window), FALSE);

    // Create a fixed layout for the login window
    GtkWidget *login_fix = gtk_fixed_new();

    // Email entry area
    GtkWidget *email_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(email_entry), "Email");
    gtk_fixed_put(GTK_FIXED(login_fix), email_entry, 65, 200);
    gtk_widget_set_size_request(email_entry, 250, 25);

    // Password entry area
    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_fixed_put(GTK_FIXED(login_fix), password_entry, 65, 250);
    gtk_widget_set_size_request(password_entry, 250, 25);

    // Store the entry widgets in the login window using g_object_set_data
    g_object_set_data(G_OBJECT(login_window), "email_entry", email_entry);
    g_object_set_data(G_OBJECT(login_window), "password_entry", password_entry);

    // Create Login Button
    GtkWidget *Login_Button = gtk_button_new_with_label("Login");
    gtk_fixed_put(GTK_FIXED(login_fix), Login_Button, 65, 300);
    gtk_widget_set_size_request(Login_Button, 250, 20);

    // Connect the clicked signal of the login button
    g_signal_connect(Login_Button, "clicked", G_CALLBACK(check_login_infoemation), login_window);

    // Set the fixed layout as the child of the login window
    gtk_window_set_child(GTK_WINDOW(login_window), login_fix);
    // Show the login window
    gtk_widget_show(login_window);

    // Close the main window
    gtk_widget_hide(main_window);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                   //
//                                                                                                   //
//                                                                                                   //
//                                                                                                   //
//                                                                                                   //
//                                                                                                   //
///////////////////////////////////////////////////////////////////////////////////////////////////////
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *fix;

    // Create a new window for the application
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 600);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // Create a CSS provider and set the background color
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, "window { background-color: #FFFFFF; }");

    // Attach the CSS provider to the window's style context
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Title information
    GtkWidget *title = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(title), "<span font='20' weight='bold' foreground='#ff8000'>\t   Welcome \n\t\t  To\n   Your Credit Manager</span>");

    fix = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(fix), title, 40, 50);


    // Login button
    GtkWidget *Login_Button = gtk_button_new_with_label("Login");
    gtk_fixed_put(GTK_FIXED(fix), Login_Button, 65, 400);
    gtk_widget_set_size_request(Login_Button, 100, 50);
    

    // Connect the clicked signal of the login button, passing the main window as user_data
    g_signal_connect(Login_Button, "clicked", G_CALLBACK(login_button_clicked), window);

    // Set the child widget


    // SignUp button
    GtkWidget *SignUp_Button = gtk_button_new_with_label("SignUp");
    gtk_fixed_put(GTK_FIXED(fix), SignUp_Button, 185, 400);
    gtk_widget_set_size_request(SignUp_Button, 100, 50);

    // Connect the clicked signal of the signup button, passing the main window as user_data
    g_signal_connect(SignUp_Button, "clicked", G_CALLBACK(signup_button_clicked), window);

    gtk_window_set_child(GTK_WINDOW(window), fix);

    // Present the main window
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}*/
