#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <regex.h>

typedef struct {
    char *email;
    char *password;
} User;

void check_birthday(char *birthday) {

}



void check_login_infoemation(GtkWidget *widget, gpointer user_data) {
    // Retrieve the login window from user_data
    GtkWidget *login_window = GTK_WIDGET(user_data);

    // Retrieve the entries using g_object_get_data
    GtkWidget *email_entry = g_object_get_data(G_OBJECT(login_window), "email_entry");
    GtkWidget *password_entry = g_object_get_data(G_OBJECT(login_window), "password_entry");
    GtkEntryBuffer *login_buffer = gtk_entry_get_buffer(GTK_ENTRY(email_entry));

    // Get text from the entry widgets

    const gchar *email = gtk_entry_buffer_get_text(login_buffer);

    // Print email and password (for testing purposes)
    g_print("Email: %s\n", email);




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

    //Password_Confirmation
    GtkWidget *Password_Confirmation =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password_Confirmation), "Confirm Password");
    gtk_fixed_put(GTK_FIXED(signup_fix), Password_Confirmation, 65, 340);
    gtk_widget_set_size_request(Password_Confirmation, 250, 25);





    // Set the fixed layout as the child of the login window
    gtk_window_set_child(GTK_WINDOW(signup_window), signup_fix);




    // Show the login window
    gtk_widget_show(signup_window);

    // Close the main window
    gtk_widget_hide(main_window);

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

    // Set the fixed layout as the child of the login window
    gtk_window_set_child(GTK_WINDOW(login_window), login_fix);

    // Create Login Button
    GtkWidget *Login_Button = gtk_button_new_with_label("Login");
    gtk_fixed_put(GTK_FIXED(login_fix), Login_Button, 65, 300);
    gtk_widget_set_size_request(Login_Button, 250, 20);

    // Connect the clicked signal of the login button
    g_signal_connect(Login_Button, "clicked", G_CALLBACK(check_login_infoemation), login_window);

    // Show the login window
    gtk_widget_show(login_window);

    // Close the main window
    gtk_widget_hide(main_window);
}

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
    gtk_css_provider_load_from_string(provider, "window { background-color: #000000; }");

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

    // Connect the clicked signal of the login button, passing the main window as user_data
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
