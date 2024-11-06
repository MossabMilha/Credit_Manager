#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <regex.h>
#define MIN_PASSWORD_LENGTH 8
#define SPECIAL_CHARACTERS "!@#$%^&*()-_=+[]{}|;:'\",.<>?/\\"

#define KEY "1A5"


typedef struct {
    char *email;
    char *password;
} User;
void show_error_message(GtkWindow *parent, const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(parent, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", message);
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_close), NULL);
    gtk_widget_show(dialog);
}
void check_first_name(const char *first_name, GtkWidget *first_name_button) {
    while (*first_name) {
        if (isdigit(*first_name)) {
            gtk_widget_set_visible(first_name_button, TRUE);
            return;
        }
        first_name++;
    }
    gtk_widget_set_visible(first_name_button, FALSE);
}
void check_last_name(const char *last_name, GtkWidget *last_name_button) {
    while (*last_name) {
        if (isdigit(*last_name)) {
            gtk_widget_set_visible(last_name_button, TRUE);
            return;
        }
        last_name++;
    }
    gtk_widget_set_visible(last_name_button, FALSE);
}
void check_CIN(const char *cin, GtkWidget *cin_button) {
    regex_t regex;
    int reti;

    // Compile the regular expression
    reti = regcomp(&regex, "^[A-Za-z]{1,2}[0-9]{1,6}$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    // Execute the regular expression
    reti = regexec(&regex, cin, 0, NULL, 0);
    if (!reti) {
        // CIN is valid
        gtk_widget_set_visible(cin_button, FALSE);
    } else if (reti == REG_NOMATCH) {
        // CIN is invalid
        gtk_widget_set_visible(cin_button, TRUE);
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    // Free the compiled regular expression
    regfree(&regex);
}

void check_email(const char *email,GtkWidget *gmail_button) {
    regex_t regex;
    int reti;

    // Define the regular expression for a valid Gmail email format
    const char *pattern = "^[A-Za-z0-9._%+-]+@gmail\\.com$";

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
    }

    // Execute the regular expression
    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        gtk_widget_set_visible(gmail_button, FALSE);; // Email format is valid
    } else if (reti == REG_NOMATCH) {
        gtk_widget_set_visible(gmail_button, TRUE); // Email format is invalid
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }
}

void check_birthday(const char *birthday, GtkWidget *birthday_button) {
    regex_t regex;
    int reti;

    // Define the regular expression for a valid birthday format
    const char *pattern = "^[0-3][0-9]/[0-1][0-9]/[0-9]{4}$";

    // Compile the regular expression
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    // Execute the regular expression
    reti = regexec(&regex, birthday, 0, NULL, 0);
    if (reti == REG_NOMATCH) {
        gtk_widget_set_visible(birthday_button, TRUE); // Invalid format
        regfree(&regex);
        return;
    }

    // Parse the date
    int day, month, year;
    sscanf(birthday, "%2d/%2d/%4d", &day, &month, &year);

    // Get the current date
    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);

    // Calculate the age
    int age = current_time->tm_year + 1900 - year;
    if (current_time->tm_mon + 1 < month || (current_time->tm_mon + 1 == month && current_time->tm_mday < day)) {
        age--;
    }

    // Check if the user is more than 18 years old
    if (age >= 18) {
        gtk_widget_set_visible(birthday_button, FALSE); // Valid birthday
    } else {
        gtk_widget_set_visible(birthday_button, TRUE); // Invalid birthday
    }

    // Free the compiled regular expression
    regfree(&regex);
}

void check_password(const gchar *password, const gchar *confirm_password, const gchar *first_name, const gchar *last_name, GtkWidget *password_button) {
    char message[1024] = "";

    // Check if password and confirmation password are identical
    if (strcmp(password, confirm_password) != 0) {
        strcat(message, "The Password and The Confirmation should be the same.\n");
    }

    // Check if password is in the most used password list
    char content[1000];
    FILE *file = fopen("Most_Used_Password.txt", "r");
    if (file != NULL) {
        while (fgets(content, sizeof(content), file) != NULL) {
            content[strcspn(content, "\n")] = '\0';  // Remove newline character
            if (strcmp(content, password) == 0) {
                strcat(message, "Weak password: easy to guess.\n");
                break;
            }
        }
        fclose(file);
    } else {
        strcat(message, "Could not open password file.\n");
    }

    // Check if password contains part of the user's name
    if (strstr(password, first_name) != NULL || strstr(password, last_name) != NULL) {
        strcat(message, "Your password contains part of your name.\n");
    }

    // Check password length
    if (strlen(password) < MIN_PASSWORD_LENGTH) {
        strcat(message, "Password must be at least 8 characters long.\n");
    }

    // Check for uppercase, lowercase, digit, and special character
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) has_upper = 1;
        if (islower(password[i])) has_lower = 1;
        if (isdigit(password[i])) has_digit = 1;
        if (strchr(SPECIAL_CHARACTERS, password[i])) has_special = 1;
    }

    if (!has_upper) strcat(message, "Add at least one uppercase letter.\n");
    if (!has_lower) strcat(message, "Add at least one lowercase letter.\n");
    if (!has_digit) strcat(message, "Add at least one digit.\n");
    if (!has_special) strcat(message, "Add at least one special character.\n");

    // Show or hide the button based on the validation results
    if (strlen(message) > 0) {
        gtk_widget_set_visible(password_button, TRUE);
        fprintf(stderr, "%s", message);  // Print the error message for debugging
    } else {
        gtk_widget_set_visible(password_button, FALSE);
    }
}


