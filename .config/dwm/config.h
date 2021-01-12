/* See LICENSE file for copyright and license details. */

#define FONT "peep-12"

/* appearance */
static const char *fonts[]                 = { FONT };
static const char normbgcolor[]          = "#181818"; // top bar bg
static const char normfgcolor[]          = "#999999"; // top bar fg
static const char selbgcolor[]           = "#181818"; // top bar selection bg
static const char selfgcolor[]           = "#eeeeee"; // top bar selection fg
static const char normbordercolor[]      = "#242424"; // window border bg
static const char selbordercolor[]       = "#990000"; // window border fg
static const char warncolor[]            = "#DE6D03"; // status bg warning
static const char critcolor[]            = "#B91807"; // status bg critical
static const unsigned int borderpx       = 1;         // window border size px
static const unsigned int gappx          = 8;         // window gap size px
static const unsigned int snap           = 8;         // snap distance px
static const unsigned int systrayspacing = 1;         // systray spacing
static const unsigned int systraypinning = 1;         // 0 tray follows mouse
static const int rmaster                 = 0;         // 1 means master-area is on the right
static const int systraypinningfailfirst = 1;         // 1 first screen, 0 last
static const int showsystray             = 1;         // 0 = no systray
static const int showbar                 = 1;         // 0 = no bar
static const int topbar                  = 1;         // 0 = bottom bar

static const char *colors[][3]      = {
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]  = { selfgcolor, selbgcolor, selbordercolor },
    [SchemeWarn] = { selfgcolor, warncolor, selbordercolor },
    [SchemeCrit] = { selfgcolor, critcolor, selbordercolor },
};

/* dmenu options */
#define DMENUOPTS "-fn", FONT, "-nb", normbgcolor, "-nf", normfgcolor, \
                  "-sb", selbgcolor, "-sf", selfgcolor

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* rules */
static const Rule rules[] = {
    /* class                instance title tagmask isfloating mon neverfocus */
    { "TelegramDesktop",      NULL, NULL,               0,    True,   -1,   0},
    { "com-sap-platin-Gui$1", NULL, "win0",             0,    True,   -1,   0},
    { "SAP GUI for Java",     NULL, "SAP GUI for Java", 0,    True,   -1,   0},
    { "mpv",                  NULL, NULL,               0,    True,   -1,   0},
    { "st-osd",               NULL, NULL,               0,    True,   -1,   0},
    { "Gimp",                 NULL, NULL,               0,    True,   -1,   0},
    { "Pqiv",                 NULL, NULL,               0,    True,   -1,   1},
    { "Pidgin",               NULL, NULL,               0,    True,   -1,   0},
    { "Seafile Client",       NULL, NULL,               0,    True,   -1,   0},
    { "QSyncthingTray",       NULL, NULL,               0,    True,   -1,   0},
};

/* layout(s) */
static const float mfact     = 0.50; // factor of master area size [0.05..0.95]
static const int nmaster     = 1;    // number of clients in master area
static const int resizehints = 0;    // 1 = respect size hints in tiles

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[D]",      deck},     // first entry is default
	{ "[F]",      NULL },    // no layout function means floating behavior
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */



/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* commands */
static char dmenumon[2] = "0";
static const char scratchpadname[] = "maeG0guw6lah0ohvooke";
static const char *dmenucmd[]    = { "dmenu_run", DMENUOPTS, NULL };

/* custom commands */
static const char *termcmd[]       = { "st", NULL };
static const char *bigtermcmd[]    = { "st","-f", "Terminus-22:bold", NULL };
static const char *smalltermcmd[]  = { "st","-f", "ProFont", NULL };

static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "160x28", NULL };
static const char *browsercmd[]    = { ".dwm/browser", DMENUOPTS, NULL };
static const char *passmenucmd[]   = { ".dwm/passmenu", DMENUOPTS, NULL };
static const char *sshot[]         = { ".dwm/sshot", NULL };
static const char *preview[]       = { "st", "-c", "st-osd", "-g", "57x6+950+30", "-f", "peep-9", "-e", "/home/sdk/.dwm/preview", NULL };
static const char *youtube[]       = { ".dwm/youtube", NULL };

static const char *timer[]       = { ".dwm/timer", NULL };
static const char *notescmd[]      = { "st", "-e", "vim", "sftp://sdk@shell.codevoid.de/work/notes/notes.txt", NULL };

