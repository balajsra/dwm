/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "$HOME/bar.sh"; /* Alternate bar launch command */
static const char *fonts[]          = { "NotoSans Nerd Font:size=10" };
static const char col_gray1[]       = "#282a36"; /* background color */
static const char col_gray2[]       = "#44475a"; /* inactive window border color */
static const char col_gray3[]       = "#f8f8f2"; /* font color */
static const char col_gray4[]       = "#282a36"; /* current tag and current window font color */
static const char col_cyan[]        = "#bd93f9"; /* Top bar second color and active window border color */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *const autostart[] = {
	// System Restore Processes
    "bash", "/home/sravan/.screenlayout/default-screen-layout.sh", NULL, // Restore default screen layout
    "nitrogen", "--restore", NULL,                                       // Restore wallpaper
    // System Tray Applications
    "volctl", NULL,                                                      // PulseAudio Volume Control
    "nyrna", NULL,                                                       // Nyrna Application Suspend
    "blueman-tray", NULL,                                                // Blueman Bluetooth Manager
    "nm-applet", NULL,                                                   // Network Manager Applet
    "kdeconnect-indicator", NULL,                                        // KDE Connect
    "flameshot", NULL,                                                   // Flameshot Screenshot Tool
	"xfce4-power-manager", NULL,                                         // XFCE4 Power Manager
    // Background Processes
    "picom", "--config", "/home/sravan/.config/picom/picom.conf", NULL,  // Picom Compositor
    "/usr/lib/xfce4/notifyd/xfce4-notifyd", NULL,                        // Xfce Notification Daemon
    "greenclip", "daemon", NULL,                                         // Greenclip Clipboard Manager
    "redshift", "-x", NULL,                                              // Reset redshift display gamma
    "redshift-gtk", NULL,                                                // Redshift Blue Light Filter
    "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,   // GNOME Polkit Authentication Agent
    "slstatus", NULL,                                                    // slstatus status bar
    "light-locker", "--lock-on-suspend", "--lock-on-lid", NULL,          // LightDM Locker
    // Hardware Driver Applications
    "solaar", "--window=hide", NULL,                                     // Logitech Mouse Driver
    "polychromatic-tray-applet", NULL,                                   // Razer Keyboard Customization
    "optimus-manager-qt", NULL,                                          // Optimus Manager Qt
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { " ₁", "龎 ₂", " ₃", " ₄", "爵 ₅", " ₆", " ₇", " ₈", " ₉" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "origin",   NULL,       NULL,       0,            1,           1,           -1 },
	// { "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static int attachbelow = 1;    /* 1 means attach after the currently active window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask		/* Mod1Mask = Alt, Mod4Mask = Super */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *rofiruncmd[]			= { "rofi", "-show", "drun",	  NULL };
static const char *roficlipcmd[]		= { "rofi", "-show", "clipboard", NULL };
static const char *lockcmd[]			= { "light-locker-command", "--lock",  NULL };
static const char *sleepcmd[]			= { "systemctl",			"suspend", NULL };
static const char *termcmd[]			= { "alacritty", NULL };
static const char *upvolcmd[]			= { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "+1%",     NULL };
static const char *downvolcmd[]			= { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "-1%",     NULL };
static const char *mutevolcmd[]			= { "/usr/bin/pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle",  NULL };
static const char *brightness_up[]		= { "xbacklight", "-inc", "1", NULL };
static const char *brightness_down[]	= { "xbacklight", "-dec", "1", NULL };
static const char *playerplaypausecmd[]	= { "playerctl", "--player=playerctld", "play-pause", NULL };
static const char *playernextcmd[]		= { "playerctl", "--player=playerctld", "next", 	  NULL };
static const char *playerprevcmd[]		= { "playerctl", "--player=playerctld", "previous",   NULL };
static const char *flameshotcmd[]		= { "flameshot", "gui",	NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key                         function              argument */
	{ MODKEY,						XK_p,	                    spawn,                {.v = rofiruncmd} },
	{ MODKEY,						XK_c,	                    spawn,                {.v = roficlipcmd} },
	{ MODKEY|ControlMask|ShiftMask, XK_l,	                    spawn,                {.v = lockcmd} },
	{ MODKEY|ControlMask|ShiftMask, XK_s,	                    spawn,                {.v = sleepcmd} },
	{ MODKEY|ShiftMask,				XK_Return,                  spawn,                {.v = termcmd} },
	{ MODKEY,                       XK_b,                       togglebar,            {0} },
	{ MODKEY,                       XK_j,                       focusstack,           {.i = +1 } },
	{ MODKEY,                       XK_k,                       focusstack,           {.i = -1 } },
	{ MODKEY,                       XK_i,                       incnmaster,           {.i = +1 } },
	{ MODKEY,                       XK_d,                       incnmaster,           {.i = -1 } },
	{ MODKEY|ControlMask,           XK_j,                       movestack,            {.i = +1 } },
	{ MODKEY|ControlMask,           XK_k,                       movestack,            {.i = -1 } },
	{ MODKEY,                       XK_h,                       setmfact,             {.f = -0.05} },
	{ MODKEY,                       XK_l,                       setmfact,             {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,                       setcfact,             {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,                       setcfact,             {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,                       setcfact,             {.f =  0.00} },
	{ MODKEY,                       XK_Return,                  zoom,                 {0} },
	{ MODKEY|ControlMask,           XK_u,                       incrgaps,             {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_u,                       incrgaps,             {.i = -1 } },
	{ MODKEY|ControlMask,           XK_i,                       incrigaps,            {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_i,                       incrigaps,            {.i = -1 } },
	{ MODKEY|ControlMask,           XK_o,                       incrogaps,            {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_o,                       incrogaps,            {.i = -1 } },
	{ MODKEY|ControlMask,           XK_6,                       incrihgaps,           {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_6,                       incrihgaps,           {.i = -1 } },
	{ MODKEY|ControlMask,           XK_7,                       incrivgaps,           {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_7,                       incrivgaps,           {.i = -1 } },
	{ MODKEY|ControlMask,           XK_8,                       incrohgaps,           {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_8,                       incrohgaps,           {.i = -1 } },
	{ MODKEY|ControlMask,           XK_9,                       incrovgaps,           {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_9,                       incrovgaps,           {.i = -1 } },
	{ MODKEY|ControlMask,           XK_0,                       togglegaps,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_0,                       defaultgaps,          {0} },
	{ MODKEY,                       XK_Tab,                     comboview,            {0} },
	{ MODKEY|ShiftMask,             XK_j,                       aspectresize,         {.i = +24} },
	{ MODKEY|ShiftMask,             XK_k,                       aspectresize,         {.i = -24} },
	{ MODKEY|ShiftMask,             XK_c,                       killclient,           {0} },
	{ MODKEY,                       XK_t,                       setlayout,            {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                       setlayout,            {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                       setlayout,            {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                   setlayout,            {0} },
	{ MODKEY|ShiftMask,             XK_space,                   togglefloating,       {0} },
	{ MODKEY|ShiftMask,             XK_f,                       togglefullscr,        {0} },
	{ MODKEY,                       XK_Tab,                     toggleAttachBelow,    {0} },
	{ MODKEY,                       XK_0,                       comboview,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                       combotag,             {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                   focusmon,             {.i = -1 } },
	{ MODKEY,                       XK_period,                  focusmon,             {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,               {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,               {.i = +1 } },
	{ 0,							XF86XK_AudioLowerVolume,	spawn,			      {.v = downvolcmd} },
	{ 0,                			XF86XK_AudioMute,			spawn,			      {.v = mutevolcmd} },
	{ 0,                			XF86XK_AudioRaiseVolume,	spawn,			      {.v = upvolcmd} },
	{ 0, 							XF86XK_MonBrightnessUp,		spawn,			      {.v = brightness_up} },
	{ 0, 							XF86XK_MonBrightnessDown,	spawn,			      {.v = brightness_down} },
	{ 0,							XF86XK_AudioPlay,			spawn,			      {.v = playerplaypausecmd} },
	{ 0,							XF86XK_AudioNext,			spawn,			      {.v = playernextcmd} },
	{ 0,							XF86XK_AudioPrev,			spawn,			      {.v = playerprevcmd} },
	{ 0,							XK_Print,					spawn,			      {.v = flameshotcmd} },
	TAGKEYS(                        XK_1,                            0)
	TAGKEYS(                        XK_2,                            1)
	TAGKEYS(                        XK_3,                            2)
	TAGKEYS(                        XK_4,                            3)
	TAGKEYS(                        XK_5,                            4)
	TAGKEYS(                        XK_6,                            5)
	TAGKEYS(                        XK_7,                            6)
	TAGKEYS(                        XK_8,                            7)
	TAGKEYS(                        XK_9,                            8)
	{ MODKEY|ControlMask|ShiftMask, XK_q,                       quit,                 {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        comboview,      {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        combotag,       {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

