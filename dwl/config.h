#include "/home/ashwin/.cache/wal/colors-wal-dwl.h"

/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 2;  /* border pixel of windows */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 0; /* 0 means bottom bar */
static const char *fonts[]                 = {"Iosevka:size=11"};
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* You can also use glsl colors */
static const float default_opacity_unfocus = 0.70f;
static const float default_opacity_focus   = 0.90f;

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

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
    * example of a HiDPI laptop monitor:
    { "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 }, */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	/* default monitor rule: can be changed but cannot be eliminated; at least one monitor rule must exist */
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	.layout = "us",
	.variant = "colemak_dh",
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
static const char *browsercmd[]   = { "qbpm", "choose", "-m dmenu", NULL };
static const char *termcmd[]      = { TERMINAL, NULL };
static const char *filescmd[]     = { "pcmanfm-qt", NULL };
static const char *lockcmd[] = { "swaylock", NULL };
static const char *emacscmd[]     = { "emacsclient", "-c", NULL };
static const char *phonecmd[]     = SHCMD("connect");
static const char *websearchcmd[] = SHCMD("websearch");
static const char *notescmd[] = SHCMD("notes");
static const char *musiccmd[]     = { TERMINAL, "-e", "rmpc", NULL };
static const char *wallpapercmd[]     = { "walmenu", NULL };

/* volume */
static const char *volup[]   = { "sh", "-c", "wpctl set-volume -l 1 @DEFAULT_AUDIO_SINK@ 5%+ && pkill -RTMIN+4 dwlblocks", NULL };
static const char *voldown[] = { "sh", "-c", "wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%- && pkill -RTMIN+4 dwlblocks", NULL };
static const char *volmute[] = { "sh", "-c", "wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle && pkill -RTMIN+4 dwlblocks", NULL };

/* brightness */
static const char *brup[]   = { "sh", "-c", "brightnessctl set +5% && pkill -RTMIN+5 dwlblocks", NULL };
static const char *brdown[] = { "sh", "-c", "brightnessctl set 5%- && pkill -RTMIN+5 dwlblocks", NULL };

static const Key keys[] = {
	/* modifier                  key                  function          argument */
	{ MODKEY,                    XKB_KEY_space,       spawn,            {.v = dmenucmd } },
	{ MODKEY,                    XKB_KEY_Return,      spawn,            {.v = termcmd} },
	{ MODKEY,                    XKB_KEY_v,           spawn,            {.v = clipcmd } },
	{ MODKEY,                    XKB_KEY_b,           spawn,            {.v = browsercmd } },
	{ MODKEY,                    XKB_KEY_f,           spawn,            {.v = filescmd } },
	{ MODKEY,                    XKB_KEY_w,           spawn,            {.v = emacscmd } },
	{ MODKEY,                    XKB_KEY_l,           spawn,            {.v = lockcmd } },
	{ MODKEY,                    XKB_KEY_p,           spawn,            {.v = phonecmd } },
	{ MODKEY,                    XKB_KEY_m,           spawn,            {.v = musiccmd } },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_r,           spawn,            {.v = websearchcmd } },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,       spawn,            {.v = notescmd } },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_space,       spawn,            {.v = wallpapercmd } },

    /* Navigation */
	{ MODKEY,                    XKB_KEY_n,           focusstack,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_o,           focusstack,       {.i = -1} },

    /* Resizing */
    { MODKEY,                    XKB_KEY_e,           setmfact,         {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_i,           setmfact,         {.f = +0.05f} },
    { MODKEY,                    XKB_KEY_g,           togglefloating,   {0} },
	{ MODKEY,                    XKB_KEY_a,           togglefullscreen, {0} },
    { MODKEY,                    XKB_KEY_s,           togglesticky,     {0} },

	/* Master Area */
	{ MODKEY,                    XKB_KEY_h,           incnmaster,       {.i = +1} },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_h,           incnmaster,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_z,           zoom,             {0} },
	{ MODKEY,                    XKB_KEY_Tab,         view,             {0} },

    /* Kill */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_q,           quit,             {0} },
	{ MODKEY,                    XKB_KEY_q,           killclient,       {0} },

    /* Layouts */
	{ MODKEY,                    XKB_KEY_t,           setlayout,        {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,           setlayout,        {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_m,           setlayout,        {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_k,           setlayout,        {0} },
 	{ MODKEY,                    XKB_KEY_x,           togglebar,        {0} },
	{ MODKEY,                    XKB_KEY_0,           view,             {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright,  tag,              {.ui = ~0} },

    /* Opacity */
    { MODKEY,                    XKB_KEY_d,          setopacityunfocus, {.f = +0.1f} },
	{ MODKEY,                    XKB_KEY_c,          setopacityunfocus, {.f = -0.1f} },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_d, setopacityfocus, {.f = +0.1f} },
	{ MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_c, setopacityfocus, {.f = -0.1f} },

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
    { 0, XKB_KEY_XF86MonBrightnessUp,   spawn, {.v = brup} },
    { 0, XKB_KEY_XF86MonBrightnessDown, spawn, {.v = brdown} },
    
	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },

#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
};
