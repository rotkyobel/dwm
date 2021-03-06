/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 24;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 3;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Sarasa Term SC:pixelsize=14:style=semibold", "JetBrainsMono Nerd Font:pixelsize=14:style=medium", "JoyPixels:pixelsize=12:antialias=true:autohint=true" };
static const char dmenufont[]       = "Sarasa Term SC:pixelsize=14:style=semibold";

#include "/home/hw/.cache/wal/colors-wal-dwm.h"

/* staticstatus */
static const int statmonval = 0;

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7" };
static const char *tags[] = { "", "", "", "ﬥ", "", "ﭮ", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance    title            tags mask     isfloating   monitor */
  /* class             instance    title            tags mask     isfloating   isterminal  noswallow  monitor */
  { "St",              NULL,       NULL,            0,            0,           1,           0,        -1 },
  { NULL,              NULL,       "Event Tester",  0,            0,           0,           1,        -1 }, /* xev */
  { "Pavucontrol",     NULL,       NULL,            0,            1,           0,           0,        -1 },
  { "gtksu",           NULL,       NULL,            0,            1,           0,           0,        -1 },
  { "obs",             NULL,       NULL,            0,            1,           0,          -1,        -1 },
  { "TelegramDesktop", NULL,       NULL,            0,            1,           0,          -1,        -1 },
  { "firefox",         NULL,       NULL,            1 << 0,       0,           0,          -1,        -1 },
  { "Code",            NULL,       NULL,            1 << 1,       0,           0,          -1,        -1 },
  { "Chromium",        NULL,       NULL,            1 << 2,       0,           0,          -1,        -1 },
  { "Insomnia",        NULL,       NULL,            1 << 3,       0,           0,          -1,        -1 },
  { "Mailspring",      NULL,       NULL,            1 << 4,       0,           0,          -1,        -1 },
  { "discord",         NULL,       NULL,            1 << 5,       0,           0,          -1,        -1 },
  { "Steam",           NULL,       NULL,            1 << 6,       0,           0,          -1,        -1 },
  { "Kodi",            NULL,       NULL,            1 << 7,       0,           0,          -1,        -1 },
  { "qBittorrent",     NULL,       NULL,            1 << 8,       0,           0,          -1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[G]",      grid },
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

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key             function            argument */
	{ MODKEY,                       XK_l,           setmfact,           {.f = +0.05} },
	{ MODKEY,                       XK_k,           focusstack,         {.i = -1} },
	{ MODKEY,                       XK_j,           focusstack,         {.i = +1} },
	{ MODKEY,                       XK_h,           setmfact,           {.f = -0.05} },
	{ Mod1Mask,                     XK_Tab,         focusstack,         {.i = +1} },
	{ MODKEY,                       XK_g,           togglebar,          {0} },
	{ MODKEY,                       XK_f,	        zoom,               {0} },
	{ MODKEY,                       XK_d,           incnmaster,         {.i = -1} },
	{ MODKEY,                       XK_s,           incnmaster,         {.i = +1} },
	{ MODKEY,		        XK_q,           killclient,         {0} },
	{ MODKEY,                       XK_w,           setlayout,          {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,           setlayout,          {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,           setlayout,          {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_r,  	        togglefloating,     {0} },
	{ MODKEY,                       XK_t,           setlayout,          {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_j,           rotatestack,        {.i = +1} },
	{ MODKEY|ShiftMask,             XK_k,           rotatestack,        {.i = -1} },
  	{ MODKEY|ShiftMask,             XK_h,           setcfact,           {.f = +0.25} },
  	{ MODKEY|ShiftMask,             XK_l,           setcfact,           {.f = -0.25} },
  	{ MODKEY|ShiftMask,             XK_o,           setcfact,           {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_f,           fullscreen,         {0} },
  	{ MODKEY|ControlMask,	        XK_comma,       cyclelayout,        {.i = -1} },
	{ MODKEY|ControlMask,           XK_period,      cyclelayout,        {.i = +1} },
	{ MODKEY,                       XK_comma,       focusmon,           {.i = -1} },
	{ MODKEY,                       XK_period,      focusmon,           {.i = +1} },
	{ MODKEY|ShiftMask,             XK_comma,       tagmon,             {.i = -1} },
	{ MODKEY|ShiftMask,             XK_period,      tagmon,             {.i = +1} },
	{ MODKEY,                       XK_space,       spawn,              SHCMD("rofi -show drun") },
	{ MODKEY|ShiftMask,             XK_space,       spawn,              SHCMD("rofi -show drun -run-command 'gtksu {cmd}'") },
	{ MODKEY,			XK_Return,      spawn,              {.v = termcmd} },
	{ MODKEY,                       XK_Tab,         view,               {0} },
  	{ MODKEY|ShiftMask,             XK_Tab,         shiftviewclients,   { .i = +1} },
	{ MODKEY|ShiftMask,             XK_backslash,   shiftviewclients,   { .i = -1} },
	{ MODKEY,                       XK_0,           view,               {.ui = ~0} },
	{ MODKEY|ShiftMask,             XK_0,           tag,                {.ui = ~0} },
	{ MODKEY,			XK_minus,       setgaps,	    {.i = -1} },
	{ MODKEY,			XK_equal,       setgaps,	    {.i = +1} },
	{ MODKEY|ShiftMask,		XK_equal,       setgaps,	    {.i =  0} },
	TAGKEYS(                        XK_1,                      	    0)
	TAGKEYS(                        XK_2,                      	    1)
	TAGKEYS(                        XK_3,                      	    2)
	TAGKEYS(                        XK_4,                               3)
	TAGKEYS(                        XK_5,                      	    4)
	TAGKEYS(                        XK_6,                         	    5)
	TAGKEYS(                        XK_7,                      	    6)
	TAGKEYS(                        XK_8,                      	    7)
	TAGKEYS(                        XK_9,                               8)
	{ MODKEY|ShiftMask,		XK_q,           quit,               {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
