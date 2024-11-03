#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <regex.h>
#define KEY "1A5"
typedef struct {
    char *email;
    char *password;
} User;

void check_password(const gchar *birthday) {

}
void check_SignUp(GtkWidget *widget, gpointer user_data) {
    // Retrieve the signup window from user_data
    GtkWidget *signup_window=GTK_WIDGET(user_data);

    //Retrieve the first_name information
    GtkWidget *First_Name = g_object_get_data(G_OBJECT(signup_window),"First Name");
    GtkEntryBuffer *first_name_buffer = gtk_entry_get_buffer(GTK_ENTRY(First_Name));
    const gchar *first_name_text = gtk_entry_buffer_get_text(first_name_buffer);

    //Retrieve the Last_name information
    GtkWidget *Last_Name = g_object_get_data(G_OBJECT(signup_window),"Last Name");
    GtkEntryBuffer *Last_Name_buffer = gtk_entry_get_buffer(GTK_ENTRY(Last_Name));
    const gchar *Last_Name_text = gtk_entry_buffer_get_text(Last_Name_buffer);

    //Retrieve the Last_name information
    GtkWidget *CIN = g_object_get_data(G_OBJECT(signup_window),"CIN");
    GtkEntryBuffer *CIN_buffer = gtk_entry_get_buffer(GTK_ENTRY(CIN));
    const gchar *CIN_text = gtk_entry_buffer_get_text(CIN_buffer);

    //Retrieve the Last_name information
    GtkWidget *Email = g_object_get_data(G_OBJECT(signup_window),"Email");
    GtkEntryBuffer *Email_buffer = gtk_entry_get_buffer(GTK_ENTRY(Email));
    const gchar *Email_text = gtk_entry_buffer_get_text(Email_buffer);

    //Retrieve the Last_name information
    GtkWidget *Birthday = g_object_get_data(G_OBJECT(signup_window),"Birthday DD//MM//YYY");
    GtkEntryBuffer *Birthday_buffer = gtk_entry_get_buffer(GTK_ENTRY(Birthday));
    const gchar *Birthday_text = gtk_entry_buffer_get_text(Birthday_buffer);

    //Retrieve the Last_name information
    GtkWidget *Password = g_object_get_data(G_OBJECT(signup_window),"Password");
    GtkEntryBuffer *Password_buffer = gtk_entry_get_buffer(GTK_ENTRY(Password));
    const gchar *Password_text = gtk_entry_buffer_get_text(Password_buffer);

    //Retrieve the Last_name information
    GtkWidget *Confirm_Password = g_object_get_data(G_OBJECT(signup_window),"Confirm Password");
    GtkEntryBuffer *Confirm_Password_buffer = gtk_entry_get_buffer(GTK_ENTRY(Confirm_Password));
    const gchar *Confirm_Password_text = gtk_entry_buffer_get_text(Confirm_Password_buffer);

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
    gtk_fixed_put(GTK_FIXED(signup_fix), first_name, 65, 100);
    gtk_widget_set_size_request(first_name, 250, 25);

    //Last name entry
    GtkWidget *Last_name =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Last_name), "Last Name");
    gtk_fixed_put(GTK_FIXED(signup_fix), Last_name, 65, 140);
    gtk_widget_set_size_request(Last_name, 250, 25);

    //CIN Entry
    GtkWidget *cin =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(cin), "CIN");
    gtk_fixed_put(GTK_FIXED(signup_fix), cin, 65, 180);
    gtk_widget_set_size_request(cin, 250, 25);

    //Email Entry
    GtkWidget *Email =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Email), "Email");
    gtk_fixed_put(GTK_FIXED(signup_fix), Email, 65, 220);
    gtk_widget_set_size_request(Email, 250, 25);

    //Birthday Entry
    GtkWidget *Birthday =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Birthday), "Birthday DD//MM//YYY");
    gtk_fixed_put(GTK_FIXED(signup_fix), Birthday, 65, 260);
    gtk_widget_set_size_request(Birthday, 250, 25);

    //Password
    GtkWidget *Password =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password), "Password");
    gtk_fixed_put(GTK_FIXED(signup_fix), Password, 65, 300);
    gtk_widget_set_size_request(Password, 250, 25);
    gtk_entry_set_visibility(GTK_ENTRY(Password),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(Password),'*');

    //Password_Confirmation
    GtkWidget *Password_Confirmation =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password_Confirmation), "Confirm Password");
    gtk_fixed_put(GTK_FIXED(signup_fix), Password_Confirmation, 65, 340);
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
    gtk_fixed_put(GTK_FIXED(signup_fix), Submit, 65, 380);
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
}