void check_SignUp(GtkWidget *widget, gpointer user_data) {
    // Retrieve the signup window from user_data
    GtkWidget *signup_window = GTK_WIDGET(user_data);
    GtkWidget *signup_fix = g_object_get_data(G_OBJECT(signup_window), "signup_fix");
    int is_feild_empty = 0;

    // Retrieve the first_name information
    GtkWidget *First_Name = g_object_get_data(G_OBJECT(signup_window), "First Name");
    GtkEntryBuffer *first_name_buffer = gtk_entry_get_buffer(GTK_ENTRY(First_Name));
    const gchar *first_name_text = gtk_entry_buffer_get_text(first_name_buffer);

    GtkWidget *First_Name_Button = g_object_get_data(G_OBJECT(signup_window), "First Name Image");

    if (strlen(first_name_text) == 0) {
        is_feild_empty = 1;
        gtk_widget_set_visible(First_Name_Button, TRUE);
    } else {
        gtk_widget_set_visible(First_Name_Button, FALSE);
        check_first_name(first_name_text, First_Name_Button);
    }

    // Retrieve the Last_name information
    GtkWidget *Last_Name = g_object_get_data(G_OBJECT(signup_window), "Last Name");
    GtkEntryBuffer *Last_Name_buffer = gtk_entry_get_buffer(GTK_ENTRY(Last_Name));
    const gchar *Last_Name_text = gtk_entry_buffer_get_text(Last_Name_buffer);

    GtkWidget *Last_Name_Button = g_object_get_data(G_OBJECT(signup_window), "Last Name Image");

    if (strlen(Last_Name_text) == 0) {
        is_feild_empty = 1;
        gtk_widget_set_visible(Last_Name_Button, TRUE);
    } else {
        gtk_widget_set_visible(Last_Name_Button, FALSE);
        check_last_name(Last_Name_text, Last_Name_Button);
    }

    // Retrieve the CIN information
    GtkWidget *CIN = g_object_get_data(G_OBJECT(signup_window), "CIN");
    GtkEntryBuffer *CIN_buffer = gtk_entry_get_buffer(GTK_ENTRY(CIN));
    const gchar *CIN_text = gtk_entry_buffer_get_text(CIN_buffer);

    GtkWidget *CIN_Button = g_object_get_data(G_OBJECT(signup_window), "CIN Image");

    if (strlen(CIN_text) == 0) {
        is_feild_empty = 1;
        gtk_widget_set_visible(CIN_Button, TRUE);
    } else {
        gtk_widget_set_visible(CIN_Button, FALSE);
        check_CIN(CIN_text, CIN_Button);
    }

    // Retrieve the Email information
    GtkWidget *Email = g_object_get_data(G_OBJECT(signup_window), "Email");
    GtkEntryBuffer *Email_buffer = gtk_entry_get_buffer(GTK_ENTRY(Email));
    const gchar *Email_text = gtk_entry_buffer_get_text(Email_buffer);

    GtkWidget *Email_Button = g_object_get_data(G_OBJECT(signup_window), "Email Image");

    if (strlen(Email_text) == 0) {
        is_feild_empty = 1;
        gtk_widget_set_visible(Email_Button, TRUE);
    } else {
        gtk_widget_set_visible(Email_Button, FALSE);
        check_email(Email_text, Email_Button);
    }

    // Retrieve the Birthday information
    GtkWidget *Birthday = g_object_get_data(G_OBJECT(signup_window), "Birthday DD//MM//YYY");
    GtkEntryBuffer *Birthday_buffer = gtk_entry_get_buffer(GTK_ENTRY(Birthday));
    const gchar *Birthday_text = gtk_entry_buffer_get_text(Birthday_buffer);

    GtkWidget *Birthday_Button = g_object_get_data(G_OBJECT(signup_window), "Birthday Image");

    if (strlen(Birthday_text) == 0) {
        is_feild_empty = 1;
        gtk_widget_set_visible(Birthday_Button, TRUE);
    } else {
        gtk_widget_set_visible(Birthday_Button, FALSE);
        check_birthday(Birthday_text, Birthday_Button);
    }

    // Retrieve the Password information
    GtkWidget *Password = g_object_get_data(G_OBJECT(signup_window), "Password");
    GtkEntryBuffer *Password_buffer = gtk_entry_get_buffer(GTK_ENTRY(Password));

    GtkWidget *Confirm_Password = g_object_get_data(G_OBJECT(signup_window), "Confirm Password");
    GtkEntryBuffer *Confirm_Password_buffer = gtk_entry_get_buffer(GTK_ENTRY(Confirm_Password));

    const gchar *Password_text = gtk_entry_buffer_get_text(Password_buffer);
    const gchar *Confirm_Password_text = gtk_entry_buffer_get_text(Confirm_Password_buffer);

    GtkWidget *Password_Button = g_object_get_data(G_OBJECT(signup_window), "Password Image");

    if (strlen(Password_text) == 0 || strlen(Confirm_Password_text) == 0) {
        is_feild_empty = 1;
        gtk_widget_set_visible(Password_Button, TRUE);
    } else {
        gtk_widget_set_visible(Password_Button, FALSE);
        check_password(Password_text, Confirm_Password_text, first_name_text, Last_Name_text, Password_Button);
    }

    if (is_feild_empty) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(signup_window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", "ALL Fields Required");
        g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_close), NULL);
        gtk_widget_show(dialog);
    }

    g_print("first_name: %s\n", first_name_text);
    g_print("last_name: %s\n", Last_Name_text);
    g_print("cin: %s\n", CIN_text);
    g_print("Email: %s\n", Email_text);
    g_print("Birthday: %s\n", Birthday_text);
    g_print("Password: %s\n", Password_text);
    g_print("Confirm Password : %s\n", Confirm_Password_text);
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
    gtk_button_set_child(GTK_BUTTON(first_name_button), first_name_image);
    gtk_fixed_put(GTK_FIXED(signup_fix), first_name_button, 310, 100);
    gtk_widget_set_size_request(first_name_button, 20, 20);
    gtk_widget_set_visible(first_name_button, FALSE);


    gtk_widget_set_size_request(first_name_button, 20, 20);

    //Last name entry
    GtkWidget *Last_name =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Last_name), "Last Name");
    gtk_fixed_put(GTK_FIXED(signup_fix), Last_name, 50, 140);
    gtk_widget_set_size_request(Last_name, 250, 25);
    //Last name image
    GtkWidget *last_name_button = gtk_button_new();
    GtkWidget *last_name_image = gtk_image_new_from_file("../info_red.png");
    GtkWidget *last_name_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(last_name_hbox), last_name_image);
    gtk_button_set_child(GTK_BUTTON(last_name_button), last_name_hbox);

    gtk_fixed_put(GTK_FIXED(signup_fix), last_name_button, 310, 140);
    gtk_widget_set_size_request(last_name_button, 20, 20);
    gtk_widget_set_visible(last_name_button, FALSE);

    //CIN Entry
    GtkWidget *cin =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(cin), "CIN");
    gtk_fixed_put(GTK_FIXED(signup_fix), cin, 50, 180);
    gtk_widget_set_size_request(cin, 250, 25);

    //CIN image
    GtkWidget *cin_button = gtk_button_new();
    GtkWidget *cin_image = gtk_image_new_from_file("../info_red.png");
    GtkWidget *cin_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(cin_hbox), cin_image);
    gtk_button_set_child(GTK_BUTTON(cin_button), cin_hbox);

    gtk_fixed_put(GTK_FIXED(signup_fix), cin_button, 310, 180);
    gtk_widget_set_size_request(cin_button, 20, 20);
    gtk_widget_set_visible(cin_button, FALSE);

    //Email Entry
    GtkWidget *Email =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Email), "Email");
    gtk_fixed_put(GTK_FIXED(signup_fix), Email, 50, 220);
    gtk_widget_set_size_request(Email, 250, 25);

    //Email image
    GtkWidget *email_button = gtk_button_new();
    GtkWidget *email_image = gtk_image_new_from_file("../info_red.png");
    GtkWidget *email_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(email_hbox), email_image);
    gtk_button_set_child(GTK_BUTTON(email_button), email_hbox);

    gtk_fixed_put(GTK_FIXED(signup_fix), email_button, 310, 220);
    gtk_widget_set_size_request(email_button, 20, 20);
    gtk_widget_set_visible(email_button, FALSE);

    //Birthday Entry
    GtkWidget *Birthday =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Birthday), "Birthday DD//MM//YYY");
    gtk_fixed_put(GTK_FIXED(signup_fix), Birthday, 50, 260);
    gtk_widget_set_size_request(Birthday, 250, 25);

    //Birthday image
    GtkWidget *Birthday_button = gtk_button_new();
    GtkWidget *Birthday_image = gtk_image_new_from_file("../info_red.png");
    GtkWidget *Birthday_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(Birthday_hbox), Birthday_image);
    gtk_button_set_child(GTK_BUTTON(Birthday_button), Birthday_hbox);

    gtk_fixed_put(GTK_FIXED(signup_fix), Birthday_button, 310, 260);
    gtk_widget_set_size_request(Birthday_button, 20, 20);
    gtk_widget_set_visible(Birthday_button, FALSE);

    //Password
    GtkWidget *Password =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password), "Password");
    gtk_fixed_put(GTK_FIXED(signup_fix), Password, 50, 300);
    gtk_widget_set_size_request(Password, 250, 25);
    gtk_entry_set_visibility(GTK_ENTRY(Password),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(Password),'*');

    //Email image
    GtkWidget *Password_button = gtk_button_new();
    GtkWidget *Password_image = gtk_image_new_from_file("../info_red.png");
    GtkWidget *Password_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(Password_hbox), Password_image);
    gtk_button_set_child(GTK_BUTTON(Password_button), Password_hbox);

    gtk_fixed_put(GTK_FIXED(signup_fix), Password_button, 310, 300);
    gtk_widget_set_size_request(Password_button, 20, 20);
    gtk_widget_set_visible(Password_button, FALSE);


    //Password_Confirmation
    GtkWidget *Password_Confirmation =gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password_Confirmation), "Confirm Password");
    gtk_fixed_put(GTK_FIXED(signup_fix), Password_Confirmation, 50, 340);
    gtk_widget_set_size_request(Password_Confirmation, 250, 25);
    gtk_entry_set_visibility(GTK_ENTRY(Password_Confirmation),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(Password_Confirmation),'*');


    //Confirm image
    GtkWidget *Confirm_Password_button = gtk_button_new();
    GtkWidget *Confirm_Password_image = gtk_image_new_from_file("../info_red.png");
    GtkWidget *Confirm_Password_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(Confirm_Password_hbox), Confirm_Password_image);
    gtk_button_set_child(GTK_BUTTON(Confirm_Password_button), Confirm_Password_hbox);

    gtk_fixed_put(GTK_FIXED(signup_fix), Confirm_Password_button, 310, 340);
    gtk_widget_set_size_request(Confirm_Password_button, 20, 20);
    gtk_widget_set_visible(Confirm_Password_button, FALSE);

    // Store the entry widgets in the login window using g_object_set_data
    g_object_set_data(G_OBJECT(signup_window), "signup_fix", signup_fix);
    g_object_set_data(G_OBJECT(signup_window), "First Name", first_name);
    g_object_set_data(G_OBJECT(signup_window), "Last Name", Last_name);
    g_object_set_data(G_OBJECT(signup_window), "CIN", cin);
    g_object_set_data(G_OBJECT(signup_window), "Email", Email);
    g_object_set_data(G_OBJECT(signup_window), "Birthday DD//MM//YYY", Birthday);
    g_object_set_data(G_OBJECT(signup_window), "Password", Password);
    g_object_set_data(G_OBJECT(signup_window), "Confirm Password", Password_Confirmation);
    g_object_set_data(G_OBJECT(signup_window), "First Name Image", first_name_button);
    g_object_set_data(G_OBJECT(signup_window), "Last Name Image", last_name_button);
    g_object_set_data(G_OBJECT(signup_window), "CIN Image", cin_button);
    g_object_set_data(G_OBJECT(signup_window), "Email Image", email_button);
    g_object_set_data(G_OBJECT(signup_window), "Birthday Image", Birthday_button);
    g_object_set_data(G_OBJECT(signup_window), "Password Image", Password_button);
    g_object_set_data(G_OBJECT(signup_window), "Confirm Password Image", Password_Confirmation);



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
}
