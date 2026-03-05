#include "/home/ashwin/.cache/wal/colors-wal-dwl.h"

/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const int smartgaps                 = 0;  /* 1 means no outer gap when there is only one window */
static const unsigned int borderpx         = 2;  /* border pixel of windows */
static const int monoclegaps               = 1;  /* 1 means outer gaps in monocle layout */
static const unsigned int gappih           = 8; /* horiz inner gap between windows */
static const unsigned int gappiv           = 8; /* vert inner gap between windows */
static const unsigned int gappoh           = 8; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov           = 8; /* vert outer gap between windows and screen edge */
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */
static const float default_opacity_unfocus = 0.70f;
static const float default_opacity_focus   = 0.95f;

/* tagging */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

 static const Rule rules[] = {
	/* app_id             title       tags mask     isfloating   alpha unfocus      monitor */
    { "mpv",              NULL,       0,            1,           1.00,                    -1 },
    { "xeyes",            NULL,       1 << 8,       1,           1,                       -1 },
 };

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients due to
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899 */
static const MonitorRule monrules[] = {
   /* name        mfact  nmaster scale layout       rotate/reflect                x    y
    * example of a HiDPI laptop monitor: */
    { "eDP-1",    0.5f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   0,  0 },
	/* default monitor rule: can be changed but cannot be eliminated; at least one monitor rule must exist */
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	.layout = "us",
	.options = NULL,
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { "sh", "-c", cmd, NULL }
#define TERMINAL "foot"

/* commands */
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *clipcmd[] = { "sh", "-c", "cliphist list | rofi -dmenu | cliphist decode | wl-copy", NULL };
static const char *browsercmd[]   = { "glide-bin", "--new-instance", NULL };
static const char *termcmd[]      = { TERMINAL, NULL };
static const char *filescmd[]     = { "pcmanfm", NULL };
static const char *lockcmd[] = { "lock.sh", NULL };
static const char *emacscmd[]     = { "emacs", NULL };
static const char *phonecmd[]     = SHCMD("connect");
static const char *websearchcmd[] = SHCMD("websearch");
static const char *notescmd[] = SHCMD("notes");
static const char *musiccmd[]     = { TERMINAL, "-e", "rmpc", NULL };
static const char *wallpapercmd[]     = SHCMD("walmenu");

/* volume */
static const char *volup[]      = { "osd", "volume", "5%+",      NULL };
static const char *voldown[]    = { "osd", "volume", "5%-",      NULL };
static const char *volmute[]    = { "osd", "volume", "toggle",   NULL };
static const char *briup[]      = { "osd", "brightness", "10%+", NULL };
static const char *bridown[]    = { "osd", "brightness", "10%-", NULL };

static const Key keys[] = {
	/* modifier                  key                  function          argument */
	{ MODKEY,                    XKB_KEY_space,       spawn,            {.v = dmenucmd } },
	{ MODKEY,                    XKB_KEY_Return,      spawn,            {.v = termcmd} },
	{ MODKEY,                    XKB_KEY_v,           spawn,            {.v = clipcmd } },
	{ MODKEY,                    XKB_KEY_t,           spawn,            {.v = browsercmd } },
	{ MODKEY,                    XKB_KEY_e,           spawn,            {.v = filescmd } },
	{ MODKEY,                    XKB_KEY_w,           spawn,            {.v = emacscmd } },
	{ MODKEY,                    XKB_KEY_u,           spawn,            {.v = lockcmd } },
	{ MODKEY,                    XKB_KEY_p,           spawn,            {.v = phonecmd } },
	{ MODKEY,                    XKB_KEY_m,           spawn,            {.v = musiccmd } },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_r,           spawn,            {.v = websearchcmd } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,       spawn,            {.v = notescmd } },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_space,       spawn,            {.v = wallpapercmd } },

    /* Navigation */
	{ MODKEY,                    XKB_KEY_j,           focusstack,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,           focusstack,       {.i = -1} },

    /* Resizing */
    { MODKEY,                    XKB_KEY_h,           setmfact,         {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,           setmfact,         {.f = +0.05f} },
    { MODKEY,                    XKB_KEY_g,           togglefloating,   {0} },
	{ MODKEY,                    XKB_KEY_a,           togglefullscreen, {0} },
    { MODKEY,                    XKB_KEY_d,           togglesticky,     {0} },

	/* Master Area */
	{ MODKEY,                    XKB_KEY_b,           zoom,             {0} },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_b,           incnmaster,       {.i = +1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_b,           incnmaster,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_Tab,         view,             {0} },

    /* Kill */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_q,           quit,             {0} },
	{ MODKEY,                    XKB_KEY_q,           killclient,       {0} },

    /* Gaps */
    { MODKEY|WLR_MODIFIER_ALT,  XKB_KEY_h,          incgaps,       {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_ALT,  XKB_KEY_l,          incgaps,       {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT,   XKB_KEY_H,      incogaps,      {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT,   XKB_KEY_L,      incogaps,      {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_ALT|WLR_MODIFIER_CTRL,    XKB_KEY_h,      incigaps,      {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_ALT|WLR_MODIFIER_CTRL,    XKB_KEY_l,      incigaps,      {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_ALT,  XKB_KEY_0,          togglegaps,     {0} },
	{ MODKEY|WLR_MODIFIER_ALT|WLR_MODIFIER_SHIFT,   XKB_KEY_parenright,defaultgaps,    {0} },
	{ MODKEY,                    XKB_KEY_y,          incihgaps,     {.i = +1 } },
	{ MODKEY,                    XKB_KEY_o,          incihgaps,     {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_y,          incivgaps,     {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_o,          incivgaps,     {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_ALT,  XKB_KEY_y,          incohgaps,     {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_ALT,  XKB_KEY_o,          incohgaps,     {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Y,          incovgaps,     {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_O,          incovgaps,     {.i = -1 } },

    /* Layouts */
	{ MODKEY,                    XKB_KEY_c,           setlayout,        {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_x,           setlayout,        {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_z,           setlayout,        {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_n,           setlayout,        {0} },
	{ MODKEY,                    XKB_KEY_0,           view,             {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright,  tag,              {.ui = ~0} },
    { MODKEY,                    XKB_KEY_y,           togglebar,        {0} },

    /* Opacity */
    { MODKEY,                    XKB_KEY_r,          setopacityunfocus, {.f = +0.1f} },
	{ MODKEY,                    XKB_KEY_s,          setopacityunfocus, {.f = -0.1f} },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_r, setopacityfocus, {.f = +0.1f} },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_s, setopacityfocus, {.f = -0.1f} },

    /* Monitors */
	{ MODKEY,                    XKB_KEY_comma,       focusmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,      focusmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,        tagmon,           {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,     tagmon,           {.i = WLR_DIRECTION_RIGHT} },

    /* Tags */
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                        0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                            1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                    2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                        3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                       4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                   5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                     6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                      7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                     8),

    /* System Keys */
    { 0, XKB_KEY_XF86AudioRaiseVolume,  spawn, {.v = volup} },
    { 0, XKB_KEY_XF86AudioLowerVolume,  spawn, {.v = voldown} },
    { 0, XKB_KEY_XF86AudioMute,         spawn, {.v = volmute} },
    { 0, XKB_KEY_XF86MonBrightnessUp,   spawn, {.v = briup} },
    { 0, XKB_KEY_XF86MonBrightnessDown, spawn, {.v = bridown} },
    
	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },

#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};


static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};

