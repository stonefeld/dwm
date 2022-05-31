/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx        = 2;        /* border pixel of windows */
static const unsigned int snap            = 8;        /* snap pixel */
static const int showbar                  = 1;        /* 0 means no bar */
static const int topbar                   = 1;        /* 0 means bottom bar */
static const char *fonts[]                = { "Fantasque Sans Mono:pixelsize=16:antialias=true:autohint=true",
                                              "Material Design Icons-Regular:pixelsize=16:antialias:true:autohint=true",
                                              "JoyPixels:pixelsize=12:antialias:true:autohint=true" };

/* dmenu */
static const char dmenufont[]             = "monospace:size=12";

/* systray */
static const unsigned int systraypinning  = 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;        /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 2;        /* systray spacing */
static const int systraypinningfailfirst  = 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray              = 1;        /* 0 means no systray */

/* statuspadding */
static const int horizpadbar              = 10;       /* horizontal padding for statusbar */
static const int vertpadbar               = 10;       /* vertical padding for statusbar */

/* barpadding */
static const int vertpad                  = 10;       /* vertical padding of bar */
static const int sidepad                  = 10;       /* horizontal padding of bar */

/* fullgaps */
static const Gap default_gap              = {.isgap = 1, .realgap = 10, .gappx = 10};

/* colors */
#include "themes/catppuccin.h"
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { norm_fg,   norm_bg,   norm_border },
	[SchemeSel]  = { sel_fg,    sel_bg,    sel_border  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance    title       tags mask     isfloating   monitor */
	{ "Pavucontrol",          NULL,       NULL,       0,            1,           -1 },
	{ "Galculator",           NULL,       NULL,       0,            1,           -1 },
	{ "Pcmanfm",              NULL,       NULL,       0,            1,           -1 },
	{ "Nemo",                 NULL,       NULL,       0,            1,           -1 },
	{ "Floating",             NULL,       NULL,       0,            1,           -1 },
	{ "MPlayer",              NULL,       NULL,       0,            1,           -1 },
	{ "Sxiv",                 NULL,       NULL,       0,            1,           -1 },
	{ "Pinentry-gtk-2",       NULL,       NULL,       0,            1,           -1 },
	{ "Nm-connection-editor", NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg, "-sf", sel_fg, "-i", NULL };
// static const char *termcmd[]  = { "st", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "alacritty", "-t", scratchpadname, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	// { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_m,      togglefullscr,  {0} },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },

	{ MODKEY|ShiftMask,             XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_q,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,      tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },

	{ MODKEY|ControlMask,           XK_j,      moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_k,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_l,      moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_h,      moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ControlMask|ShiftMask, XK_j,      moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ControlMask|ShiftMask, XK_k,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ControlMask|ShiftMask, XK_l,      moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ControlMask|ShiftMask, XK_h,      moveresize,     {.v = "0x 0y -25w 0h" } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("dmlogout") },
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },

	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
};

