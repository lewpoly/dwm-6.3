/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const unsigned int gappih    = 18;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 18;       /* vert inner gap between windows */
static const unsigned int gappoh    = 18;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 18;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const char *fonts[]          = { "FiraCode Nerd Font:size=13.5", "JoyPixels:pixelsize=13.5:antialias=true:autohint=true", };
static const char dmenufont[]       = "FiraCode Nerd Font:size=13.5";
static const char *brupcmd[]            = { "brightnessctl", "set", "10%+", NULL };
static const char *brdowncmd[]          = { "brightnessctl", "set", "10%-", NULL };
static const char col_gray1[]       = "#222222";
/* static const char col_gray1[]       = "#000000"; */
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#d4d4d4";
static const char col_gray4[]       = "#fff";
static const char col_cyan[]        = "#005577";
/* static const char col_cyan[]        = "#042e48"; */
static const unsigned int baralpha = 0x70;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray3  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance  title           tags mask  iscentered    isfloating  isterminal  noswallow  monitor */
	{ "Alacritty",       NULL,     NULL,           0,         0,            0,          1,           0,        -1 },
	/* { "St",              NULL,     NULL,           0,         0,            0,          1,           0,        -1 }, */
	{ "Gimp",            NULL,     NULL,           1 << 5,    0,            0,          0,           0,        -1 },
	{ "discord",         NULL,     NULL,           1 << 4,    0,            0,          0,           0,        -1 },
	{ NULL,              NULL,     "Event Tester", 0,         0,            0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "alacritty", NULL };
static const char *webcmd[]  = { "brave", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key                        function        argument */
  { MODKEY|ShiftMask,             XK_d,                      spawn,          SHCMD("dmenu_run -l 20") },
	{ MODKEY,                       XK_d,                      spawn,          SHCMD("rofi -show drun") },
	{ MODKEY,                       XK_e,                      spawn,          SHCMD("rofi -show emoji -modi emoji") },
	{ MODKEY,                       XK_BackSpace,              spawn,          SHCMD("sysact") },
	{ MODKEY|ShiftMask,			        XK_p,                      spawn,		       SHCMD("feh --bg-fill --randomize ~/pics/wallpaper/* &") },
	{ MODKEY,			                  XK_r,                      spawn,		       SHCMD(TERMINAL " -e ranger") },
	{ MODKEY,			                  XK_y,                      spawn,		       SHCMD("flameshot screen -p ~/pics/screenshots") },
	{ MODKEY|ShiftMask,			        XK_y,                      spawn,		       SHCMD("flameshot gui -p ~/pics/screenshots") },
	{ MODKEY|ShiftMask,			        XK_v,                      spawn,		       SHCMD("mpv /dev/video0") },
  { MODKEY,                       XK_Tab,                    spawn,          SHCMD("skippy-xd --toggle-window-picker") },
	{ MODKEY,                       XK_p,                      spawn,          SHCMD("spotprev") },
	{ MODKEY,                       XK_n,                      spawn,          SHCMD("spotnext") },
	{ MODKEY,                       XK_v,                      spawn,          SHCMD("spotpause") },
	{ MODKEY,                       XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,                      spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_b,                      togglebar,      {0} },
	/* { MODKEY,                       XK_f,                      togglefullscr,  {0} }, */
	{ MODKEY,                       XK_t,                      setlayout,      {.v = &layouts[0]} }, //tile
	{ MODKEY,                       XK_m,                      setlayout,      {.v = &layouts[1]} }, //monocle
	{ MODKEY,                       XK_c,                      setlayout,      {.v = &layouts[11]} }, //centeredmaster
	{ MODKEY|ShiftMask,             XK_c,                      setlayout,      {.v = &layouts[12]} }, //centeredfloatingmaster
	{ MODKEY|ShiftMask,             XK_s,                      setlayout,      {.v = &layouts[2]} }, //spiral
	{ MODKEY|ShiftMask,             XK_j,                      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,                      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
	/* { MODKEY|ShiftMask,             XK_h,                      setcfact,       {.f = +0.25} }, */
	/* { MODKEY|ShiftMask,             XK_l,                      setcfact,       {.f = -0.25} }, */
	/* { MODKEY|ShiftMask,             XK_o,                      setcfact,       {.f =  0.00} }, */
	{ MODKEY,                       XK_x,                      incrgaps,       {.i = -1 } },
	{ MODKEY,                       XK_z,                      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Return,                 zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,                    view,           {0} },
	{ MODKEY,                       XK_q,                      killclient,     {0} },
	{ MODKEY,                       XK_space,                  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_f,                      togglefloating, {0} },
	{ MODKEY,                       XK_s,                      togglesticky,   {0} },
	/* { MODKEY,                       XK_0,                      view,           {.ui = ~0 } }, */
	/* { MODKEY|ShiftMask,             XK_0,                      tag,            {.ui = ~0 } }, */
	{ MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_equal,                  spawn,          SHCMD("changevolume up") },
 	{ MODKEY,                       XK_minus,                  spawn,          SHCMD("changevolume down") },
	{ MODKEY,                       XK_0,                      spawn,          SHCMD("changevolume mute") },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,          SHCMD("changevolume up") },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,          SHCMD("changevolume down") },
	{ 0,                            XF86XK_AudioMute,          spawn,          SHCMD("changevolume mute") },
  { 0,                            XF86XK_MonBrightnessUp,    spawn,          {.v = brupcmd}},
  { 0,                            XF86XK_MonBrightnessDown,  spawn,          {.v = brdowncmd}},
	TAGKEYS(                        XK_1,                                      0)
	TAGKEYS(                        XK_2,                                      1)
	TAGKEYS(                        XK_3,                                      2)
	TAGKEYS(                        XK_4,                                      3)
	TAGKEYS(                        XK_5,                                      4)
	TAGKEYS(                        XK_6,                                      5)
	TAGKEYS(                        XK_7,                                      6)
	TAGKEYS(                        XK_8,                                      7)
	TAGKEYS(                        XK_9,                                      8)
	{ MODKEY|ShiftMask,             XK_q,                      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,                      quit,           {1} }, 
	{ MODKEY|Mod1Mask,              XK_i,                      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,                      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,                      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,                      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,                      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,                      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,                      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,                      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,                      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,                      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,                      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,                      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_g,                      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_g,                      defaultgaps,    {0} },
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
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
