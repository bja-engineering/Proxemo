#if !defined(_VIEW_H)
#define _VIEW_H

#define EDJ_FILE "edje/main.edj"
#define GRP_MAIN "main"

#define RADIUS_MIN 80
#define CENTER_REF_X 180
#define CENTER_REF_Y 180

#define DAIL_INPUT_MAX 512

/* Text Style for Dial Entry */
#define DIAL_TEXT_STYLE_NORMAL "DEFAULT='font=Tizen:style=Light font_size=34 align=center'"
#define DIAL_TEXT_STYLE_SMALL "DEFAULT='font=Tizen:style=Light font_size=28 align=center'"
#define DIAL_TEXT_STYLE_SMALLER "DEFAULT='font=Tizen:style=Regular font_size=23 align=center'"

#define ENTRY_TEXT_MAX DAIL_INPUT_MAX

/* Entry text Control Option */
#define ENTRY_TEXT_CLEAR_ALL 0
#define ENTRY_TEXT_ADD_TEXT 1
#define ENTRY_TEXT_BACKSPACE 2

#define LONGPRESS_TIME 0.5f

void view_create(void);
Evas_Object *view_create_win(const char *pkg_name);
Evas_Object *view_create_conformant_without_indicator(Evas_Object *win);
Evas_Object *view_create_layout(Evas_Object *parent, const char *file_path, const char *group_name, Eext_Event_Cb cb_function, void *user_data);
Evas_Object *view_create_layout_for_conformant(Evas_Object *parent, const char *file_path, const char *group_name, Eext_Event_Cb cb_function, void *user_data);
Evas_Object *view_create_layout_by_theme(Evas_Object *parent, const char *class_name, const char *group_name, const char *style);
void view_destroy(void);
void view_set_image(Evas_Object *parent, const char *part_name, const char *image_path);
void view_set_text(Evas_Object *parent, const char *part_name, const char *text);
void view_set_color(Evas_Object *parent, const char *part_name, int r, int g, int b, int a);
void view_set_button(Evas_Object *parent, const char *part_name, const char *style, const char *image_path, const char *text,
		Evas_Object_Event_Cb down_cb, Evas_Object_Event_Cb up_cb, Evas_Smart_Cb clicked_cb, void *user_data);
Evas_Object *view_create_entry(Evas_Object *parent, const char *part_name, Evas_Smart_Cb clicked_cb, void *user_data);
Eina_Bool bezelRotationHandler(void *data, Eext_Rotary_Event_Info *ev);

Evas_Object *view_dialer_create_rectangle(void);
void view_dialer_create(const char *file_path);
int view_dialer_set_entry_text(int operation, const char *text);
void view_dialer_set_entry(const char *part_name);
Evas_Object *view_dialer_get_layout_object(void);
#endif
