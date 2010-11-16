
/* External Programs used
   amixer
   mpc
   dmpc
   dmenu
   xterm
*/

#include <X11/XF86keysym.h> /* makes XF86* keys work */
#include "gaplessgrid.c" /* gapless layout */
#include "bstack.c"
#include "bstackhoriz.c"
/* appearance */
static const char font[]            = "-*-GohuFont-*-*-*-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#8BB4FF";
static const char normbgcolor[]     = "#000000";
static const char normfgcolor[]     = "#83AFB5";
static const char selbordercolor[]  = "#C60000";
static const char selbgcolor[]      = "#5488FF";
static const char selfgcolor[]      = "#000000";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;     /* False means bottom bar */
/* tagging */
static const char *tags[] = { "Chat", "Web", "3", "4", "Gimp", "6", "7", "8", "Junk" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Namoroka", NULL,       NULL,       2,            False,       -1 },
        { "MPlayer",  NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
	{ "flt",      NULL },    /* no layout function means floating behavior */
	{ "===",  bstackhoriz}, 
        { "[M]",      monocle },
	{ "TTT",      bstack },
        { "###",      gaplessgrid }, /* gapless */
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
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "xterm", NULL };
 /* Volume */
static const char *sound_up[] = { "/usr/bin/amixer", "-q", "set", "Master", "3+", NULL };
static const char *sound_down[] = { "/usr/bin/amixer", "-q", "set", "Master", "3-", NULL };
static const char *sound_mute[] = { "/usr/bin/amixer", "-q", "set", "Master", "toggle", NULL };
 /* MPD */
static const char *mpd_toggle[] = { "/usr/bin/mpc", "toggle", NULL };
static const char *mpd_stop[] = { "/usr/bin/mpc", "stop", NULL };
static const char *mpd_prev[] = { "/usr/bin/mpc", "prev", NULL };
static const char *mpd_next[] = { "/usr/bin/mpc", "next", NULL };
static const char *dmpc_start[] = { "/usr/bin/dmpc", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[3]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
        /* Volume */
         { 0,                           XF86XK_AudioRaiseVolume, spawn, {.v = sound_up } },
         { 0,                           XF86XK_AudioLowerVolume, spawn, {.v = sound_down } },
         { 0,                           XF86XK_AudioMute, spawn,        {.v = sound_mute } },
        /* MPD */
         { 0,                           XF86XK_AudioPlay, spawn,        {.v = mpd_toggle } },
         { 0,                           XF86XK_AudioStop, spawn,        {.v = mpd_stop } },
         { 0,                           XF86XK_AudioPrev, spawn,        {.v = mpd_prev } },
         { 0,                           XF86XK_AudioNext, spawn,        {.v = mpd_next } },
         { MODKEY|ShiftMask,            XK_m,      spawn,               {.v = dmpc_start } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)   
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