static const char *updateStatus[]  = { "pkill", "-SIGUSR1", "dwmstatus", NULL };
static const char *unMute[]        = { "mixerctl", "outputs.spkr_mute=off", NULL };

#include "maximize.c"
static Key keys[] = {
    /* modifier            key         function        argument */
    { 0,                   0x1008ff13, spawn,          {.v = updateStatus } },
    { 0,                   0x1008ff11, spawn,          {.v = updateStatus } },
    { 0,                   0x1008ff12, spawn,          {.v = unMute } },
    { MODKEY,              XK_d,       spawn,          {.v = dmenucmd } },
    { MODKEY,              XK_Return,  spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,    XK_Return,  spawn,          {.v = bigtermcmd } },
    { ControlMask|ShiftMask,    XK_Return,  spawn,          {.v = smalltermcmd } },
    { MODKEY|ShiftMask,    XK_f,       spawn,          {.v = browsercmd } },
    { MODKEY|ShiftMask,    XK_p,       spawn,          {.v = passmenucmd } },
    { MODKEY,              XK_p,       spawn,          {.v = preview } },
    { MODKEY,              XK_y,       spawn,          {.v = youtube } },
    { MODKEY|ShiftMask,    XK_Print,   spawn,          {.v = sshot } },
    { MODKEY|ShiftMask,    XK_o,       spawn,          {.v = notescmd } },
    { MODKEY|ShiftMask,    XK_t,       spawn,          {.v = timer } },
    { MODKEY,              XK_minus,   togglescratch,  {.v = scratchpadcmd } },
    { MODKEY|ShiftMask,    XK_r,       togglermaster,  {0} },
    { MODKEY,              XK_b,       togglebar,      {0} },
    { MODKEY,              XK_Right,   focusstack,     {.i = +1 } },
    { MODKEY,              XK_Left,    focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,    XK_i,       incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,    XK_d,       incnmaster,     {.i = -1 } },
    { MODKEY,              XK_m,       zoom,           {0} },
    { MODKEY,              XK_h,       setmfact,       {.f = -0.05} },
    { MODKEY,              XK_l,       setmfact,       {.f = +0.05} },
    { MODKEY,              XK_Tab,     view,           {0} },
    { MODKEY,    	   XK_q,       killclient,     {0} },
  //{ MODKEY,              XK_t,       setlayout,      {.v = &layouts[0]} },
  //{ MODKEY,              XK_m,       setlayout,      {.v = &layouts[1]} },
    { MODKEY,              XK_f,       togglemaximize, {0} },
    { MODKEY|ShiftMask,    XK_space,   togglefloating, {0} },
    { MODKEY,              XK_0,       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,    XK_0,       tag,            {.ui = ~0 } },
    { MODKEY,              XK_comma,   focusmon,       {.i = -1 } },
    { MODKEY,              XK_period,  focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,    XK_comma,   tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,    XK_period,  tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask,    XK_Left,    viewtoleft,     {0} },
    { MODKEY|ShiftMask,    XK_Right,   viewtoright,    {0} },
    { MODKEY|ShiftMask,    XK_End,     quit,           {0} },
    TAGKEYS(               XK_1,                       0)
    TAGKEYS(               XK_2,                       1)
    TAGKEYS(               XK_3,                       2)
    TAGKEYS(               XK_4,                       3)
    TAGKEYS(               XK_5,                       4)
    TAGKEYS(               XK_6,                       5)
    TAGKEYS(               XK_7,                       6)
    TAGKEYS(               XK_8,                       7)
    TAGKEYS(               XK_9,                       8)
};

/* button definitions; click can be:
 * ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, ClkRootWin */
static Button buttons[] = {
    /* click         event mask button   function        argument */
    { ClkLtSymbol,   0,         Button1, setlayout,      {0} },
    { ClkLtSymbol,   0,         Button3, setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,   0,         Button2, zoom,           {0} },
    { ClkStatusText, 0,         Button2, spawn,          {.v = termcmd } },
    { ClkClientWin,  MODKEY,    Button1, movemouse,      {0} },
    { ClkClientWin,  MODKEY,    Button2, togglefloating, {0} },
    { ClkClientWin,  MODKEY,    Button3, resizemouse,    {0} },
    { ClkTagBar,     0,         Button1, view,           {0} },
    { ClkTagBar,     0,         Button3, toggleview,     {0} },
    { ClkTagBar,     MODKEY,    Button1, tag,            {0} },
    { ClkTagBar,     MODKEY,    Button3, toggletag,      {0} },
};

